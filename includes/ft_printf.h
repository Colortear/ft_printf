/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 20:07:25 by wdebs             #+#    #+#             */
/*   Updated: 2017/01/29 19:29:40 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

typedef struct	s_conv
{
	int			minus;
	int			plus;
	int			space;
	int			hash;
	int			zero;
	int			width;
	int			precision;
	int			length;
	int			specifier;
	int			i;
	int			c_count;
}				t_conv;

int				ft_printf(const char *format, ...);
void			ini_params(t_conv *options);
void			set_options(const char *format, t_conv *options, va_list args);
void			set_args(va_list args, t_conv *options, const char *format);
void			eval_args(va_list args, t_conv *options, const char *format);

void			specifier_check(char c, t_conv *options);
void			flags_check(const char *format, t_conv *options);
void			width_check(const char *format, t_conv *options);
void			precision_check(const char *format, t_conv *options);
int				length_check(const char *format, t_conv *options);

intmax_t		int_cast(va_list args, t_conv *options);
uintmax_t		int_castu(va_list args, t_conv *options);

void			add_count(intmax_t integer, t_conv *options);
void			apply_signs(intmax_t integer, t_conv *options);
void			width_math(t_conv *options, int len, intmax_t integer);
void			write_width(t_conv *options);
void			write_prec(t_conv *options);

void			characters(va_list args, t_conv *options);
void			char_conv(int c, t_conv *options);
void			mod_char(const char *format, t_conv *options);

int				find_size(uintmax_t integer, int num);
char			*itoa_base(uintmax_t integer, int num, int sign);
char			*upcase(char *int_str);
char			*itoa_ext(uintmax_t integer, int num);

void			ints(va_list args, t_conv *options);
void			int_conv(intmax_t integer, t_conv *options);
void			octal_conv(uintmax_t integer, t_conv *options);
void			hex_conv(uintmax_t integer, t_conv *options);
void			us_int_conv(uintmax_t integer, t_conv *options);

void			p_conv(va_list args, t_conv *options);
void			extra_int(t_conv *options, intmax_t integer,
							char *int_str, int len);
void			pwidth_math(t_conv *options, char *num);
void			set_n(va_list args, t_conv *options);

void			print_left(uintmax_t inte, t_conv *options, char *str);
void			print_z(uintmax_t inte, t_conv *options, char *str);
void			print_right(uintmax_t inte, t_conv *options, char *str);
void			print(char *str, t_conv *options, intmax_t integer);
void			print_things(char c, int len, t_conv *options);

void			strings(va_list args, t_conv *options);
void			str_conv(char *str, t_conv *options);
void			str_ext(t_conv *options, char *str, int len);

int				ft_atoi(const char *str);
char			*ft_itoa(intmax_t n);
size_t			ft_strlen(const char *s);
char			*ft_strnew(size_t size);
void			ft_bzero(void *s, size_t n);
char			*ft_strdup(const char *s1);

#endif
