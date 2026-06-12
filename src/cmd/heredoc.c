/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:17:01 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/12 08:21:00 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "structs.h"
#include "get_next_line.h"
#include "execution.h"
#include "libft.h"
#include "env.h"
#include <errno.h>
#include <stdlib.h>

void	heredoc(t_data *data, t_ast *node)
{
	int		fd;
	char	*given_line;

	fd = open("/tmp/.heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (!fd)
		error_and_cleanup(data, "open", 0);
	while (1)
	{
		errno = 0;
		given_line = readline(">");
		if (errno)
			error_and_cleanup(data, "malloc", 0);
		if (!ft_strncmp(given_line, node->cmd_argv[0],
					ft_strlen(node->cmd_argv[0])))
			break ;
		ft_putstr_fd(given_line, fd);
		free(given_line);
	}
	free(given_line);
	if (dup2(node->in_redir_fd, fd))
		error_and_cleanup(data, "dup", 0);
}
