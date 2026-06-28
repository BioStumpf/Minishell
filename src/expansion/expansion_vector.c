/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 15:24:10 by david             #+#    #+#             */
/*   Updated: 2026/06/27 15:48:34 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <stdlib.h>

bool	init_exp_vec(t_exp_vec *vec)
{
	vec->size = 0;
	vec->capacity = 5;
	vec->expansions = malloc(sizeof(t_exp) * 5);
	if (!vec->expansions)
		return (false);
	return (true);
}

static void	*grow_exp_vec(t_exp_vec *vec)
{
	char	*new_buff;

	new_buff = malloc(vec->capacity * sizeof(t_exp));
	if (!new_buff)
		return (free(vec), NULL);
	ft_memcpy(new_buff, vec->expansions, vec->size * sizeof(t_exp));
	free(vec->expansions);
	return (new_buff);
}

void	*add_exp(t_exp_vec *vec, size_t idx, t_exp *exp)
{
	size_t	to_move;
	void	*dest;
	void	*src;

	if (!vec->expansions && !init_exp_vec(vec))
		return (NULL);
	if (vec->size >= vec->capacity)
	{
		vec->capacity *= 2;
		vec->expansions = grow_exp_vec(vec);
	}
	if (!vec->expansions)
		return (NULL);
	to_move = vec->size - idx;
	dest = &vec->expansions[idx + 1];
	src = &vec->expansions[idx];
	ft_memmove(dest, src, to_move * sizeof(t_exp));
	vec->expansions[idx] = *exp; 
	vec->size++;
	return (vec);
}
