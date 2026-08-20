/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 11:01:30 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/20 09:54:07 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "structs.h"
#include "execution.h"
#include "err.h"
#include <stdio.h>

char	**env_ptrptr(t_data *dat, t_list *env_list, char **env)
{
	t_node	*node_list;
	t_env	*k_a_v;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (i++ < CAPACITY)
	{
		node_list = (t_node *) env_list[i - 1].head;
		while (node_list)
		{
			k_a_v = (t_env *)node_list->content;
			if (k_a_v->value != NULL)
			{
				env[k] = ft_strjoin(k_a_v->key_w_equal, k_a_v->value);
				if (!env[k])
					return (free_out(env, k), set_error(dat, ERR_SYS, NULL),
						NULL);
			}
			node_list = node_list->next;
			k++;
		}
	}
	return (env[k] = 0, env);
}

int	replace(t_list *map_env, char *key, char *val)
{
	t_env	*key_val_node;

	key_val_node = hash_search(map_env, key);
	if (key_val_node)
		return (free(key_val_node->value), key_val_node->value = val, 1);
	else
		return (0);
}

t_node	*add(char *key, char *val)
{
	t_env	*key_val_node;
	t_node	*content_node;

	key_val_node = make_kv_node(key, val);
	if (!key_val_node)
		return (free(key), free(val), NULL);
	content_node = ft_nodenew(key_val_node);
	if (!content_node)
		return (delete_envnode(key_val_node), free(key_val_node), NULL);
	return ((t_node *) content_node);
}

int	replace_or_add(t_list *map_env, t_env_tracker *tracker,
		unsigned int key_index, char **env_var)
{
	t_node				*content_node;
	char				*value[2];

	if (env_var[1])
	{
		value[1] = ft_strdup(env_var[1]);
		if (!value[1])
			return (0);
	}
	else
		value[1] = NULL;
	if (replace(map_env, env_var[0], value[1]) == 1)
		return (1);
	value[0] = ft_strdup(env_var[0]);
	if (!value[0])
		return (free(value[1]), 0);
	content_node = add(value[0], value[1]);
	if (!content_node)
		return (0);
	ft_lstadd_back(&map_env[key_index], content_node);
	return (tracker->elem_num++, 1);
}

int	insert_new(t_list *env_ptr, t_env_tracker *tracker, char **new_variable)
{
	int				var_len;
	unsigned int	hash;

	var_len = ft_strlen(new_variable[0]);
	hash = find_hash_key(new_variable[0]);
	if (var_len > 0)
		if (replace_or_add(env_ptr, tracker, hash, new_variable) == 0)
			return (0);
	return (1);
}
