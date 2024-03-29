/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_c_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 01:32:24 by rabougue          #+#    #+#             */
/*   Updated: 2016/08/10 18:09:42 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	percent_c_up_2(t_printf *print, wint_t c)
{
	if (c < 65536)
	{
		ft_putchar(224 | (c >> 12));
		ft_putchar(128 | ((c >> 6) & 63));
		ft_putchar(128 | (c & 63));
		print->ret += 3;
	}
	else if (c < 1114112)
	{
		ft_putchar(240 | (c >> 18));
		ft_putchar(128 | ((c >> 12) & 63));
		ft_putchar(128 | ((c >> 6) & 63));
		ft_putchar(128 | (c & 63));
		print->ret += 4;
	}
}

void		percent_c_up(va_list pa, t_printf *print)
{
	wint_t	c;

	c = va_arg(pa, wint_t);
	if (c < 128)
	{
		ft_putchar(c);
		print->ret++;
	}
	else if (c < 2048)
	{
		ft_putchar(192 | (c >> 6));
		ft_putchar(128 | (c & 63));
		print->ret += 2;
	}
	else
		percent_c_up_2(print, c);
}
