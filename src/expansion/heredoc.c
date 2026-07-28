/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 10:20:35 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/28 15:48:21 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "err.h"
#include "ft_printf.h"
#include "libft.h"
#include "parsing.h"
#include "structs.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <errno.h>

// void	make_name(char name[25], int id)
// {
// 	char	num[11];
// 	if (id == 0)
// 		ft_strlcpy(name, "/tmp/.heredoc_", 15);
// 	ft_itoa_buff(id, num, 11);
// 	ft_strlcpy(name + 14, num, 11);
// }
//
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

static bool	open_heredoc(t_data *dat, t_compound *comp)
{
	comp->u_value.s_redir.open_fd
		= open(".heredoc", O_CREAT | O_RDWR | O_EXCL, 0600);
	if (!comp_heredoc(comp))
		return (set_error(dat, ERR_OPEN), close_heredocs(dat), false);
	if (dat->heredoc_start == 0)
		dat->heredoc_start = comp_heredoc(comp);
	dat->heredoc_end = comp_heredoc(comp);
	return (true);
}

bool	heredoc(t_data *dat, t_compound *comp, bool expand)
{
	char		*line;
	char		*expanded;
	t_exp_vec	exps;

	if (!open_heredoc(dat, comp))
		return (false);
	while (1)
	{
		if (!read_input(dat, &line))
			return (unlink(".heredoc"), close_heredocs(dat), false);
		if (find_limiter(line, comp_filename(comp)))
			return (unlink(".heredoc"), free(line), true);
		if (expand)
		{
			expanded = expand_str(dat, line, KEEP_QUOTES, &exps);
			if (!expanded)
				return (unlink(".heredoc"), close_heredocs(dat), false);
			free(line);
			free(exps.expansions);
			line = expanded;
		}
		ft_putstr_fd(line, comp_heredoc(comp));
		free(line);
	}
}
