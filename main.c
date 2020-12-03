/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:58:15 by aes-salm          #+#    #+#             */
/*   Updated: 2020/12/03 14:55:26 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_struct(void)
{
	g_data.px = (g_file.py + 0.5F) * SQUARE;
	g_data.py = (g_file.px + 0.5F) * SQUARE;
	g_data.walk_direction = 0;
	g_data.move_speed = SQUARE / (SQUARE / 50);
	g_data.turn_direction = 0;
	g_data.turn_speed = 0.0000000005F;
	g_data.rotation = PI / g_file.player_view;
	g_data.rotation_speed = 0.01f;
	g_data.side = 0;
}

int		texture_handle(void)
{
	int tx;

	g_texture[0].path = g_file.no_texture;
	g_texture[1].path = g_file.so_texture;
	g_texture[2].path = g_file.ea_texture;
	g_texture[3].path = g_file.we_texture;
	g_texture[4].path = g_file.sprite_texture;
    
    printf("\n");
    printf("%s\n", g_texture[0].path);
    printf("%s\n", g_texture[1].path);
    printf("%s\n", g_texture[2].path);
    printf("%s\n", g_texture[3].path);
    printf("%s\n", g_texture[4].path);
	tx = 0;
	while (tx < 5)
	{
		if (!(g_texture[tx].img = mlx_xpm_file_to_image(g_data.connection_id,
			g_texture[tx].path, &g_texture[tx].width, &g_texture[tx].height)))
			return (1);
		if (!(g_texture[tx].colors = (int*)mlx_get_data_addr(g_texture[tx].img,
			&g_texture[tx].a, &g_texture[tx].b, &g_texture[tx].c)))
			return (1);
		tx++;
	}
	return (0);
}

int		start_program(void)
{
	if (!(g_data.connection_id = mlx_init()))
		return (0);
	if (!(g_data.window_id = mlx_new_window(g_data.connection_id,
		g_file.window_w_td, g_file.window_h_td, "cub")))
		return (0);
	if (!(g_data.image_td = mlx_new_image(g_data.connection_id,
		g_file.window_w_td, g_file.window_h_td)))
		return (0);
	if (!(g_data.img_matrix_td = (int*)mlx_get_data_addr(g_data.image_td,
		&g_data.bits_per_pixel, &g_data.size_line, &g_data.endian)))
		return (0);
	if (texture_handle())
	{
		write(1, "Error\nSomething wrong with the Textures !!\n", 45);
		exit_cub(EXIT_FAILURE);
	}
	mlx_hook(g_data.window_id, 2, 0, keypress, 0);
	mlx_hook(g_data.window_id, 3, 0, keyrelease, 0);
	mlx_hook(g_data.window_id, 17, 1L << 17, destroy_window_button, 0);
	mlx_loop_hook(g_data.connection_id, update, 0);
	mlx_loop(g_data.connection_id);
	return (0);
}

int		main(int argc, char **argv)
{
	args_check(argc, argv);
	file_handle(argv[1]);

	// for (int i = 0; i < g_file.num_cols; i++)
	// {
	// 	printf("%s\n", g_file.map[i]);
	// }	

	// printf("WW: %d\n", g_file.window_w_td);
	// printf("WH: %d\n", g_file.window_h_td);
	// printf("NO: %s\n", g_file.no_texture);
	// printf("SO: %s\n", g_file.so_texture);
	// printf("WE: %s\n", g_file.we_texture);
	// printf("EA: %s\n", g_file.ea_texture);
	// printf("FLOOR: %d\n", g_file.floor_color);
	// printf("SKY: %d\n", g_file.sky_color);
	// printf("MAPTOUR: %d\n", g_file.map_tour);




	init_struct();
	start_program();
	return (EXIT_SUCCESS);
}
