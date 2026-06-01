/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 09:46:59 by knajmech          #+#    #+#             */
/*   Updated: 2026/05/12 11:12:52 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

t_node	*delete_node(t_node *node)
{
	t_env	*env;
	t_node	*node_next;

	node_next = node->next;
	env = node->content;
	free(env->key);
	free(env->value);
	free((t_env *) node->content);
	free(node);
	return (node_next);
}

void	unset_variable(t_list *map_env, char *key)
{
	t_node			*node;
	t_env			*env;
	unsigned int	hash_key;
	int				len;

	assert(key != NULL);
	hash_key = find_hash_key(key);
	node = map_env[hash_key].head;
	if (!node)
		return ;
	len = ft_strlen(key);
	while(node)
	{
		env = node->content;
		if (!ft_strncmp(env->key, key, len + 1))
		{
			map_env[hash_key].tail = ft_nodeadd_back(&map_env[hash_key].head,
					delete_node(node), map_env[hash_key].tail);
			map_env[hash_key].len--;
			assert(map_env[hash_key].len != ULLONG_MAX);
			return ;
		}
		node = node->next;
	}
	return ;
}
