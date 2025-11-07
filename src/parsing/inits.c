/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:28 by mafioron          #+#    #+#             */
/*   Updated: 2025/11/07 16:50:15 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

t_cub	*inits(void)
{
	t_cub *cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (NULL);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (free(cub), NULL);
	cub->win = NULL;
	cub->img = NULL;
	cub->map = NULL;
	cub->textures = NULL;
	cub->height = 32;
	cub->width = 32;
	return (cub);
}

char **init_textures(char **cub)
{
	int		i;
	int		j;
	char	**textures;
	int		err;

	i = -1;
	j = 0;
	textures = malloc(sizeof(char *) * 7);
	if (!textures)
		return (NULL);
	while (++i < 6)
	{
		if (!ft_strncmp(cub[i], "NO ", 3) && j == 0)
			err = set_texture(cub[i], textures[j], &j, &i);
		else if (!ft_strncmp(cub[i], "SO ", 3) && j == 1)
			err = set_texture(cub[i], textures[j], &j, &i);
		else if (!ft_strncmp(cub[i], "WE ", 3) && j == 2)
			err = set_texture(cub[i], textures[j], &j, &i);
		else if (!ft_strncmp(cub[i], "EA ", 3) && j == 3)
			err = set_texture(cub[i], textures[j], &j, &i);
		else if (!ft_strncmp(cub[i], "F ", 2) && j == 4)
			err = set_texture(cub[i], textures[j], &j, &i);
		else if (!ft_strncmp(cub[i], "C ", 2) && j == 5)
			err = set_texture(cub[i], textures[j], &j, &i);
		if (err == -1)
			return (ft_free_split(textures), NULL);
	}
	if (j != 6)
		return (ft_free_split(textures), NULL);
	textures[j] = 0;
	return (textures);
}

int	set_texture(char *cub, char *texture, int *text_count, int *count_cub)
{
	int	i;

	i = 2;

	while (cub[i] == ' ')
		i++;
	texture = ft_strdup(cub + i);
	if (!texture)
		return (-1);
	(*text_count)++;
	(*count_cub) = -1;
	return (0);
}
