/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 21:34:36 by david             #+#    #+#             */
/*   Updated: 2026/06/22 14:18:56 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "ft_printf.h"

static int	token_error(enum e_token err)
{
	if (err == AND)
		return (ft_printf(2, "Parsing error near '&&'\n"), 2);
	else if (err == PIPE)
		return (ft_printf(2, "Parsing error near '|'\n"), 2);
	else if (err == LEFT_PARA)
		return (ft_printf(2, "Parsing error near '('\n"), 2);
	else if (err == RIGHT_PARA)
		return (ft_printf(2, "Parsing error near ')'\n"), 2);
	else if (err == OR)
		return (ft_printf(2, "Parsing error near '||'\n"), 2);
	return (0);
}

static int	print_error_get_return(enum e_err err)
{
	if (err == ERR_MALLOC)
		return (ft_printf(2, "Malloc fail\n"), 1);
	else if (err == PARSE_ERR_UNCLOSED_QUOTES)
		return (ft_printf(2, "Parsing error, unclosed quotes\n"), 2);
	else if (err == PARSE_ERR_REDIR)
		return (ft_printf(2, "Parsing error, redirection invalid\n"), 2);
	else if (err == ERR_DUP)
		return (ft_printf(2, "dup error\n"), 2);
	else if (err == ERR_PIPE)
		return (ft_printf(2, "pipe error\n"), 2);
	else if (err == ERR_READ)
		return (ft_printf(2, "read error\n"), 2);
	else if (err == ERR_OPEN)
		return (ft_printf(2, "open error\n"), 2);
	else if (err == ERR_FORK)
		return (ft_printf(2, "fork error\n"), 2);
	else if (err == ERR_SIG)
		return (ft_printf(2, "signal error\n"), 2);
	else
		return (token_error((enum e_token)err));
}

void	set_error(t_data *dat, enum e_err status)
{
	dat->err = status;
	dat->ret_code = print_error_get_return(dat->err);
}

bool	status_ok(t_data *dat)
{
	return (dat->err == OK);
}

bool	fatal_error(t_data *dat)
{
	return (dat->err == ERR_MALLOC);
}
