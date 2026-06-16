/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 13:45:26 by david             #+#    #+#             */
/*   Updated: 2026/06/16 11:27:54 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "structs.h"
#include <unistd.h>

char	is_redir(char c)
{
	const char	*redirs;

	redirs = "<>";
	return (char_in_str(c, redirs));
}

bool	is_double_redir(char *input)
{
	char	cur;
	char	next;

	cur = *input;
	next = input[1];
	return (is_redir(cur) && is_redir(next));
}

//handles default cases (when there was no word infront the redirection)
int	get_redir_fd(char *word, int ttype)
{
	if (!word)
	{
		if (ttype == REDIR_APPEND || ttype == REDIR_OUTFILE)
			return (STDOUT_FILENO);
		else
		// if (ttype == REDIR_INFILE || ttype == REDIR_HEREDOC)
			return (STDIN_FILENO);
	}
	if (is_numeric(word))
		return (ft_atoi(word));
	return (-1);
}

char	*get_redir_file(char **input, t_data *dat)
{
	skip_white_metachars(input);
	return (set_word(input, dat));
}
