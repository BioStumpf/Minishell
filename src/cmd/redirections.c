/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 09:24:30 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/04 11:50:59 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "env.h"
#include "execution.h"
#include "builtins.h"

/*
int	fd_assign(enum e_token type, char *file_name, t_data *data)
{
	int	fd;

	if (type == REDIR_INFILE)
		fd = open(file);
	else if (type == REDIR_OUTFILE)
		fd = open(file);
	
	else if (type == REDIR_HEREDOC)
		fd = open(file);
	
	else if (type == REDIR_APPEND)
		fd = open(file);
	if (fd == -1)
		error_and_cleanup(data, "open", 0);
}*/

void	redirections(t_data *data, t_ast *redir, char **cmd)
{
	int	saved_fd;
	int	file_fd;
	int	double_or_single;

	double_or_single = 1;
	if (!redir)
	{
		which_builtin(data, cmd, is_builtin(cmd[0]));
		return ;
	}
	file_fd = open(redir->out_redir_file,
				O_CREAT | O_CREAT | O_WRONLY, 0664);
	saved_fd = dup(redir->in_redir_fd);
	dup2(file_fd, redir->in_redir_fd);
	close(file_fd);
	redirections(data, redir->left, cmd);
	dup2(saved_fd, redir->in_redir_fd);
	close(saved_fd);
}

