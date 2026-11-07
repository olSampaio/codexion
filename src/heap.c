/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 14:49:49 by lusampai          #+#    #+#             */
/*   Updated: 2026/11/07 14:56:34 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	heap_init(t_heap *heap, int capacity)
{
	heap->nodes = malloc(sizeof(t_heap_node) * capacity);
	if (!heap->nodes)
		return (1);
	heap->size = 0;
	heap->capacity = capacity;
	return (0);
}

void	heap_destroy(t_heap *heap)
{
	free(heap->nodes);
	heap->nodes = NULL;
	heap->size = 0;
}

int	heap_push(t_heap *heap, t_heap_node node)
{
	if (heap->size >= heap->capacity)
		return (1);
	heap->nodes[heap->size] = node;
	sift_up(heap, heap->size);
	heap->size++;
	return (0);
}

int	heap_pop(t_heap *heap, t_heap_node *out)
{
	if (heap->size == 0)
		return (1);
	*out = heap->nodes[0];
	heap->size--;
	heap->nodes[0] = heap->nodes[heap->size];
	sift_down(heap, 0);
	return (0);
}

int	heap_peek(t_heap *heap, t_heap_node *out)
{
	if (heap->size == 0)
		return (1);
	*out = heap->nodes[0];
	return (0);
}
