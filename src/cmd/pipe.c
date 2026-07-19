/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 12:08:14 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/19 15:11:11 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "execution.h"
#include "env.h"

int	launch_childp(t_ast *direction, int *fds, int std_fd,
		t_pipe_manager *pipe_info)
{
	if (std_fd == STDOUT_FILENO)
	{
		if (pipe_info->child[0] == -1)
			error_and_cleanup(pipe_info->data, "fork", 0);
		else if (pipe_info->child[0] == 0)
			close(fds[0]);
		pipe_info->in_pipeline = IN_PIPELINE;
	}
	else
	{
		if (pipe_info->child[1] == -1)
			error_and_cleanup(pipe_info->data, "fork", 0);
		else if (pipe_info->child[1] == 0)
			close(fds[1]);
		pipe_info->in_pipeline = IN_PIPELINE;
	}
	if (dup2(fds[std_fd], std_fd) == -1)
		return (-1);
	close(fds[std_fd]);
	return (execute(direction, pipe_info));
}

int	exec_pipe(t_ast *node, t_pipe_manager *pipe_info)
{
	int		fds[2];
	int		status;

	status = 0;
	if (pipe(fds) == -1)
		error_and_cleanup(pipe_info->data, "pipe", 0);
	pipe_info->child[0] = fork();
	if (pipe_info->child[0] <= 0)
		launch_childp(node->left, fds, STDOUT_FILENO, pipe_info);
	else
		pipe_info->child[1] = fork();
	if (pipe_info->child[1] <= 0)
		status = launch_childp(node->right, fds, STDIN_FILENO, pipe_info);
	close(fds[0]);
	close(fds[1]);
	if (pipe_info->child[0])
		waitpid(pipe_info->child[0], NULL, 0);
	if (pipe_info->child[1])
		waitpid(pipe_info->child[1], &status, 0);
	if (pipe_info->in_pipeline)
		error_and_cleanup(pipe_info->data, NULL, WEXITSTATUS(status));
	return (WEXITSTATUS(status));
}

