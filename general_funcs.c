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

void	struct_initiation(t_params *params)
{
	(*params).x_board = 0;
	(*params).y_board = 0;
	(*params).x_figure = 0;
	(*params).y_figure = 0;
	(*params).diff = 0;
	(*params).x_diff = -1;
	(*params).y_diff = -1;
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
	ft_strdel(&buf);
}
