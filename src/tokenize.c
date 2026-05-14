/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:15:50 by dstumpf           #+#    #+#             */
/*   Updated: 2026/05/14 17:53:48 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"
#include "parsing.h"
#include "unistd.h"

//after knowing the current char is a metachar, check if its a double (&& || >> <<)
//an invalid one (; & \\) -> note that these are not supposed to be handled
//whitespace metachar that we should skip (SPACE TAB \n)
//or else a valid single metachar ( | < > ')' '(' )
static void	meta_token(char **input, t_node *new, char metachar)
{
	if (is_double_metachar(**input) && (*input)[1] == metachar)
	{
		(*input) = (*input) + 2;
		set_token_node(new, double_ttype(metachar), NULL);
	}
	else if (invalid_metachar(metachar))
	{
		set_error(PARSE_ERR_INVALID_CHAR, metachar);
		return ;
	}
	else if (skip_metachar(metachar))
	{
		(*input)++;
		return ;
	}
	else
	{
		(*input)++;
		set_token_node(new, metachar, NULL);
	}
}

static void	word_token(char **input, t_node *new)
{
	char	*word;
	size_t	word_len;

	word_len = get_word_len(*input);
	word = malloc(sizeof(char) * (word_len + 1));
	if (!word)
	{
		set_error(ERR_MALLOC, NOCHAR);
		return ;
	}
	set_word(input, word, word_len);
	set_token_node(new, T_WORD, word); 
}

static void	find_next_token(char **input, t_node *new)
{
	char	metachar;

	metachar = get_metachar(**input);
	if (metachar)
		meta_token(input, new, metachar);
	else
		word_token(input, new);
}

static bool	empty_node(t_node *node)
{
	return (((t_token *)node->content)->type == T_NONE);
}

t_list	*tokenize(t_data *dat)
{
	char		*input;
	t_node		*new_node;
	t_list		*lst;

	input = dat->input;
	lst = ft_lstnew();
	if (!lst)
		return (set_error(ERR_MALLOC, NOCHAR), token_cleanup(lst, dat), NULL);
	while (*input)
	{
		new_node = new_token_node();
		if (!new_node)
			return (set_error(ERR_MALLOC, NOCHAR), token_cleanup(lst, dat), NULL);
		find_next_token(&input, new_node);
		if (evaluate_state() != OK)
			return (token_cleanup(lst, dat), NULL);
		if (empty_node(new_node))
		{
			ft_lstdelone(new_node, free_token);
			new_node = NULL;
		}
		ft_lstadd_back(lst, new_node);
	}
	return (lst);
}
