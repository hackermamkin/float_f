/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:31:21 by pstein            #+#    #+#             */
/*   Updated: 2019/10/22 14:21:17 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*round_after(char *str, int add)
{
	int i;
	int inc;

	i = ft_strlen(str) - 1;
	inc = 0;
	if (str[i] >= '5')
		inc = 1;
	i--;
	while (i >= 0)
	{
		if (i == 0 && str[i] == '9')
			add = 1;
		if (inc && str[i] == '9')
			str[i] = '0';
		else if (inc)
		{
			str[i] += 1;
			inc = 0;
		}
		i--;
	}
	str[ft_strlen(str) - 1] = 0;
	return (str);
}

static char		*round_before(char *str, int add, int neg)
{
	int		i;
	int		is_neg;
	char	*new;

	is_neg = (str[0] == '-' ? 1 : 0);
	i = ft_strlen(str) - 1;
	while (i >= is_neg && i--)
	{
		if (i == is_neg && str[i] == '9' && add && (str[is_neg] = '0'))
		{
			if (!(new = ft_strdup("1")))
			{
				free(str);
				return (NULL);
			}
			str = ft_sets1_inside(new, str, is_neg);
		}
		else if (add && str[i] == '9')
			str[i] = '0';
		else if (add && (add = 0))
			str[i] += 1;
	}
	if (neg && str[0] != '-')
		str = ft_strplus("-", str, 0, 1);
	return (str);
}

static char		*render_before(long double nb, int add)
{
	char		*str;
	int			is_neg;

	is_neg = (nb < 0 ? 1 : 0);
	if ((str = ft_itoa_base(nb, 10, 'a')) == NULL)
		return (NULL);
	str = round_before(str, add, is_neg);
	return (str);
}

static char		*render_after(long double nb, int precision, int add)
{
	char		*ret;
	intmax_t	temp;
	int			i;

	if (!precision)
		return (ft_strdup(""));
	nb = nb - (intmax_t)nb;
	i = 0;
	if ((ret = ft_strnew(precision + 1)) == NULL)
		return (NULL);
	while (precision-- + 1)
	{
		temp = (intmax_t)(nb * 10);
		ret[i] = temp + '0';
		nb = nb * 10 - temp;
		i++;
	}
	ret = round_after(ret, add);
	return (ft_strplus(".", ret, 0, 1));
}

char			*render_double(va_list *va, t_flags *flags)
{
	long double	nb;
	char		*before;
	char		*after;
	int			add;

	add = 0;
	if (flags->type == L)
		nb = va_arg(*va, long double);
	else
		nb = (long double)va_arg(*va, double);
	if (flags->precision == -1)
		flags->precision = 6;
	if (!(after = render_after(nb >= 0 ? nb : -nb, flags->precision,
		add)))
		return (NULL);
	if (((intmax_t)(nb * 10) % 10 >= 5 || (intmax_t)(nb * 10) % 10 <= -5)
		&& flags->precision == 0)
		add = 1;
	if (!(before = render_before(nb, add)))
	{
		if (after)
			free(after);
		return (NULL);
	}
	return (ft_strplus(before, after, 1, 1));
}
