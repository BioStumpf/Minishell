/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 09:37:47 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/18 16:50:14 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "structs.h"
#include "err.h"

void	unset_var(t_env_tracker *env_tracker, t_list *map_env, char *key)
{
	unsigned int	hash_key;

	if (!key)
		return ;
	hash_key = find_hash_key(key);
	unset_variable(env_tracker, map_env, key);
	if (map_env[hash_key].len == 0)
		map_env[hash_key].head = NULL;
}

void	unset_var_start(t_data *data, char **argv)
{
	int		i;

	i = 1;
	g_ret = 0;
	if (!argv[i])
		return ;
	while (argv[i])
	{
		unset_var(data->env_mp, data->env_mp->env_ptr, argv[i]);
		i++;
	}
}
