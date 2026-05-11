/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 12:05:48 by knajmech          #+#    #+#             */
/*   Updated: 2026/05/11 09:41:19 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/builtins.h"

int	which_builtin(t_data *data, int	builtin_call)
{
	t_builtin	e_builtin;
	int			status;

	assert (builtin_call <= 6 && builtin_call >= 0);
	if (builtin_call == ECHO)
		return (echo_print(data, int flag));
	else if (builtin_call == CD)
		return (change_dir(data));
	else if (builtin_call == PWD)
		return (pworkdir(data));
	else if (builtin_call == EXPORT)
		return (export_var(data));
	else if (builtin_call == UNSET)
	{
		data->env_mp->elem_num--;
		return (unset_var(data->env_mp->env_ptr, data->input), 1);
	}
	else if (builtin_call == ENV)
		return (env_var(data));
	else if (builtin_call == EXIT)
		return (exit_Minishell(data));
	return (-1);
}
