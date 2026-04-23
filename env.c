/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 09:36:17 by knajmech          #+#    #+#             */
/*   Updated: 2026/04/22 12:09:51 by knajmech         ###   ########.fr       */
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

int	

int	fill_env(t_env_map **map_env, t_env_tracker *tracker, char **env)
{
	int				index_arr;
	int				i_str;
	int				var_len;
	unsigned int	hash;
	char			*str;

	index_arr = 0;
	while (env[index_arr])
	{
		i_str = 0;
		hash = 5381;
		str = env[index_arr];
		var_len = ft_strlen_char(str, '=');
		while(i_str < var_len && var_len > 0)//remove var_len and just check up until hardcoded '='
		{
			hash = hash * 31 + str[i_str];
			i_str++;
		}
		hash_function(map_env, tracker, hash, var_len);
		index_arr++;
	}
}

void	intialise_env(t_env_map **map_env, t_env_tracker *tracker)
{
	tracker->elem_num = 0;
	tracker->capacity = 67;
	map_env = malloc(sizeof(map_env) * 67);
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
