/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:15:50 by dstumpf           #+#    #+#             */
/*   Updated: 2026/05/17 21:37:34 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"
#include "parsing.h"
#include "unistd.h"

//after knowing the current char is a metachar, check if its a double (&& || >> <<)
//if not double metachar but and and, we dont want to do anything because in our minishell this one does not have special meaning
//whitespace metachar that we should skip (SPACE TAB \n)
//or else a valid single metachar ( | < > ')' '(' )
static int	meta_token(char **input, t_node *new)
{
	if (is_double_metachar(*input))
	{
		set_token_node(new, double_tok_type(**input), NOWORD);
		(*input) = (*input) + 2;
		return (2);
	}
	else if (is_whitespace_metachar(**input))
	{
		(*input)++;
		return (1);
	}
	else if (is_single_metachar(**input))
	{
		set_token_node(new, **input, NOWORD);
		(*input)++;
		return (1);
	}
	return (0);
}

static void	word_token(char **input, t_node *new, t_data *dat)
{
	char	*word;
	size_t	word_len;

	word_len = get_word_len(*input, dat);
	if (!status_ok(dat))
		return ;
	word = malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (set_error(dat, ERR_MALLOC), (void)0);
	set_word(input, word, word_len);
	set_token_node(new, T_WORD, word); 
}

static void	find_next_token(char **input, t_node *new, t_data *dat)
{
	int			token_bytes;

	//what if char **input is nothing?
	token_bytes = meta_token(input, new);
	if (token_bytes == 0)
		word_token(input, new, dat);
}

static bool	empty_node(t_node *node)
{
	return (((t_token *)node->content)->type == T_NONE);
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
	while (*input)
	{
		node = new_token_node();
		if (!node)
			return (token_cleanup(lst, ERR_MALLOC, dat, node), NULL);
		find_next_token(&input, node, dat);
		if (!status_ok(dat))
			return (token_cleanup(lst, OK, dat, node), NULL);
		if (empty_node(node))
		{
			ft_lstdelone(node, free_token);
			node = NULL;
		}
		ft_lstadd_back(lst, node);
	}
	return (lst);
}
