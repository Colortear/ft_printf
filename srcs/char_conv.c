/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:34:19 by wdebs             #+#    #+#             */
/*   Updated: 2016/12/12 00:45:10 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	characters(va_list args, t_conv *options)
{
	int		c;

	c = 0;
	if (options->specifier == 'c' || options->specifier == 'C')
	{
		c = va_arg(args, int);
		char_conv(c, options);
	}
}

void	char_conv(int c, t_conv *options)
{
	if (options->width > 0 && options->minus == 0)
	{
		if (options->zero == 0)
			print_things(' ', options->width - 1, options);
		else
			print_things('0', options->width - 1, options);
	}
	write(1, &c, 1);
	options->c_count++;
	if (options->width > 0 && options->minus > 0)
		print_things(' ', options->width - 1, options);
	options->i = options->i - 1;
}

void	mod_char(const char *format, t_conv *options)
{
	options->i = options->i - 1;
	if (options->minus == 0 && format[options->i] && options->zero == 0)
		print_things(' ', options->width - 1, options);
	else if (options->minus == 0 && format[options->i] && options->zero > 0)
		print_things('0', options->width - 1, options);
	write(1, &format[options->i], 1);
	options->c_count = options->c_count + 1;
	if (options->minus == 1)
		print_things(' ', options->width - 1, options);
}
