/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:32:14 by aes-salm          #+#    #+#             */
/*   Updated: 2020/02/21 22:59:01 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int update(t_struct *data)
{
    mlx_clear_window(data->connection_id, data->window_id);
    draw_map(data);
    draw_player(data);
    return (0);
}