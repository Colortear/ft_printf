/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int2str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 21:36:38 by wdebs             #+#    #+#             */
/*   Updated: 2017/01/14 17:13:53 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		find_size(uintmax_t integer, int num)
{
	int		i;

	i = 0;
	while (integer > 0)
	{
		integer = integer / num;
		i++;
	}
	return (i);
}

char	*itoa_base(uintmax_t integer, int num, int sign)
{
	char	*ret;

	if (integer == 9223372036854775808ull && sign != 0)
	{
		ret = ft_strnew(20);
		ret = "-9223372036854775808";
	}
	else if (integer == 0)
	{
		ret = ft_strnew(1);
		ret[0] = '0';
		return (ret);
	}
	else
		ret = itoa_ext(integer, num);
	return (ret);
}

char	*upcase(char *int_str)
{
	int		i;

	i = 0;
	while (int_str[i] != '\0')
	{
		if (int_str[i] >= 'a')
			int_str[i] = int_str[i] - 32;
		i++;
	}
	return (int_str);
}

char	*itoa_ext(uintmax_t integer, int num)
{
	int		size;
	char	*ret;
	char	*radix;

	size = find_size(integer, num);
	ret = ft_strnew(size);
	radix = "0123456789abcdef";
	while (size--)
	{
		ret[size] = radix[(integer % num)];
		integer = integer / num;
	}
	return (ret);
}
