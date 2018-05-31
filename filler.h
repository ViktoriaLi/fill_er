/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 13:15:59 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/30 14:20:12 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <time.h>
# include "libft/includes/libft.h"
# include "libft/includes/ft_printf.h"
# include "libft/includes/get_next_line.h"

typedef	struct	s_params
{
	char	*buf;
	int		player_number;
	int		oppos_number;
	int		x_board;
	int		y_board;
	int		x_figure;
	int		y_figure;
	int		diff;
	int		x_diff;
	int		y_diff;
	char	**board;
	char	**figure;
}				t_params;

typedef struct	s_coordinate
{
	int					x;
	int					y;
	struct s_coordinate	*next;
}				t_coordinate;

typedef struct	s_iter
{
	int					x;
	int					y;
	int					k;
	int					l;
	int					m;
	int					n;
	int					res;
	int					res1;
}				t_iter;

void			struct_initiation(t_params *params);
void			coords_parsing(int *x, int *y, char *buf);
void			choose_prime_position1(t_coordinate *coords, t_params *params);
void			choose_prime_position2(t_coordinate *coords, t_params *params);
void			coord_push_back(int x, int y, t_coordinate **coords);
int				check_in_field(int i, int j, int count, t_params *params);
int				figure_size(t_params *params, int i);
int				save_coord(t_params *params);
void			board_making(char **buf, int fd, t_params *params);
int				figure_making(char **buf, int fd, t_params *params);
void			iters_initiation(t_iter *iters);
void			check_symbs(char board, t_params *params, int *x, int *y);
void			free_list(t_coordinate **list);

void			color_fin_display(char *buf, int fd);
void			black_fin_display(char *buf, int fd, int argc);
void			square_board_print(t_params *params, char *buf);
void			symb_board_print(t_params *params, char *buf);
void			black_board_print(t_params *params, char *buf);
int				save_coord(t_params *params);

#endif
