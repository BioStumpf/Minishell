/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 10:20:35 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/07 10:15:13 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "err.h"
#include "ft_printf.h"
#include "libft.h"
#include "parsing.h"
#include "structs.h"
#include "get_next_line.h"
#include "readline_sigs.h"
#include <fcntl.h>
#include <errno.h>

static bool	read_input(t_data *dat, char **line)
{
	errno = 0;
	if (dat->read_input == read_terminal)
		write(2, "> ", 2);
	*line = get_next_line(STDIN_FILENO);
	if (errno != 0 && !line)
	{
		if (errno == ENOMEM)
			return (set_error(dat, ERR_SYS, NULL), false);
		else
			return (set_error(dat, ERR_SYS, NULL), false);
	}
	return (true);
}

static bool	find_limiter(char *line, char *limiter)
{
	size_t	lim_len;
	size_t	line_len;

	if (!line)
		return (ft_printf(2,
				"warning: here-document delimited by end-of-file"), true);
	lim_len = ft_strlen(limiter);
	line_len = ft_strlen(line);
	if (lim_len + 1 != line_len)
		return (false);
	if (ft_strncmp(line, limiter, lim_len) == 0)
		return (true);
	return (false);
}

void	close_heredocs(t_data *dat)
{
	int	start;
	int	end;

	if (dat->heredoc_start == 0)
		return ;
	start = dat->heredoc_start;
	end = dat->heredoc_end;
	while (start <= end)
		close(start++);
	dat->heredoc_start = 0;
	dat->heredoc_end = 0;
}

static bool	open_heredoc(t_data *dat, t_ast *node)
{
	set_open_fd(node, open("/tmp", O_TMPFILE | O_WRONLY | O_EXCL, 0600));
	if (get_open_fd(node) == -1)
		return (set_error(dat, ERR_SYS, NULL), false);
	if (dat->heredoc_start == 0)
		dat->heredoc_start = get_open_fd(node);
	dat->heredoc_end = get_open_fd(node);
	return (true);
}

void	heredoc(t_data *dat, t_ast *node, bool expand)
{
	char		*line;
	char		*expanded;
	t_exp_vec	exps;

	if (!open_heredoc(dat, node))
		return (close_heredocs(dat));
	while (1)
	{
		if (!read_input(dat, &line))
			return (close_heredocs(dat));
		if (find_limiter(line, get_operand(node)))
			return (free(line));
		if (expand)
		{
			expanded = expand_str(dat, line, KEEP_QUOTES, &exps);
			if (!expanded)
				return (free(line), close_heredocs(dat));
			free(line);
			free(exps.expansions);
			line = expanded;
		}
		ft_putstr_fd(line, get_open_fd(node));
		free(line);
	}
}
