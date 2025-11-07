/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strndup_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:07:24 by ufalzone          #+#    #+#             */
/*   Updated: 2025/03/24 16:17:40 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/garbage_collector.h"

char	**gc_strndup_array(char **s1, size_t size)
{
	int		j;
	char	**new_array;

	j = 0;
	new_array = gc_malloc((sizeof(char *) * size) + 1);
	if (!new_array)
		return (NULL);
	while (s1[j])
	{
		new_array[j] = gc_strdup(s1[j]);
		if (!new_array[j])
			return (NULL);
		j++;
	}
	new_array[j] = NULL;
	return (new_array);
}
