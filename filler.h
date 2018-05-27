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
# include <time.h>
 
typedef	struct	s_params
{
  int player_number;
  int oppos_number;
  int x_board;
  int y_board;
  int x_figure;
  int y_figure;
  int diff;
  int x_diff;
  int y_diff;
  char **board;
  char **figure;
}				t_params;

typedef struct	s_coordinate
{
	int x;
	int y;
  int x_diff;
  int y_diff;
  struct s_coordinate	*next;
}				t_coordinate;

int		get_next_line(const int fd, char **line);
int		ft_printf(const char *format, ...);
char	*ft_strstr(const char *big, const char *little);
char		**ft_strsplit(char const *s, char c);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
void	ft_strdel(char **as);
char	**two_dim_arr_mem(char **field, int x, int y, char c);
char	*ft_strcpy(char *dst, const char *src);
char **free_mem(char **field, int num);
void struct_initiation(t_params *params);
void coords_parsing(int *x, int *y, char *buf);

char	*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_itoa(int n);

#endif
