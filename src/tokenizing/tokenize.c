/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:15:50 by dstumpf           #+#    #+#             */
/*   Updated: 2026/06/16 13:45:51 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "err.h"

//after knowing the current char is a metachar, check if its a double (&& || >> <<)
//if not double metachar but and and, we dont want to do anything because in our minishell this one does not have special meaning
//whitespace metachar that we should skip (SPACE TAB \n)
//or else a valid single metachar ( | < > ')' '(' )
static bool	meta_token(char **input, t_node *new)
{
	if (is_double_metachar(*input))
	{
		set_tok(new, double_tok_type(**input));
		(*input) = (*input) + 2;
		return (true);
	}
	else if (is_single_metachar(**input))
	{
		set_tok(new, **input);
		(*input)++;
		return (true);
	}
	return (false);
}

static void	word_token(char **input, t_node *new, t_data *dat)
{
	bool	space;
	char	*word;
	size_t	word_len;

	word_len = get_word_len(*input, dat);
	if (!status_ok(dat))
		return ;
	word = malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (set_error(dat, ERR_MALLOC), (void)0);
	set_word(input, word, word_len);
	space = is_whitespace_metachar(**input);
	set_word_tok(new, WORD, word, space); 
}

static void	find_next_token(char **input, t_node *new, t_data *dat)
{
	bool	is_metatok;

	//what if char **input is nothing?
	is_metatok = meta_token(input, new);
	if (!is_metatok)
		word_token(input, new, dat);
}

t_list	*tokenize(t_data *dat)
{
	char		*input;
	t_node		*node;
	t_list		*lst;

	input = dat->input;
	lst = ft_lstnew();
	node = NULL;
	if (!lst)
		return (token_cleanup(lst, ERR_MALLOC, dat, node), NULL);
	while (skip_whitespace(&input))
	{
		node = new_token_node();
		if (!node)
			return (token_cleanup(lst, ERR_MALLOC, dat, node), NULL);
		find_next_token(&input, node, dat);
		if (!status_ok(dat))
			return (token_cleanup(lst, OK, dat, node), NULL);
		ft_lstadd_back(lst, node);
	}
	return (lst);
}
