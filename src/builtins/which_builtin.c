/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 09:46:08 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/17 17:50:17 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "structs.h"
#include "libft.h"
#include "builtins.h"
#include "ft_printf.h"

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (-1);
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

void	which_builtin(t_data *data, char **cmd_argv, int builtin_call)
{
	if (builtin_call == ECHO)
		return (echo_print(cmd_argv));
	else if (builtin_call == CD)
	{
		if (cmd_argv[1] && cmd_argv[2])
			return (ft_printf(2, "Minishell: cd: too many arguments\n"),
				(void)0);
		return (data->newdir = cmd_argv[1], change_dir(data));
	}
	else if (builtin_call == PWD)
		return (pworkdir(data));
	else if (builtin_call == EXPO)
		return (export_var_start(data, cmd_argv));
	else if (builtin_call == UNSET)
		return (unset_var(data->env_mp,
				data->env_mp->env_ptr, cmd_argv[1]));
	else if (builtin_call == ENV)
		return (env_var(data));
	else if (builtin_call == EXIT)
		return (exit_minishell(data, cmd_argv));
}

// int	execute_builtin(t_ast *node, bool in_pipeline, t_data *data)
// {
// 	int	builtin;
//
// 	builtin = is_builtin(node->cmd_argv[0]);
// 	if (node->out_redir_file && !in_pipeline)
// 		return (which_builtin(data, node->cmd_argv, builtin));
// 	else
// 		return (which_builtin(data, node->cmd_argv, builtin));
// }
/*void	execute_builtin(t_ast *node, bool in_pipeline, t_data *data)
{
	int	builtin;

	builtin = is_builtin(get_av(node)[0]);
	if (get_operand(node) && !in_pipeline)
		return (which_builtin(data, get_av(node), builtin));
	else
		return (which_builtin(data, get_av(node), builtin));
}*/
