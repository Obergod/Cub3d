/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:15:33 by ufalzone          #+#    #+#             */
/*   Updated: 2025/03/24 16:16:56 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/garbage_collector.h"

char	**gc_strdup_array(char **s1)
{
	int		i;
	int		array_size;
	char	**new_array;

	array_size = 0;
	while (s1[array_size])
		array_size++;
	new_array = gc_malloc(sizeof(char *) * (array_size + 1));
	if (!new_array)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new_array[i] = gc_strdup(s1[i]);
		if (!new_array[i])
			return (NULL);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}
