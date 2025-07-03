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
		return (-1);
	if (check_textures(cub) == 1)
		return (1);
	//must check if nothing after map + gotta split map
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
// Need to check path and if colors are good
	return (0);
}

int	check_wall(char **map, char c, int i, int j)
{
	t_points size;
	int	row;
	int	col;
	char	**flood_map;
	// put in struct in a good way later
	bool	is_valid_map = true;

	// Maybe isolate the map from the texture here ? ex : map + 5
	flood_map = ft_2dstrdup(map);
	if (!flood_map)
		return (-1);
	row = -1;
	col = -1;
	size.y = i;
	size.x = j;
	while (map[col][row] != c)
	{
		col++;
		row++;
	}
	flood_map[col][row] = '0';
	flood_fill(flood_map, row, col, &is_valid_map);
	ft_free_split(flood_map);
	if (is_valid_map == false)
	{
		ft_free_split(map);
		return (1);
	}
}

void	flood_fill(char **map, int row, int col, bool *is_valid)
{
	if (row < 0 || col < 0 || !map[col][row])
	{
		*is_valid = false;
		return ;
	}
	if (map[col][row] == 'x' || map[col][row] == '1')
		return ;
	if (map[col][row] != '0')
	{
		*is_valid = false;
		return ;
	}
	map[col][row] = 'x';
	flood_fill(map, row + 1, col, is_valid);
	flood_fill(map, row - 1, col, is_valid);
	flood_fill(map, row, col + 1, is_valid);
	flood_fill(map, row, col - 1, is_valid);
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
