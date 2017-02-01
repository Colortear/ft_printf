/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagsnwidth.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 09:22:43 by wdebs             #+#    #+#             */
/*   Updated: 2017/01/29 13:40:08 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	add_count(intmax_t integer, t_conv *options)
{
	if (options->zero > 0 && integer < 0)
		options->c_count++;
	if (options->space == 1 && options->plus != 1 && integer >= 0
			&& options->specifier != 'U' && options->specifier != 'u'
			&& options->specifier != 'o' && options->specifier != 'O'
			&& options->specifier != 'x' && options->specifier != 'X')
		options->c_count++;
	if (options->plus == 1 && integer >= 0 && (options->specifier == 'i' ||
				options->specifier == 'd' || options->specifier == 'D'))
		options->c_count++;
	if (options->hash > 0 && options->precision == 0
			&& (options->specifier == 'o' || options->specifier == 'O'))
		options->c_count++;
	if (options->hash > 0 && options->specifier == 'x')
		options->c_count = options->c_count + 2;
	if (options->hash > 0 && options->specifier == 'X')
		options->c_count = options->c_count + 2;
}

void	apply_signs(intmax_t integer, t_conv *options)
{
	if (options->zero > 0 && integer < 0)
		write(1, "-", 1);
	if (options->space == 1 && options->plus != 1 && integer >= 0
			&& options->specifier != 'U' && options->specifier != 'u'
			&& options->specifier != 'o' && options->specifier != 'O'
			&& options->specifier != 'x' && options->specifier != 'X')
		write(1, " ", 1);
	if (options->plus == 1 && integer >= 0 && (options->specifier == 'i' ||
				options->specifier == 'd' || options->specifier == 'D'))
		write(1, "+", 1);
	if (options->hash > 0 && options->precision <= 0
			&& (options->specifier == 'o' || options->specifier == 'O'))
		write(1, "0", 1);
	if (options->hash > 0 && options->specifier == 'x')
		write(1, "0x", 2);
	if (options->hash > 0 && options->specifier == 'X')
		write(1, "0X", 2);
	if (integer < 0 && options->precision >= 0 && options->zero == 0)
	{
		write(1, "-", 1);
		options->c_count++;
	}
	add_count(integer, options);
}

void	width_math(t_conv *options, int len, intmax_t integer)
{
	options->width = options->width - len;
	options->precision = options->precision - len;
	if (integer < 0 && options->precision >= 0)
	{
		options->precision = options->precision + 1;
		if (options->width < options->precision || options->zero != 0)
			options->width = options->width - 1;
	}
	if (options->plus > 0 && integer >= 0)
		options->width = options->width - 1;
	if (options->space > 0)
		options->width = options->width - 1;
	if (options->width > options->precision && options->precision > 0)
		options->width = options->width - options->precision;
	if (options->width < options->precision)
		options->width = 0;
	if (options->hash > 0 && (options->specifier == 'o'
			|| options->specifier == 'O'))
	{
		options->c_count = options->c_count + 1;
		options->width = options->width - 1;
	}
}

void	write_width(t_conv *options)
{
	if (options->hash > 0 && (options->specifier == 'x'
				|| options->specifier == 'X'))
		options->width = options->width - 2;
	if (options->zero == 1 && options->minus != 1 && options->precision <= 0)
		print_things('0', options->width, options);
	else
		print_things(' ', options->width, options);
}

void	write_prec(t_conv *options)
{
	int		i;

	i = 0;
	while (i < options->precision && options->precision > 0)
	{
		write(1, "0", 1);
		options->c_count++;
		i++;
	}
	if (options->hash > 0 && options->precision > 0 &&
			(options->specifier == 'o' || options->specifier == 'O'))
		options->c_count--;
}
