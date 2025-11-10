/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:28 by mafioron          #+#    #+#             */
/*   Updated: 2025/11/10 19:42:12 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

t_cub	*inits(void)
{
	t_cub	*cub;

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
	cub->map_height = 0;
	cub->map_width = 0;
	cub->player_row = -1;
	cub->player_col = -1;
	cub->player_dir = '\0';
	return (cub);
}

static int	parse_texture_line(char *line, char **textures)
{
	if (!ft_strncmp(line, "NO ", 3) && !textures[0])
		return (set_texture(line, &textures[0]));
	if (!ft_strncmp(line, "SO ", 3) && !textures[1])
		return (set_texture(line, &textures[1]));
	if (!ft_strncmp(line, "WE ", 3) && !textures[2])
		return (set_texture(line, &textures[2]));
	if (!ft_strncmp(line, "EA ", 3) && !textures[3])
		return (set_texture(line, &textures[3]));
	if (!ft_strncmp(line, "F ", 2) && !textures[4])
		return (set_texture(line, &textures[4]));
	if (!ft_strncmp(line, "C ", 2) && !textures[5])
		return (set_texture(line, &textures[5]));
	return (-1);
}

char	**init_textures(char **cub)
{
	int		i;
	char	**textures;

	i = -1;
	textures = malloc(sizeof(char *) * 7);
	if (!textures)
		return (NULL);
	ft_memset(textures, 0, sizeof(char *) * 7);
	while (++i < 6)
	{
		if (parse_texture_line(cub[i], textures) == -1)
		{
			ft_free_split(textures);
			return (NULL);
		}
	}
	if (!textures[0] || !textures[1] || !textures[2]
		|| !textures[3] || !textures[4] || !textures[5])
	{
		ft_free_split(textures);
		return (NULL);
	}
	textures[6] = NULL;
	return (textures);
}

int	set_texture(char *cub, char **texture)
{
	int	i;

	i = 0;
	while (cub[i] && (cub[i] != ' ' || cub[i] == '\t'))
		i++;
	while (cub[i] == ' ' || cub[i] == '\t')
		i++;
	*texture = ft_strdup(cub + i);
	if (!*texture)
		return (-1);
	return (0);
}
