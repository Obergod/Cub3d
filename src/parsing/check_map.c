/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:09:02 by mafioron          #+#    #+#             */
/*   Updated: 2025/07/08 16:09:03 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	check_map(char **cub)
{
	char	**map;
	int		err;
	int		i;
	int		j;
	char	c;

	i = -1;
	err = 0;
	map = ft_2dstrdup(cub + 6);
	if (!map)
		return (-1);
	while (map[++i])
	{
		j = 0;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' || 
					map[i][j] == 'S' || map[i][j] == 'E')
			{
				c = map[i][j];
				err++;
			}
			else if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' ')
				return (free(map), 1);
		}
	}
	if (err != 1)
		return (free(map), 1);
	err = check_wall(map, c);
	if (err != 0)
		return (free(map), err);
	return (0);
}

int	check_wall(char **map, char c)
{
	int	row;
	int	col;
	char	**flood_map;
	// put in struct in a good way later
	bool	is_valid_map = true;

	// Maybe isolate the map from the texture here ? ex : map + 5
	flood_map = ft_2dstrdup(map);
	if (!flood_map)
		return (-1);
	col = -1;
	row = 0;
	while (map[++col])
	{
		row = 0;
		while (map[col][row] && map[col][row] != c)
			row++;
		if (map[col][row] == c)
			break ;
	}
	if (flood_map[col] && flood_map[col][row])
		flood_map[col][row] = '0';
	flood_fill(flood_map, row, col, &is_valid_map);
	ft_free_split(flood_map);
	if (is_valid_map == false)
	{
		ft_free_split(map);
		return (1);
	}
	return (0);
}

void	flood_fill(char **map, int row, int col, bool *is_valid)
{
	if (row < 0 || col < 0 || !map[col] || !map[col][row])
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
