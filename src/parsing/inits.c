/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:28 by mafioron          #+#    #+#             */
/*   Updated: 2025/07/04 17:53:29 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	inits(t_vars *vars)
{
	vars->mlx = NULL;
	vars->win = NULL;
	vars->img = NULL;
	vars->map = NULL;
	vars->textures = NULL;
	vars->height = 32;
	vars->width = 32;
}
