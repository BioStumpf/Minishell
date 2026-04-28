/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 09:36:17 by knajmech          #+#    #+#             */
/*   Updated: 2026/04/28 11:44:05 by knajmech         ###   ########.fr       */
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
	if (!str[i])
		return (-1);
	return (i);
}

void	hash_function(t_env_map **map_env, t_env_tracker *tracker,
			unsigned int hash, char *env_var)
{
	unsigned int		key_index;
	char				*value;

	assert(hash > 0);
	key_index = hash % tracker->capacity;
	value = ft_strchr(env_var, '=') + 1;
	assert(key_index <= (unsigned int) tracker->capacity);
	if (map_env[key_index] == NULL)
		map_env[key_index] = ft_newnode(value);
	else if (map_env[key_index])
		while (map_env[key_index]->next != NULL)
			map_env[key_index] = map_env[key_index]->next;
	//assert(map_env[key_index]->value == NULL);
	//if (map_env[key_index]->value == NULL)
	//	map_env[key_index]->value = value;
	if (map_env[key_index]->next == NULL)
	{
		map_env[key_index]->next = ft_newnode(value);
		map_env[key_index]->next->next = NULL;
		map_env[key_index]->next->value = NULL;
	}
	tracker->elem_num++;
}

int	fill_env(t_env_map **map_env, t_env_tracker *tracker, char **env)
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
	t_env_map				**map_env;

	tracker->elem_num = 0;
	tracker->capacity = 67;
	map_env = ft_calloc(tracker->capacity, sizeof(t_env_map *));
	if (!map_env)
		return (0);
	tracker->env_ptr = map_env;
	return (1);
}

int process_env(t_data *data, char **env)
{
	static t_env_tracker	tracker;

	if (!initialise_env(&tracker) || !fill_env(tracker.env_ptr, &tracker, env))
		error_and_cleanup(data, "malloc");
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	static t_data	data;

	(void) argc;
	(void) argv;
	process_env(&data, env);
}
