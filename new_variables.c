/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 11:01:30 by knajmech          #+#    #+#             */
/*   Updated: 2026/05/06 12:30:20 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	replace_or_add(t_list *map_env, t_env_tracker *tracker,
		unsigned int hash, char **env_var)
{
	unsigned int		key_index;
	t_env				*key_val_node;
	t_node				*content_node;
	char				*value[2];

	assert(hash > 0);
	key_index = hash % tracker->capacity;
	assert(key_index <= (unsigned int) tracker->capacity);
	value[1] = ft_strdup(env_var[0]);
	value[0] = ft_strdup(env_var[1]);
	if (!value[0])
		return (free(value[0]), free(value[1]), 0);
	key_val_node = hash_search((map_env[key_index].head), value[0]);
	if (key_val_node)
		return (key_val_node->value = val, 1));
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
	int				i_str;
	int				var_len;
	unsigned int	hash;

	assert(new_variable != NULL && new_variable[0]);
	i_str = 0;
	hash = 5381;
	var_len = ft_strlen(new_variable[0]);
	while(i_str < var_len)//remove var_len and just check up until hardcoded '='
	{
		hash = hash * 31 + new_variable[0][i_str];
		i_str++;
	}
	if (var_len > 0)
		if(replace_or_add(env_ptr, tracker, hash, new_variable) == 0)
			return (0); //consider if variable adding is needed.
	return (1);
}
