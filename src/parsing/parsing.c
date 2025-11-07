/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:08:00 by mafioron          #+#    #+#             */
/*   Updated: 2025/11/07 20:35:56 by mafioron         ###   ########.fr       */
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
	free(stock);
	if (!cub)
		return (NULL);
	return (cub);
}

int	check_errors(int fd, t_cub *cub)
{
	char	**cub_file;
	int		err;

	cub_file = split_all_file(fd);
	if (!cub_file)
		return (-1);
	err = check_textures(cub_file, cub);
	if (err != 0)
		return (ft_free_split(cub_file), err);
	err = check_map(cub_file, cub);
	if (err != 0)
		return (ft_free_split(cub_file), err);
	cub->textures = init_textures(cub_file);
	if (!cub->textures)
		return (ft_free_split(cub_file), -1);
	ft_free_split(cub_file);
	return (0);
}
