/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 19:05:41 by ufalzone          #+#    #+#             */
/*   Updated: 2025/11/15 19:05:41 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	key_exit_hook(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_window(game);
	return (key_press(keycode, &game->player));
}
