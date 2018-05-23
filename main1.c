#include "filler.h"

char **free_mem(char **field, int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		free(field[i]);
		field[i] = NULL;
		i++;
	}
	free(field);
	field = NULL;
	return (field);
}

void	coord_push_back(int x, int y)
{
	int i;
	t_coordinate	*list;
	t_coordinate	*oneelem;

	i = 0;
	oneelem = NULL;
	if (!(oneelem = (t_coordinate *)malloc(sizeof(t_coordinate))))
		return ;
	list = coords;
  coords->x = x;
  coords->y = y;
	if (!list)
	{
		coords = oneelem;
		return ;
	}
	while (list->next)
		list = list->next;
	list->next = oneelem;
}

int		check_in_field(int i, int j, int count, t_params *params)
{
  int jj;
  int my;
	int opos;
  int x_finish;
  int y_finish;
  int tmp;
	int k;
	int l;

  my = 0;
	opos = 0;
  x_finish = i;
  y_finish = j;
  tmp = 0;
  jj = j;
	k = 0;
	l = 0;
	while (k < (*params).x_figure && i < (*params).x_board && tmp < count)
	{
      j = jj;
      l = 0;
		while (l < (*params).y_figure && j < (*params).y_board && tmp < count)
		{
			if ((*params).figure[k][l] == '*')
			{
				if ((*params).board[i][j] == (*params).player_number || (*params).board[i][j] == (*params).player_number + 32)
					my++;
				if ((*params).board[i][j] == (*params).oppos_number || (*params).board[i][j] == (*params).oppos_number + 32)
					opos++;
        tmp++;
			}
      l++;
			j++;
		}
    k++;
		i++;
	}

	if (tmp == count && my == 1 && opos == 0)
		{
      //coord_push_back();
			ft_printf("%d %d\n", x_finish, y_finish);
	    return (1);
		}
	else
		return (0);
}

int save_coord(t_params *params)
{
  int i;
  int j;
  int count;

  i = 0;
  j = 0;
  count = 0;
  while (i < (*params).x_figure)
  {
    j = 0;
    while (j < (*params).y_figure)
      if ((*params).figure[i][j++] == '*')
        count++;
    i++;
  }
  i = 0;
  j = 0;
  while (i < (*params).x_board)
	{
    j = 0;
    while (j < (*params).y_board)
      //check_in_field(i, j, 0, 0, count);
      if (check_in_field(i, j++, count, params) == 1)
          return (1);
    i++;
	}
  return (-1);
}

void struct_initiation(t_params *params)
{
  (*params).x_board = 0;
  (*params).y_board = 0;
  (*params).x_figure = 0;
  (*params).y_figure = 0;
  (*params).diff = 0;
  (*params).board = NULL;
  (*params).figure = NULL;
}

void coords_parsing(int *x, int *y, char *buf)
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

void board_making(char *buf, int fd, t_params *params)
{
  int i;
  int j;
  int k;

  coords_parsing(&params->x_board, &params->y_board, buf);
	(*params).board = two_dim_arr_mem((*params).board, (*params).x_board, (*params).y_board, '0');
  if ((*params).x_board <= 100)
      (*params).diff = 4;
  else
      (*params).diff = 5;
  get_next_line(fd, &buf);
  ft_strdel(&buf);
  i = 0;
  while (i < (*params).x_board)
  {
    j = 0;
    k = (*params).diff;
    get_next_line(fd, &buf);
    while (k < (*params).y_board + (*params).diff)
      (*params).board[i][j++] = buf[k++];
    i++;
    ft_strdel(&buf);
  }
}

void figure_making(char *buf, int fd, t_params *params)
{
  int i;
  int j;

	(*params).figure = (char **)malloc(sizeof(char *) * (*params).x_figure);
	i = 0;
	while (i < (*params).x_figure)
		(*params).figure[i++] = (char *)malloc((*params).y_figure);
	i = 0;
	while (i < (*params).x_figure)
	{
		j = 0;
		get_next_line(fd, &buf);
		while (j < (*params).y_figure)
		{
			(*params).figure[i][j] = buf[j];
			j++;
		}
		i++;
		ft_strdel(&buf);
	}
}

int piece_check(char *buf, int fd, t_params *params)
{
	int i;
  int j;

	if (ft_strstr(buf, "Piece"))
	{
		coords_parsing(&params->x_figure, &params->y_figure, buf);
		(*params).figure = two_dim_arr_mem((*params).figure, (*params).x_figure, (*params).y_figure, '0');
		i = 0;
		while (i < (*params).x_figure)
		{
			j = 0;
			get_next_line(fd, &buf);
			(*params).figure[i] = ft_strcpy((*params).figure[i], buf);
			i++;
			ft_strdel(&buf);
		}
		if (save_coord(params) == -1)
		{
			ft_printf("%d %d\n", 0, 0);
			return (0);
		}
		(*params).figure = free_mem((*params).figure, (*params).x_figure);
		(*params).board = free_mem((*params).board, (*params).x_board);
	}
	return (1);
}

int main(void)
{
	int i;
  int j;
  int fd;
  char *buf;
	t_params params;

  fd = 0;
  buf = NULL;
	params.player_number = 'O';
  params.oppos_number = 'X';
  struct_initiation(&params);
	while (get_next_line(fd, &buf) > 0)
	{
		if (ft_strstr(buf, "p2") && ft_strstr(buf, "vlikhotk"))
		{
		    params.player_number = 'X';
		    params.oppos_number = 'O';
        ft_strdel(&buf);
        continue ;
		}
		if (ft_strstr(buf, "Plateau"))
		{
      board_making(buf, fd, &params);
      continue ;
		}
		/*if (!piece_check(buf, fd))
			return (0);*/
			if (ft_strstr(buf, "Piece"))
			{
				coords_parsing(&params.x_figure, &params.y_figure, buf);
				params.figure = two_dim_arr_mem(params.figure, params.x_figure, params.y_figure, '0');
				i = 0;
				while (i < params.x_figure)
				{
					j = 0;
					get_next_line(fd, &buf);
					params.figure[i] = ft_strcpy(params.figure[i], buf);
					i++;
					ft_strdel(&buf);
				}
				if (save_coord(&params) == -1)
				{
					ft_printf("%d %d\n", 0, 0);
					return (0);
				}
				params.figure = free_mem(params.figure, params.x_figure);
				params.board = free_mem(params.board, params.x_board);
			}
    ft_strdel(&buf);
	}
}
