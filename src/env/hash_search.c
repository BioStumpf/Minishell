/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 10:03:18 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/04 07:27:08 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/env.h"

unsigned int	find_hash_key(char	*key)
{
	unsigned int	hash;
	unsigned int	key_index;
	unsigned int	i;
	unsigned int	key_len;

	assert(key != NULL);
	hash = 5381;
	key_len = ft_strlen_char(key, '=');
	i = 0;
	while (i < key_len)
	{
		hash = hash * 31 + key[i];
		i++;
	}
	key_index = hash % CAPACITY;
	return (key_index);
}

t_env	*hash_search(t_node *list, char *key)
{
	t_env	*key_check;

	if (!list)
		return (NULL);
	while (list)
	{
		key_check = list->content;
		if (!ft_strncmp(key_check->key, key, ft_strlen(key) + 1))
			return (key_check);
		else
			list = list->next;
	}
	return (NULL);
}

/*void	hash_find(t_data *data, char *var)
{
	assert (var != NULL && data->env_mp->env_ptr != NULL);
	
}*/
