/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 09:24:30 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/30 12:39:20 by dstumpf          ###   ########.fr       */
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

	if (type == REDIR_INFILE)
		fd = open(file_name, O_RDONLY);
	else if (type == REDIR_OUTFILE)
		fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == REDIR_HEREDOC)
		fd = reopen_heredoc(get_open_fd(redir));
	else
		fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd == -1)
		return (set_error(data, ERR_OPEN), 0);
	return (fd);
}

void	close_fds(int first_fd, int last_fd)
{
	if (first_fd == -1)
		return ;
	while (first_fd <= last_fd)
	{
		close(first_fd);
		first_fd++;
	}
}

void	redirect_extern(t_data *data, t_ast *redir, int first_fd)
{
	int	file_fd;

	if (!redir)
	{
		extern_child_wrapper(data->pipe_info->cmd_node, data->pipe_info);
		return ;
	}
	file_fd = fd_assign(redir->type, get_operand(redir), data, redir);
	dup2(file_fd, get_fd(redir));
	close(file_fd);
	redirect_extern(data, redir->left, first_fd);
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

