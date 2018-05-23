/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 13:15:59 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/03/01 18:21:51 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef	struct	s_params
{
  int player_number;
  int oppos_number;
  int x_board;
  int y_board;
  int x_figure;
  int y_figure;
  char **board;
  char **figure;
}				t_params;

t_params params;

typedef	struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct	s_coordinate
{
	int x;
	int y;
  struct s_coordinate	*next;
}				t_coordinate;

t_coordinate *coords;

int		get_next_line(const int fd, char **line);
int		ft_printf(const char *format, ...);
char	*ft_strstr(const char *big, const char *little);
char		**ft_strsplit(char const *s, char c);
int			ft_atoi(const char *str);
char	**two_dim_arr_mem(char **field, int x, int y, char c);
size_t		ft_strlen(const char *s);
void	ft_strdel(char **as);

void	coordinatemin(t_coordinate *c, int size);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_itoa(int n);

#endif
