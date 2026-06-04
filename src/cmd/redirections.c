/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 09:24:30 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/04 10:40:00 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/main.h"

int	fd_assign(enum e_token type, char *file_name)
{
	int	fd;


}

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
	if (redir->type == T_)

	file_fd = open(redir->out_redir_file,
				O_CREAT | O_CREAT | O_WRONLY, 0664);
	saved_fd = dup(redir->in_redir_fd);
	dup2(file_fd, redir->in_redir_fd);
	close(file_fd);
	redirections(data, redir->left, cmd);
	dup2(saved_fd, redir->in_redir_fd);
	close(saved_fd);
}

