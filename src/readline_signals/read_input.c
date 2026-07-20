/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 13:00:27 by david             #+#    #+#             */
/*   Updated: 2026/07/07 17:48:27 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "err.h"
#include "get_next_line.h"
#include "structs.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "readline_sigs.h"
#include <signal.h>
#include <errno.h>

void	read_terminal(t_data *dat)
{
	setup_signals(SIG_IGN, sigint_readline);
	dat->input = readline("minishell$ ");
	if (dat->input)
		add_history(dat->input);
	setup_signals(sigquit_execute, sigint_execute);
}

void	read_stdin(t_data *dat)
{
	setup_signals(sigquit_execute, sigint_execute);
	errno = 0;
	dat->input = get_next_line(STDIN_FILENO);
	if (!dat->input && errno != 0)
	{
		if (errno == ENOMEM)
			set_error(dat, ERR_MALLOC);
		else
			set_error(dat, ERR_READ);
	}
}
