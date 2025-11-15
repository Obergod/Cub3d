/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:16:48 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/15 18:38:01 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "../minilibx-linux/mlx.h"
# include "parsing.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDHT 1280
# define HEIGHT 720
# define PI 3.141592653
# define BLOCKSIZE 64
# define SKY_COLOR 0x87CEEB
# define FLOOR_COLOR 0x006400
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_rect
{
	int			x;
	int			y;
	int			w;
	int			h;
}				t_rect;

typedef struct s_player
{
	float		x;
	float		y;
	float		angle;
	bool		key_up;
	bool		key_down;
	bool		key_right;
	bool		key_left;
	bool		left_rotate;
	bool		right_rotate;
}				t_player;

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_len;
	int			endian;
}				t_texture;

typedef struct s_ray
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_x;
	double		delta_y;
	double		wall_dist;
	double		wall_x;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
	int			tex_id;
}				t_ray;

typedef struct s_column
{
	int			height;
	int			start;
	int			end;
	int			tex_x;
	double		step;
	double		tex_pos;
}				t_column;

typedef struct s_game
{
	char		*data;
	int			bpp;
	int			size_line;
	int			nb_column;
	int			nb_lines;
	int			endian;
	t_player	player;
	int			ceiling_color;
	int			floor_color;
	t_texture	textures[4];
	t_cub		*cub;
	char		**map;
}				t_game;

void			init_player(float x, float y, float angle, t_player *player);
int				key_press(int keycode, t_player *player);
int				key_release(int keycode, t_player *player);
int				key_exit_hook(int keycode, t_game *game);
void			move_player(t_player *player, t_game *game);
bool			is_blocked(float px, float py, t_game *game);

int				load_wall_textures(t_game *game);
void			destroy_textures(t_game *game);
int				init_colors(t_game *game);

int				create_window(t_game *game);
void			clean_window(t_game *game);

void			put_pixel(int x, int y, int color, t_game *game);
void			clear_image(t_game *game);
int				get_texture_color(t_texture *tex, int x, int y);
void			prepare_column(t_column *col, t_ray *ray, t_texture *tex);
void			draw_wall_segment(t_game *game, t_texture *tex, t_column *col,
					int column);
void			draw_ceiling(t_game *game, int column, int end);
void			draw_floor(t_game *game, int column, int start);

void			draw_minimap(t_game *game, t_player *player);
void			render_frame(t_game *game);

int				init_game(t_game *game);
void			set_map_data(t_game *game);
int				draw_loop(t_game *game);
int				close_window(t_game *game);

void			init_ray(t_ray *ray, t_player *player, double angle);
void			step_ray(t_ray *ray, t_game *game);
void			resolve_ray(t_ray *ray);

#endif
