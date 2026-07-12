/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 07:31:26 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/04 11:52:04 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <execution.h>
#include "env.h"

void	error_and_cleanup(t_data *data, char *error_desc, int status)
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
	exit (status);
}
