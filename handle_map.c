/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 15:04:58 by aes-salm          #+#    #+#             */
/*   Updated: 2020/10/17 14:11:57 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     line_len(char *data)
{
    int len;
    int i;

    len = 0;
    i = file.i;
    while (data[i] != '\n' && data[i])
    {
        len++;
        i++;
    }
    return (len);
}

int     num_of_rows(char *data)
{
    int i;
    int rows;

    rows = 1;
    i = file.i;
    while (data[i])
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
    int j;

    i = 0;
    while (i < file.num_rows)
    {
        j = 0;
        while (j < file.num_cols)
        {
            if (file.map[i][j] != '1' && file.map[i][j] != '0')
                file.map[i][j] = '.';
            j++;
        }
        file.map[i][j] = '\0';
        i++;
    }
}

void    handle_map(char *data)
{
    int row_len;
    int i;

    i = 0;
    while (data[file.i] == '\n')
        file.i++;
    file.num_rows = num_of_rows(data);
    file.map = (char **)malloc(file.num_rows * sizeof(char*));
    while (i < file.num_rows)
    {
        row_len = line_len(data);
        file.num_cols = (file.num_cols < row_len) ? row_len : file.num_cols;
        i++;
    }
    i = 0;
    while (i < file.num_rows)
        file.map[i++] = (char *)malloc(file.num_cols * sizeof(char));
    fill_map(data);
    my_bzero();
	handle_map_error();
}
