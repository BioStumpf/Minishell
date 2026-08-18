/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */ /*   read_input.c                                       :+:      :+:    :+:   */ /*                                                    +:+ +:+         +:+     */ /*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 13:00:27 by david             #+#    #+#             */
/*   Updated: 2026/08/17 16:31:01 by dstumpf          ###   ########.fr       */
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
	dat->input = readline("minishell$ ");
	if (dat->input && *dat->input)
		add_history(dat->input);
}

void	read_stdin(t_data *dat)
{
	char	*line;

	errno = 0;
	line = get_next_line(STDIN_FILENO);
	if (!line)
	{
		if (errno != 0)
			set_error(dat, ERR_SYS, NULL);
		dat->input = NULL;
		return ;
	}
	dat->input = ft_strtrim(line, "\n");
	free(line);
	if (!dat->input)
		set_error(dat, ERR_SYS, NULL);
}
