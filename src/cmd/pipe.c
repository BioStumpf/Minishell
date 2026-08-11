/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 12:08:14 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/07 10:24:57 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "execution.h"
#include "err.h"
#include "parsing.h"

static void	launch_childp(t_ast *direction, int *fds, int std_fd,
		t_pipe_manager *pipe_info)
{
	if (std_fd == STDOUT_FILENO)
	{
		if (pipe_info->child[0] == -1)
			return (set_error(pipe_info->data, ERR_SYS, NULL));
		else if (pipe_info->child[0] == 0)
			close(fds[0]);
	}
	else
	{
		if (pipe_info->child[1] == -1)
			return (set_error(pipe_info->data, ERR_SYS, NULL));
		else if (pipe_info->child[1] == 0)
			close(fds[1]);
	}
	pipe_info->in_pipeline = IN_PIPELINE;
	if (dup2(fds[std_fd], std_fd) == -1)
	{
		pipe_info->data->err = ERR_SYS;
		g_ret = 1;
	}
	close(fds[std_fd]);
	if (fatal_error(pipe_info->data))
	{
		close_heredocs(pipe_info->data);
		cleanup_child(pipe_info->data, pipe_info);
	}
	return (execute(direction, pipe_info));
}

void	exec_pipe(t_ast *node, t_pipe_manager *pipe_info)
{
	int		status;
	int		fds[2];

	status = 0;
	if (pipe(fds) == -1)
		set_error(pipe_info->data, ERR_SYS, NULL);
	pipe_info->child[0] = fork();
	if (pipe_info->child[0] <= 0)
		launch_childp(node->left, fds, STDOUT_FILENO, pipe_info);
	pipe_info->child[1] = fork();
	if (pipe_info->child[1] <= 0)
		launch_childp(node->right, fds, STDIN_FILENO, pipe_info);
	close_fds(fds, 2);
	if (pipe_info->child[0] != -1)
		waitpid(pipe_info->child[0], NULL, 0);
	if (pipe_info->child[1] != -1)
		waitpid(pipe_info->child[1], &status, 0);
	if (WIFEXITED(status))
		g_ret = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_ret = 128 + WTERMSIG(status);
	if (pipe_info->in_pipeline)
		return (close_heredocs(pipe_info->data),
			cleanup_child(pipe_info->data, pipe_info));
}
