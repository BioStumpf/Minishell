/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 09:24:30 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/14 12:56:38 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "structs.h"
#include "env.h"
#include "execution.h"
#include "builtins.h"

int	fd_assign(enum e_token type, char *file_name, t_data *data, t_ast *redir)
{
	int	fd;

	if (type == REDIR_INFILE)
		fd = open(file_name, O_RDONLY);
	else if (type == REDIR_OUTFILE)
		fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC);
	else if (type == REDIR_HEREDOC)
	{
		heredoc(data, redir);
		fd = get_fd(redir);
	}
	else
		fd = open(file_name, O_CREAT | O_APPEND);
	if (fd == -1)
		error_and_cleanup(data, "open", 0);
	return (fd);
}

void	redirections(t_data *data, t_ast *redir, char **cmd)
{
	int	saved_fd;
	int	file_fd;

	if (!redir)
	{
		which_builtin(data, cmd, is_builtin(cmd[0]));
		return ;
	}
	saved_fd = dup(get_fd(redir));
	file_fd = fd_assign(redir->type, get_operand(redir), data, redir);
	dup2(file_fd, get_fd(redir));
	close(file_fd);
	redirections(data, redir->left, cmd);
	dup2(saved_fd, get_fd(redir));
	close(saved_fd);
}

