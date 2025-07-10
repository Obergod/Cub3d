/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:10:45 by mafioron          #+#    #+#             */
/*   Updated: 2025/07/08 16:10:51 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

//	think about how to do textures, linked lists or strncmp
int	check_textures(char **cub, t_vars *vars)
{
	int	 i;
	int	nb_texture;

	nb_texture = 0;
	i = -1;
	//find a way to check if ! NO + NO
	while (cub[++i])
	{
		if (!ft_strncmp(cub[i], "NO ", 3) || !ft_strncmp(cub[i], "SO ", 3) || 
				!ft_strncmp(cub[i], "WE ", 3) || !ft_strncmp(cub[i], "EA ", 3))
		{
			if (test_image(vars, cub[i]) == 1)
				return (1);
			nb_texture++;
		}
		else if (!ft_strncmp(cub[i], "F ", 2) || !ft_strncmp(cub[i], "C ", 2))
		{
			if (check_colors(cub[i]) == 1)
				return (1);
			nb_texture++;
		}
	}
	if (nb_texture != 6)
		return (1);
	return (0);
}

int	check_colors(char *texture)
{
	int		i;
	char	**color;
	int		rgb;

	i = only_textures(texture);
	if (i == -1)
		return (1);
	color = ft_split(texture + i, ',');
	if (!color)
		return (1);
	i = -1;
	while (color[++i])
	{
		rgb = ft_atoi(color[i]);
		if (rgb < 0 || rgb > 255)
			return (1);
	}
	free(color);
	if (i != 3)
		return (1);
	return (0);
}

int	test_image(t_vars *vars, char *texture)
{
	int	i;

	i = only_textures(texture);
	if (i == -1)
		return (1);
	if (vars->img)
		mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_xpm_file_to_image(vars->mlx, texture + i,
			&vars->height, &vars->width);
	if (vars->img == NULL)
		return (1);
	return (0);
}

int	only_textures(char *texture)
{
	int	i;

	i = 2;
	while (texture[i] == ' ')
		i++;
	if (texture[i] == '\0')
		return (-1);
	return (i);
}
