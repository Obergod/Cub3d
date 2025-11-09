/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:16:48 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/07 16:27:39 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "parsing.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define WIDHT 1280
#define HEIGHT 720
#define FOV (PI / 3.0)
# define W 119
#define A 97
#define S 115
#define D 100
#define LEFT 65361
#define RIGHT 65363

#define PI 3.141592653
#define BLOCKSIZE 64
#define MINIMAP_BLOCKSIZE (BLOCKSIZE / 4)
#define MINI_FACTOR ((float)MINIMAP_BLOCKSIZE / BLOCKSIZE)

#define SKY_COLOR  0x87CEEB
#define FLOOR_COLOR 0x006400

typedef struct s_player
{
    float x;
    float y;
    float angle;

    bool key_up;
    bool key_down;
    bool key_right;
    bool key_left;

    bool left_rotate;
    bool right_rotate;
} t_player; 

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_ray
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_x;
	double	delta_y;
	double	wall_dist;
	double	wall_x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		tex_id;
}	t_ray;

typedef struct s_column
{
	int		height;
	int		start;
	int		end;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_column;

typedef struct s_game
{
    char *data;
    int bpp;
    int size_line;
    int nb_column;
    int nb_lines;
    int endian;
    t_player player;
	int ceiling_color;
	int floor_color;
	t_texture textures[4];
    t_cub *cub;
    char **map;
} t_game;

void init_player(float x, float y, float angle, t_player *player);
int key_press(int keycode, t_player *player);
int key_release(int keycode, t_player *player);
void move_player(t_player *player, t_game *game);
bool touch(float px, float py, t_game *game);
int	load_wall_textures(t_game *game);
int	init_colors(t_game *game);
void	destroy_textures(t_game *game);
void	init_ray(t_ray *ray, t_player *player, double angle);
void	step_ray(t_ray *ray, t_game *game);
void	resolve_ray(t_ray *ray);
