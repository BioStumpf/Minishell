/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 09:36:17 by knajmech          #+#    #+#             */
/*   Updated: 2026/05/06 10:13:35 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <assert.h>

int		ft_strlen_char(char *str, char delimitter)
{
	int	i;

	i = 0;
	while (str[i] != delimitter && str[i])
		i++;
	/*if (!str[i])
		return (-1);*/
	return (i);
}

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

void	replace_val(t_env *key_val_node, char *val)
{
	key_val_node->value = val;
}

int	hash_function(t_list *map_env, t_env_tracker *tracker,
			unsigned int hash, char *env_var)
{
	unsigned int		key_index;
	t_env				*key_val_node;
	t_node				*content_node;
	char				*value[2];

	assert(hash > 0);
	key_index = hash % tracker->capacity;
	value[1] = ft_strdup(ft_strchr(env_var, '=') + 1);
	value[0] = ft_strndup(env_var,'=');
	if (!value[0])
		return (free(value[0]), free(value[1]), 0);
	key_val_node = hash_search((map_env[key_index].head), value[0]);
	if (key_val_node)
		return (replace_val(key_val_node, value[1]), 1);
	assert(key_index <= (unsigned int) tracker->capacity);
	key_val_node = make_kv_node(value[0], value[1]);
	content_node = ft_nodenew(key_val_node);
	if (!content_node)
		return (0);
	ft_lstadd_back(&map_env[key_index], content_node);
	tracker->elem_num++;
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
	int				i_str;
	int				var_len;
	unsigned int	hash;

	index_arr = 0;
	while (env[index_arr])
	{
		i_str = 0;
		hash = 5381;
		var_len = ft_strlen_char(env[index_arr], '=');
		while(i_str < var_len && var_len > 0)//remove var_len and just check up until hardcoded '='
		{
			hash = hash * 31 + env[index_arr][i_str];
			i_str++;
		}
		if (var_len > 0)
			hash_function(map_env, tracker, hash, env[index_arr]); //consider if variable adding is needed.
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

int process_env(t_data *data, char **env)
{
	static t_env_tracker	tracker;

	if (!initialise_env(&tracker) || !fill_env(tracker.env_ptr, &tracker, env))
		error_and_cleanup(data, "malloc");
	data->env_mp = &tracker;
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	static t_data	data;

	(void) argc;
	(void) argv;
	process_env(&data, env);
}
