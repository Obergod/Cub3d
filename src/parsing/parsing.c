/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:08:00 by mafioron          #+#    #+#             */
/*   Updated: 2025/11/07 17:21:32 by ufalzone         ###   ########.fr       */
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

int	check_errors(int fd, t_cub *cub)
{
	char	**cub_file;
	int		err;
	char	**textures;

	cub_file = split_all_file(fd);
	if (!cub_file)
		return (-1);
	err = check_textures(cub_file, cub);
	if (err != 0)
		return (err);
	err = check_map(cub_file, cub);
	if (err != 0)
		return (err);
	textures = init_textures(cub_file);
	if (!textures)
		return (-1);
	return (0);
}
