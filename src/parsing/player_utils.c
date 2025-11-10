/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <mafioron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:46:37 by mafioron          #+#    #+#             */
/*   Updated: 2025/11/10 15:47:59 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	save_player(t_cub *cub, int row, int col, char dir)
{
	if (cub->player_dir != '\0')
		return (1);
	cub->player_row = row;
	cub->player_col = col;
	cub->player_dir = dir;
	return (0);
}

int	check_tile(t_cub *cub, char **map, int row, int col)
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
