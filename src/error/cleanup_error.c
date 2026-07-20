/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:22:15 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/20 16:56:49 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "execution.h"
#include "env.h"
#include "structs.h"
#include "err.h"

void	cleanup(t_data *data)
{
	int		i;
	t_list	*map_env;
	t_node	*node;

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
	return ;
}
