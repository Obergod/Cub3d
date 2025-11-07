/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <mafioron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 19:24:55 by mafioron          #+#    #+#             */
/*   Updated: 2025/11/07 20:34:44 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void free_cub(t_cub *cub)
{
	if (!cub)
		return ;
	if (cub->map)
		ft_free_split(cub->map);
	if (cub->textures)
		ft_free_split(cub->textures);
    free(cub->mlx);
	free(cub);
}
