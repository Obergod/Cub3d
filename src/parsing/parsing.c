/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:08:00 by mafioron          #+#    #+#             */
/*   Updated: 2025/06/30 17:08:02 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

char	**split_all_file(int fd)
{
	char	*line;
	char	*stock;
	char	**cub;

	stock = NULL;
	if (fd < 0)
		return (NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		stock = stock_extend(stock, line);
		if (!stock)
			return (NULL);
	}
	cub = ft_split(stock, '\n');
	if (!cub)
		return (NULL);
	return (cub);
}

int	check_errors(int fd)
{
	char	**cub;

	cub = split_all_file(fd);
	if (!cub)
		return (1);
	if (check_textures(cub) == 1)
		return (1);
	return (0);
}

int	check_textures(char **cub)
{
	int	 i;

	i = 0;
	while (cub[i])
		i++;
	if (i < 6)
		return (1);
	if (strncmp(cub[0], "NO ", 3) != 0)
		return (1);
	if (strncmp(cub[1], "SO ", 3) != 0)
		return (1);
	if (strncmp(cub[2], "WE ", 3) != 0)
		return (1);
	if (strncmp(cub[3], "EA ", 3) != 0)
		return (1);
	if (strncmp(cub[4], "F ", 2) != 0)
		return (1);
	if (strncmp(cub[5], "C ", 2) != 0)
		return (1);
	return (0);
}

// faire un flood fill remplant les zeros par des x, si un x est colle a un espace
// ou un out of bound = map kk

int	check_map(char **map, int x, int y)
{
	if (x < 0 || y < 0)
		return ;
	check_map(map[y][x], x + 1, y)
}

int	main(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		return (printf("Error\n"), 1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	if (check_errors(fd) == 1)
		printf("Error textures\n");
	return (0);
}
