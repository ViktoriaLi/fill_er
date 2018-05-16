
#include "filler.h"

int		check_in_field(int i, int j, t_coordinate *c, int size)
{
	int k;
  int my;
	int opos;
  int x_finish;
  int y_finish;

	k = 0;
  my = 0;
	opos = 0;
  x_finish = 0;
  y_finish = 0;
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
}

void struct_initiation()
{
  params.x_diff = -1;
  params.y_diff = -1;
  params.player_number = 'O';
  params.oppos_number = 'X';
}

int main(void)
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
  struct_initiation();
    get_next_line(fd, &buf);
    /*write(fd1, buf, ft_strlen(buf));
    write(fd1, "\n", 1);*/
    if (ft_strstr(buf, "vlikhotk") && ft_strstr(buf, "p2"))
    {
      params.player_number = 'X';
      params.oppos_number = '0';
    }
    free(buf);
    get_next_line(fd, &buf);
    while (buf[i] > '9')
      i++;
    params.x_board = ft_atoi(&buf[i++]);
    while (buf[i] >= '0' && buf[i] <= '9')
      i++;
    i++;
    params.y_board = ft_atoi(&buf[i]);
    free(buf);

    //ft_printf("%s\n", buf);
  //ft_printf("%c\n", params.player_number );
  //ft_printf("%d\n", params.x_board );
  //ft_printf("%d\n", params.y_board );
  get_next_line(fd, &buf);
  /*write(fd1, buf, ft_strlen(buf));
     write(fd1, "\n", 1);*/
  free(buf);
  params.board = (char **)malloc(sizeof(char *) * params.x_board);
  i = 0;
  while (i < params.x_board)
	{
    get_next_line(fd, &buf);
    /*write(fd1, buf, ft_strlen(buf));
     write(fd1, "\n", 1);*/
    params.board[i++] = ft_strsub(buf, 4, params.y_board + 1);
    //ft_printf("1%s\n", params.board[i]);
    free(buf);
	}
  get_next_line(fd, &buf);
  /*write(fd1, buf, ft_strlen(buf));
     write(fd1, "\n", 1);*/
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
  params.figure = (char **)malloc(sizeof(char *) * params.x_figure);
  free(buf);
  i = 0;
  while (i < params.x_figure)
  {
    get_next_line(fd, &buf);
    /*write(fd1, buf, ft_strlen(buf));
     write(fd1, "\n", 1);*/
     params.figure[i++] = ft_strsub(buf, 0, params.y_figure + 1);
    //ft_printf("1%s\n", params.figure[i]);
    free(buf);
  }
  save_coord();
  i = 0;
  while (i < params.x_figure)
  {
    free(params.figure[i++]);
    //params.figure[i++] = NULL;
  }
  free(params.figure);
  while (get_next_line(fd, &buf))
  {
    free(buf);
    //get_next_line(fd, &buf);
    //ft_printf("2%s\n", buf);
    get_next_line(fd, &buf);
    free(buf);
    struct_initiation();
    //ft_printf("2%s\n", buf);
    i = 0;
    while (i < params.x_board)
    {
      get_next_line(fd, &buf);
      params.board[i++] = ft_strsub(buf, 4, params.y_board + 1);
      //ft_printf("3%s\n", params.board[i]);
      free(buf);
    }
    get_next_line(fd, &buf);
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
      get_next_line(fd, &buf);
      params.figure[i++] = ft_strsub(buf, 0, params.y_figure + 1);
      //ft_printf("6%s\n", params.figure[i]);
      free(buf);
    }
    //ft_printf("%d %d\n", i, j);
    save_coord();
    i = 0;
    while (i < params.x_figure)
      free(params.figure[i++]);
    free(params.figure);
  }
}
