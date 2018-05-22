/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 13:24:07 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/01/15 11:05:52 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	swap_and_join(char **tmp, char *buf)
{
	char *swap;

	swap = NULL;
	swap = *tmp;
	*tmp = ft_strjoin(swap, buf);
	if (swap[0])
		ft_strdel(&swap);
}

void	if_next(char **line, char **tmp, char **next_s, int i)
{
	char	*rem;

	while ((*next_s)[i] != '\n' && (*next_s)[i] != '\0')
		i++;
	if ((*next_s)[i] == '\n')
	{
		*line = ft_strsub((*next_s), 0, i);
		if (i != (int)ft_strlen((*next_s)) && (*next_s)[i + 1])
		{
			rem = (*next_s);
			(*next_s) = ft_strsub((*next_s), i + 1, ft_strlen((*next_s)) - i);
			ft_strdel(&rem);
		}
		else
		{
			if ((*next_s))
				ft_strdel(next_s);
		}
	}
	else
	{
		swap_and_join(tmp, (*next_s));
		ft_strdel(next_s);
	}
}

int		if_n_found(char *buf, char **tmp, int ret, char **all_fd)
{
	int		i;
	char	*rem;

	i = 0;
	rem = NULL;
	while (i < ret && buf[i] != '\n')
		i++;
	if ((buf[i] == '\n' || (i == ret && i != BUFF_SIZE)))
	{
		rem = ft_strsub(buf, 0, i);
		swap_and_join(tmp, rem);
		ft_strdel(&rem);
		if ((ret - i - 1) > 0)
		{
			rem = *all_fd;
			*all_fd = ft_strsub(buf, i + 1, ret - i - 1);
			ft_strdel(&rem);
		}
		return (1);
	}
	return (0);
}

int		reading(char **line, char **all_fd, char **tmp, int fd)
{
	int		i;
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*swap;

	swap = NULL;
	while ((ret = read(fd, &buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = 0;
		if ((i = if_n_found(buf, tmp, ret, &all_fd[fd])))
		{
			if (i == ret)
				ft_strdel(all_fd);
			*line = *tmp;
			return (1);
		}
		else
			swap_and_join(tmp, buf);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	int					res;
	char				*tmp;
	char				*buf;
	int fd2;
	static char			*all_fd[FD_LIMIT];

	res = 0;
	fd2 = open("123", O_WRONLY);
	tmp = (char*)malloc(sizeof(char));
	tmp = "";
	buf = NULL;
	if (fd < 0 || fd > FD_LIMIT || BUFF_SIZE < 1 || BUFF_SIZE > STACK_LIMIT ||
		!line || read(fd, NULL, 0) < 0)
		return (-1);
	*line = NULL;
	if (all_fd[fd])
	{
		// printf("ok4\n");
		if_next(line, &tmp, &all_fd[fd], res);
	}
	// printf("ok\n");

	if (*line)
		return (1);
	res = reading(line, all_fd, &tmp, fd);
	if (tmp[0] != 0)
	{
		*line = tmp;
		return (1);
	}
	// printf("ok1\n");
	return (res);
}

int main()
{
	char *line;
	line =NULL;
	int fd = open("1", O_RDONLY);
	while (get_next_line(0, &line))
	{
		printf("%s\n", line);
		ft_strdel(&line);
	}
	return (0);
}
/*#include "get_next_line.h"
#include <fcntl.h>

char	*ft_realoc(char *save, int i, char *line)
{
	char	*new;
	int		j;
	int		k;

	new = NULL;
	if (!save)
	{
		if (!(new = (char*)malloc(sizeof(char) * (i + 1))))
			return (NULL);
	}
	else if (!(new = (char*)malloc(sizeof(char) * (ft_strlen(save) + i + 1))))
		return (NULL);
	j = 0;
	if (save)
		while (save[j] != '\0')
		{
			new[j] = save[j];
			++j;
		}
	k = 0;
	while (k < i)
		new[j++] = line[k++];
	new[j] = '\0';
	ft_strdel(&save);
	return (new);
}

char	*ft_re_save(char *save, int i)
{
	char *new;

	if (save[i] == '\0')
	{
		ft_strdel(&save);
		return (ft_strdup("\0"));
	}
	new = ft_strdup(&save[i + 1]);
	ft_strdel(&save);
	return (new);
}

void	ft_new_fd(t_list **l, int fd, t_list **new)
{
	t_list *head;

	if (*l)
	{
		if (fd != (int)((*l)->content_size))
		{
			head = *l;
			while (head != NULL)
			{
				if ((int)(head->content_size) == fd && (*new = head))
					return ;
				head = head->next;
			}
			*new = ft_lstnew(NULL, 0);
			(*new)->content_size = fd;
			ft_lstadd(l, *new);
		}
		else
			*new = *l;
		return ;
	}
	*l = ft_lstnew(NULL, 0);
	(*l)->content_size = fd;
	*new = *l;
}

int		ft_gnl(t_list **s, int fd)
{
	char	*buf;
	int		i;

	buf = NULL;
	if ((*s)->content == NULL || !ft_strchr((char*)((*s)->content), '\n'))
	{
		if (!(buf = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
			return (-1);
		while ((i = read(fd, buf, BUFF_SIZE)) > 0)
		{
			buf[i] = '\0';
			(*s)->content = (void*)ft_realoc((char*)((*s)->content), i, buf);
			if (ft_strchr(buf, '\n') != NULL)
				break ;
		}
		ft_strdel(&buf);
		if (((*s)->content && ((char*)((*s)->content))[0] == '\0' && i == 0) ||
			(!((*s)->content) && i == 0))
			return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	t_list			*s;
	static t_list	*list = NULL;
	char			*buf;
	int				i;

	if (fd < 0 || line == NULL || read(fd, NULL, 0) < 0)
		return (-1);
	ft_new_fd(&list, fd, &s);
	i = ft_gnl(&s, fd);
	if (i <= 0)
		return (i);
	i = 0;
	while (((char*)(s->content))[i] != '\n' && ((char*)(s->content))[i] != 0)
		++i;
	buf = ft_strnew(i + 1);
	i = -1;
	while (((char*)(s->content))[++i] != '\n' && ((char*)(s->content))[i] != 0)
		buf[i] = ((char*)(s->content))[i];
	buf[i] = '\0';
	*line = buf;
	s->content = ft_re_save((char*)(s->content), i);
	return (1);
}*/
