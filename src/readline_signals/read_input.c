/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 13:00:27 by david             #+#    #+#             */
/*   Updated: 2026/07/31 15:07:22 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "err.h"
#include "get_next_line.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "readline_sigs.h"
#include <errno.h>

void	read_terminal(t_data *dat)
{
	setup_signal(SIGINT, sigint_readline);
	setup_signal(SIGQUIT, SIG_IGN);
	dat->input = readline("minishell$ ");
	if (dat->input && *dat->input)
		add_history(dat->input);
	setup_signal(SIGINT, sigint_exec);
	setup_signal(SIGQUIT, sigquit_handler);
}

void	read_stdin(t_data *dat)
{
	char	*line;

	errno = 0;
	line = get_next_line(STDIN_FILENO);
	if (!dat->input && errno != 0)
	{
		if (errno == ENOMEM)
			set_error(dat, ERR_MALLOC);
		else
			set_error(dat, ERR_READ);
	}
	dat->input = ft_strtrim(line, "\n");
	free(line);
}
