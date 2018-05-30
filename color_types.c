/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 15:28:41 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/30 15:36:28 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	color_fin_display(char *buf, int fd)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	tmp = buf;
	i = 0;
	while (tmp[i] != ':')
		i++;
	j = ft_atoi(&tmp[++i]);
	get_next_line(fd, &buf);
	i = 0;
	while (tmp[i] != ':')
		i++;
	k = ft_atoi(&buf[++i]);
	ft_printf("%s%c%s", "\x1b[1;47m\x1b[?25l", '\n', "\x1b[0m");
	j > k ? ft_printf("%s%s%s\n",
		"\x1b[1;32m\x1b[1;47m\x1b[?25l", tmp, "\x1b[0m") :
	ft_printf("%s%s%s\n", "\x1b[1;31m\x1b[1;47m\x1b[?25l", tmp, "\x1b[0m");
	k > j ? ft_printf("%s%s%s\n",
		"\x1b[1;32m\x1b[1;47m\x1b[?25h", buf, "\x1b[0m") :
	ft_printf("%s%s%s\n", "\x1b[1;31m\x1b[1;47m\x1b[?25h", buf, "\x1b[0m");
	ft_strdel(&buf);
	ft_strdel(&tmp);
}

void	black_fin_display(char *buf, int fd, int argc)
{
	char	*tmp;

	tmp = buf;
	if (argc > 1)
	{
		color_fin_display(buf, 0);
		return ;
	}
	get_next_line(fd, &buf);
	ft_printf("%s%s%s\n", "\x1b[?25l", tmp, "\x1b[0m");
	ft_printf("%s%s%s\n", "\x1b[?25h", buf, "\x1b[0m");
	ft_printf("\n%s\n", "Use vizualizer with [symb | square] flags next time!");
	ft_strdel(&buf);
	ft_strdel(&tmp);
}

void	square_board_print(t_params *params, char *buf)
{
	int k;

	k = (*params).diff;
	while (k < (*params).y_board + (*params).diff)
	{
		if (buf[k] == (*params).player_number)
			ft_printf("%s%c %s",
			"\x1b[1;35m\x1b[1;45m\x1b[?25l", buf[k], "\x1b[0m");
		else if (buf[k] == (*params).player_number + 32)
			ft_printf("%s%c %s",
			"\x1b[2;35m\x1b[2;45m\x1b[?25l", buf[k], "\x1b[0m");
		else if (buf[k] == (*params).oppos_number)
			ft_printf("%s%c %s",
			"\x1b[1;34m\x1b[1;44m\x1b[?25l", buf[k], "\x1b[0m");
		else if (buf[k] == (*params).oppos_number + 32)
			ft_printf("%s%c %s",
			"\x1b[2;34m\x1b[2;44m\x1b[?25l", buf[k], "\x1b[0m");
		else
			ft_printf("%s%c %s",
			"\x1b[1;33m\x1b[1;43m\x1b[?25l", buf[k], "\x1b[0m");
		k++;
	}
	ft_printf("%s%c%s", "\x1b[1;47m\x1b[?25l", '\n', "\x1b[0m");
}

void	symb_board_print(t_params *params, char *buf)
{
	int k;

	k = (*params).diff;
	while (k < (*params).y_board + (*params).diff)
	{
		if (buf[k] == (*params).player_number)
			ft_printf("%s%c %s",
			"\x1b[1;35m\x1b[1;47m\x1b[?25l", buf[k], "\x1b[0m");
		else if (buf[k] == (*params).player_number + 32)
			ft_printf("%s%c %s",
			"\x1b[2;35m\x1b[2;47m\x1b[?25l", buf[k], "\x1b[0m");
		else if (buf[k] == (*params).oppos_number)
			ft_printf("%s%c %s",
			"\x1b[1;34m\x1b[1;47m\x1b[?25l", buf[k], "\x1b[0m");
		else if (buf[k] == (*params).oppos_number + 32)
			ft_printf("%s%c %s",
			"\x1b[2;34m\x1b[2;47m\x1b[?25l", buf[k], "\x1b[0m");
		else
			ft_printf("%s%c %s",
			"\x1b[1;33m\x1b[1;47m\x1b[?25l", buf[k], "\x1b[0m");
		k++;
	}
	ft_printf("%s%c%s", "\x1b[1;47m\x1b[?25l", '\n', "\x1b[0m");
}

void	black_board_print(t_params *params, char *buf)
{
	int k;

	k = (*params).diff;
	while (k < (*params).y_board + (*params).diff)
	{
		if (buf[k] == (*params).player_number)
			ft_printf("%s%c %s", "\x1b[?25l", buf[k], "\x1b[0m");
		else if (buf[k] == (*params).player_number + 32)
			ft_printf("%s%c %s", "\x1b[?25l", buf[k], "\x1b[0m");
		else if (buf[k] == (*params).oppos_number)
			ft_printf("%s%c %s", "\x1b[?25l", buf[k], "\x1b[0m");
		else if (buf[k] == (*params).oppos_number + 32)
			ft_printf("%s%c %s", "\x1b[?25l", buf[k], "\x1b[0m");
		else
			ft_printf("%s%c %s", "\x1b[?25l", buf[k], "\x1b[0m");
		k++;
	}
	ft_printf("%s%c%s", "\x1b[1;47m\x1b[?25l", '\n', "\x1b[0m");
}
