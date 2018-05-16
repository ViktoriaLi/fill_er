
#include "filler.h"
#include "filler.h"

int main(void)
{
  int i;
  int j;
  int k;
  int fd;
  //int fd1;
  char *buf;

  i = 0;
  j = 0;
  k = 0;
  params.player_number = 'O';
  //fd = open(argv[1], O_RDONLY);
  //fd1 = open("res", O_WRONLY);
  fd = 0;
  while (get_next_line(fd, &buf))
  {
    //write(fd1, buf, ft_strlen(buf));
    //write(fd1, "\n", 1);
    if (ft_strstr(buf, "vlikhotk") && ft_strstr(buf, "p2"))
      params.player_number = 'X';
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
    //ft_printf("%s\n", buf);
  }
  //ft_printf("%c\n", params.player_number );
  //ft_printf("%d\n", params.x_board );
  //ft_printf("%d\n", params.y_board );
  get_next_line(fd, &buf);
  i = 0;
  params.board = (char **)malloc(sizeof(char *) * params.x_board);
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
  buf = NULL;
  //ft_printf("%d\n", params.x_figure );
  //ft_printf("%d\n", params.y_figure );
  i = 0;
  params.figure = (char **)malloc(sizeof(char *) * params.x_figure);
  while (i < params.x_figure)
  {
    params.figure[i] = (char *)malloc(params.y_figure + 1);
    //params.figure[i][params.y_figure] = 0;
    //params.figure[i] = NULL;
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
  }
  i = 0;
  while (i < params.x_board && params.board[i][j] != params.player_number)
  {
    j = 0;
    while (j < params.y_board && params.board[i][j] != params.player_number)
      j++;
    if (params.board[i][j] == params.player_number)
      break;
    i++;
  }
  ft_printf("%d %d\n", i, j);
  /*i = 0;
  while (i < params.x_figure)
    free(params.figure[i++]);
  free(params.figure);*/
  /*i = 0;
  while ()
  {
    get_next_line(fd, &buf);
    get_next_line(fd, &buf);
    i = 0;
    while (i < params.x_board)
    {
      j = 0;
      k = 4;
      while (k < params.y_board + 4)
      {
        params.board[i][j] = buf[k];
        k++;
        j++;
      }
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
    }
  }*/
}
