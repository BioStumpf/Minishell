/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:17:19 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/01 08:58:18 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

int	execute(t_ast *node, t_pipe_manager *pipe_info);

int	launch_childp(t_ast *direction, int *fds, int std_fd,
		t_pipe_manager *pipe_info)
{
	
	if (std_fd == 1)
	{
		close(fds[0]);
	}
	else
		close(fds[1]);
	if (dup2(fds[std_fd], std_fd) == -1)
		return (-1);
	close(fds[std_fd]);
	return (execute(direction, pipe_info));
}

int	exec_pipe(t_ast *node, t_pipe_manager *pipe_info)
{
	int		fds[2];
	pid_t	child[2];
	int		status;

	if (pipe(fds) == -1)
		error_and_cleanup(pipe_info->data, "pipe", 0);
	child[0] = fork();
	if (child[0] == -1)
		error_and_cleanup(pipe_info->data, "fork", 0);
	else if (child[0] == 0)
	{
		status = launch_childp(node->left, fds, STDOUT_FILENO, pipe_info);
		error_and_cleanup(pipe_info->data, NULL, status);
	}
	child[1] = fork();
	if (child[1] == -1)
		error_and_cleanup(pipe_info->data, "fork", 0);
	else if (child[0] == 0)
	{
		status = launch_childp(node->left, fds, STDOUT_FILENO, pipe_info);
		error_and_cleanup(pipe_info->data, NULL, status);
	}

}

int	exec_or(t_ast *node, t_pipe_manager *pipe_info)
{
	int	status;

	assert(node->left != NULL && node->right != NULL);
	pipe_info->in_pipeline = NO_PIPELINE;
	status = execute(node->left, pipe_info);
	if (status > 0)
		status = execute(node->right, pipe_info);
	if (pipe_info->in_pipeline)
		error_and_cleanup(pipe_info->data, "execution", status);
	return (status);
}

int	exec_and(t_ast *node, t_pipe_manager *pipe_info)
{
	int	status;

	assert(node->left != NULL && node->right != NULL);
	pipe_info->in_pipeline = NO_PIPELINE;
	status = execute(node->left, pipe_info);
	if (status == 0)
		status = execute(node->right, pipe_info);
	if (pipe_info->in_pipeline)
		error_and_cleanup(pipe_info->data, "execution", status);
	return (status);
}

int	execute(t_ast *node, t_pipe_manager *pipe_info)
{
	if (node->type == AND)
		return (exec_and(node, pipe_info));
	else if (node->type == OR)
		return (exec_or(node, pipe_info));
	else if (node->type == PIPE)
		return (exec_pipe(node, pipe_info));
	else if (node->type == CMD && is_builtin(node->cmd_argv[0]) > -1)
		return (exec_builtin(node, pipe_info));
	else
		return (exec_extern(node, pipe_info));
}

int	coordinate_exec(t_data *data)
{
	t_ast			*node;
	t_pipe_manager	pipe_info;

	assert(data->ast && data->ast.start);
	pipe_info.data = data;
	pipe_info.in_pipeline = NO_PIPELINE;
	pipe_info.child[0] = 0;
	pipe_info.child[1] = 0;
	node = data->ast.start;
	execute(node, &pipe_info);
}
