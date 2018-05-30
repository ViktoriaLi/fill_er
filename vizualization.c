/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizualization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 14:22:02 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/30 14:26:07 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	board_display(t_params *params, int fd, char **argv, int argc)
{
	int				i;
	struct timespec tw;
	struct timespec tr;

	i = 0;
	tw.tv_sec = 0;
	tw.tv_nsec = 100000000;
	system("clear");
	if ((*params).x_board > 100)
		(*params).diff = 5;
	get_next_line(fd, &params->buf);
	ft_strdel(&params->buf);
	while (i++ < (*params).x_board)
	{
		get_next_line(fd, &params->buf);
		if (argc > 1 && ft_strcmp(argv[1], "square") == 0)
			square_board_print(params, (*params).buf);
		else if (argc > 1 && ft_strcmp(argv[1], "symb") == 0)
			symb_board_print(params, (*params).buf);
		else
			black_board_print(params, (*params).buf);
		ft_strdel(&params->buf);
	}
	ft_strdel(&params->buf);
	nanosleep(&tw, &tr);
}

int		main(int argc, char **argv)
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
		if (ft_strstr(params.buf, "fin"))
		{
			black_fin_display(params.buf, 0, argc);
			return (0);
		}
		if (ft_strstr(params.buf, "Plateau"))
		{
			coords_parsing(&params.x_board, &params.y_board, params.buf);
			board_display(&params, 0, argv, argc);
		}
	}
}
