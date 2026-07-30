/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 09:46:59 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/30 09:47:44 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "structs.h"

void	delete_envnode(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env->key_w_equal);
	//free(env);
}

t_node	*delete_node(t_node *node)
{
	t_env	*env;
	t_node	*next;

	env = node->content;
	delete_envnode(env);
	next = node->next;
	free(node->content);
	free(node);
	return (next);
}

void	unset_variable(t_list *map_env, char *key)
{
	t_node			*node;
	t_node			*prev_node;
	t_env			*env;
	unsigned int	hash_key;
	int				len;

	prev_node = 0;
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
			delete_envnode(env);
			ft_lstmid_rm(&map_env[hash_key], node, prev_node, free);
			assert(map_env[hash_key].len != ULLONG_MAX);
			return ;
		}
		prev_node = node;
		node = node->next;
	}
	return ;
}
