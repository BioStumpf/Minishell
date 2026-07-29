/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 10:20:35 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/29 19:15:09 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "err.h"
#include "ft_printf.h"
#include "libft.h"
#include "parsing.h"
#include "structs.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <errno.h>

static bool	read_input(t_data *dat, char **line)
{
	errno = 0;
	*line = get_next_line(STDIN_FILENO);
	if (errno != 0 && !line)
	{
		if (errno == ENOMEM)
			return (set_error(dat, ERR_MALLOC), false);
		else
			return (set_error(dat, ERR_READ), false);
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
	if (lim_len != line_len)
		return (false);
	if (ft_strncmp(line, limiter, line_len))
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
}

static void	make_name(char name[24], int fd)
{
	char	num[11];

	ft_strlcpy(name, "/proc/self/fd/", 15);
	ft_itoa_buff(fd, num, 11);
	ft_strlcpy(name + 14, num, 11);
}

static bool	open_heredoc(t_data *dat, t_compound *comp, int *fd)
{
	char	proc_name[25];

	*fd = open("/tmp", O_TMPFILE | O_WRONLY | O_EXCL, 0600);
	if (*fd)
		return (set_error(dat, ERR_OPEN), false);
	make_name(proc_name, *fd);
	comp->u_value.s_redir.open_fd = open(proc_name, O_RDONLY);
	if (!comp_heredoc(comp))
		return (close(*fd), set_error(dat, ERR_OPEN), false);
	if (dat->heredoc_start == 0)
		dat->heredoc_start = comp_heredoc(comp);
	dat->heredoc_end = comp_heredoc(comp);
	return (true);
}

bool	heredoc(t_data *dat, t_compound *comp, bool expand)
{
	int			fd;
	char		*line;
	char		*expanded;
	t_exp_vec	exps;

	if (!open_heredoc(dat, comp, &fd))
		return (close_heredocs(dat), false);
	while (1)
	{
		if (!read_input(dat, &line))
			return (close_heredocs(dat), false);
		if (find_limiter(line, comp_filename(comp)))
			return (free(line), true);
		if (expand)
		{
			expanded = expand_str(dat, line, KEEP_QUOTES, &exps);
			if (!expanded)
				return (close_heredocs(dat), false);
			free(line);
			free(exps.expansions);
			line = expanded;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
}
