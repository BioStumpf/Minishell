/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 12:05:48 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/01 11:02:51 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

int	is_builtin(char *cmd)
{
	assert(cmd != NULL);
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd) + 1))
		return (0);
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd) + 1))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd) + 1))
		return (2);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd) + 1))
		return (3);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd) + 1))
		return (4);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd) + 1))
		return (5);
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd) + 1))
		return (6);
	return (-1);
}

int	which_builtin(t_data *data, char **cmd_argv, int builtin_call)
{
	t_builtin	e_builtin;
	int			status;

	assert (builtin_call <= 6 && builtin_call >= 0);
	if (builtin_call == ECHO)
		return (echo_print(node->cmd_argv));
	else if (builtin_call == CD)
		return (change_dir(data));
	else if (builtin_call == PWD)
		return (pworkdir(data));
	else if (builtin_call == EXPORT)
		return (export_var(data), 0);
	else if (builtin_call == UNSET)
	{
		data->env_mp->elem_num--;
		return (unset_var(data->env_mp->env_ptr, data->input), 0);
	}
	else if (builtin_call == ENV)
		return (env_var(data), 0);
	else if (builtin_call == EXIT)
		return (exit_minishell(data), 0);
	return (-1);
}

int	execute_builtin(t_ast *node, bool in_pipeline, t_data *data)
{
	int	builtin;

	builtin = is_builtin(node->cmd_argv[0]);
	if (node->out_redir_file && !in_pipeline)
	{
		backup_fds(data->);
		return (which_builtin(data, builtin));
	}
	else
		return (which_builtin(data, builtin));
}
