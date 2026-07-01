/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 09:24:30 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/12 11:55:40 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		fd = open(file_name, O_CREAT | O_WRONLY);
	else if (type == REDIR_HEREDOC)
	{
		heredoc(data, redir);
		fd = redir->in_redir_fd;
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
	saved_fd = dup(redir->in_redir_fd);
	file_fd = fd_assign(redir->type, redir->out_redir_file, data, redir);
	dup2(file_fd, redir->in_redir_fd);
	close(file_fd);
	redirections(data, redir->left, cmd);
	dup2(saved_fd, redir->in_redir_fd);
	close(saved_fd);
}

