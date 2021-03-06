void	coord_push_back(int x, int y, t_coordinate **coords)
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
	if (!list)
	{
		*coords = oneelem;
		return ;
	}
	while (list->next)
		list = list->next;
	list->next = oneelem;
}

int		figure_size(t_params *params, int i)
{
	int j;
	int count;

	count = 0;
	while (i < (*params).x_figure)
	{
		j = 0;
		while (j < (*params).y_figure)
		{
			if ((*params).figure[i][j] == '*')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	board_making(char *buf, int fd, t_params *params)
{
	int i;
	int j;
	int k;

	coords_parsing(&params->x_board, &params->y_board, buf);
	(*params).board = two_dim_arr_mem((*params).board,
		(*params).x_board, (*params).y_board, '\0');
	ft_strdel(&buf);
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

int		figure_making(char *buf, int fd, t_params *params)
{
	int i;

	coords_parsing(&params->x_figure, &params->y_figure, buf);
	(*params).figure = two_dim_arr_mem((*params).figure, (*params).x_figure,
		(*params).y_figure, '\0');
	ft_strdel(&buf);
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

int		main(void)
{
	t_params	params;

	struct_initiation(&params);
	while (get_next_line(0, &params.buf) > 0)
	{
		if (ft_strstr(params.buf, "p2") && ft_strstr(params.buf, "vlikhotk"))
		{
			params.player_number = 'X';
			params.oppos_number = 'O';
			ft_strdel(&params.buf);
			continue ;
		}
		if (ft_strstr(params.buf, "Plateau"))
		{
			board_making(params.buf, 0, &params);
			continue ;
		}
		if (ft_strstr(params.buf, "Piece"))
		{
			if (!figure_making(params.buf, 0, &params))
				return (0);
			continue;
		}
		ft_strdel(&params.buf);
	}
}
