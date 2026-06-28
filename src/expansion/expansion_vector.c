/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 15:24:10 by david             #+#    #+#             */
/*   Updated: 2026/06/28 19:27:43 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <stdio.h>
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
// int main(){
// 	t_exp_vec vec = {0, 0, 0};
// 	add_exp(&vec, 0, &(t_exp){true, 1, 5});
// 	add_exp(&vec, 1, &(t_exp){false, 2, 10});
// 	add_exp(&vec, 2, &(t_exp){false, 3, 0});
// 	add_exp(&vec, 3, &(t_exp){true, 3, 5});
// 	add_exp(&vec, 4, &(t_exp){false, 4, 10});
// 	add_exp(&vec, 5, &(t_exp){false, 5, 0});
// 	add_exp(&vec, 6, &(t_exp){true, 6, 5});
// 	add_exp(&vec, 7, &(t_exp){false, 7, 10});
// 	add_exp(&vec, 8, &(t_exp){false, 8, 0});
// 	for (size_t i = 0; i < vec.size; i++){
// 		printf("quoted: %d;   start: %zu;   len: %zu\n", exp_quote(&vec, i), exp_start(&vec, i), exp_len(&vec, i));
// 	}
// 	free(vec.expansions);
// }
