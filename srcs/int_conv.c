/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:08:25 by wdebs             #+#    #+#             */
/*   Updated: 2017/01/29 19:26:11 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ints(va_list args, t_conv *options)
{
	intmax_t	integers;
	uintmax_t	integeru;

	integers = 0;
	integeru = 0;
	if (options->specifier == 'i' || options->specifier == 'd' ||
			options->specifier == 'D')
		integers = int_cast(args, options);
	else
		integeru = int_castu(args, options);
	if (options->specifier == 'd' || options->specifier == 'i' ||
			options->specifier == 'D')
		int_conv(integers, options);
	if (options->specifier == 'o' || options->specifier == 'O')
		octal_conv(integeru, options);
	if (options->specifier == 'x' || options->specifier == 'X')
		hex_conv(integeru, options);
	if (options->specifier == 'u' || options->specifier == 'U')
		us_int_conv(integeru, options);
}

void	int_conv(intmax_t integer, t_conv *options)
{
	char		*int_str;
	int			len;
	uintmax_t	hold;

	if ((hold = (uintmax_t)integer) && hold == -9223372036854775808ull)
	{
		len = find_size(hold, 10);
		int_str = itoa_base(hold, 10, 1);
	}
	else
	{
		int_str = ft_itoa(integer);
		len = ft_strlen(int_str);
	}
	if (options->precision == 0 && integer == 0)
		write_width(options);
	else
		extra_int(options, integer, int_str, len);
	options->i = options->i - 1;
}

void	octal_conv(uintmax_t integeru, t_conv *options)
{
	char	*int_str;
	int		len;

	int_str = itoa_base(integeru, 8, 0);
	if (integeru != 0)
	{
		len = ft_strlen(int_str);
		width_math(options, len, integeru);
		if (options->minus == 0 && options->zero == 0)
			print_left(0, options, int_str);
		else if (options->minus == 0 && options->zero > 0
				&& options->precision <= 0)
			print_z(0, options, int_str);
		else if (options->minus > 0)
			print_right(0, options, int_str);
	}
	else if (options->precision < 0 || (integeru == 0 && options->hash > 0))
		print_things('0', 1, options);
	else
		write_width(options);
	options->i = options->i - 1;
}

void	hex_conv(uintmax_t integeru, t_conv *options)
{
	char	*int_str;
	int		len;

	int_str = itoa_base(integeru, 16, 0);
	if (integeru != 0)
	{
		if (options->specifier == 'X')
			int_str = upcase(int_str);
		len = ft_strlen(int_str);
		width_math(options, len, integeru);
		if (options->minus == 0 && options->zero == 0)
			print_left(0, options, int_str);
		else if (options->minus == 0 && options->zero > 0
				&& options->precision <= 0)
			print_z(0, options, int_str);
		else if (options->minus > 0)
			print_right(0, options, int_str);
	}
	else if (options->precision < 0)
		print_things('0', 1, options);
	else
		write_width(options);
	options->i = options->i - 1;
}

void	us_int_conv(uintmax_t integer, t_conv *options)
{
	char	*int_str;
	int		len;

	int_str = itoa_base(integer, 10, 0);
	len = ft_strlen(int_str);
	if (options->precision == 0 && integer == 0)
		write_width(options);
	else
	{
		width_math(options, len, integer);
		if (options->minus == 0 && options->zero == 0)
			print_left(0, options, int_str);
		else if (options->minus == 0 && options->zero > 0
				&& options->precision <= 0)
			print_z(0, options, int_str);
		else if (options->minus > 0)
			print_right(0, options, int_str);
	}
	options->i = options->i - 1;
}
