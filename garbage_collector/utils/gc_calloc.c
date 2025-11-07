/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:23:15 by ufalzone          #+#    #+#             */
/*   Updated: 2025/04/27 16:42:40 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/garbage_collector.h"

/**
 * @brief Alloue et initialise à zéro un
 bloc de mémoire avec le garbage collector
 *
 * @param count Nombre d'éléments à allouer
 * @param size Taille de chaque élément
 * @return void* Pointeur vers le bloc alloué ou NULL si erreur
 */
void	*gc_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total;
	size_t	i;

	total = count * size;
	ptr = gc_malloc(total);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total)
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
