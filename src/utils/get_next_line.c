/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:03:13 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/25 09:02:27 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int			find_nl(char *tmp)
{
	int i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static void			del_new_line(char **tmp, char **line, char **rest)
{
	int		nl;
	char	*sub_tmp;

	nl = find_nl(*tmp);
	*rest = get_strdup(&tmp[0][nl + 1]);
	sub_tmp = get_substr(*tmp, 0, nl);
	*line = get_strjoin(line, sub_tmp);
	free_all(&sub_tmp);
	free_all(tmp);
}

static int			rest_not_empty(char **rest, char **line, char **tmp)
{
	if (find_nl(*rest) > -1)
	{
		free_all(tmp);
		*tmp = *rest;
		del_new_line(tmp, line, rest);
		return (1);
	}
	else
	{
		*line = get_strjoin(line, *rest);
		free_all(rest);
	}
	return (0);
}

int					get_next_line(int fd, char **line)
{
	static char		*rest;
	char			*tmp;
	int				char_read;

	if (fd < 0 || BUFFER_SIZE < 0 || BUFFER_SIZE > 2147483647 ||
		!(tmp = malloc(BUFFER_SIZE + 1)))
		return (-1);
	*line = get_strdup("");
	if (rest)
		if (rest_not_empty(&rest, line, &tmp))
			return (1);
	while ((char_read = read(fd, tmp, BUFFER_SIZE)) > 0)
	{
		tmp[char_read] = '\0';
		if (find_nl(tmp) > -1)
		{
			del_new_line(&tmp, line, &rest);
			return (1);
		}
		*line = get_strjoin(line, tmp);
	}
	if (!char_read)
		free_all(&tmp);
	return (char_read > 0 ? 1 : char_read);
}
