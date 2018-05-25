#include "filler.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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

int main()
{
	int i;
 	int j;
 	int k;
	int fd;
	int winner;
	char *buf;
	char *tmp;
	t_params params;
	struct timespec tw = {0, 100000000};
	struct timespec tr;

	i = 0;
	j = 0;
	k = 0;
	fd = 0;
	buf = NULL;
	tmp = NULL;
	winner = 0;
	struct_initiation(&params);
	params.player_number = 'O';
  	params.oppos_number = 'X';
	while (get_next_line(fd, &buf) > 0)
	{
		//ft_printf("%s\n", buf);
		if (ft_strstr(buf, "p2") && ft_strstr(buf, "vlikhotk"))
		{
		    params.player_number = 'X';
		    params.oppos_number = 'O';
        	ft_strdel(&buf);
        	continue ;
		}
		if (ft_strstr(buf, "fin"))
		{
			tmp = buf;
			i = 0;
			while (tmp[i] != ':')
				i++;
			i++;
			j = ft_atoi(&tmp[i]);
			get_next_line(fd, &buf);
			i = 0;
			while (tmp[i] != ':')
				i++;
			i++;
			k = ft_atoi(&buf[i]);
			write (1, "\n", 1);
			j > k ? ft_printf("%s%s%s\n", "\x1b[1;32m\x1b[1;47m\x1b[?25l", tmp, "\x1b[0m") : 
			ft_printf("%s%s%s\n", "\x1b[1;31m\x1b[1;47m\x1b[?25l", tmp, "\x1b[0m");
			k > j? ft_printf("%s%s%s\n", "\x1b[1;32m\x1b[1;47m\x1b[?25l", buf, "\x1b[0m") : 
			ft_printf("%s%s%s\n", "\x1b[1;31m\x1b[1;47m\x1b[?25l", buf, "\x1b[0m");
			//ft_printf("%s%s%s\n", "\x1b[32m\x1b[47m\x1b[?25l", tmp, "\x1b[0m");
			//ft_printf("%s%s%s\n", "\x1b[32m\x1b[47m\x1b[?25l", buf, "\x1b[0m");
        	ft_strdel(&buf);
        	ft_strdel(&tmp);
        	return (0);
		}
		if (ft_strstr(buf, "Plateau"))
		{
			system("clear");
			coords_parsing(&params.x_board, &params.y_board, buf);
			if (params.x_board <= 100)
      			params.diff = 4;
  			else
    		  params.diff = 5;
  			get_next_line(fd, &buf);
  			ft_strdel(&buf);
 			i = 0;
 			while (i < params.x_board)
 			{
    			j = 0;
   				k = params.diff;
    			get_next_line(fd, &buf);
   				while (k < params.y_board + params.diff)
      			{
      				if (buf[k] == params.player_number)
      					ft_printf("%s%c%s", "\x1b[1;35m\x1b[1;47m\x1b[?25l", buf[k], "\x1b[0m");
      				else if (buf[k] == params.player_number + 32)
      					ft_printf("%s%c%s", "\x1b[35m\x1b[1;47m\x1b[?25l", buf[k], "\x1b[0m");
      				else if (buf[k] == params.oppos_number)
      					ft_printf("%s%c%s", "\x1b[1;34m\x1b[1;47m\x1b[?25l", buf[k], "\x1b[0m");
      				else if (buf[k] == params.oppos_number + 32)
      					ft_printf("%s%c%s", "\x1b[34m\x1b[1;47m\x1b[?25l", buf[k], "\x1b[0m");
      				else
      					ft_printf("%s%c%s", "\x1b[1;33m\x1b[1;47m\x1b[?25l", buf[k], "\x1b[0m");
      				k++;
      			}
      			write(1, "\n", 1);
   				i++;
    			ft_strdel(&buf);

  			}
		ft_strdel(&buf);
		nanosleep (&tw, &tr);
		
		//ft_printf("\033[22;31mbuf");
	}
}
}