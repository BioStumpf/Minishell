/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 21:34:36 by david             #+#    #+#             */
/*   Updated: 2026/08/07 12:32:35 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "ft_printf.h"
#include "err.h"

static int	print_error_get_return(enum e_err err, const char *str)
{
	if (err == ERR_SYS)
		return (perror("minishell"), 1);
	if (err == PARSE_ERR_UNCLOSED_QUOTES)
		return (ft_printf(2, "Minishell: syntax error, unclosed quotes\n"), 2);
	else if (err == PARSE_ERR_UNCLOSED_PARA)
		return (ft_printf(2,
				"Minishell: syntax error, unclosed paranthesis\n"), 2);
	else if (err == PARSE_ERR_REDIR)
	{
		if (!str)
			return (ft_printf(2, "Minishell: ambiguous redirect\n"), 2);
		return (ft_printf(2, "Minishell: %s: ambiguous redirect\n", str), 1);
	}
	else if (err == PARSE_ERR_TREE)
		return (ft_printf(2,
				"Minishell: syntax error near unexpected token \'%s\'\n",
				str), 2);
	else
		return (0);
}

void	set_error(t_data *dat, enum e_err status, const char *str)
{
	dat->err = status;
	g_ret = print_error_get_return(dat->err, str);
}

bool	status_ok(t_data *dat)
{
	return (dat->err == OK);
}

bool	fatal_error(t_data *dat)
{
	return (dat->err == ERR_SYS);
}
