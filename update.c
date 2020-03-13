/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:32:14 by aes-salm          #+#    #+#             */
/*   Updated: 2020/03/12 18:28:52 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int update(t_struct *data)
{
	//draw_map(data);
	draw_td_project(data);
	draw_player(data);
	draw_rays(data);
	mlx_put_image_to_window(data->connection_id, data->window_id, data->image_td, 0, 0);
	//mlx_put_image_to_window(data->connection_id, data->window_id, data->image, 0, 0);
    return (0);
}