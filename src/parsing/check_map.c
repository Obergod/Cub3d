/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:09:02 by mafioron          #+#    #+#             */
/*   Updated: 2025/11/10 20:54:18 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static int	width_and_char(t_cub *cub, char **map)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	while (map[++i])
	{
		len = ft_strlen(map[i]);
		if (len > cub->map_width)
			cub->map_width = len;
		j = -1;
		while (map[i][++j])
			if (check_tile(cub, map, i, j))
				return (ft_free_split(map), 1);
	}
	cub->map_height = i;
	return (0);
}

int	check_map(char **cub_file, t_cub *cub)
{
	char	**map;
	int		err;

	map = ft_2dstrdup(cub_file + 6);
	if (!map)
		return (-1);
	if (width_and_char(cub, map) == 1)
		return (1);
	if (cub->player_dir == '\0')
		return (ft_free_split(map), 1);
	err = check_wall(map, cub->player_col, cub->player_row);
	if (err != 0)
		return (ft_free_split(map), err);
	cub->map = map;
	return (0);
}

int	check_wall(char **map, int row, int col)
{
	char	**flood_map;
	bool	is_valid_map;

	is_valid_map = true;
	flood_map = ft_2dstrdup(map);
	if (!flood_map)
		return (-1);
	if (row < 0 || col < 0 || !flood_map[col]
		|| (int)ft_strlen(flood_map[col]) <= row)
	{
		ft_free_split(flood_map);
		return (1);
	}
	flood_fill(flood_map, row, col, &is_valid_map);
	ft_free_split(flood_map);
	if (is_valid_map == false)
		return (1);
	return (0);
}

void	flood_fill(char **map, int row, int col, bool *is_valid)
{
	if (row < 0 || col < 0 || !map[col] || !map[col][row])
	{
		*is_valid = false;
		return ;
	}
	if (map[col][row] == 'x' || map[col][row] == '1' || map[col][row] == ' ')
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
