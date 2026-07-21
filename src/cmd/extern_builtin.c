/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 12:11:39 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/20 17:11:42 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"
#include "env.h"
#include "err.h"

void	extern_helper(t_pipe_manager *pipe_info, char ***env)
{
		*env = env_ptrptr(pipe_info->data,
				pipe_info->data->env_mp->env_ptr, *env);
		pathfinder(pipe_info, split_path_env(pipe_info->data));
		if (!pipe_info->pathwcmd)
		{
			if (pipe_info->cmd_found)
				printf("%s: permission denied\n", get_av(pipe_info->cmd_node)[0]);
			else
				printf("%s: command not found\n", get_av(pipe_info->cmd_node)[0]);
			error_and_cleanup(pipe_info->data, NULL, 0);
		}
}

int	exec_extern(t_ast *node, t_pipe_manager *pipe_info)
{
	char	**env;
	int		status;
	pid_t	child;

	assert (pipe_info);
	pipe_info->cmd_found = 0;
	child = fork();
	if (child == 0)
	{
		env = malloc(pipe_info->data->env_mp->elem_num * sizeof(char *));
		if (!env)
			error_and_cleanup(pipe_info->data, "malloc", 0);
		extern_helper(pipe_info, &env);
		execve(pipe_info->pathwcmd, get_av(node), env);
		free_out(env, pipe_info->data->env_mp->elem_num);
		free(pipe_info->pathwcmd);
		clean_ast(&pipe_info->data->ast);
		free(pipe_info->data->input);
		cleanup(pipe_info->data);
		set_error(pipe_info->data, ERR_MALLOC);
	}
	waitpid(child, &status, 0);
	if (pipe_info->in_pipeline)
		exit(WEXITSTATUS(status));
	return (WEXITSTATUS(status));
}

int	exec_builtin(t_ast *node, t_pipe_manager *pipe_info)
{
	redirect_builtin(pipe_info->data, node->left, get_av(node));
	if (pipe_info->in_pipeline)
		exit(0);
	return (0);
}
