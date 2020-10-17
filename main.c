/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:58:15 by aes-salm          #+#    #+#             */
/*   Updated: 2020/10/17 14:20:26 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_struct(t_struct *data)
{
	data->px = 10 * SQUARE;
	data->py = 2 * SQUARE;
    data->walk_direction = 0;
    data->move_speed = SQUARE / 25;
    data->turn_direction = 0;
    data->turn_speed = 0.0000000005F;
    data->rotation = PI / 2;
    data->rotation_speed = 0.04f;
}

int    texture_handle(t_struct *data)
{
    int tx;

    texture[0].path = file.no_texture;
    texture[1].path = file.so_texture;
    texture[2].path = file.we_texture;
    texture[3].path = file.ea_texture;
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
    // if (!(data->window_id = mlx_new_window(data->connection_id, WINDOW_WIDTH, WINDOW_HIGHT, "Cub3d")))
    //     return (0);
	// if (!(data->image = mlx_new_image(data->connection_id, file.window_w_td, file.window_h_td)))
	//  	return (0);
	// if (!(data->img_matrix = (int*)mlx_get_data_addr(data->image, &data->bits_per_pixel, &data->size_line, &data->endian)))
	//  	return (0);

    if (!(data->window_id = mlx_new_window(data->connection_id, file.window_w_td, file.window_h_td, "Cub3d")))
       return (0);
	if (!(data->image_td = mlx_new_image(data->connection_id, file.window_w_td, file.window_h_td)))
	 	return (0);
	if (!(data->img_matrix_td = (int*)mlx_get_data_addr(data->image_td, &data->bits_per_pixel, &data->size_line, &data->endian)))
	 	return (0);


//////////// Texture ////////
    if (texture_handle(data))
    {
        write(1, "Error\nTexture Error !!\n", 23);
        exit_cub(EXIT_FAILURE);
    }
//////////// Texture //////
	mlx_hook(data->window_id, 2, 0, keypress, data);
    mlx_hook(data->window_id, 3, 0, keyrelease, data);
    mlx_loop_hook(data->connection_id, update, data);
    mlx_loop(data->connection_id);
    return (0);
}

int     main(int argc, char **argv)
{
    if (argc != 2)
    {
        write(1, "Error\nYou have to add a file '.cub' as a parameter !!\n", 54);
        exit(EXIT_FAILURE);
    }
    t_struct *data;

    if (!(data = (t_struct*)malloc(sizeof(t_struct))))
        return (0);
//////////// Reading From File ////////
    file_handle(argv[1]);
    rays = (t_rays *)malloc(sizeof(t_rays) * file.window_w_td);

    // printf("------- R -------\n");
	// printf("%d\n", file.window_w_td);
	// printf("%d\n", file.window_h_td);
	// printf("------- T -------\n");
	// printf("%s\n", file.no_texture);
	// printf("%s\n", file.so_texture);
	// printf("%s\n", file.we_texture);
	// printf("%s\n", file.ea_texture);
	// printf("%s\n", file.sprite_texture);
	// printf("------- F -------\n");
	// printf("%d\n", file.floor_color);
	// printf("------- C -------\n");
	// printf("%d\n", file.sky_color);
	// printf("------- M -------\n");
    
	printf("%d\n", file.num_rows);
	printf("%d\n", file.num_cols);

	int i = 0;
	while (i < file.num_rows)
	{
		printf("%s", file.map[i]);
		printf("\n");
		i++;
	}
    
//////////// Reading From File ////////
    init_struct(data);
    start_program(data);
    return (EXIT_SUCCESS);
}
