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
#include "execution.h"
#include <asm-generic/errno-base.h>
#include <readline/readline.h>
#include "parsing.h"
#include <sys/stat.h>

void	clean_extern_helper(t_pipe_manager *pipe_info, char ***env, char ***pb)
{
	*env = free_out(*env, pipe_info->data->env_mp->elem_num);
	*pb = free_out(*pb, ft_count_2d(*pb));
	cleanup_child(pipe_info->data, pipe_info);
}

int	check_path(char *cmd)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf) == -1)
		return (ENOENT);
	else if (S_ISDIR(statbuf.st_mode))
		return (EISDIR);
	if (!(statbuf.st_mode & S_IXUSR))
		return (EACCES);
	return (0);
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
