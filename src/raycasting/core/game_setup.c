/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:50:16 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/10 18:50:16 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static int init_image(t_game *game)
{
    game->cub->img = mlx_new_image(game->cub->mlx, WIDHT, HEIGHT);
    if (!game->cub->img)
        return (1);
    game->data = mlx_get_data_addr(game->cub->img, &game->bpp,
            &game->size_line, &game->endian);
    if (!game->data)
        return (1);
    return (0);
}

int create_window(t_game *game)
{
    clean_window(game);
    game->cub->win = mlx_new_window(game->cub->mlx, WIDHT, HEIGHT, "Cub3D");
    if (!game->cub->win)
        return (1);
    if (init_image(game) != 0)
    {
        clean_window(game);
        return (1);
    }
    mlx_put_image_to_window(game->cub->mlx, game->cub->win,
        game->cub->img, 0, 0);
    return (0);
}

void clean_window(t_game *game)
{
    if (game->cub->img)
    {
        mlx_destroy_image(game->cub->mlx, game->cub->img);
        game->cub->img = NULL;
    }
    if (game->cub->win)
    {
        mlx_destroy_window(game->cub->mlx, game->cub->win);
        game->cub->win = NULL;
    }
}

int init_game(t_game *game)
{
    set_map_data(game);
    if (load_wall_textures(game) != 0)
        return (1);
    if (init_colors(game) != 0)
    {
        destroy_textures(game);
        return (1);
    }
    if (create_window(game) != 0)
    {
        destroy_textures(game);
        return (1);
    }
    return (0);
}

int close_window(t_game *game)
{
    destroy_textures(game);
    clean_window(game);
    mlx_destroy_display(game->cub->mlx);
    free_cub(game->cub);
    exit(0);
    return (0);
}
