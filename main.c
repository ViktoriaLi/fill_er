
#include "filler.h"

/*void	list_push_back(t_list **begin_list, t_coordinate *c)
{
	t_list	*list;
	t_list	*oneelem;

	coordinatemin(c);
	list = *begin_list;
	oneelem = ft_lstnew(c, sizeof(t_coordinate) * 4);
	if (!list)
	{
		*begin_list = oneelem;
		return ;
	}
	while (list->next)
		list = list->next;
	list->next = oneelem;
}*/

/*int		check_in_field(int i, int j, t_coordinate *c, int size)
{
	int k;
  int my;
	int opos;
  int x_finish;
  int y_finish;

	k = 0;
  my = 0;
	opos = 0;
  x_finish = i + c[k].x;
  y_finish = j + c[k].y;
	while (k < size)
	{
		if (i + c[k].x < params.x_board && j +
		c[k].y < params.y_board)
    {
      if (params.board[i + c[k].x][j +
  		 c[k].y] == params.player_number || params.board[i + c[k].x][j +
   		 c[k].y] == params.player_number + 32)
        my++;
      if (params.board[i + c[k].x][j +
    	 c[k].y] == params.oppos_number || params.board[i + c[k].x][j +
     	 c[k].y] == params.oppos_number + 32)
        opos++;
      if (k < size && (i + c[k].x >= params.x_board || j +
      	c[k].y >= params.y_board))
      	return (0);
    }
			k++;
	}
  if (my == 1 && opos == 0)
  {
    if (params.x_diff != -1)
      x_finish += params.x_diff;
    if (params.y_diff != -1)
      x_finish += params.y_diff ;
    ft_printf("%d %d\n", x_finish, y_finish);
    return (1);
  }
  else
   return (0);

}

void	coordinatemin(t_coordinate *c, int size)
{
	int minx;
	int miny;
	int i;

	i = 0;
	minx = params.x_figure - 1;
	miny = params.y_figure - 1;
  if (minx < 0)
    minx = 0;
  if (miny < 0)
    miny = 0;
	while (i < size)
	{
		if (c[i].x < minx)
			minx = c[i].x;
		if (c[i].y < miny)
			miny = c[i].y;
		i++;
	}
	i = 0;
  params.x_diff = minx;
  params.y_diff = miny;
	while (i < size)
	{
		c[i].x = c[i].x - minx;
		c[i].y = c[i].y - miny;
    //ft_printf("N coord %d %d\n", c[i].x, c[i].y);
		i++;
	}
}

void find_coord(t_coordinate *c, int size)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while (i < params.x_board)
	{
    j = 0;
    while (j < params.y_board)
    {
      if (check_in_field(i, j, c, size) == 1)
          break;
      j++;
    }
    if (j != params.y_board)
      break;
    i++;
	}
}

void save_coord()
{
  int i;
  int j;
  int count;
  t_coordinate	*c;

  i = 0;
  j = 0;
  count = 0;
  while (i < params.x_figure)
  {
    j = 0;
    while (j < params.y_figure)
    {
      if (params.figure[i][j] == '*')
        count++;
      j++;
    }
    i++;
  }
  c = malloc(sizeof(t_coordinate) * count);
  i = 0;
  j = 0;
  count = 0;
  while (i < params.x_figure)
  {
    j = 0;
    while (j < params.y_figure)
    {
      if (params.figure[i][j] == '*')
      {
        c[count].x = i;
  			c[count].y = j;
        //ft_printf("B coord %d %d\n", c[count].x, c[count].y);
        count++;
      }
      j++;
    }
    i++;
  }
  coordinatemin(c, count);
  find_coord(c, count);
//list_push_back(&(*list), c);
}*/

int		check_in_field(int i, int j, int k, int l)
{
  int my;
	int opos;
  int x_finish;
  int y_finish;
	int a;
	int b;

  my = 0;
	opos = 0;
	a = 0;
	b = 0;
  x_finish = i;
  y_finish = j;
	while (a < params.x_figure && i < params.x_board)
	{
		while (b < params.y_figure && j < params.y_board)
		{
			if (params.figure[k][l] == '*')
			{
				if (params.board[i][j] == params.player_number || params.board[i][j] == params.player_number + 32)
					my++;
				if (params.board[i][j] == params.oppos_number || params.board[i][j] == params.oppos_number + 32)
					opos++;
			}
			if (my > 1 || opos > 0)
				return (0);
			b++;
			j++;
		}
		if (b != params.y_figure)
			return (0);
		a++;
		i++;
	}
	if (a != params.x_figure)
		return (0);
	if (a == params.x_figure && b == params.y_figure && my == 1 && opos == 0)
		{
			ft_printf("%d %d\n", x_finish, y_finish);
	    return (1);
		}
	else
		return (0);
	/*while (k < size)
	{
		if (i + c[k].x < params.x_board && j +
		c[k].y < params.y_board)
    {
      if (params.board[i + c[k].x][j +
  		 c[k].y] == params.player_number || params.board[i + c[k].x][j +
   		 c[k].y] == params.player_number + 32)
        my++;
      if (params.board[i + c[k].x][j +
    	 c[k].y] == params.oppos_number || params.board[i + c[k].x][j +
     	 c[k].y] == params.oppos_number + 32)
        opos++;
      if (k < size && (i + c[k].x >= params.x_board || j +
      	c[k].y >= params.y_board))
      	return (0);
    }
			k++;
	}
  if (my == 1 && opos == 0)
  {
    if (params.x_diff != -1)
      x_finish += params.x_diff;
    if (params.y_diff != -1)
      x_finish += params.y_diff ;
    ft_printf("%d %d\n", x_finish, y_finish);
    return (1);
  }
  else
   return (0);*/

}

void save_coord()
{
  int i;
  int j;
	int k;
  int l;

  i = 0;
  j = 0;
	k = 0;
	l = 0;
  while (k < params.x_figure)
  {
    l = 0;
    while (l < params.y_figure)
    {
      if (params.figure[k][l] == '*')
        break;
      l++;
    }
		if (l != params.y_figure)
			break;
    k++;
  }
  while (i < params.x_board)
	{
    j = 0;
    while (j < params.y_board)
    {
      if (check_in_field(i, j, k, l) == 1)
          break;
      j++;
    }
    if (j != params.y_board)
      break;
    i++;
	}
}

int main(void)
{
  int i;
  int j;
	int count;
  int k;
  int fd;
  int fd1;
  char *buf;
  //t_list	*list;
  i = 0;
  j = 0;
  k = 0;
	count = 0;
  //fd = open("test", O_RDONLY);
  fd1 = open("res", O_WRONLY);
  fd = 0;
	params.player_number = 'O';
  params.oppos_number = 'X';
	while (1)
	{
		if (get_next_line(fd, &buf) < 1)
			break;
		//ft_printf("%s\n", "1test");
		if (count == 1 && ft_strstr(buf, "vlikhotk"))
		{
			params.player_number = 'X';
			params.oppos_number = 'O';
		}
		//ft_printf("1%c %c\n", params.player_number, params.oppos_number);
		//ft_printf("%s\n", "2test");
		if (count == 2)
		{
			i = 0;
			while (buf[i] > '9')
				i++;
			params.x_board = ft_atoi(&buf[i++]);
			while (buf[i] >= '0' && buf[i] <= '9')
				i++;
			i++;
			params.y_board = ft_atoi(&buf[i]);
			//ft_printf("2%d %d\n", params.x_board, params.y_board);
			params.board = (char **)malloc(sizeof(char *) * params.x_board);
			i = 0;
			while (i < params.x_board)
			{
				params.board[i] = (char *)malloc(params.y_board);
				params.board[i][params.y_board] = 0;
				i++;
			}
		}
		if (ft_strstr(buf, "Plateau"))
		{//ft_printf("%s\n", "3test");
			get_next_line(fd, &buf);
			free(buf);
			i = 0;
		  while (i < params.x_board)
			{
				j = 0;
		    k = 4;
		    get_next_line(fd, &buf);
		    while (k < params.y_board + 4)
		    {
		      params.board[i][j] = buf[k];
		      k++;
		      j++;
		    }
				//ft_printf("3%s\n", params.board[i]);
		    //ft_printf("1%s\n", params.board[i]);
		    free(buf);
				i++;
			}
		}
		//ft_printf("%s\n", "4test");
		if (ft_strstr(buf, "Piece"))
		{
			i = 0;
		  while (buf[i] > '9')
		    i++;
		  params.x_figure = ft_atoi(&buf[i++]);
		  while (buf[i] >= '0' && buf[i] <= '9')
		    i++;
		  i++;
		  params.y_figure = ft_atoi(&buf[i]);
			//ft_printf("4%d %d\n", params.x_figure, params.y_figure);
		  //ft_printf("%d\n", params.x_figure );
		  //ft_printf("%d\n", params.y_figure );
		  params.figure = (char **)malloc(sizeof(char *) * params.x_figure);
		  i = 0;
			while (i < params.x_figure)
		 	{
			 	params.figure[i] = (char *)malloc(params.y_figure);
			 	params.figure[i][params.y_figure] = 0;
			 	i++;
		 	}
			free(buf);
			i = 0;
		  while (i < params.x_figure)
		  {
				j = 0;
		    get_next_line(fd, &buf);
		    while (j < params.y_figure)
		    {
		      params.figure[i][j] = buf[j];
		      j++;
		    }
				//ft_printf("5%s\n", params.figure[i]);
		    //ft_printf("1%s\n", params.figure[i]);
		    i++;
		    free(buf);
		  }
			//save_coord();
			ft_printf("%d %d", 8, 2);
			i = 0;
			 while (i < params.x_figure)
				 free(params.figure[i++]);
			 //free(buf);
		}
		//ft_printf("%d %d", 8, 2);
		count++;
	}

}

/*int main(void)
{
  int i;
  int j;

  int k;
  int fd;
  int fd1;
  char *buf;
  //t_list	*list;
  i = 0;
  j = 0;
  k = 0;
  //fd = open("test", O_RDONLY);
  fd1 = open("res", O_WRONLY);
  fd = 0;
	params.player_number = 'O';
  params.oppos_number = 'X';
		while (get_next_line(fd, &buf))
		  {
		    //write(fd1, buf, ft_strlen(buf));
		    //write(fd1, "\n", 1);
		    if (ft_strstr(buf, "vlikhotk") && ft_strstr(buf, "p2"))
				{
					params.player_number = 'X';
					params.oppos_number = 'O';
				}

		    if (ft_strstr(buf, "Plateau"))
		    {
		      while (buf[i] > '9')
		        i++;
		      params.x_board = ft_atoi(&buf[i++]);
		      while (buf[i] >= '0' && buf[i] <= '9')
		        i++;
		      i++;
		      params.y_board = ft_atoi(&buf[i]);
		      break;
		    }
				free(buf);
		    //ft_printf("%s\n", buf);
		  }
  //ft_printf("%s\n", buf);
  //ft_printf("%c\n", params.player_number );
  //ft_printf("%d\n", params.x_board );
  //ft_printf("%d\n", params.y_board );
  get_next_line(fd, &buf);
  free(buf);
  params.board = (char **)malloc(sizeof(char *) * params.x_board);
  i = 0;
	while (i < params.x_board)
  {
    params.board[i] = (char *)malloc(params.y_board + 1);
		params.board[i][params.y_board] = 0;
    i++;
  }
	i = 0;
  while (i < params.x_board)
	{
		j = 0;
    k = 4;
    get_next_line(fd, &buf);
    while (k < params.y_board + 4)
    {
      params.board[i][j] = buf[k];
      k++;
      j++;
    }
    //ft_printf("1%s\n", params.board[i]);
    free(buf);
		i++;
	}
  get_next_line(fd, &buf);
  i = 0;
  while (buf[i] > '9')
    i++;
  params.x_figure = ft_atoi(&buf[i++]);
  while (buf[i] >= '0' && buf[i] <= '9')
    i++;
  i++;
  params.y_figure = ft_atoi(&buf[i]);
  //ft_printf("%d\n", params.x_figure );
  //ft_printf("%d\n", params.y_figure );
	free(buf);
  params.figure = (char **)malloc(sizeof(char *) * params.x_figure);
  i = 0;
	while (i < params.x_figure)
 {
	 params.figure[i] = (char *)malloc(params.y_figure + 1);
	 params.figure[i][params.y_figure] = 0;
	 i++;
 }
	i = 0;
  while (i < params.x_figure)
  {
		j = 0;
    get_next_line(fd, &buf);
    while (j < params.y_figure)
    {
      params.figure[i][j] = buf[j];
      j++;
    }
    //ft_printf("1%s\n", params.figure[i]);
    i++;
    free(buf);
  }
  save_coord();
	//ft_printf("%d %d", 8, 2);
  i = 0;
  while (i < params.x_figure)
  {
    free(params.figure[i++]);
    //params.figure[i++] = NULL;
  }
  free(params.figure);
  while (get_next_line(fd, &buf))
  {
		write(fd1, "1", 1);
		write(fd1, buf, ft_strlen(buf));
		write(fd1, "\n", 1);
    free(buf);
    //get_next_line(fd, &buf);
    //ft_printf("2%s\n", buf);
    //get_next_line(fd, &buf);
    //free(buf);
		get_next_line(fd, &buf);
		write(fd1, "2", 1);
		write(fd1, buf, ft_strlen(buf));
		write(fd1, "\n", 1);
    free(buf);
		get_next_line(fd, &buf);
		write(fd1, "2", 1);
		write(fd1, buf, ft_strlen(buf));
		write(fd1, "\n", 1);
    free(buf);
    //ft_printf("2%s\n", buf);
    i = 0;
    while (i < params.x_board)
    {
			j = 0;
	 		k = 4;
	 		get_next_line(fd, &buf);
			write(fd1, buf, ft_strlen(buf));
			write(fd1, "\n", 1);
			write(fd1, "3", 1);
			write(fd1, "\n", 1);
	 		while (k < params.y_board + 4)
	 		{
		 		params.board[i][j] = buf[k];
		 		k++;
		 		j++;
	 		}
	 //ft_printf("1%s\n", params.board[i]);
	 		i++;
      free(buf);
    }
    get_next_line(fd, &buf);
		write(fd1, buf, ft_strlen(buf));
		write(fd1, "\n", 1);
		write(fd1, "4", 1);
		write(fd1, "\n", 1);
    //ft_printf("4%s\n", buf);
    i = 0;
    while (buf[i] > '9')
      i++;
    params.x_figure = ft_atoi(&buf[i++]);
    while (buf[i] >= '0' && buf[i] <= '9')
      i++;
    i++;
    params.y_figure = ft_atoi(&buf[i]);
    free(buf);
    //ft_printf("%d\n", params.x_figure );
    //ft_printf("%d\n", params.y_figure );
    params.figure = (char **)malloc(sizeof(char *) * params.x_figure);
    i = 0;
		while (i < params.x_figure)
 		{
	 		params.figure[i] = (char *)malloc(params.y_figure + 1);
			params.figure[i][params.y_figure] = 0;
	 		i++;
 		}
 		i = 0;
    while (i < params.x_figure)
    {
			j = 0;
    	get_next_line(fd, &buf);
			write(fd1, buf, ft_strlen(buf));
			write(fd1, "\n", 1);
			write(fd1, "5", 1);
			write(fd1, "\n", 1);
    	while (j < params.y_figure)
    	{
      	params.figure[i][j] = buf[j];
      	j++;
    	}
    //ft_printf("1%s\n", params.figure[i]);
    	i++;
      free(buf);
    }
    //ft_printf("%d %d\n", i, j);
    save_coord();
		//ft_printf("%d %d", 8, 2);
    i = 0;
    while (i < params.x_figure)
      free(params.figure[i++]);
    free(params.figure);
  }
}*/
