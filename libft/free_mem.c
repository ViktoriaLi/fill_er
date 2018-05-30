/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 13:33:48 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/30 13:34:24 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	**free_mem(char **field, int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		free(field[i]);
		field[i] = NULL;
		i++;
	}
	free(field);
	field = NULL;
	return (field);
}
