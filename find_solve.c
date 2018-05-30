/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 19:14:03 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/30 19:19:49 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	choose_prime_position(t_coordinate *coords, t_params *params)
{
	int				i;
	int				j;
	int				x;
	int				y;
	int				res;
	int				res1;
	int				tmp1;
	int				tmp2;
	t_coordinate	*list;

	list = coords;
	res = -1;
	i = 0;
	while (i < (*params).x_board)
	{
		j = 0;
		while (j < (*params).y_board)
		{
			if ((*params).board[i][j] == (*params).oppos_number
			|| (*params).board[i][j] == (*params).oppos_number + 32)
			{
				coords = list;
				while (coords)
				{
					tmp1 = (((*coords).x - i) >= 0) ? ((*coords).x - i) :
						(-1 * ((*coords).x - i));
					tmp2 = (((*coords).y - j) >= 0) ? ((*coords).y - j) :
						(-1 * ((*coords).y - j));
					res1 = tmp1 + tmp2;
					if (res == -1 || (res != -1 && res1 < res))
					{
						res = res1;
						x = (*coords).x;
						y = (*coords).y;
					}
					coords = coords->next;
				}
			}
			j++;
		}
		i++;
	}
	ft_printf("%d %d\n", x, y);
	while (list)
	{
		coords = list->next;
		free(list);
		list = coords;
	}
}

int		check_in_field(int i, int j, int count, t_params *params)
{
	int jj;
	int my;
	int opos;
	int k;
	int l;

	my = 0;
	opos = 0;
	jj = j;
	k = 0;
	while (k < (*params).x_figure && i < (*params).x_board && count >= 0)
	{
		j = jj;
		l = 0;
		while (l < (*params).y_figure && j < (*params).y_board && count >= 0)
		{
			if ((*params).figure[k][l] == '*')
			{
				if ((*params).board[i][j] == (*params).player_number ||
					(*params).board[i][j] == (*params).player_number + 32)
					my++;
				if ((*params).board[i][j] == (*params).oppos_number ||
					(*params).board[i][j] == (*params).oppos_number + 32)
					opos++;
				count--;
			}
			l++;
			j++;
		}
		k++;
		i++;
	}
	if (count == 0 && my == 1 && opos == 0)
		return (1);
	return (0);
}

int		save_coord(t_params *params)
{
	int				i;
	int				j;
	int				count;
	t_coordinate	*coords;

	i = 0;
	count = figure_size(params, i);
	coords = NULL;
	while (i < (*params).x_board)
	{
		j = 0;
		while (j < (*params).y_board)
		{
			if (check_in_field(i, j, count, params) == 1)
				coord_push_back(i, j, &coords);
			j++;
		}
		i++;
	}
	if (coords)
	{
		choose_prime_position(coords, params);
		return (1);
	}
	return (-1);
}
