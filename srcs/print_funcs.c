/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 17:27:53 by wdebs             #+#    #+#             */
/*   Updated: 2016/12/12 00:59:13 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_left(uintmax_t inte, t_conv *options, char *str)
{
	write_width(options);
	apply_signs(inte, options);
	write_prec(options);
	print(str, options, inte);
}

void	print_z(uintmax_t inte, t_conv *options, char *str)
{
	apply_signs(inte, options);
	write_width(options);
	if (options->precision > 0)
		write_prec(options);
	print(str, options, inte);
}

void	print_right(uintmax_t inte, t_conv *options, char *str)
{
	apply_signs(inte, options);
	write_prec(options);
	print(str, options, inte);
	write_width(options);
}

void	print(char *str, t_conv *options, intmax_t integer)
{
	int		i;

	i = 0;
	if (integer < 0 && (options->zero > 0 || options->precision >= 0)
			&& (options->specifier == 'd' || options->specifier == 'D'
				|| options->specifier == 'i'))
		i++;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
		options->c_count++;
	}
}

void	print_things(char c, int len, t_conv *options)
{
	int		i;

	i = 0;
	if (options->specifier == 'p' && options->minus == 0 && options->zero > 0)
		c = '0';
	while (len > 0 && i < len)
	{
		write(1, &c, 1);
		i++;
		options->c_count++;
	}
}
