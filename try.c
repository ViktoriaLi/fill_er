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
fd = open("test", O_RDONLY);
fd1 = open("res", O_WRONLY);
//fd = 0;
struct_initiation();
  while (get_next_line(fd, &buf))
    {
      //write(fd1, buf, ft_strlen(buf));
      //write(fd1, "\n", 1);
      if (ft_strstr(buf, "vlikhotk") && ft_strstr(buf, "p2"))
      {
        params.player_number = 'X';
        params.oppos_number = '0';
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
  /*if (ft_strstr(buf, "vlikhotk") && ft_strstr(buf, "p2"))
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
  free(buf);*/

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

Piece 1 11:
....**.....


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


launched resources/players/vlikhotk.filler
$$$ exec p1 : [resources/players/vlikhotk.filler]
launched resources/players/grati.filler
$$$ exec p2 : [resources/players/grati.filler]
Plateau 15 17:
    01234567890123456
000 .................
001 .................
002 .................
003 .................
004 .................
005 .................
006 .................
007 .................
008 ..O..............
009 .................
010 .................
011 .................
012 ..............X..
013 .................
014 .................
Piece 2 3:
.**
***


launched resources/players/vlikhotk.filler
$$$ exec p1 : [resources/players/vlikhotk.filler]
launched resources/players/grati.filler
$$$ exec p2 : [resources/players/grati.filler]
Plateau 15 17:
    01234567890123456
000 .................
001 .................
002 .................
003 .................
004 .................
005 .................
006 .................
007 .................
008 ..O..............
009 .................
010 .................
011 .................
012 ..............X..
013 .................
014 .................
Piece 2 3:
.**
.**



launched resources/players/vlikhotk.filler
launched resources/players/grati.filler
Plateau 15 17:
    01234567890123456
000 .................
001 .................
002 .................
003 .................
004 .................
005 .................
006 .................
007 .................
008 ..O..............
009 .................
010 .................
011 .................
012 ..............X..
013 .................
014 .................
Piece 2 1:
*
*
<got (O): [7, 0]


Plateau 15 17:
    01234567890123456
000 .................
001 .................
002 .................
003 .................
004 .................
005 .................
006 .................
007 .................
008 ..O..............
009 .................
010 .................
011 .................
012 ..............X..
013 .................
014 .................
Piece 2 3:
...
***
