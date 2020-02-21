/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:38:20 by aes-salm          #+#    #+#             */
/*   Updated: 2020/02/21 22:58:47 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct	s_struct
{
	void *window_id;
	void *connection_id;

	float		px;
	float		py;
	float		walk_direction;
	float		move_speed;
	float		turn_direction;
	float		turn_speed;
	float		rotation;
}				t_struct;

# define SQUARE 40
# define WINDOW_WIDTH SQUARE * 29
# define WINDOW_HIGHT SQUARE * 14

# define PI 3.142

# define W 13
# define S 1
# define A 0
# define D 2
# define ESC 53
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123

void	draw_map(t_struct *data);
void draw_player(t_struct *data);
int		update(t_struct *data);
int		keypress(int keycode, t_struct *data);
int		keyrelease(int keycode, t_struct *data);

#endif
