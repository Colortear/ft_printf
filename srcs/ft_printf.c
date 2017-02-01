/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:08:02 by wdebs             #+#    #+#             */
/*   Updated: 2017/01/29 19:37:00 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ini_params(t_conv *options)
{
	options->minus = 0;
	options->plus = 0;
	options->hash = 0;
	options->zero = 0;
	options->space = 0;
	options->width = 0;
	options->precision = 0;
	options->length = 0;
	options->specifier = 0;
}

void	set_options(const char *format, t_conv *options, va_list args)
{
	int		opt;

	flags_check(format, options);
	if (options->specifier == 0 && format[options->i] == '*' && options->i++)
		options->width = va_arg(args, int);
	else if (options->specifier == 0)
		width_check(format, options);
	if (options->specifier == 0 && format[options->i] == '.')
	{
		options->i = options->i + 1;
		precision_check(format, options);
	}
	else
		options->precision = -1;
	if (options->specifier == 0 && (opt = length_check(format, options)) != 0)
	{
		options->length = opt;
		options->i = options->i + 1;
		if (options->length == 'm' || options->length == 'i')
			options->i = options->i + 1;
	}
	if (options->specifier == 0)
		specifier_check(format[options->i], options);
	options->i = options->i + 1;
}

void	set_args(va_list args, t_conv *options, const char *format)
{
	int		s;

	s = options->specifier;
	if (s == 0)
		mod_char(format, options);
	if (s == 'n')
		set_n(args, options);
	if (s == 'S' || s == 's')
		strings(args, options);
	if (s == 'c' || s == 'C')
		characters(args, options);
	if (s == 'p')
		p_conv(args, options);
	if (s == 'd' || s == 'i' || s == 'o' || s == 'x' || s == 'X' ||
			s == 'u' || s == 'D' || s == 'O' || s == 'U')
		ints(args, options);
}

void	eval_args(va_list args, t_conv *options, const char *format)
{
	if (format[options->i] == '%' && format[options->i + 1] == '%')
	{
		write(1, "%", 1);
		options->c_count = options->c_count + 1;
		options->i = options->i + 2;
	}
	else if (format[options->i] == '%' && format[options->i + 1] == '\0')
		options->i++;
	else if (format[options->i] == '%' && format[options->i + 1] != '%')
	{
		options->i = options->i + 1;
		ini_params(options);
		set_options(format, options, args);
		set_args(args, options, format);
		options->i = options->i + 1;
	}
	else
	{
		write(1, &format[options->i], 1);
		options->c_count++;
		options->i = options->i + 1;
	}
}

int		ft_printf(const char *format, ...)
{
	va_list	args;
	t_conv	*options;

	options = (t_conv *)malloc(sizeof(t_conv));
	va_start(args, format);
	options->c_count = 0;
	options->i = 0;
	while (format[options->i] != '\0')
		eval_args(args, options, format);
	va_end(args);
	free(options);
	return (options->c_count);
}
