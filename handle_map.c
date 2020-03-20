/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 15:04:58 by aes-salm          #+#    #+#             */
/*   Updated: 2020/03/19 14:11:59 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     line_len(char *data)
{
    int len;

    len = 0;
    while (data[file.i] != '\n' && data[file.i] != EOF)
    {
        len++;
        file.i++;
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

void    fill_map(char *data, int origin_i)
{
    int i;
    int j;

    file.i = origin_i;
    i = 0;
    while (i < file.num_rows)
    {
        j = 0;
        while (j < file.num_cols && data[file.i] != '\n')
        {
            file.map[i][j] = data[file.i];
            j++;
            file.i++;
        }
        if (data[file.i] == '\n')
            file.i++;
        i++;
    }
}

void    my_bzero(char *ptr)
{
    int i;

    i = 0;
    while (ptr[i])
    {
        ptr[i] = 's';
        i++;
    }
}

void    handle_map(char *data)
{
    int origin_i;
    int row_len;
    int i;

    i = 0;
    while (data[file.i] == '\n')
        file.i++;
    file.num_rows = num_of_rows(data);
    file.map = (char **)malloc(file.num_rows * sizeof(char*));
    origin_i = file.i;
    while (i < file.num_rows)
    {
        row_len = line_len(data);
        file.num_cols = (file.num_cols < row_len) ? row_len : file.num_cols;
        i++;
    }
    i = 0;
    while (i < file.num_rows)
        file.map[i++] = (char *)malloc(file.num_cols * sizeof(char));
    fill_map(data, origin_i);
}
