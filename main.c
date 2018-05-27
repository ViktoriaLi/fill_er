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
	//int x_diff;
	//int y_diff;
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
   					if (res == -1 || (res != -1 && res1 < res))
   					{
   						res = res1;
   						x = (*coords).x;
   						y = (*coords).y;	
   						//x_diff = (*coords).x_diff;
   						//y_diff = (*coords).y_diff;
   					}
   					coords = coords->next;
   				}
   			}
      		j++;
    	}
     	i++;
  	}
	
	/*if (x_diff != -1)
		x = -1 * x_diff;
	if (y_diff != -1)
		y = -1 * y_diff;*/
    ft_printf("%d %d\n", x, y);
	while (list)
	{
		coords = list->next;
		free(list);
		list = coords;
	}
}

void	coord_push_back(int x, int y, t_coordinate **coords, t_params *params)
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
 	oneelem->x_diff = (*params).x_diff;
 	oneelem->y_diff = (*params).y_diff;
	if (!list)
	{
		*coords = oneelem;
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
	int k;
	int l;

  my = 0;
	opos = 0;
  jj = j;
  if ((*params).x_diff == -1)
   	k = 0;
  else
  	k = (*params).x_diff;
if ((*params).y_diff == -1)
	l = 0;
else
	l = (*params).y_diff;
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

int figure_size(t_params *params)
{
	int i;
  int j;
  int count;

  i = 0;
  count = 0;
  while (i < (*params).x_figure)
  {
    j = 0;
    while (j < (*params).y_figure)
    {
    	if ((*params).figure[i][j] == '*')
      {
      	
   		if (((*params).x_diff != -1 && i < (*params).x_diff) || (*params).x_diff == -1)
   			(*params).x_diff = i;
   		if (((*params).y_diff != -1 && j < (*params).y_diff) || (*params).y_diff == -1)
   			(*params).y_diff = j;
      	count++;
      }
      j++;
    }
    i++;
  }
  return (count);
}

int save_coord(t_params *params)
{
  int i;
  int j;
  int count;
  t_coordinate *coords;

  i = 0;
  j = 0;
  count = figure_size(params);
  coords = NULL;
  while (i < (*params).x_board)
	{
    j = 0;
    while (j < (*params).y_board)
    {
    if (check_in_field(i, j, count, params) == 1)
      	coord_push_back(i, j, &coords, params);
      j++;
    } 
    i++;
	}
	if (coords)
	{
		choose_prime_position(coords, params);
		return (1);
	}
  	else 
  		return (-1);
}

void board_making(char *buf, int fd, t_params *params)
{
  int i;
  int j;
  int k;

  coords_parsing(&params->x_board, &params->y_board, buf);
	(*params).board = two_dim_arr_mem((*params).board, 
		(*params).x_board, (*params).y_board, '\0');
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

int figure_making(char *buf, int fd, t_params *params)
{
	int i;

		coords_parsing(&params->x_figure, &params->y_figure, buf);
		
		(*params).figure = two_dim_arr_mem((*params).figure, (*params).x_figure,
			(*params).y_figure, '\0');
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
	return (1);
}

int main(void)
{
  char *buf;
	t_params params;

  buf = NULL;
  struct_initiation(&params);
	while (get_next_line(0, &buf) > 0)
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
      		board_making(buf, 0, &params);
      		continue ;
		}
			if (ft_strstr(buf, "Piece"))
			{
				if (!figure_making(buf, 0, &params))
					return (0);
				continue;
			}
    ft_strdel(&buf);
	}
}
