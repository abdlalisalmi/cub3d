/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:58:15 by aes-salm          #+#    #+#             */
/*   Updated: 2020/10/26 19:29:17 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_struct(t_struct *data)
{
	data->px = file.py * SQUARE;
	data->py = file.px * SQUARE;
    data->walk_direction = 0;
    data->move_speed = SQUARE / (SQUARE / 50);
    data->turn_direction = 0;
    data->turn_speed = 0.0000000005F;
    data->rotation = PI / file.player_view ;
    data->rotation_speed = 0.04f;
    data->side = 0;
}

int    texture_handle(t_struct *data)
{
    int tx;

    texture[0].path = file.no_texture;
    texture[1].path = file.so_texture;
    texture[2].path = file.ea_texture;
    texture[3].path = file.we_texture;
    texture[4].path = file.sprite_texture;
    tx = 0;
    while (tx < 5)
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

    // if (!(data->window_id = mlx_new_window(data->connection_id, file.window_w_td, file.window_h_td, "Cub3d")))
    //     return (0);
	// if (!(data->image = mlx_new_image(data->connection_id, (SQUARE * file.num_cols), (SQUARE * file.num_rows))))
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
        write(1, "Error\nSomething wrong with the Textures !!\n", 45);
        exit_cub(EXIT_FAILURE);
    }
//////////// Texture //////
    
	mlx_hook(data->window_id, 2, 0, keypress, data);
    mlx_hook(data->window_id, 3, 0, keyrelease, data);
    mlx_loop_hook(data->connection_id, update, data);
    mlx_loop(data->connection_id);
    return (0);
}

int     file_etantion_check(char *filename, char *ext, char split)
{
    char *point;

    if((point = ft_strrchr(filename, split)) != NULL ) {
        if(ft_strncmp(point, ext, ft_strlen(filename)) == 0)
            return (1);
    }
    return (0);
}

int     main(int argc, char **argv)
{
    if (argc < 2 || argc > 3)
    {
        write(1, "Error\nYou have more than 3 parameters or less than 1 !!\n", 58);
        exit(EXIT_FAILURE);
    }
    else
    {
        if (!file_etantion_check(argv[1], ".cub", '.'))
        {
            write(1, "Error\nYou have to add a file '.cub' as a parameter !!\n", 54);
            exit(EXIT_FAILURE);
        }
        if (argc == 3 && file_etantion_check(argv[2], "-save", '-'))
            file.save_flag = 1;
        else if (argc == 3 && !file_etantion_check(argv[2], "-save", '-'))
        {
            write(1, "Error\nYou have to add a valid flag like --save !!\n", 52);
            exit(EXIT_FAILURE);
        }
    }
    

    

    if (!(data = (t_struct*)malloc(sizeof(t_struct))))
        return (0);
//////////// Reading From File ////////
    file_handle(argv[1]);
    rays = (t_rays *)malloc(sizeof(t_rays) * file.window_w_td);
    sprites = (t_sprites *)malloc(sizeof(t_sprites) * file.number_of_sprites);

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
    


	// int i = 0;
	// while (i < file.num_rows)
	// {
	// 	printf("%s", file.map[i]);
	// 	printf("\n");
	// 	i++;
	// }
	// printf("rows : %d\n", file.num_rows);
	// printf("coloms : %d\n", file.num_cols);
    
    // printf("%d\n", file.px);
    // printf("%d\n", file.py);
//////////// Reading From File ////////
    file_components_check();
    init_struct(data);
    init_sprites();
    // printf("%d\n", file.save_flag);
    start_program(data);
    return (EXIT_SUCCESS);
}
