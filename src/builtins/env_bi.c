/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 09:10:22 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/17 14:33:17 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "structs.h"
#include "err.h"
#include <stdio.h>

void	print_var(t_list *env_arr, int capacity)
{
	int	i;

	i = 0;
	while (i < capacity)
	{
		if (env_arr[i].head)
			print_expolist(env_arr[i].head);
		i++;
	}
}

void	print_list(t_node *env_list)
{
	t_env	*node;
	int		i;

	i = 0;
	while (env_list)
	{
		node = env_list->content;
		if (node->value)
			printf("%s=%s\n", node->key, node->value);
		env_list = env_list->next;
		i++;
	}
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
			print_list(env_arr[i].head);
		i++;
	}
	g_ret = 0;
}
//remember to remove assert len check here
