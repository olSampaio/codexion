/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 13:59:33 by lusampai          #+#    #+#             */
/*   Updated: 2026/11/07 14:48:10 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	node_less(t_heap_node *a, t_heap_node *b)
{
	if (a->key != b->key)
		return (a->key < b->key);
	return (a->id < b->id);
}

static void	swap_nodes(t_heap_node *a, t_heap_node *b)
{
	t_heap_node	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sift_up(t_heap *heap, int i)
{
	int	parent;

	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (node_less(&heap->nodes[i], &heap->nodes[parent]))
		{
			swap_nodes(&heap->nodes[i], &heap->nodes[parent]);
			i = parent;
		}
		else
			break ;
	}
}

void	sift_down(t_heap *heap, int i)
{
	int	left;
	int	right;
	int	smallest;

	while (1)
	{
		left = 2 * i + 1;
		right = 2 * i + 2;
		smallest = i;
		if (left < heap->size && node_less(&heap->nodes[left],
				&heap->nodes[smallest]))
			smallest = left;
		if (right < heap->size && node_less(&heap->nodes[right],
				&heap->nodes[smallest]))
			smallest = right;
		if (smallest == i)
			break ;
		swap_nodes(&heap->nodes[i], &heap->nodes[smallest]);
		i = smallest;
	}
}
