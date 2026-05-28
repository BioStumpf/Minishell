/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:17:19 by knajmech          #+#    #+#             */
/*   Updated: 2026/05/28 16:20:14 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

int	execute(t_ast *node, bool in_pipeline, t_data *data);

int	child_forking(t_data *data, t_ast *direction, int fd, int std_fd)
{
	if (std_fd == 1)
		close(fd - 1);
	else
		close(fd + 1);
	if (dup2(fd, std_fd) == -1)
		return (-1);
	close(fd);
	exit(execute(direction, IN_PIPELINE, data));
}

int	execute_pipe(t_ast *node, bool in_pipeline, t_data *data)
{
	pid_t	child[2];
	int		fds[2];
	int		status;

	if (pipe(fds) == -1)
		error_and_cleanup(data, "pipe");
	child[0] = fork();
	if (child[0] < 0)
		error_and_cleanup(data, "fork");
	else if (child[0] == 0)
		if (child_forking(data, node->left, fds[1], STDOUT_FILENO) == -1)
			error_and_cleanup(data, "dup2");
	child[1] = fork();
	if (child[1] < 0)
		error_and_cleanup(data, "fork");
	else if (child[1] == 0)
		if (child_forking(data, node->right, fds[0], STDIN_FILENO) == -1)
			error_and_cleanup(data, "dup2");
	waitpid(child[0], NULL, 0);
	waitpid(child[1], &status, 0);
	if (in_pipeline)
		exit (WEXITSTATUS(status));
	return (WEXITSTATUS(status));
}

int	execute_or(t_ast *node, bool in_pipeline, t_data *data)
{
	int	status;

	status = execute(node->left, NO_PIPELINE, data);
	if (status)
		status = execute(node->right, NO_PIPELINE, data);
	if (in_pipeline)
		exit(status);
	return (status);
}

int	execute_and(t_ast *node, bool in_pipeline, t_data *data)
{
	int	status;

	status = execute(node->left, NO_PIPELINE, data);
	if (!status)
		status = execute(node->right, NO_PIPELINE, data);
	if (in_pipeline)
		exit(status);
	return (status);
}

int	execute(t_ast *node, bool in_pipeline, t_data *data)
{
	if (node->type == AND)
		return (execute_and(node, in_pipeline, data));
	else if (node->type == OR)
		return (execute_or(node, in_pipeline, data));
	else if (node->type == PIPE)
		return (execute_pipe(node, in_pipeline, data));
	else if (node->type == CMD && is_builtin(node->cmd_argv[0]) > -1)
		return (execute_builtin(node, in_pipeline, data));
	else
		return (execute_extern(node, in_pipeline, data));
}

int	coordinate_exec(t_data *data)
{
	t_ast	*node;

	assert(data->ast && data->ast.start);
	node = data->ast.start;
	execute(node, NO_PIPELINE, data);
}
