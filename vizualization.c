#include "filler.h"

void fin_display(char *buf, int fd)
{
	int i;
 	int j;
 	int k;
	char *tmp;

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
	ft_printf("%s%c%s", "\x1b[1;47m\x1b[?25l", '\n', "\x1b[0m");
	j > k ? ft_printf("%s%s%s\n", "\x1b[1;32m\x1b[1;47m\x1b[?25l", tmp, "\x1b[0m") : 
	ft_printf("%s%s%s\n", "\x1b[1;31m\x1b[1;47m\x1b[?25l", tmp, "\x1b[0m");
	k > j? ft_printf("%s%s%s\n", "\x1b[1;32m\x1b[1;47m\x1b[?25l", buf, "\x1b[0m") : 
	ft_printf("%s%s%s\n", "\x1b[1;31m\x1b[1;47m\x1b[?25l", buf, "\x1b[0m");
    ft_strdel(&buf);
    ft_strdel(&tmp);
}

void board_print(t_params *params, char *buf)
{
	int k;

	k = (*params).diff;
	while (k < (*params).y_board + (*params).diff)
    	{
    		if (buf[k] == (*params).player_number)
    			ft_printf("%s%c%s", "\x1b[1;35m\x1b[1;47m\x1b[?25l", buf[k], "\x1b[0m");
    		else if (buf[k] == (*params).player_number + 32)
    			ft_printf("%s%c%s", "\x1b[2;35m\x1b[1;47m\x1b[?25l", buf[k], "\x1b[0m");
    		else if (buf[k] == (*params).oppos_number)
    			ft_printf("%s%c%s", "\x1b[1;34m\x1b[1;47m\x1b[?25l", buf[k], "\x1b[0m");
    		else if (buf[k] == (*params).oppos_number + 32)
    			ft_printf("%s%c%s", "\x1b[2;34m\x1b[1;47m\x1b[?25l", buf[k], "\x1b[0m");
    		else
    			ft_printf("%s%c%s", "\x1b[1;33m\x1b[1;47m\x1b[?25l", buf[k], "\x1b[0m");
    		k++;
    	}
}

void board_display(t_params *params, char *buf, int fd)
{
	int i;
 	int j;
 	struct timespec tw = {0, 100000000};
	struct timespec tr;

 	i = 0;
	j = 0;
	system("clear");
	if ((*params).x_board <= 100)
    	(*params).diff = 4;
  	else
      (*params).diff = 5;
  	get_next_line(fd, &buf);
  	ft_strdel(&buf);
 	while (i < (*params).x_board)
 	{
   		
    	get_next_line(fd, &buf);
   		board_print(params, buf);
    	ft_printf("%s%c%s", "\x1b[1;47m\x1b[?25l", '\n', "\x1b[0m");
   		i++;
    	ft_strdel(&buf);
  	}
	ft_strdel(&buf);
	nanosleep (&tw, &tr);
}

int main()
{
	int fd;
	char *buf;
	t_params params;
	
	fd = 0;
	buf = NULL;
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
		if (ft_strstr(buf, "fin"))
		{
			fin_display(buf, fd);
        	return (0);
		}
		if (ft_strstr(buf, "Plateau"))
		{
			coords_parsing(&params.x_board, &params.y_board, buf);
			board_display(&params, buf, fd);
		}
	}
}