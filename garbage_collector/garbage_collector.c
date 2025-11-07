/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:52:33 by ufalzone          #+#    #+#             */
/*   Updated: 2025/03/21 16:12:37 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_collector.h"

t_gc_head	*gc_singleton(void)
{
	static t_gc_head	gc = {NULL};

	return (&gc);
}

/**
 * @brief Ajoute un pointeur à gérer par le collecteur
 *
 * @param data Pointeur vers les données allouées
 * @return int 0 en cas de succès, 1 en cas d'erreur
 */
int	gc_alloc(void *data)
{
	t_gc	*node;
	t_gc_head	*head_ref;

	if (!data)
		return (1);
	head_ref = gc_singleton();
	if (gc_contains(data) == 1)
		return (1);
	node = malloc(sizeof(t_gc));
	if (!node)
		return (1);
	node->data = data;
	node->next = head_ref->head;
	head_ref->head = node;
	return (0);
}

/**
 * @brief Supprime une allocation spécifique du collecteur
 *
 * @param ptr Pointeur vers les données à libérer
 * @return int 0 en cas de succès,
 * 	1 si le pointeur n'est pas trouvé ou en cas d'erreur
 */
int	gc_free(void *ptr)
{
	t_gc	*tmp;
	t_gc	*prev;
	t_gc_head	*head_ref;

	if (!ptr)
		return (1);
	head_ref = gc_singleton();
	tmp = head_ref->head;
	prev = NULL;
	while (tmp)
	{
		if (tmp->data == ptr)
		{
			if (prev)
				prev->next = tmp->next;
			else
				head_ref->head = tmp->next;
			free(tmp->data);
			free(tmp);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

/**
 * @brief Détruit le collecteur et libère toutes les allocations
 */
void	gc_destroy(void)
{
	t_gc	*current;
	t_gc	*next;
	t_gc_head	*head_ref;

	head_ref = gc_singleton();
	current = head_ref->head;
	while (current)
	{
		next = current->next;
		if (current->data != NULL)
			free(current->data);
		free(current);
		current = next;
	}
	head_ref->head = NULL;
}
