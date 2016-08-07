/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_space_or_zero.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 03:07:15 by rabougue          #+#    #+#             */
/*   Updated: 2016/08/07 18:56:59 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	loop_space_no_ret(t_printf *print)
{
	while (print->precision_space-- > 0)
		ft_putchar(' ');
}

void	loop_space(t_printf *print)
{
	while (print->precision_space-- > 0)
	{
		ft_putchar(' ');
		++print->ret;
	}
}

void	loop_zero(t_printf *print)
{
	while (print->precision_zero-- > 0)
	{
		ft_putchar('0');
		++print->ret;
	}
}
