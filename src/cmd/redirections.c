/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 09:24:30 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/07 12:03:32 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "structs.h"
#include "execution.h"
#include "builtins.h"
#include "err.h"

int	fd_assign(enum e_token type, char *file_name, t_data *data, t_ast *redir)
{
	int	fd;

	errno = 0;
	if (fatal_error(data))
		return (-1);
	if (type == REDIR_INFILE)
		fd = open(file_name, O_RDONLY);
	else if (type == REDIR_OUTFILE)
		fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == REDIR_HEREDOC)
		fd = reopen_heredoc(get_open_fd(redir));
	else
		fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd == -1)
		return (data->err = ERR_OPEN, data->ret = 1, perror_messaging
			(NULL, file_name), -1);
	return (fd);
}

void	redirect_extern(t_data *data, t_ast *redir)
{
	int	file_fd;

	if (!redir)
	{
		close_heredocs(data);
		extern_child_wrapper(data->pipe_info->cmd_node, data->pipe_info);
		return ;
	}
	file_fd = fd_assign(redir->type, get_operand(redir), data, redir);
	if (file_fd != -1)
	{
		errno = 0;
		if (dup2(file_fd, get_fd(redir)) == -1)
		{
			close(file_fd);
			set_error(data, ERR_DUP);
			perror_messaging("dup", NULL);
			return ;
		}
		close(file_fd);
		redirect_extern(data, redir->left);
	}
}

void	redirect_builtin(t_data *data, t_ast *redir, char **cmd)
{
	int	saved_fd;
	int	file_fd;

	if (!redir)
	{
		if (!cmd)
			return ;
		return (which_builtin(data, cmd, is_builtin(cmd[0])));
	}
	errno = 0;
	saved_fd = dup(get_fd(redir));
	if (saved_fd == -1)
		return (set_error(data, ERR_DUP), perror_messaging("dup", NULL));
	file_fd = fd_assign(redir->type, get_operand(redir), data, redir);
	if (file_fd == -1)
		return (close(saved_fd), (void)0);
	if (dup2(file_fd, get_fd(redir)) == -1)
		return (g_ret = 1, close(saved_fd), close(file_fd), (void)0);
	close(file_fd);
	redirect_builtin(data, redir->left, cmd);
	if (dup2(saved_fd, get_fd(redir)) == -1)
	{
		set_error(data, ERR_DUP);
		perror_messaging("dup", NULL);
	}
	close(saved_fd);
}
