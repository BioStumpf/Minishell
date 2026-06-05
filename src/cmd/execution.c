/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:17:19 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/04 11:42:47 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "execution.h"
#include "env.h"
#include "builtins.h"

int	execute(t_ast *node, t_pipe_manager *pipe_info);

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

	if (pipe(fds) == -1)
		error_and_cleanup(pipe_info->data, "pipe", 0);
	pipe_info->child[0] = fork();
	if (pipe_info->child[0] <= 0)
		launch_childp(node->left, fds, STDOUT_FILENO, pipe_info);
	pipe_info->child[1] = fork();
	if (pipe_info->child[1] <= 0)
		launch_childp(node->right, fds, STDIN_FILENO, pipe_info);
	close(fds[0]);
	close(fds[1]);
	waitpid(pipe_info->child[0], NULL, 0);
	waitpid(pipe_info->child[1], &status, 0);
	if (pipe_info->in_pipeline)
		error_and_cleanup(pipe_info->data, NULL, WEXITSTATUS(status));
	return (WEXITSTATUS(status));
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
		error_and_cleanup(pipe_info->data, NULL, status);
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
		error_and_cleanup(pipe_info->data, NULL, status);
	return (status);
}

int	exec_extern(t_ast *node, t_pipe_manager *pipe_info)
{
	char	**env;
	int		status;
	pid_t	child;

	pipe_info->cmd_found = 0;
	child = fork();
	if (child == 0)
	{
		env = malloc(pipe_info->data->env_mp->elem_num * sizeof(char *));
		if (!env)
			error_and_cleanup(pipe_info->data, "malloc", 0);
		env = env_ptrptr(pipe_info->data,
				pipe_info->data->env_mp->env_ptr, env);
		pathfinder(pipe_info, split_path_env(pipe_info->data), node->cmd_argv);
		if (!pipe_info->pathwcmd)
		{
			if (pipe_info->cmd_found)
				printf("%s: permission denied\n", node->cmd_argv[0]);
			else
				printf("%s: command not found\n", node->cmd_argv[0]);
			error_and_cleanup(pipe_info->data, NULL, 0);
		}
		execve(pipe_info->pathwcmd, node->cmd_argv, env);
		free_out(env, pipe_info->data->env_mp->elem_num);
		free(pipe_info->pathwcmd);
		error_and_cleanup(pipe_info->data, "execve", 0);
	}
	waitpid(child, &status, 0);
	if (pipe_info->in_pipeline)
		exit(WEXITSTATUS(status));
	return (WEXITSTATUS(status));
}

int	exec_builtin(t_ast *node, t_pipe_manager *pipe_info)
{
	redirections(pipe_info->data, node->left, node->cmd_argv);
	return (0);
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
	else if (node->type == CMD)
		return (pipe_info->pathwcmd = NULL, exec_extern(node, pipe_info));
	else
		return (0);
}

void	coordinate_exec(t_data *data)
{
	t_ast			*node;
	t_pipe_manager	pipe_info;

	assert(data->ast.start != NULL);
	pipe_info.data = data;
	pipe_info.in_pipeline = NO_PIPELINE;
	pipe_info.child[0] = 0;
	pipe_info.child[1] = 0;
	node = data->ast.start;
	execute(node, &pipe_info);
}
