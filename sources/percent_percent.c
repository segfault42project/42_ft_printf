/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 03:40:46 by rabougue          #+#    #+#             */
/*   Updated: 2016/08/07 04:45:25 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	write_space_or_zero(t_printf *print, int len, int nb_char)
{
	while (len < nb_char--)
	{
		ft_putchar(' ');
		++print->ret;
	}
}

const char	*if_percent(const char *format, t_printf *printf)
{
	if (*format == '-')
	{
		format++;
		percent_percent_neg(format, printf);
		while (ft_isdigit(*format) == 1)
			format++;
	}
	else if (*format == '%')
	{
		ft_putchar('%');
		++printf->ret;
		return (format);
	}
	else
	{
		percent_percent(format, printf);
		while (ft_isdigit(*format) == 1)
			format++;
	}
	return (format);
}

const char	*percent_percent(const char *format, t_printf *printf)
{
	char	num[10];
	int		i;
	int		nb_char;
	int		len_format;

	i = 0;
	while (ft_isdigit(*format) == 1)
	{
		num[i] = *format;
		format++;
		i++;
	}
	num[i] = 'a';
	nb_char = ft_atoi(num);
	len_format = ft_strclen(format, '%') + 1;
	write_space_or_zero(printf, len_format, nb_char);
	if (format[0] != '-')
	{
		ft_putchar('%');
		++printf->ret;
	}
	return (format);
}

const char	*percent_percent_neg(const char *format, t_printf *printf)
{
	char	num[10];
	int		i;
	int		nb_char;
	int		len_format;

	i = 0;
	while (ft_isdigit(*format) == 1)
	{
		num[i] = *format;
		format++;
		i++;
	}
	num[i] = 'a';
	nb_char = ft_atoi(num);
	len_format = ft_strclen(format, '%') + 1;
	ft_putchar('%');
	printf->ret++;
	format++;
	while (len_format < nb_char--)
	{
		ft_putchar(' ');
		printf->ret++;
	}
	return (format);
}
