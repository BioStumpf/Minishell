/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 10:08:30 by david             #+#    #+#             */
/*   Updated: 2026/08/17 19:43:41 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "err.h"
#include "ft_printf.h"
#include "libft.h"
#include "parsing.h"
#include "structs.h"
#include "readline_sigs.h"
#include <fcntl.h>
#include <readline/readline.h>

static bool	read_input(t_data *dat, char **line)
{
	if (dat->read_input == read_terminal)
		*line = readline("> ");
	else
		*line = readline("");
	if (g_ret == 128 + SIGINT)
		return (free(*line), *line = NULL, false);
	return (true);
}

static bool	find_limiter(char *line, char *limiter)
{
	size_t	lim_len;
	size_t	line_len;

	if (!line)
		return (ft_printf(2,
				"warning: here-document delimited by end-of-file\n"), true);
	lim_len = ft_strlen(limiter);
	line_len = ft_strlen(line);
	if (lim_len != line_len)
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

static bool	open_heredoc(t_data *dat, t_compound *comp)
{
	comp_set_open_fd(comp, open("/tmp", O_TMPFILE | O_WRONLY | O_EXCL, 0600));
	if (comp_open_fd(comp) == -1)
		return (set_error(dat, ERR_SYS, NULL), false);
	if (dat->heredoc_start == 0)
		dat->heredoc_start = comp_open_fd(comp);
	dat->heredoc_end = comp_open_fd(comp);
	return (true);
}

void	prompt_heredoc(t_data *dat, t_compound *comp)
{
	char		*line;
	char		*expanded_str;
	t_exp_vec	exps;

	ft_bzero(&exps, sizeof(t_exp_vec));
	expanded_str = remove_dollar_quotes(&exps, comp_filename(comp), RM_QUOTES);
	if (!expanded_str)
		return (set_error(dat, ERR_SYS, NULL));
	comp_set_expand(comp,
		(ft_strlen(expanded_str) == ft_strlen(comp_filename(comp))));
	free(comp_filename(comp));
	comp_set_filename(comp, expanded_str);
	if (!open_heredoc(dat, comp))
		return (close_heredocs(dat));
	while (1)
	{
		if (!read_input(dat, &line))
			return (close_heredocs(dat));
		if (find_limiter(line, comp_filename(comp)))
			return (free(line));
		ft_putendl_fd(line, comp_open_fd(comp));
		free(line);
	}
}
