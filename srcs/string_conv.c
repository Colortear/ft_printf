/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:33:26 by wdebs             #+#    #+#             */
/*   Updated: 2017/01/29 13:39:33 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	strings(va_list args, t_conv *options)
{
	char	*str;

	if (options->specifier == 's' || options->specifier == 'S')
	{
		if ((str = va_arg(args, char *)) != NULL || options->precision >= 0)
			str_conv(str, options);
		else
		{
			write(1, "(null)", 6);
			options->i = options->i - 1;
			options->c_count = options->c_count + 6;
		}
	}
}

void	str_conv(char *str, t_conv *options)
{
	int		len;
	int		spaces;

	spaces = 0;
	if (str != NULL)
		len = ft_strlen(str);
	else
		len = 0;
	if ((options->width > 0 && len > options->precision
			&& options->precision >= 0) || (options->width <= 0
			&& options->precision >= 0))
		len = options->precision;
	if (len < options->width)
		spaces = options->width - len;
	if (options->minus == 0 && spaces > 0 && options->zero == 0)
		print_things(' ', spaces, options);
	else if (options->minus == 0 && spaces > 0 && options->zero > 0)
		print_things('0', spaces, options);
	str_ext(options, str, len);
	if (options->minus > 0 && spaces > 0)
		print_things(' ', spaces, options);
	options->i = options->i - 1;
}

void	str_ext(t_conv *options, char *str, int len)
{
	int		i;

	i = 0;
	while (str != NULL && i < len && str[i] != '\0')
	{
		write(1, &str[i], 1);
		options->c_count = options->c_count + 1;
		i++;
	}
}
