/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:41:49 by wdebs             #+#    #+#             */
/*   Updated: 2016/12/12 16:59:48 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	p_conv(va_list args, t_conv *options)
{
	void		*p;
	uintmax_t	q;
	char		*num;
	int			zero;

	zero = 0;
	p = va_arg(args, void *);
	q = (uintmax_t)p;
	options->c_count = options->c_count + 2;
	num = itoa_base(q, 16, 0);
	if (options->precision == 0 && q == 0)
		zero = 1;
	pwidth_math(options, num);
	if (options->minus == 0 && options->zero == 0
			&& options->width > options->precision)
		print_things(' ', options->width, options);
	write(1, "0x", 2);
	if (options->precision > options->width)
		print_things('0', options->precision, options);
	if (zero == 0)
		print(num, options, 0);
	if (options->minus > 0 || options->zero > 0)
		print_things(' ', options->width, options);
	options->i = options->i - 1;
}

void	extra_int(t_conv *options, intmax_t integer, char *int_str, int len)
{
	width_math(options, len, integer);
	if (options->minus == 0 && options->zero == 0)
		print_left(integer, options, int_str);
	else if (options->minus == 0 && options->zero > 0
			&& options->precision <= 0)
		print_z(integer, options, int_str);
	else if (options->minus == 0 && options->precision >= 0)
		print_z(integer, options, int_str);
	else if (options->minus > 0)
		print_right(integer, options, int_str);
}

void	pwidth_math(t_conv *options, char *num)
{
	int	len;

	len = ft_strlen(num);
	if (options->width > options->precision)
	{
		options->width = options->width - 2;
		options->precision = -1;
	}
	if (options->precision >= len)
		options->precision = options->precision - len;
	if (options->width > len && options->width > (len + options->precision)
			&& options->precision >= 0)
		options->width = options->width - (options->precision + len);
	else
		options->width = options->width - len;
}

void	set_n(va_list args, t_conv *options)
{
	signed int	num;

	num = va_arg(args, signed int);
	num = options->c_count;
	options->i--;
}
