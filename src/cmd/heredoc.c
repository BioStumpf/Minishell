/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:17:01 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/27 16:24:20 by knajmech         ###   ########.fr       */
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
#include <parsing.h>
#include "err.h"

void	heredoc(t_data *data, t_ast *node)
{
	int		fd;
	char	*given_line;

	fd = open("/tmp/.heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (!fd)
	{
		set_error(data, ERR_OPEN);
		return ;
	}
	while (1)
	{
		errno = 0;
		given_line = readline("> ");
		if (errno)
		{
			close(fd);
			set_error(data, ERR_MALLOC);
			return ;
		}
		if (!ft_strncmp(given_line, get_av(node)[0],
					ft_strlen(get_av(node)[0])))
			break ;
		ft_putstr_fd(given_line, fd);
		free(given_line);
	}
	free(given_line);
	if (dup2(get_fd(node), fd))
	{
		close(get_fd(node));
		set_error(data, ERR_DUP);
	}
	unlink("/tmp/.heredoc");
}

