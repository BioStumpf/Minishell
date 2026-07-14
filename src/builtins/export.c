/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 09:27:50 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/14 11:36:00 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "env.h"
#include "execution.h"

void	print_expolist(t_node	*env_list)
{
	t_env	*node;
	int		i;

	i = 0;
	while (env_list)
	{
		assert(env_list->content != NULL);
		node = env_list->content;
		assert(node->key != NULL);
		if (node->value && ft_strncmp(node->key, "_", 2))
			printf("declare -x %s=\"%s\"\n", node->key, node->value);
		else
			printf("declare -x %s\n", node->key);
		env_list = env_list->next;
		i++;
	}
}

void	export_var(t_data *data)
{
	t_list	*env_arr;
	int		i;

	env_arr = data->env_mp->env_ptr;
	i = 0;
	while (i < data->env_mp->capacity)
	{
		if (env_arr[i].head)
			print_expolist(env_arr[i].head);
		i++;
	}
	assert(i == data->env_mp->capacity);
}
