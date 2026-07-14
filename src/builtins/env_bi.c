/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 09:10:22 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/14 11:36:20 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "execution.h"
#include "env.h"

void	print_list(t_node	*env_list, int len)
{
	t_env	*node;
	int		i;

	i = 0;
	while (env_list)
	{
		assert(env_list->content != NULL);
		node = env_list->content;
		assert(node->key != NULL);
		if (node->value)
			printf("%s=%s\n", node->key, node->value);
		env_list = env_list->next;
		i++;
	}
	assert(i == len);
}

void	env_var(t_data *data)
{
	t_list	*env_arr;
	int		i;

	env_arr = data->env_mp->env_ptr;
	i = 0;
	while (i < data->env_mp->capacity)
	{
		if (env_arr[i].head)
			print_list(env_arr[i].head, env_arr[i].len);
		i++;
	}
	assert(i == data->env_mp->capacity);
}

//remember to remove assert len check here
