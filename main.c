/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:58:15 by aes-salm          #+#    #+#             */
/*   Updated: 2020/02/26 20:51:44 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_struct(t_struct *data)
{
	data->px = 14 * 40;
	data->py = 3 * 40;
    data->walk_direction = 0;
    data->move_speed = 10;
    data->turn_direction = 0;
    data->turn_speed = 0.09f;
    data->rotation = PI / 2;
    data->rotation_speed = 0.1f;
    data->ray_angle = 0;
    data->wall_hit_X = 0;
    data->wall_hit_Y = 0;
    data->wall_distance = 0;
    data->ray_facing_up = 0;
    data->ray_facing_down = 0;
    data->ray_facing_R = 0;
    data->ray_facing_L = 0;
    data->distance = 0;

}

int    start_program(t_struct *data)
{
    if (!(data->connection_id = mlx_init()))
        return (0);
    if (!(data->window_id = mlx_new_window(data->connection_id, WINDOW_WIDTH, WINDOW_HIGHT, "Cub3d")))
        return (0);
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
// esc 53
//  126
//123 124
//  125
