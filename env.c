/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 09:36:17 by knajmech          #+#    #+#             */
/*   Updated: 2026/05/10 09:44:37 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/env.h"
#include <assert.h>

/*int		ft_strlen_char(char *str, char delimitter)
{
	int	i;

	i = 0;
	while (str[i] != delimitter && str[i])
		i++;
	if (!str[i])
		return (-1);
	return (i);
}*/

t_env	*make_kv_node(char *key, char *val)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	assert(key != NULL);
	assert(val != NULL);
	node->key = key;
	node->value = val;
	return (node);
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
			return ;
		}
		node = node->next;
	}
}

int	hash_function(t_list *map_env, t_env_tracker *tracker,
			unsigned int key_index, char *env_var)
{
	t_env				*key_val_node;
	t_node				*content_node;
	char				*value[2];

	assert(key_index <= (unsigned int) tracker->capacity);
	value[1] = ft_strdup(ft_strchr(env_var, '=') + 1);
	value[0] = ft_strndup(env_var,'=');
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

	/*if (map_env[key_index].content)
		while (map_env[key_index].next != NULL)
			map_env[key_index].next = map_env[key_index].next;*/

	//map_env[key_index].content = ft_nodenew(value);
	//assert(map_env[key_index]->value == NULL);
	//if (map_env[key_index]->value == NULL)
	//	map_env[key_index]->value = value;

int	fill_env(t_list *map_env, t_env_tracker *tracker, char **env)
{
	int				index_arr;
	int				var_len;
	unsigned int	hash_key;

	index_arr = 0;
	while (env[index_arr])
	{
		var_len = ft_strlen_char(env[index_arr], '=');
		/*while(i_str < var_len && var_len > 0)//remove var_len and just check up until hardcoded '='
		{
			hash = hash * 31 + env[index_arr][i_str];
			i_str++;
		}*/
		hash_key = find_hash_key(env[index_arr]);
		if (var_len > 0)
			if (hash_function(map_env, tracker, hash_key, env[index_arr]) == 0)
				return (0); //consider if variable adding is needed.
		index_arr++;
	}
	return (1);
}

int	initialise_env(t_env_tracker *tracker)
{
	static t_list	map_env[CAPACITY + 1];

	tracker->elem_num = 0;
	tracker->capacity = CAPACITY;
	tracker->env_ptr = map_env;
	return (1);
}

int process_env(t_data *data, char **env)
{
	static t_env_tracker	tracker;

	if (tracker.capacity == 0)
	{
		initialise_env(&tracker); 
		if (!fill_env(tracker.env_ptr, &tracker, env))
			error_and_cleanup(data, "malloc");
		data->env_mp = &tracker;
		return (1);
	}
	if (data->new_variable)
	{
		if (!insert_new(tracker.env_ptr, &tracker, data->new_variable))
			return (0);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	static t_data	data;

	(void) argc;
	(void) argv;
	process_env(&data, env);
	error_and_cleanup(&data, NULL);
}
