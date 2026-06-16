/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 13:45:26 by david             #+#    #+#             */
/*   Updated: 2026/06/16 17:33:01 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "structs.h"
#include <unistd.h>

//handles default cases (when there was no word infront the redirection)
static void	redir_fd(t_node *redir, t_node *fd, t_node *before_fd)
{
	if (fd && tok_type(fd) == WORD && !tok_space(fd)
		&& is_numeric(tok_word(fd)))
	{
		before_fd->next = redir;
		set_redir_fd(redir, ft_atoi(tok_word(fd)));
		ft_lstdelone(fd, free_token);
	}
	else if (tok_type(redir) == REDIR_APPEND || tok_type(redir) == REDIR_OUTFILE)
		return (set_redir_fd(redir, STDOUT_FILENO));
	else
		return (set_redir_fd(redir, STDIN_FILENO));
}

// static char	*get_redir_file(t_node *redir, t_node *file, t_node *after_file)
// {
// }

static bool	is_redir(enum e_token ttype)
{
	return (ttype == REDIR_APPEND || ttype == REDIR_HEREDOC
			|| ttype == REDIR_INFILE || ttype == REDIR_OUTFILE);
}

void	refine_redirs(t_list *lst)
{
	t_node	*cur;
	t_node	*prev;

	cur = lst->head;
	prev = NULL;
	while (cur && cur->next)
	{
		if (is_redir(tok_type(cur->next)))
			redir_fd(cur->next, cur, prev);
		// if (is_redir(tok_type(cur)))
		// 	redir_file(cur, cur->next, cur->next->next);
		prev = cur;
		cur = cur->next;
	}
}
