/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 09:37:47 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/04 07:32:06 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/builtins.h"

void	unset_var(t_list *map_env, char *key)
{
	unsigned int	hash_key;

	hash_key = find_hash_key(key);
	unset_variable(map_env, key);
	if (map_env[hash_key].len == 0)
		map_env[hash_key].head = NULL;
}
