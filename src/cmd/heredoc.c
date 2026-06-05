/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:17:01 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/04 09:45:04 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/main.h"

void	heredoc(t_data *data, t_ast *node)
{
	int		fd;
	char	*eof_id;
	char	*given_line;

	fd = open("/tmp/.heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	eof_id = node->cmd_argv[0];
	while (ft_strncmp(eof_id, $`const char *s2`, $`size_t n`)
	{
		
	}

}
