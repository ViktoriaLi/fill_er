#include "filler.h"

void choose_prime_position(t_coordinate *coords, t_params *params)
{
	int i;
	int j;
	int x;
	int y;
	int res;
	int res1;
	int tmp1;
	int tmp2;
	t_coordinate *list;

	list = coords;
	res = -1;
	i = 0;
	while (i < (*params).x_board)
	{
   		j = 0;
   		while (j < (*params).y_board)
   		{
   			if ((*params).board[i][j] == (*params).oppos_number)
   			{
   				coords = list;
   				while (coords)
   				{
   					
   					tmp1 = (((*coords).x - i) >= 0) ? ((*coords).x - i) : (-1 * ((*coords).x - i));
   					tmp2 = (((*coords).y - j) >= 0) ? ((*coords).y - j) : (-1 * ((*coords).y - j));
   					res1 = tmp1 + tmp2;
   					if (res == -1)
   					{
   						res = res1;
   						x = (*coords).x;
   						y = (*coords).y;	
   					}
   					else
   						if (res1 < res)
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

void	coord_push_back(int x, int y, t_coordinate **coords, int fd)
{
	t_coordinate	*list;
	t_coordinate	*oneelem;

	write(fd, "c", 1);
      	write(fd, "\n", 1);

	oneelem = NULL;
	list = *coords;
	if (!(oneelem = (t_coordinate *)malloc(sizeof(t_coordinate)))) {
	write(fd, "j", 1);
      write(fd, "\n", 1);
		return ;
	}
	oneelem->next = NULL;
  	oneelem->x = x;
 	oneelem->y = y;
	if (!list)
	{
		*coords = oneelem;
	write(fd, "s", 1);
      write(fd, "\n", 1);
		return ;
	}
	while (list->next)
		list = list->next;
	list->next = oneelem;
	write(fd, "k", 1);
      write(fd, "\n", 1);
}

int		check_in_field(int i, int j, int count, t_params *params)
{
  int jj;
  int my;
	int opos;
  int tmp;
	int k;
	int l;

  my = 0;
	opos = 0;
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
				if ((*params).board[i][j] == (*params).player_number ||
					(*params).board[i][j] == (*params).player_number + 32)
					my++;
				if ((*params).board[i][j] == (*params).oppos_number ||
					(*params).board[i][j] == (*params).oppos_number + 32)
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
			//ft_printf("%d %d\n", x_finish, y_finish);
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
  t_coordinate *coords;
  //t_coordinate *list;
  int fd = open("res", O_WRONLY | O_APPEND);
  write(fd, "\n", 1);
  write(fd, "\n", 1);
  write(fd, "d", 1);
  write(fd, "\n", 1);

  i = 0;
  j = 0;
  count = 0;
  coords = NULL;
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
    {
    if (check_in_field(i, j, count, params) == 1)
      {
      	//ft_printf("%s\n", "test");
      	write(fd, "a", 1);
      	write(fd, "\n", 1);
      	coord_push_back(i, j, &coords, fd);
      	//ft_printf("%d %d\n", i, j);
          //return (1);
      }
      j++;
    } 
    i++;
	}
	//list = coords;
	/*while (coords->next)
	{
		ft_printf("%d %d\n", (*coords).x, (*coords).y);
		coords = coords->next;
	}*/
	if (coords)
	{
		//ft_printf("%s\n", "check");
		//choose_prime_position(coords, params);
		write(fd, "b", 1);
      	write(fd, "\n", 1);

		ft_printf("%d %d\n", (*coords).x, (*coords).y);
		close(fd);
		return (1);
	}
  	else {
		write(fd, "v", 1);
      	write(fd, "\n", 1);
		close(fd);
  		return (-1);
  	}
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

	if (ft_strstr(buf, "Piece"))
	{
		coords_parsing(&params->x_figure, &params->y_figure, buf);
		(*params).figure = two_dim_arr_mem((*params).figure, (*params).x_figure, (*params).y_figure, '0');
		i = 0;
		while (i < (*params).x_figure)
		{
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
  int fd;
  char *buf;
	t_params params;

  fd = 0;
//	fd = open("test", O_RDONLY);
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
