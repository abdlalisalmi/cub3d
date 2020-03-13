/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:58:15 by aes-salm          #+#    #+#             */
/*   Updated: 2020/03/13 11:41:53 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_struct(t_struct *data)
{
	data->px = 14 * SQUARE;
	data->py = 3 * SQUARE;
    data->walk_direction = 0;
    data->move_speed = SQUARE / 12;
    data->turn_direction = 0;
    data->turn_speed = 0.0000000005F;
    data->rotation = PI / 2;
    data->rotation_speed = 0.1f;
}

int    texture_handle(t_struct *data)
{
    int tx;

    texture[0].path = "./src/texture/tx0.xpm";
    texture[1].path = "./src/texture/tx1.xpm";
    texture[2].path = "./src/texture/tx2.xpm";
    texture[3].path = "./src/texture/tx3.xpm";
    tx = 0;
    while (tx < 4)
    {
        if (!(texture[tx].img = mlx_xpm_file_to_image(data->connection_id,
                    texture[tx].path, &texture[tx].width, &texture[tx].height)))
            return (1);
        if (!(texture[tx].colors = (int*)mlx_get_data_addr(texture[tx].img,
                    &texture[tx].a,&texture[tx].b,&texture[tx].c)))
            return (1);
        tx++;
    }
    return (0);
}

int    start_program(t_struct *data)
{
    if (!(data->connection_id = mlx_init()))
        return (0);
    if (!(data->window_id = mlx_new_window(data->connection_id, WINDOW_W_TD, WINDOW_H_TD, "Cub3d")))
        return (0);

	if (!(data->image = mlx_new_image(data->connection_id, WINDOW_WIDTH, WINDOW_HIGHT)))
	 	return (0);
	if (!(data->img_matrix = (int*)mlx_get_data_addr(data->image, &data->bits_per_pixel, &data->size_line, &data->endian)))
	 	return (0);

	if (!(data->image_td = mlx_new_image(data->connection_id, WINDOW_W_TD, WINDOW_H_TD)))
	 	return (0);
	if (!(data->img_matrix_td = (int*)mlx_get_data_addr(data->image_td, &data->bits_per_pixel, &data->size_line, &data->endian)))
	 	return (0);
////////////
    if (texture_handle(data))
    {
        write(1, "Error\nTexture Error !!", 22);
        return (1);
    }
////////////
	mlx_hook(data->window_id, 2, 0, keypress, data);
    mlx_hook(data->window_id, 3, 0, keyrelease, data);
    mlx_loop_hook(data->connection_id, update, data);
    mlx_loop(data->connection_id);
    return (0);
}

int     main()
{
    t_struct *data;

    if (!(data = (t_struct*)malloc(sizeof(t_struct))))
        return (0);
    init_struct(data);
    start_program(data);
    return (EXIT_SUCCESS);
}
