/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 12:08:14 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/30 11:15:56 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "execution.h"
#include "env.h"
#include "err.h"

int	launch_childp(t_ast *direction, int *fds, int std_fd,
		t_pipe_manager *pipe_info)
{
	if (std_fd == STDOUT_FILENO)
	{
		if (pipe_info->child[0] == -1)
			return (set_error(pipe_info->data, ERR_FORK), -1);
		else if (pipe_info->child[0] == 0)
			close(fds[0]);
		pipe_info->in_pipeline = IN_PIPELINE;
	}
	else
	{
		if (pipe_info->child[1] == -1)
			return (set_error(pipe_info->data, ERR_FORK), -1);
		else if (pipe_info->child[1] == 0)
			close(fds[1]);
		pipe_info->in_pipeline = IN_PIPELINE;
	}
	if (dup2(fds[std_fd], std_fd) == -1)
		set_error(pipe_info->data, ERR_DUP);
	close(fds[std_fd]);
	if (fatal_error(pipe_info->data))
		return (-1);
	return (execute(direction, pipe_info));
}

int	exec_pipe(t_ast *node, t_pipe_manager *pipe_info)
{
	int		fds[2];

	if (pipe(fds) == -1)
		set_error(pipe_info->data, ERR_PIPE);
	pipe_info->child[0] = fork();
	if (pipe_info->child[0] <= 0)
		launch_childp(node->left, fds, STDOUT_FILENO, pipe_info);
	pipe_info->child[1] = fork();
	if (pipe_info->child[1] <= 0)
	{
		g_ret = launch_childp(node->right, fds, STDIN_FILENO, pipe_info);
		cleanup_child(pipe_info->data, pipe_info);
	}
	pipe_info->data->pipe_info = pipe_info;
	close_fds(fds, 2);
	waitpid(pipe_info->child[0], NULL, 0);
	waitpid(pipe_info->child[1], (int *)&g_ret, 0);
	if (pipe_info->in_pipeline)
		cleanup_child(pipe_info->data, pipe_info);
	if (WIFEXITED(g_ret))
		return (WEXITSTATUS(g_ret));
	else if (WIFSIGNALED(g_ret))
		return (128 + WTERMSIG(g_ret));
	return (-1);
}
