/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:09:02 by mafioron          #+#    #+#             */
/*   Updated: 2025/11/07 17:05:27 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	save_player(t_cub *cub, int row, int col, char dir)
{
	if (cub->player_dir != '\0')
		return (1);
	cub->player_row = row;
	cub->player_col = col;
	cub->player_dir = dir;
	return (0);
}

static int	check_tile(t_cub *cub, char **map, int row, int col)
{
	if (is_player(map[row][col]))
	{
		if (save_player(cub, row, col, map[row][col]))
			return (1);
		map[row][col] = '0';
		return (0);
	}
	if (map[row][col] == '0' || map[row][col] == '1' || map[row][col] == ' ')
		return (0);
	return (1);
}

int	check_map(char **cub_file, t_cub *cub)
{
	char	**map;
	int		err;
	int		i;
	int		j;
	int		len;

	i = -1;
	map = ft_2dstrdup(cub_file + 6);
	if (!map)
		return (-1);
	while (map[++i])
	{
		len = ft_strlen(map[i]);
		if (len > cub->map_width)
			cub->map_width = len;
		j = -1;
		while (map[i][++j])
			if (check_tile(cub, map, i, j))
			{
				ft_free_split(map);
				return (1);
			}
	}
	cub->map_height = i;
	if (cub->player_dir == '\0')
	{
		ft_free_split(map);
		return (1);
	}
	err = check_wall(map, cub->player_col, cub->player_row);
	if (err != 0)
	{
		ft_free_split(map);
		return (err);
	}
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
