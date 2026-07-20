/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 09:24:30 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/20 10:23:24 by knajmech         ###   ########.fr       */
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
		fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == REDIR_HEREDOC)
	{
		heredoc(data, redir);
		fd = get_fd(redir);
	}
	else
		fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd == -1)
		error_and_cleanup(data, "open", 0);
	return (fd);
}

void	redirect_extern(t_data *data, t_ast *redir, t_ast *p_dir)
{
	int	saved_fd;
	int	file_fd;

	if (!redir)
	{
		exec_extern(p_dir, data->pipe_info);
		return ;
		error_and_cleanup(data, "execve", data->ret_code);
	}
	saved_fd = dup(get_fd(redir));
	file_fd = fd_assign(redir->type, get_operand(redir), data, redir);
	dup2(file_fd, get_fd(redir));
	close(file_fd);
	redirect_extern(data, redir->left, redir);
	dup2(saved_fd, get_fd(redir));
	close(saved_fd);
}

void	redirect_builtin(t_data *data, t_ast *redir, char **cmd)
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
	redirect_builtin(data, redir->left, cmd);
	dup2(saved_fd, get_fd(redir));
	close(saved_fd);
}

