/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:26:17 by pstein            #+#    #+#             */
/*   Updated: 2019/10/22 12:56:27 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) && (s1[i] != '\0') && (s2[i] != '\0') && (s1[i] == s2[i]))
		i++;
	if (n == i)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		init_color(char **str, int color, int len)
{
	while (len-- > 0)
		(*str)++;
	if (color == 1)
		return ((ft_putstr(RED)));
	else if (color == 2)
		return ((ft_putstr(GREEN)));
	else if (color == 3)
		return ((ft_putstr(YELLOW)));
	else if (color == 4)
		return ((ft_putstr(BLUE)));
	else if (color == 5)
		return ((ft_putstr(MAGENTA)));
	else if (color == 6)
		return ((ft_putstr(CYAN)));
	else if (color == 7)
		return ((ft_putstr(WHITE)));
	else if (color == 0)
		return ((ft_putstr(RESET)));
	return (0);
}

int		color_check(char **str, char buff[4096], int *buff_i)
{
	if (**str == '{')
	{
		if (ft_strncmp(*str, "{red}", 5) == 0)
			return (print_buff(buff, buff_i) + init_color(str, 1, 5));
		else if (ft_strncmp(*str, "{green}", 7) == 0)
			return (print_buff(buff, buff_i) + init_color(str, 2, 7));
		else if (ft_strncmp(*str, "{yellow}", 8) == 0)
			return (print_buff(buff, buff_i) + init_color(str, 3, 8));
		else if (ft_strncmp(*str, "{blue}", 6) == 0)
			return (print_buff(buff, buff_i) + init_color(str, 4, 6));
		else if (ft_strncmp(*str, "{magenta}", 9) == 0)
			return (print_buff(buff, buff_i) + init_color(str, 5, 9));
		else if (ft_strncmp(*str, "{cyan}", 6) == 0)
			return (print_buff(buff, buff_i) + init_color(str, 6, 6));
		else if (ft_strncmp(*str, "{white}", 7) == 0)
			return (print_buff(buff, buff_i) + init_color(str, 7, 7));
		else if (ft_strncmp(*str, "{eoc}", 5) == 0)
			return (print_buff(buff, buff_i) + init_color(str, 0, 5));
	}
	return (0);
}
