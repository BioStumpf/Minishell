/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 09:37:47 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/04 15:23:29 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "structs.h"

void	unset_var(t_env_tracker *env_tracker, t_list *map_env, char *key)
{
	unsigned int	hash_key;

	if (!key)
		return ;
	hash_key = find_hash_key(key);
	unset_variable(env_tracker, map_env, key);
	if (map_env[hash_key].len == 0)
		map_env[hash_key].head = NULL;
}
