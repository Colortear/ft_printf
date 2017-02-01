/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 14:57:02 by wdebs             #+#    #+#             */
/*   Updated: 2017/01/29 19:30:12 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	int_cast(va_list args, t_conv *options)
{
	intmax_t	integer;

	integer = 0;
	if (options->specifier == 'D')
		options->length = -1;
	if (options->length == 'i')
		integer = (va_arg(args, signed char));
	if (options->length == 'h')
		integer = (va_arg(args, short int));
	if (options->length == 'l')
		integer = (va_arg(args, long));
	if (options->length == 'm')
		integer = (va_arg(args, long long));
	if (options->length == 'j' || options->specifier == 'D')
		integer = va_arg(args, intmax_t);
	if (options->length == 'z')
		integer = (va_arg(args, size_t));
	if (options->length == 0)
		integer = (va_arg(args, int));
	return (integer);
}

uintmax_t	int_castu(va_list args, t_conv *options)
{
	uintmax_t	integer;

	integer = 0;
	if (options->specifier == 'U' || options->specifier == 'O')
		options->length = -1;
	if (options->length == 'i')
		integer = (va_arg(args, unsigned char));
	if (options->length == 'h')
		integer = (va_arg(args, unsigned short int));
	if (options->length == 'l')
		integer = (va_arg(args, unsigned long int));
	if (options->length == 'm')
		integer = (va_arg(args, unsigned long long int));
	if (options->length == 'j' || options->specifier == 'U'
			|| options->specifier == 'O')
		integer = va_arg(args, uintmax_t);
	if (options->length == 'z')
		integer = (va_arg(args, size_t));
	if (options->length == 0)
		integer = (va_arg(args, unsigned int));
	return (integer);
}
