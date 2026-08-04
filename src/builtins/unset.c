/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 09:37:47 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/04 14:01:30 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "env.h"
#include "err.h"

void	unset_var(t_list *map_env, char *key)
{
	unsigned int	hash_key;

	if (!key)
	{
		g_ret = 134;
		return ;
	}
	hash_key = find_hash_key(key);
	unset_variable(map_env, key);
	if (map_env[hash_key].len == 0)
		map_env[hash_key].head = NULL;
}
