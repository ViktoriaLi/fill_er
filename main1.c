#include "filler.h"

/*int		check_in_field(int i, int j, int k, int l)
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
}*/

int		check_in_field(int i, int j, int k, int l, int count)
{
//ft_printf("FIRST%d %d %d %d %d\n", i, j, k, l, count);
  int jj;
  int my;
	int opos;
  int x_finish;
  int y_finish;
  my = 0;
	opos = 0;
  x_finish = i;
  y_finish = j;
  int tmp;
  tmp = 0;
  jj = j;
	while (k < params.x_figure && i < params.x_board && tmp < count)
	{
      j = jj;
      l = 0;
		while (l < params.y_figure && j < params.y_board && tmp < count)
		{
			if (params.figure[k][l] == '*')
			{
        //ft_printf("!!!  %d %d %d %d %d\n", i, j, k, l, tmp);
        //ft_printf("%c", params.board[i][j]);
        //ft_printf("%c", params.figure[k][l]);
				if (params.board[i][j] == params.player_number || params.board[i][j] == params.player_number + 32)
					my++;
				if (params.board[i][j] == params.oppos_number || params.board[i][j] == params.oppos_number + 32)
					opos++;
        tmp++;
			}
      l++;
			j++;
      //ft_printf("333 %d %d %d %d %d\n", my, opos, k, l, tmp);
		}
    k++;
		i++;
	}

	if (tmp == count && my == 1 && opos == 0)
		{
			ft_printf("%d %d\n", x_finish, y_finish);
	    return (1);
		}
	else
		return (0);
}

void save_coord()
{
  int i;
  int j;
	int k;
  int l;
  int count;

  i = 0;
  j = 0;
	k = 0;
	l = 0;
  count = 0;
  while (i < params.x_figure)
  {
    j = 0;
    while (j < params.y_figure)
    {
      if (params.figure[i][j] == '*')
        count++;
      if (count == 1)
      {
        k = i;
        l = j;
      }
      j++;
    }
    i++;
  }
  i = 0;
  j = 0;
  while (i < params.x_board)
	{
    j = 0;
    while (j < params.y_board)
    {
      if (check_in_field(i, j, k, l, count) == 1)
          return ;
      j++;
    }
    i++;
	}
}

void struct_initiation()
{
  params.x_board = 0;
  params.y_board = 0;
  params.x_figure = 0;
  params.y_figure = 0;
  params.board = NULL;
  params.figure = NULL;
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
  char *tmp;
  //t_list	*list;
  i = 0;
  j = 0;
  k = 0;
	count = 0;

  //fd = open("test1", O_RDONLY);
  fd1 = open("res", O_WRONLY);
  fd = 0;
  buf = NULL;
  tmp = NULL;
	params.player_number = 'O';
  params.oppos_number = 'X';
  struct_initiation();
	while (1)
	{
    i = 0;
		if (get_next_line(fd, &buf) < 1)
			break;
    write(fd1, "1", 1);
    write(fd1, buf, ft_strlen(buf));
    write(fd1, "\n", 1);
		//ft_printf("BUF%s\n", buf);
		if (count == 1 && ft_strstr(buf, "vlikhotk"))
		{
			params.player_number = 'X';
			params.oppos_number = 'O';
      count++;
      continue ;
		}
		if (ft_strstr(buf, "Plateau"))
		{
      i = 0;
			while (buf[i] != ' ')
				i++;
			params.x_board = ft_atoi(&buf[++i]);
			while (buf[i] != ' ')
				i++;
			params.y_board = ft_atoi(&buf[++i]);
      //tmp = ft_itoa(params.x_board);
      params.board = (char **)malloc(sizeof(char *) * params.x_board);
			i = 0;
			while (i < params.x_board)
				params.board[i++] = (char *)malloc(params.y_board);
			get_next_line(fd, &buf);
      write(fd1, "2", 1);
      write(fd1, buf, ft_strlen(buf));
      write(fd1, "\n", 1);
      //ft_printf("EMPTY line%s\n", buf);
			ft_strdel(&buf);
      //ft_printf("DDD%d\n", params.x_board);
			i = 0;
		  while (i < params.x_board)
			{
        write(fd1, "test", 4);
				j = 0;
		    k = 4;
		    get_next_line(fd, &buf);
        write(fd1, "3", 1);
        write(fd1, buf, ft_strlen(buf));
        write(fd1, "\n", 1);
		    while (k < params.y_board + 4)
		    {
		      params.board[i][j] = buf[k];
		      k++;
		      j++;
		    }
				//ft_printf("BOARD%s\n", params.board[i]);
		    ft_strdel(&buf);
				i++;
			}
      count++;
      continue ;
		}
    //ft_printf("BOARD%s\n", "test");
		if (ft_strstr(buf, "Piece"))
		{
      //ft_printf("BOARD%s\n", "test");
			i = 0;
		  while (buf[i] != ' ')
		    i++;
		  params.x_figure = ft_atoi(&buf[++i]);
		  while (buf[i] != ' ')
		    i++;
		  params.y_figure = ft_atoi(&buf[++i]);
			//ft_printf("FIG size%d %d\n", params.x_figure, params.y_figure);
		  params.figure = (char **)malloc(sizeof(char *) * params.x_figure);
		  i = 0;
			while (i < params.x_figure)
			 	params.figure[i++] = (char *)malloc(params.y_figure);
			ft_strdel(&buf);
			i = 0;
		  while (i < params.x_figure)
		  {
				j = 0;
		    get_next_line(fd, &buf);
        write(fd1, "4", 1);
        write(fd1, buf, ft_strlen(buf));
        write(fd1, "\n", 1);
		    while (j < params.y_figure)
		    {
		      params.figure[i][j] = buf[j];
		      j++;
		    }
				//ft_printf("FIGURE%s\n", params.figure[i]);
		    i++;
		    ft_strdel(&buf);
		  }
			save_coord();
			//ft_printf("%d %d", 8, 2);
			i = 0;
			 while (i < params.x_figure)
        ft_strdel(&params.figure[i++]);
        i = 0;
  			while (i < params.x_board)
        ft_strdel(&params.board[i++]);
			 //free(buf);
		}
    //ft_printf("BOARD%s\n", "test");
		count++;
	}
  //ft_printf("%d %d", 8, 2);
}
