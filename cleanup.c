/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 07:31:26 by knajmech          #+#    #+#             */
/*   Updated: 2026/05/07 10:23:47 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/env.h"
#include <errno.h>
#include <stdio.h>

t_node	*delete_node(t_node *node)
{
	t_env	*env;
	t_node	*node_next;

	node_next = node->next;
	env = node->content;
	free(env->key);
	free(env->value);
	free((t_env *) node->content);
	free(node);
	return (node_next);
}

void	error_and_cleanup(t_data *data, char *error_desc)
{
	t_list			*map_env;
	t_node			*node;
	int				i;

	if (data->env_mp)
	{
		map_env = data->env_mp->env_ptr;
		i = 0;
		while (i < CAPACITY)
		{
			node = map_env[i].head;
			while (node)
				node = delete_node(node);
			map_env[i].head = NULL;
			map_env[i].tail = NULL;
			i++;
		}
	}
	if (error_desc)
		perror(error_desc);
}
