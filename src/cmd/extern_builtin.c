/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 12:11:39 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/30 11:13:35 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"
#include "env.h"
#include "err.h"
#include "ft_printf.h"

void	print_errors(bool cmd_found, t_pipe_manager *pipe_info)
{
	if (cmd_found)
		ft_printf(2, "%s: permission denied\n",
			get_av(pipe_info->cmd_node)[0]);
	else
		ft_printf(2, "%s: command not found\n",
			get_av(pipe_info->cmd_node)[0]);
}

void	extern_helper(t_pipe_manager *pipe_info, char ***env,
		char ***path_parts)
{
	*env = env_ptrptr(pipe_info->data,
			pipe_info->data->env_mp->env_ptr, *env);
	if (!*env && fatal_error(pipe_info->data))
	{
		free_out(*path_parts, ft_count_2d(*path_parts));
		free_out(*env, pipe_info->data->env_mp->elem_num);
		cleanup_child(pipe_info->data, pipe_info);
	}
	pathfinder(pipe_info, *path_parts);
	if (fatal_error(pipe_info->data))
	{
		free_out(*env, pipe_info->data->env_mp->elem_num);
		free_out(*path_parts, ft_count_2d(*path_parts) - 1);
		cleanup_child(pipe_info->data, pipe_info);
	}
	else if (!pipe_info->pathwcmd)
	{
		print_errors(pipe_info->cmd_found, pipe_info);
		free_out(*env, pipe_info->data->env_mp->elem_num);
	}
	free_out(*path_parts, ft_count_2d(*path_parts));
}

void	extern_child_wrapper(t_ast *node, t_pipe_manager *pipe_info)
{
	char	**env;
	char	**path_parts;

	env = malloc((pipe_info->data->env_mp->elem_num + 1) * sizeof(char *));
	if (!env)
	{
		set_error(pipe_info->data, ERR_MALLOC);
		cleanup_child(pipe_info->data, pipe_info);
	}
	path_parts = split_path_env(pipe_info->data);
	if (!path_parts)
	{
		set_error(pipe_info->data, ERR_MALLOC);
		free(env);
	}
	extern_helper(pipe_info, &env, &path_parts);
	if (pipe_info->pathwcmd)
		execve(pipe_info->pathwcmd, get_av(node), env);
	else
		cleanup_child(pipe_info->data, pipe_info);
	set_error(pipe_info->data, ERR_EXECVE);
	cleanup_child(pipe_info->data, pipe_info);
}

int	exec_extern(t_ast *node, t_pipe_manager *pipe_info)
{
	int	status;

	assert (pipe_info);
	if (pipe_info->in_pipeline == NO_PIPELINE)
	{
		pipe_info->child[0] = fork();
		if (pipe_info->child[0] == 0)
		{
			pipe_info->in_pipeline = IN_PIPELINE;
			redirect_extern(pipe_info->data, node);
			if (fatal_error(pipe_info->data))
				cleanup_child(pipe_info->data, pipe_info);
		}
		if (pipe_info->child[0] == -1)
			return (set_error(pipe_info->data, ERR_FORK), ERR_FORK);
		return (waitpid(pipe_info->child[0], &status, 0), status);
	}
	redirect_extern(pipe_info->data, node);
	if (fatal_error(pipe_info->data))
		cleanup_child(pipe_info->data, pipe_info);
	return (WEXITSTATUS(0));
}

int	exec_builtin(t_ast *node, t_pipe_manager *pipe_info)
{
	redirect_builtin(pipe_info->data, node->left, get_av(node));
	if (pipe_info->in_pipeline)
		cleanup_child(pipe_info->data, pipe_info);
	return (0);
}
