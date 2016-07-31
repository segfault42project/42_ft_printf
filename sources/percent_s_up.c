#include "../includes/ft_printf.h"

int		count_octet_wchar(wchar_t *s, t_printf *print, int zero_plus_wchar)
{
	int	i;
	int	octet;

	i = 0;
	octet = 0;
	if (s != NULL)
	{
		while (s[i])
		{
			if (s[i] > 0 && s[i] < 128)
				octet++;
			else if (s[i] < 2048)
				octet+=2;
			else if (s[i] < 65536)
			{
				if (print->precision_space > 0)
					if (print->precision_space < octet)
					{
						++print->ret;
						print->precision_space -= 3;
						return (octet);
					}
				octet+=3;
			}
			else if (s[i] < 1114112)
				octet+=4;
				i++;
		}
	}
	return (octet);
}


void	percent_S_precision(t_printf *print, wchar_t *s, int zero_plus_wchar)
{
	int i;

	i= 0;
	/*while (print->precision_space-- > 0)*/
	/*{*/
		/*ft_putchar(' ');*/
		/*print->ret++;*/
	/*}*/
	if (print->negatif == 0)
	{
		print->ret_wchar = count_octet_wchar(s, print, zero_plus_wchar);
		write_space_wchar(print);
	}
	zero_plus_wchar = print->precision_zero + print->ret_wchar;
	if (s != NULL)
	{
		while (s[i])
		{
			if (s[i] > 0 && s[i] < 128)
			{
				print->ret_wchar++;
				if (print->precision_zero > 0)
					if (print->ret_wchar > zero_plus_wchar)
					{
						++print->ret;
						return ;
					}
				ft_putchar(s[i]);
			}
			else if (s[i] < 2048)
			{
				print->ret_wchar+=2;
				if (print->precision_zero > 0)
					if (print->ret_wchar > zero_plus_wchar)
					{
						print->ret += 2;
						return ;
					}
				ft_putchar(192 | (s[i] >> 6));
				ft_putchar(128 | (s[i] & 63));
			}
			else if (s[i] < 65536)
			{
				print->ret_wchar+=3;
				if (print->precision_zero > 0)
					if (print->ret_wchar > zero_plus_wchar)
					{
						print->ret+=3;
						return ;
					}
				ft_putchar(224 | (s[i] >> 12));
				ft_putchar(128 | ((s[i] >> 6) & 63));
				ft_putchar(128 | (s[i] & 63));
			}
			else if (s[i] < 1114112)
			{
				print->ret_wchar+=4;
				if (print->precision_zero > 0)
					if (print->ret_wchar > zero_plus_wchar)
					{
						print->ret+=4;
						return ;
					}
				ft_putchar(240 | (s[i] >> 18));
				ft_putchar(128 | ((s[i] >> 12) & 63));
				ft_putchar(128 | ((s[i] >> 6) & 63));
				ft_putchar(128 | (s[i] & 63));
			}
			i++;
		}
	}
	print->ret += count_octet_wchar(s, print, zero_plus_wchar);
}

void	percent_S_normal(t_printf *print, wchar_t *s, int zero_plus_wchar)
{
	int	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i])
		{
			if (s[i] > 0 && s[i] < 128)
			{
				print->ret_wchar++;
				ft_putchar(s[i]);
			}
			else if (s[i] < 2048)
			{
				print->ret_wchar+=2;
				ft_putchar(192 | (s[i] >> 6));
				ft_putchar(128 | (s[i] & 63));
			}
			else if (s[i] < 65536)
			{
				print->ret_wchar+=3;
				ft_putchar(224 | (s[i] >> 12));
				ft_putchar(128 | ((s[i] >> 6) & 63));
				ft_putchar(128 | (s[i] & 63));
			}
			else if (s[i] < 1114112)
			{
				print->ret_wchar+=4;
				ft_putchar(240 | (s[i] >> 18));
				ft_putchar(128 | ((s[i] >> 12) & 63));
				ft_putchar(128 | ((s[i] >> 6) & 63));
				ft_putchar(128 | (s[i] & 63));
			}
			i++;
		}
	}
	else
	{
		ft_putstr("(null)");
		print->ret += 6;
	}
	if (print->negatif == 1)
	{
		print->ret_wchar = count_octet_wchar(s, print, zero_plus_wchar);
		write_space_wchar(print);
		write_space_wchar(print);
	}
	print->ret += count_octet_wchar(s, print, zero_plus_wchar);
}

void	print_space(t_printf *print)
{
	while (print->precision_space-- > 0)
	{
		ft_putchar(' ');
		++print->ret;
	}
}

void	print_zero(t_printf *print)
{
	while (print->precision_space-- > 0)
	{
		ft_putchar('0');
		++print->ret;
	}
	while (print->space_number-- > 0)
	{
		ft_putchar('0');
		++print->ret;
	}
}

void	percent_S(va_list pa, t_printf *print)
{
	wchar_t			*s;
	int				i;
	int				zero_plus_wchar;
	int				cp_pre_space;

	i = 0;
	cp_pre_space = print->precision_space;
	s = va_arg(pa, wchar_t*);
	if (print->zero == 1)
	{
		print->space_number -= count_octet_wchar(s, print, zero_plus_wchar);
		print_zero(print);
	}
	if (print->precision_space > 0 || print->precision_zero > 0)
	{
		if (print->precision_space > 0 && print->precision_zero > 0)
		{
			print->precision_space -= count_octet_wchar(s, print, zero_plus_wchar);
			print->precision_space = cp_pre_space - 3;
			print_space(print);
			percent_S_precision(print, s, zero_plus_wchar);
		}
		else
		{
			print->precision_space -= count_octet_wchar(s, print, zero_plus_wchar);
			print_space(print);
			percent_S_precision(print, s, zero_plus_wchar);
		}
	}
	else
		percent_S_normal(print, s, zero_plus_wchar);
}

