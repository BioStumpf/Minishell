/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 09:36:17 by knajmech          #+#    #+#             */
/*   Updated: 2026/04/23 08:59:25 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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
	int					i;
	char				*value;

	assert(hash > 0);
	key_index = hash % tracker->capacity;
	value = ft_strchr(env_var, '=') + 1;
	assert(key_index <= tracker->capacity);
	i = 0;
	while (map_env[key_index]->value != NULL)
		map_env[key_index] = map_>env[key_index]->next;
	if (map_env[key_index]->value == NULL)
		map_env[key_index]->value = value;
	else
	{
		map_env[key_index]->next = ft_lstnew(value);
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

void	intialise_env(t_env_map **map_env, t_env_tracker *tracker)
{
	tracker->elem_num = 0;
	tracker->capacity = 67;
	map_env = ft_calloc(tracker->capacity, sizeof(map_env *));
	if (!map_env)
		error_and_cleanup(data, "malloc");
	tracker->env_ptr = map_env;
	return ;
}

int process_env(t_data *data, char **env)
{
	t_env_map		**map_env;
	t_env_tracker	*tracker;

	tracker = malloc(sizeof(t_data));
	if (!tracker)
		error_and_cleanup(data, "malloc");
	initialise_env(map_env, tracker);
	fill_env(map_env, tracker, env);
}
