/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:50:08 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/10 20:47:59 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include <fcntl.h>

static t_cub	*parsing_error(void)
{
	printf("Error\n");
	return (NULL);
}

static int	open_config(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		printf("Error\n");
	return (fd);
}

static t_cub	*init_parsing(int ac, char **av)
{
	int		fd;
	t_cub	*vars;

	if (ac != 2)
		return (parsing_error());
	if (!strstr(av[1], ".cub"))
		return (parsing_error());
	fd = open_config(av[1]);
	if (fd < 0)
		return (NULL);
	vars = inits();
	if (!vars)
	{
		free_cub(vars);
		return (parsing_error());
	}
	if (check_errors(fd, vars) == 1)
	{
		free_cub(vars);
		return (parsing_error());
	}
	printf("Tout est bon!");
	return (vars);
}

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->cub->win, 2, 1L << 0, key_exit_hook, game);
	mlx_hook(game->cub->win, 3, 1L << 1, key_release, &game->player);
	mlx_hook(game->cub->win, 17, 0, close_window, game);
	mlx_loop_hook(game->cub->mlx, draw_loop, game);
}

int	main(int ac, char **av)
{
	t_game	game;
	t_cub	*vars;

	ft_memset(&game, 0, sizeof(t_game));
	vars = init_parsing(ac, av);
	if (!vars)
		return (1);
	game.cub = vars;
	if (init_game(&game) != 0)
	{
		mlx_destroy_display(game.cub->mlx);
		free_cub(game.cub);
		return (1);
	}
	setup_hooks(&game);
	mlx_loop(game.cub->mlx);
	return (0);
}
