/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:49:10 by ufalzone          #+#    #+#             */
/*   Updated: 2025/03/21 15:23:10 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_collector.h"

/**
 * @brief Alloue de la mémoire et l'enregistre dans le collecteur
 *
 * @param size Taille en octets à allouer
 * @return void* Pointeur vers la mémoire allouée ou NULL en cas d'erreur
 */
void	*gc_malloc(size_t size)
{
	void	*data;
	t_gc_head	*head;

	if (size == 0)
		return (NULL);
	head = gc_singleton();
	data = malloc(size);
	if (!data)
		return (NULL);
	if (gc_alloc(data))
	{
		free(data);
		return (NULL);
	}
	return (data);
}

/**
 * @brief Vérifie si un pointeur est géré par le collecteur
 *
 * @param ptr Pointeur à vérifier
 * @return int 1 si le pointeur est géré, 0 sinon
 */
int	gc_contains(void *ptr)
{
	t_gc	*current;
	t_gc_head	*head;

	if (!ptr)
		return (0);
	head = gc_singleton();
	current = head->head;
	while (current)
	{
		if (current->data == ptr)
			return (1);
		current = current->next;
	}
	return (0);
}

/**
 * @brief Compte le nombre d'allocations gérées par le collecteur
 *
 * @return size_t Nombre d'allocations
 */
size_t	gc_count(void)
{
	t_gc	*current;
	size_t	count;
	t_gc_head	*head;

	count = 0;
	head = gc_singleton();
	current = head->head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	gc_print(void)
{
	t_gc	*current;
	t_gc_head	*head;

	head = gc_singleton();
	current = head->head;
	while (current)
	{
		printf("%p\n", current->data);
		current = current->next;
	}
}
