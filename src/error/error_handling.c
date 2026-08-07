/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 21:34:36 by david             #+#    #+#             */
/*   Updated: 2026/08/05 07:58:12 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "ft_printf.h"
#include "err.h"
#include "readline_sigs.h"

static int	parser_err(enum e_err err)
{
	if (err == PARSE_ERR_AND)
		return (ft_printf(2, "Parsing error near '&&'\n"), 2);
	else if (err == PARSE_ERR_UNCLOSED_QUOTES)
		return (ft_printf(2, "Parsing error, unclosed quotes\n"), 2);
	else if (err == PARSE_ERR_REDIR)
		return (ft_printf(2, "Parsing error, redirection invalid\n"), 2);
	else if (err == PARSE_ERR_PIPE)
		return (ft_printf(2, "Parsing error near '|'\n"), 2);
	else if (err == PARSE_ERR_LEFT_PARA)
		return (ft_printf(2, "Parsing error near '('\n"), 2);
	else if (err == PARSE_ERR_RIGHT_PARA)
		return (ft_printf(2, "Parsing error near ')'\n"), 2);
	else if (err == PARSE_ERR_OR)
		return (ft_printf(2, "Parsing error near '||'\n"), 2);
	else if (err == PARSE_ERR_REDIR_OUTFILE)
		return (ft_printf(2, "Parsing error near '>'\n"), 2);
	else if (err == PARSE_ERR_REDIR_INFILE)
		return (ft_printf(2, "Parsing error near '<'\n"), 2);
	else if (err == PARSE_ERR_REDIR_APPEND)
		return (ft_printf(2, "Parsing error near '>>'\n"), 2);
	else if (err == PARSE_ERR_REDIR_HEREDOC)
		return (ft_printf(2, "Parsing error near '<<'\n"), 2);
	return (0);
}

static int	print_error_get_return(enum e_err err)
{
	if (err == ERR_MALLOC)
		return (ft_printf(2, "Malloc fail\n"), 1);
	else if (err == ERR_DUP)
		return (ft_printf(2, "dup error\n"), 1);
	else if (err == ERR_PIPE)
		return (ft_printf(2, "pipe error\n"), 1);
	else if (err == ERR_READ)
		return (ft_printf(2, "read error\n"), 1);
	else if (err == ERR_OPEN)
		return (ft_printf(2, "open error\n"), 1);
	else if (err == ERR_FORK)
		return (ft_printf(2, "fork error\n"), 1);
	else if (err == ERR_EXECVE)
		return (ft_printf(2, "execve error\n"), 1);
	else if (err == EXIT_CALL)
		return (0);
	else
		return (parser_err(err));
}

void	set_error(t_data *dat, enum e_err status)
{
	dat->err = status;
	g_ret = print_error_get_return(dat->err);
}

bool	status_ok(t_data *dat)
{
	return (dat->err == OK);
}

bool	fatal_error(t_data *dat)
{
	if (dat->err <= ERR_EXECVE && dat->err >= ERR_MALLOC)
		return (true);
	return (false);
}
