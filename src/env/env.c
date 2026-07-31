/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 09:36:17 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/30 16:33:17 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "err.h"
#include "env.h"
#include "builtins.h"
#include <assert.h>
#include <stdio.h>

t_env	*make_kv_node(char *key, char *val)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	assert(key != NULL);
	assert(val != NULL);
	node->key = key;
	node->key_w_equal = ft_strjoin(key, "=");
	if (!node->key_w_equal)
		return (free(node), NULL);
	assert(ft_strlen(node->key_w_equal));
	node->value = val;
	return (node);
}

int	hash_function(t_list *map_env, t_env_tracker *tracker,
			unsigned int key_index, char *env_var)
{
	t_env				*key_val_node;
	t_node				*content_node;
	char				*value[2];

	assert(key_index <= (unsigned int) tracker->capacity);
	value[0] = ft_strndup(env_var, '=');
	value[1] = ft_strdup(ft_strchr(env_var, '=') + 1);
	if (!value[0] || !value[1])
		return (free(value[0]), free(value[1]), 0);
	key_val_node = hash_search(map_env, value[0]);
	if (key_val_node)
		return (free(value[0]), key_val_node->value = value[1], 1);
	key_val_node = make_kv_node(value[0], value[1]);
	if (!key_val_node)
		return (free(value[0]), free(value[1]), 0);
	content_node = ft_nodenew(key_val_node);
	if (!content_node)
		return (free(value[0]), free(value[1]), free(key_val_node->key_w_equal)
			, free(key_val_node), 0);
	ft_lstadd_back(&map_env[key_index], content_node);
	tracker->elem_num++;
	return (1);
}

int	fill_env(t_list *map_env, t_env_tracker *tracker, char **env)
{
	int				index_arr;
	int				var_len;
	unsigned int	hash_key;

	index_arr = 0;
	while (env[index_arr])
	{
		var_len = ft_strlen_char(env[index_arr], '=');
		hash_key = find_hash_key(env[index_arr]);
		if (var_len > 0)
			if (hash_function(map_env, tracker, hash_key, env[index_arr]) == 0)
				return (0);
		index_arr++;
	}
	return (1);
}

int	initialise_env(t_env_tracker *tracker)
{
	static t_list	map_env[CAPACITY];

	tracker->elem_num = 0;
	tracker->capacity = CAPACITY;
	tracker->env_ptr = map_env;
	return (1);
}

int	process_env(t_data *data, char **env)
{
	static t_env_tracker	tracker;

	if (tracker.capacity == 0)
	{
		if (!env)
			return (1);
		initialise_env(&tracker);
		data->env_mp = &tracker;
		if (!fill_env(tracker.env_ptr, &tracker, env))
			return (set_error(data, ERR_MALLOC), -1);
		return (1);
	}
	else if (data->new_variable)
	{
		if (!insert_new(tracker.env_ptr, &tracker, data->new_variable))
			return (set_error(data, ERR_MALLOC), 0);
		return (1);
	}
	return (0);
}
