/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 13:44:54 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/30 14:02:25 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	coord_push_back(int x, int y, t_coordinate **coords)
{
	t_coordinate	*list;
	t_coordinate	*oneelem;

	oneelem = NULL;
	list = *coords;
	if (!(oneelem = (t_coordinate *)malloc(sizeof(t_coordinate))))
		return ;
	oneelem->next = NULL;
	oneelem->x = x;
	oneelem->y = y;
	if (!(*coords))
	{
		*coords = oneelem;
		return ;
	}
	while ((*coords)->next)
		(*coords) = (*coords)->next;
	(*coords)->next = oneelem;
	*coords = list;
}

int		figure_size(t_params *params, int i)
{
	int j;
	int count;

	count = 0;
	while (i < (*params).x_figure)
	{
		j = 0;
		while (j < (*params).y_figure)
		{
			if ((*params).figure[i][j] == '*')
			{
				count++;
			}
			j++;
		}
		i++;
	}
	return (count);
}

void	board_making(char **buf, int fd, t_params *params)
{
	int i;
	int j;
	int k;

	i = 0;
	coords_parsing(&(params->x_board), &(params->y_board), *buf);
	ft_strdel(buf);
	two_dim_arr_mem(&((*params).board),
		(*params).x_board, (*params).y_board, '\0');
	get_next_line(fd, buf);
	ft_strdel(buf);
	while (i < (*params).x_board)
	{
		j = 0;
		k = (*params).diff;
		get_next_line(fd, buf);
		while (k < (*params).y_board + (*params).diff)
			(*params).board[i][j++] = (*buf)[k++];
		i++;
		ft_strdel(buf);
	}
}

int		figure_making(char **buf, int fd, t_params *params)
{
	int i;

	i = 0;
	coords_parsing(&params->x_figure, &params->y_figure, *buf);
	ft_strdel(buf);
	two_dim_arr_mem(&((*params).figure), (*params).x_figure,
		(*params).y_figure, '\0');
	while (i < (*params).x_figure)
	{
		get_next_line(fd, buf);
		(*params).figure[i] = ft_strcpy((*params).figure[i], *buf);
		i++;
		ft_strdel(buf);
	}
	if (save_coord(params) == -1)
	{
		ft_printf("%d %d\n", 0, 0);
		free_mem((*params).figure, (*params).x_figure);
		free_mem((*params).board, (*params).x_board);
		return (0);
	}
	free_mem((*params).figure, (*params).x_figure);
	free_mem((*params).board, (*params).x_board);
	return (1);
}

int		main(void)
{
	t_params	params;

	struct_initiation(&params);
	while (get_next_line(0, &params.buf) > 0)
	{
		if (ft_strstr(params.buf, "p2") && ft_strstr(params.buf, "vlikhotk"))
		{
			params.player_number = 'X';
			params.oppos_number = 'O';
			ft_strdel(&params.buf);
			continue ;
		}
		if (ft_strstr(params.buf, "Plateau"))
		{
			board_making(&(params.buf), 0, &params);
			continue ;
		}
		if (ft_strstr(params.buf, "Piece"))
		{
			if (!figure_making(&(params.buf), 0, &params))
				return (0);
			continue;
		}
		ft_strdel(&params.buf);
	}
}
