/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:16:48 by ufalzone          #+#    #+#             */
/*   Updated: 2025/07/08 16:59:42 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"

#include <stdio.h>
#include <stdbool.h>

#define WIDHT 1280
#define HEIGHT 720
# define W 119
#define A 97
#define S 115
#define D 100

#define PI 3.141592653

typedef struct s_game
{
    void *mlx;
    void *win;
    void *img;
    char *data;
    int bpp;
    int size_line;
    int endian;
} t_game;

typedef struct s_player
{
    float x;
    float y;
    bool key_up;
    bool key_down;
    bool key_right;
    bool key_left;
} t_player; 