/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 11:01:30 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/04 08:07:56 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/env.h"

char	**env_ptrptr(t_data *dat, t_list *env_list, char **env)
{
	t_node	*node_list;
	t_env	*key_and_val;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (i < CAPACITY)
	{
		node_list = (t_node *) env_list[i].head;
		k = 0;
		while (node_list)
		{
			key_and_val = (t_env *)node_list->content;
			assert(node_list && key_and_val);
			env[i] = ft_strjoin(key_and_val->key_w_equal, key_and_val->value);
			if (!env[i])
				return (free_out(env, k), error_and_cleanup(dat, "mall", 0), NULL);
			k++;
			node_list = node_list->content;
		}
		i++;
	}
	env[i] = 0;
	return (env);
}

int	replace_or_add(t_list *map_env, t_env_tracker *tracker,
		unsigned int key_index, char **env_var)
{
	t_env				*key_val_node;
	t_node				*content_node;
	char				*value[2];

	assert(key_index <= (unsigned int) tracker->capacity);
	value[0] = ft_strdup(env_var[0]);
	value[1] = ft_strdup(env_var[1]);
	if (!value[0])
		return (free(value[0]), free(value[1]), 0);
	key_val_node = hash_search((map_env[key_index].head), value[0]);
	if (key_val_node)
		return (key_val_node->value = value[1], 1);
	key_val_node = make_kv_node(value[0], value[1]);
	content_node = ft_nodenew(key_val_node);
	if (!content_node)
		return (0);
	ft_lstadd_back(&map_env[key_index], content_node);
	tracker->elem_num++;
	return (1);
}

int	insert_new(t_list *env_ptr, t_env_tracker *tracker, char **new_variable)
{
	int				var_len;
	unsigned int	hash;

	assert(new_variable != NULL && new_variable[0]);
	var_len = ft_strlen(new_variable[0]);
	hash = find_hash_key(new_variable[0]);
	if (var_len > 0)
		if(replace_or_add(env_ptr, tracker, hash, new_variable) == 0)
			return (0); //consider if variable adding is needed.
	return (1);
}
