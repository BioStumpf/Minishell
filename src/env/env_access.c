/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_access.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 15:49:29 by david             #+#    #+#             */
/*   Updated: 2026/06/18 16:05:31 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*fetch_env_value(t_env_tracker *map, char *key)
{
	unsigned int	idx;

	idx = find_hash_key(key);
	return (hash_search(map->env_ptr[idx].head, key)->value);
}
