/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 12:11:39 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/05 12:20:55 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
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
		*path_parts = free_out(*path_parts, ft_count_2d(*path_parts));
		*env = free_out(*env, pipe_info->data->env_mp->elem_num);
		cleanup_child(pipe_info->data, pipe_info);
	}
	pathfinder(pipe_info, *path_parts);
	if (fatal_error(pipe_info->data))
	{
		*env = free_out(*env, pipe_info->data->env_mp->elem_num);
		*path_parts = free_out(*path_parts, ft_count_2d(*path_parts) - 1);
		cleanup_child(pipe_info->data, pipe_info);
	}
	else if (!pipe_info->pathwcmd)
	{
		if (pipe_info->cmd_found)
			g_ret = 126;
		else
			g_ret = 127;
		print_errors(pipe_info->cmd_found, pipe_info);
		*env = free_out(*env, pipe_info->data->env_mp->elem_num);
	}
	*path_parts = free_out(*path_parts, ft_count_2d(*path_parts));
}

char	**fill_curr_dir(t_data *data)
{
	char **path_parts;

	path_parts = ft_calloc(2, sizeof(char *));
	if (!path_parts)
		return (set_error(data, ERR_SYS, NULL), NULL);
	path_parts[0] = ft_strdup("./");
	path_parts[1] = '\0';
	if (!path_parts[0])
		return (set_error(data, ERR_SYS, NULL), free(path_parts), NULL);
	return (path_parts);
}

void	extern_child_wrapper(t_ast *node, t_pipe_manager *pipe_info)
{
	char	**env;
	char	**path_parts;

	env = malloc((pipe_info->data->env_mp->elem_num + 1) * sizeof(char *));
	if (!env)
	{
		set_error(pipe_info->data, ERR_SYS, NULL);
		cleanup_child(pipe_info->data, pipe_info);
	}
	if (hash_search(pipe_info->data->env_mp->env_ptr, "PATH") == NULL)
		 path_parts = fill_curr_dir(pipe_info->data);
	else
		path_parts = split_path_env(pipe_info->data);
	if (fatal_error(pipe_info->data))
		return (free(env), env = NULL, cleanup_child(pipe_info->data, pipe_info));
	extern_helper(pipe_info, &env, &path_parts);
	errno = 0;
	if (pipe_info->pathwcmd)
		execve(pipe_info->pathwcmd, get_av(node), env);
	else
		cleanup_child(pipe_info->data, pipe_info);
	env = free_out(env, ft_count_2d(env));
	path_parts = free_out(path_parts, ft_count_2d(path_parts));
	perror_messaging(NULL, pipe_info->pathwcmd);
	if (pipe_info->cmd_found)
		g_ret = 126;
	else
		g_ret = 127;
	pipe_info->data->err = ERR_SYS;
	//set_error(pipe_info->data, ERR_SYS, NULL);
	cleanup_child(pipe_info->data, pipe_info);
}

void	exec_extern(t_ast *node, t_pipe_manager *pipe_info)
{
	int	status;

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
		else if (pipe_info->child[0] == -1)
			return (set_error(pipe_info->data, ERR_SYS, NULL));
		waitpid(pipe_info->child[0], &status, 0);
		if (WIFEXITED(status))
			g_ret = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_ret = 128 + WTERMSIG(status);
		return ;
	}
	redirect_extern(pipe_info->data, node);
	if (fatal_error(pipe_info->data))
		cleanup_child(pipe_info->data, pipe_info);
}

void	exec_builtin(t_ast *node, t_pipe_manager *pipe_info)
{
	if (node->type == CMD && is_builtin(get_av(node)[0]) > -1)
		redirect_builtin(pipe_info->data, node->left, get_av(node));
	else
		redirect_builtin(pipe_info->data, node, NULL);
	if (pipe_info->in_pipeline == IN_PIPELINE)
	{
		close_heredocs(pipe_info->data);
		cleanup_child(pipe_info->data, pipe_info);
	}
}
