/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 13:45:26 by david             #+#    #+#             */
/*   Updated: 2026/07/27 20:53:28 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "structs.h"
#include <unistd.h>
#include "err.h"

//handles default cases (when there was no word infront the redirection)
static void	redir_fd(t_list *lst, t_node *redir, t_node *fd, t_node *before_fd)
{
	if (fd && tok_type(fd) == WORD && !tok_space(fd)
		&& ft_is_numeric(tok_word(fd)))
	{
		set_redir_fd(redir, ft_atoi(tok_word(fd)));
		ft_lstmid_rm(lst, fd, before_fd, free_token);
	}
	else if (tok_type(redir) == REDIR_APPEND
		|| tok_type(redir) == REDIR_OUTFILE)
		return (set_redir_fd(redir, STDOUT_FILENO));
	else
		return (set_redir_fd(redir, STDIN_FILENO));
}

static bool	redir_file(t_list *lst, t_node *redir, t_node *file)
{
	if (!file || tok_type(file) != WORD)
		return (false);
	set_redir_file(redir, tok_word(file));
	ft_lstmid_rm(lst, file, redir, free);
	return (true);
}

bool	is_redir(enum e_token ttype)
{
	return (ttype == REDIR_APPEND || ttype == REDIR_HEREDOC
		|| ttype == REDIR_INFILE || ttype == REDIR_OUTFILE);
}

void	refine_redirs(t_data *dat, t_list *lst)
{
	t_node	*cur;
	t_node	*prev;
	t_node	*pre_prev;

	cur = lst->head;
	prev = NULL;
	pre_prev = NULL;
	while (cur)
	{
		if (is_redir(tok_type(cur)))
		{
			redir_fd(lst, cur, prev, pre_prev);
			if (!redir_file(lst, cur, cur->next))
				return (set_error(dat, PARSE_ERR_REDIR));
		}
		pre_prev = prev;
		prev = cur;
		cur = cur->next;
	}
}

void	move_redirs(t_list *tokens)
{
	t_node	*dst;
	t_node	*prev;
	t_node	*cur;
	t_node	*src;

	dst = NULL;
	prev = NULL;
	cur = tokens->head;
	while (cur)
	{
		if (is_redir(tok_type(cur)))
		{
			src = cur;
			cur = cur->next;
			ft_lstswitch(tokens, dst, src, prev);
			dst = src;
			continue ;
		}
		if (tok_type(cur) != WORD)
			dst = cur;
		prev = cur;
		cur = cur->next;
	}
}
