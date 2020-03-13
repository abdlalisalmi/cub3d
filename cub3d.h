/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:38:20 by aes-salm          #+#    #+#             */
/*   Updated: 2020/03/13 22:01:04 by aes-salm         ###   ########.fr       */
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
# include <fcntl.h>

# define SQUARE 400
# define NUM_ROWS 25
# define NUM_COLS 25
# define WINDOW_WIDTH SQUARE * NUM_COLS
# define WINDOW_HIGHT SQUARE * NUM_ROWS

# define WINDOW_W_TD 1920
# define WINDOW_H_TD 1080


# define PI 3.14159265358979323846
# define FOV_ANGLE 60 * (PI / 180)
# define NUM_RAYS WINDOW_W_TD

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

typedef struct	s_struct
{
	void	*window_id;
	void	*connection_id;

	void	*image;
	int		*img_matrix;

	void	*image_td;
	int		*img_matrix_td;

	int		bits_per_pixel;
	int		size_line;
	int		endian;

	float		px;
	float		py;
	float		walk_direction;
	float		move_speed;
	float		turn_direction;
	float		turn_speed;
	float		rotation;
	float		rotation_speed;

}				t_struct;

typedef struct	s_rays
{
	float		ray_angle;
	float		wall_hit_X;
	float		wall_hit_Y;
	float		wall_distance;
	int			was_hit_vertical;
	int			ray_facing_up;
	int			ray_facing_down;
	int			ray_facing_R;
	int			ray_facing_L;
}				t_rays;
t_rays rays[NUM_RAYS];

typedef struct	s_tr_project
{
	float	real_distance;
	float	distance_project_plane;
	float	project_wall_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
}				t_tr_project;
t_tr_project	tr_project;

typedef struct s_texture
{
	void *img;
	char *path;
	int *colors;
	int width;
    int height;
	int a;
	int b;
	int c;

	int color;
	int *wall;
}				t_texture;
t_texture		texture[4];

typedef struct s_file
{
	int i;
	int num_rows;
	int num_cols;
	int window_heigth;
	int window_width;
	
	int window_w_td;
	int window_h_td;
}				t_file;
t_file			file;


void	draw_map(t_struct *data);
void	draw_player(t_struct *data);
void	draw_rays(t_struct *data);
int		update(t_struct *data);
int		keypress(int keycode, t_struct *data);
int		keyrelease(int keycode, t_struct *data);
int		wall_check(float x, float y);
float   distance_between_points(float x1, float y1, float x2, float y2);
float   normalize_angle(float angle);
void	draw_td_project(t_struct *data);

void	file_handle();
void	handle_resolution(char *data);
#endif
