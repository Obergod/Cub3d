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

int	check_errors(int fd, t_vars *vars)
{
	char	**cub;
	int		err;
	char	**textures;

	cub = split_all_file(fd);
	if (!cub)
		return (-1);
	err = check_textures(cub, vars);
	if (err != 0)
		return (err);
	err = check_map(cub);
	if (err != 0)
		return (err);
	textures = init_textures(cub);
	if (!textures)
		return (-1);
	//must check if nothing after map + gotta split map
	return (0);
}




int	main(int ac, char **av)
{
	int	fd;
	t_vars *vars;

	if (ac != 2)
		return (printf("Error\n"), 1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (printf("Error\n"), 1);
	vars = inits();
	if (!vars)
		return (printf("Error\n"), 1);
	if (check_errors(fd, vars) == 1)
		printf("Error cub\n");
	return (0);
}
