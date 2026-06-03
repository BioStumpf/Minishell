/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 09:24:30 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/03 11:59:00 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	redirections(t_data *data, t_ast *redir, char **cmd)
{
	int	saved_fd;
	int	file_fd;

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

