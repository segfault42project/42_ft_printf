/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 05:00:42 by rabougue          #+#    #+#             */
/*   Updated: 2016/08/07 08:54:10 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		precision_space_x(t_printf *print, int x)
{
	print->space_number -= ft_strlen(ft_hexa_itoa(x, 0));
	while (print->space_number-- > 0)
	{
		ft_putchar(' ');
		++print->ret;
	}
}

const char	*percent_x(va_list pa, t_printf *print, const char *format)
{
	int		x;
	char	num[10];

	if (print->sharp == 1 && print->zero == 1 && print->negatif == 1)
	{
		ft_putchar('0');
		if (*format == 'x')
			ft_putchar('x');
		else if (*format == 'X')
			ft_putchar('X');
		print->ret += 2;
		print->space_number -= 2;
	}
	x = va_arg(pa, int);
	if (print->precision_zero <= 0 && print->precision_space <= 0
	&& print->sharp == 1 && print->point == 1)
		return (format);
	if (print->precision_zero <= 0 || print->precision_space <= 0)
		write_space_hex(x, print);
	if (print->precision_zero > 0 || print->precision_space > 0)
		put_space_or_zero_x(print, x);
	if (print->sharp == 1 && x != 0 && print->zero == 0)
	{
		ft_putchar('0');
		if (*format == 'x')
			ft_putchar('x');
		else if (*format == 'X')
			ft_putchar('X');
		print->ret += 2;
	}
	if (print->d == 1 && print->point == 1)
		ft_putchar(' ');
	else if (*format == 'x')
		ft_putstr(ft_hexa_itoa(x, 0));
	else if (*format == 'X')
		ft_putstr(ft_hexa_itoa(x, 1));
	if (print->precision_zero > 0 || print->precision_space > 0)
		write_space_hex(x, print);
	if (print->negatif_x == 1)
		precision_space_x(print, x);
	if (print->negatif == 1)
		precision_space_x(print, x);
	print->ret += ft_strlen(ft_hexa_itoa(x, 0));
	return (format);
}
