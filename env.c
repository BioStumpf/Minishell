/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 09:36:17 by knajmech          #+#    #+#             */
/*   Updated: 2026/04/22 10:54:42 by knajmech         ###   ########.fr       */
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

void	fill_env(t_env_map *map_env, t_env_tracker *tracker, char **env)
{
	int				bucket_index;
	int				i;
	int				var_len;
	unsigned int	hash;
	char			*str;

	i = 0;
	bucket_index = 0;
	hash = 5381;
	while ()
	{
		var_len = 
		hash = hash * 31 + str[
	}
}

void	intialise_env(t_env_map *map_env, t_env_tracker *tracker)
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
