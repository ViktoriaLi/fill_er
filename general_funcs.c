/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 13:41:29 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/30 13:42:24 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	iters_initiation(t_iter *iters)
{
	(*iters).x = 0;
	(*iters).y = 0;
	(*iters).k = 0;
	(*iters).l = 0;
	(*iters).m = 0;
	(*iters).n = 0;
	(*iters).res = -1;
	(*iters).res1 = 0;
}

void	struct_initiation(t_params *params)
{
	(*params).x_board = 0;
	(*params).y_board = 0;
	(*params).x_figure = 0;
	(*params).y_figure = 0;
	(*params).diff = 4;
	(*params).buf = NULL;
	(*params).board = NULL;
	(*params).figure = NULL;
	(*params).player_number = 'O';
	(*params).oppos_number = 'X';
}

void	coords_parsing(int *x, int *y, char *buf)
{
	int i;

	i = 0;
	while (buf[i] != ' ')
		i++;
	*x = ft_atoi(&buf[++i]);
	while (buf[i] != ' ')
		i++;
	*y = ft_atoi(&buf[++i]);
}

void	free_list(t_coordinate **list)
{
	if (list && *list)
	{
		while (*list)
		{
			free(*list);
			*list = (*list)->next;
		}
		*list = NULL;
	}
}
