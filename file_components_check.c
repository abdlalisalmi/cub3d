/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_components_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 13:51:38 by aes-salm          #+#    #+#             */
/*   Updated: 2020/10/23 10:19:18 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_error_message(char *message)
{
    write(1, "Error\n", 7);
    write(1, message, ft_strlen(message));
    write(1, "\n", 1);
    exit(EXIT_FAILURE);
}

void file_components_check()
{
    if (!file.window_w_td || !file.window_h_td)
        print_error_message("You haven't added the resolution values properly !!");
    if (!file.floor_color)
        print_error_message("You haven't added the floor color value properly !!");
    if (!file.sky_color)
        print_error_message("You haven't added the sky color value properly !!");
    if (!file.no_texture[0] || !file.so_texture[0] || !file.we_texture[0] || !file.ea_texture[0])
        print_error_message("You haven't added the walls textures values properly !!");
    if (!file.sprite_texture[0])
        print_error_message("You haven't added the sprite texture value properly !!");
}