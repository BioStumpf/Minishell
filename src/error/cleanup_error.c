/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:22:15 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/30 16:30:03 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "execution.h"
#include "env.h"
#include "structs.h"
#include "err.h"
#include <readline/readline.h>
#include "parsing.h"

void	close_fds(int *fd_arr, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		close(fd_arr[i]);
		i++;
	}
}

void	cleanup_env(t_data *data)
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

void	cleanup_normal(t_data *data)
{
	cleanup_env(data);
}

void	cleanup_child(t_data *data, t_pipe_manager *pipe_info)
{
	rl_clear_history();
	cleanup_env(data);
	free(data->input);
	free(pipe_info->pathwcmd);
	clean_ast(&data->ast);
	exit(g_ret);
}
