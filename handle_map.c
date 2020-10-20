/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 15:04:58 by aes-salm          #+#    #+#             */
/*   Updated: 2020/10/20 09:55:20 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     line_len(char *data)
{
    int len;

    len = 0;
    while (data[file.i] != '\n' && data[file.i])
    {
        len++;
        file.i++;
    }
    file.i++;
    return (len);
}

int     num_of_rows(char *data)
{
    int i;
    int rows;

    rows = 1;
    i = file.i;
    while (data[i] && data[i] != EOF)
    {
        if (data[i] == '\n')
            rows++;
        i++;
    }
    return (rows);
}

void    fill_map(char *data)
{
    int i;
    int j;

    i = 0;
    while (i < file.num_rows)
    {
        j = 0;
        while (j < file.num_cols && data[file.i] != '\n' && data[file.i] != EOF)
        {
            if (data[file.i] == 'N')
            {
                file.px = i;
                file.py = j;
            }
            if (data[file.i] != ' ')
                file.map[i][j] = data[file.i];
            j++;
            file.i++;
        }
        file.map[i][j] = '\0';
        if (data[file.i] == '\n')
            file.i++;
        i++;
    }
}

void    my_bzero()
{
    int i;

    i = 0;
    while (i < file.num_rows)
    {
        file.map[i] = ft_memset(file.map[i], '.', file.num_cols);
        i++;
    }
}

void    handle_map(char *data)
{
    int row_len;
    int i;
    int old_position;

    i = 0;
    while (data[file.i] == '\n')
        file.i++;
    file.num_rows = num_of_rows(data);
    file.map = (char **)malloc(file.num_rows * sizeof(char*));
    old_position = file.i;
    while (i < file.num_rows)
    {
        row_len = line_len(data);
        file.num_cols = (file.num_cols < row_len) ? row_len : file.num_cols;
        i++;
    }
    file.i = old_position;
    i = 0;
    while (i < file.num_rows)
        file.map[i++] = (char *)malloc(file.num_cols * sizeof(char));
    my_bzero();
    fill_map(data);
	// handle_map_error();
}
