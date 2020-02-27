/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:38:20 by aes-salm          #+#    #+#             */
/*   Updated: 2020/02/26 21:17:51 by aes-salm         ###   ########.fr       */
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
	float		rotation_speed;

	float		ray_angle;
	float		wall_hit_X;
	float		wall_hit_Y;
	float		wall_distance;
	int			ray_facing_up;
	int			ray_facing_down;
	int			ray_facing_R;
	int			ray_facing_L;
	float		distance;

}				t_struct;

# define SQUARE 40
# define WINDOW_WIDTH SQUARE * 25
# define WINDOW_HIGHT SQUARE * 25

# define PI 3.14159265358979323846
# define FOV_ANGLE 60 * (PI / 180)
# define WALL_COLUME_WIDTH 15
# define NUM_RAYS (WINDOW_WIDTH / WALL_COLUME_WIDTH)

# define INT_MAX 2147483647

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
void	draw_player(t_struct *data);
void	draw_rays(t_struct *data);
int		update(t_struct *data);
int		keypress(int keycode, t_struct *data);
int		keyrelease(int keycode, t_struct *data);
int		wall_check(float x, float y);
float   distance_between_points(float x1, float y1, float x2, float y2);
float   normalize_angle(float angle);

#endif
