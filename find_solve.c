/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 19:14:03 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/31 12:24:57 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	count_prime_coords(t_coordinate *coords, t_iter *iters)
{
	(*iters).m = (((*coords).x - (*iters).k) >= 0) ? ((*coords).x - (*iters).k)
		: (-1 * ((*coords).x - (*iters).k));
	(*iters).n = (((*coords).y - (*iters).l) >= 0) ? ((*coords).y - (*iters).l)
		: (-1 * ((*coords).y - (*iters).l));
	(*iters).res1 = (*iters).m + (*iters).n;
	if ((*iters).res == -1 || ((*iters).res != -1 &&
		(*iters).res1 < (*iters).res))
	{
		(*iters).res = (*iters).res1;
		(*iters).x = (*coords).x;
		(*iters).y = (*coords).y;
	}
}

void	choose_prime_position1(t_coordinate *coords, t_params *params)
{
	t_iter			iters;
	t_coordinate	*list;

	list = coords;
	iters_initiation(&iters);
	while (iters.k < (*params).x_board)
	{
		iters.l = 0;
		while (iters.l < (*params).y_board)
		{
			if (((*params).board[iters.k][iters.l] == (*params).oppos_number
			|| (*params).board[iters.k][iters.l] == (*params).oppos_number + 32)
		|| (iters.k == 0 ||
		iters.k == (*params).x_board - 1 || iters.l == 0 || iters.l == (*params).y_board - 1))
			{
				coords = list;
				while (coords)
				{
					count_prime_coords(coords, &iters);
					coords = coords->next;
				}
			}
			iters.l++;
		}
		iters.k++;
	}
	ft_printf("%d %d\n", iters.x, iters.y);
}

void	choose_prime_position2(t_coordinate *coords, t_params *params)
{
	t_iter			iters;
	t_coordinate	*list;

	list = coords;
	iters_initiation(&iters);
	while (iters.k < (*params).x_board)
	{
		iters.l = 0;
		while (iters.l < (*params).y_board)
		{
			if ((iters.k == 0 ||
			iters.k == (*params).x_board - 1 || iters.l == 0 || iters.l == (*params).y_board - 1) ||
			((*params).board[iters.k][iters.l] == (*params).oppos_number
			|| (*params).board[iters.k][iters.l] == (*params).oppos_number + 32))
			{
				coords = list;
				while (coords)
				{
					count_prime_coords(coords, &iters);
					coords = coords->next;
				}
			}
			iters.l++;
		}
		iters.k++;
	}
	ft_printf("%d %d\n", iters.x, iters.y);
}

void	check_symbs(char board, t_params *params, int *x, int *y)
{
	if (board == (*params).player_number ||
		board == (*params).player_number + 32)
		(*x)++;
	if (board == (*params).oppos_number ||
		board == (*params).oppos_number + 32)
		(*y)++;
}

int		check_in_field(int i, int j, int count, t_params *params)
{
	t_iter iters;

	iters_initiation(&iters);
	iters.m = j;
	while (iters.k < (*params).x_figure && i < (*params).x_board && count >= 0)
	{
		j = iters.m;
		iters.l = 0;
		while (iters.l < (*params).y_figure && j < (*params).y_board
		&& count >= 0)
		{
			if ((*params).figure[iters.k][iters.l++] == '*')
			{
				check_symbs((*params).board[i][j], params, &iters.x, &iters.y);
				count--;
			}
			j++;
		}
		iters.k++;
		i++;
	}
	if (count == 0 && iters.x == 1 && iters.y == 0)
		return (1);
	return (0);
}

int		save_coord(t_params *params)
{
	t_iter			iters;
	int				count;
	t_coordinate	*coords;

	iters_initiation(&iters);
	count = figure_size(params, iters.k);
	coords = NULL;
	while (iters.k < (*params).x_board)
	{
		iters.l = 0;
		while (iters.l < (*params).y_board)
		{
			if (check_in_field(iters.k, iters.l, count, params) == 1)
				coord_push_back(iters.k, iters.l, &coords);
			iters.l++;
		}
		iters.k++;
	}
	if (coords)
	{
		/*if ((*params).player_number == 'X' && (*params).x_board > 20)
			choose_prime_position2(coords, params);
		else*/
			choose_prime_position1(coords, params);
		free_list(&coords);
		return (1);
	}
	return (-1);
}
