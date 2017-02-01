/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:30:43 by wdebs             #+#    #+#             */
/*   Updated: 2017/01/29 19:25:57 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	specifier_check(char c, t_conv *options)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' || c == 'i' ||
			c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x' || c == 'X'
			|| c == 'c' || c == 'C' || c == 'n')
		options->specifier = c;
}

void	flags_check(const char *format, t_conv *options)
{
	int		i;

	i = options->i;
	while (format[i] == '-' || format[i] == '+' || format[i] == '#' ||
			format[i] == '0' || format[i] == ' ')
	{
		if (format[i] == '-')
			options->minus = 1;
		if (format[i] == '+')
			options->plus = 1;
		if (format[i] == '#')
			options->hash = 1;
		if (format[i] == '0')
			options->zero = 1;
		if (format[i] == ' ')
			options->space = 1;
		i++;
	}
	options->i = i;
	specifier_check(format[i], options);
}

void	width_check(const char *format, t_conv *options)
{
	int		j;
	int		k;
	int		i;
	int		len;
	char	*nums;

	i = options->i;
	j = i;
	len = 0;
	k = 0;
	while (format[j] != '\0' && format[j] >= '0' && format[j] <= '9')
		j++;
	len = j - i;
	if ((nums = ft_strnew(len)) != NULL)
	{
		while (i < j)
			nums[k++] = format[i++];
		k = ft_atoi(nums);
		free(nums);
	}
	options->width = k;
	specifier_check(format[i], options);
	options->i = i;
}

void	precision_check(const char *format, t_conv *options)
{
	int		j;
	int		k;
	int		len;
	int		i;
	char	*nums;

	i = options->i;
	j = i;
	len = 0;
	k = 0;
	while (format[j] != '\0' && format[j] >= '0' && format[j] <= '9')
		j++;
	len = j - i;
	if ((nums = ft_strnew(len)) != NULL)
	{
		while (i < j)
			nums[k++] = format[i++];
		k = ft_atoi(nums);
		free(nums);
	}
	options->precision = k;
	specifier_check(format[i], options);
	options->i = i;
}

int		length_check(const char *format, t_conv *options)
{
	int		i;

	i = options->i;
	if (format[i] == 'h' && format[i + 1] == 'h')
		return ('i');
	else if (format[i] == 'h')
		return ('h');
	if (format[i] == 'l' && format[i + 1] == 'l')
		return ('m');
	else if (format[i] == 'l')
		return ('l');
	if (format[i] == 'j')
		return ('j');
	if (format[i] == 'z')
		return ('z');
	return (0);
}
