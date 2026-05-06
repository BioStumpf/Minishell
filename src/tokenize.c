/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:15:50 by dstumpf           #+#    #+#             */
/*   Updated: 2026/05/06 16:49:32 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	double_ttype(char metachar)
{
	return (metachar * 2 + 1);
}

//note for tokens: &&, ||, >> or << the actual numeric enum value/type variable inside the token
//refers to 2 * token + 1 which is passed to new_token_node
static t_node	*meta_token(char **input, char metachar, t_parse_err *err)
{
	t_node	*node;

	if (is_double_metachar(**input) && (*input)[1] == metachar)
	{
		(*input) = (*input) + 2;
		node = new_token_node(double_ttype(metachar), NONE, NULL);
	}
	else if (invalid_metachar(metachar))
	{
		err->status = PARSE_ERR_INVALID_CHAR;
		err->invalid = metachar;
		return (NULL);
	}
	else if (skip_metachar(metachar))
		return (NULL);
	else
	{
		(*input)++;
		node = new_token_node(metachar, NONE, NULL);
	}
	if (!node)
		return (err->status = PARSE_ERR_MALLOC, NULL);
	return (node);
}

static t_node	*word_token(char **input)
{
	(void)input;
	while (**input && !get_metachar(**input))
		(*input)++;
	return (new_token_node(WORD, NONE, "test_word"));
}

static t_node	*find_next_token(char **input, t_parse_err *err)
{
	char	metachar;

	metachar = get_metachar(**input);
	if (metachar)
		return (meta_token(input, metachar, err));
	return (word_token(input));
}

t_list	*tokenize(t_data *dat)
{
	char		*input;
	t_node		*new_node;
	t_list		*lst;
	t_parse_err	err;

	err.status = PARSE_OK;
	input = dat->input;
	lst = ft_lstnew();
	if (!lst)
		token_cleanup(lst, &err);
	while (*input)
	{
		new_node = find_next_token(&input, &err);
		if (!new_node)
			token_cleanup(lst, &err);
		ft_lstadd_back(lst, new_node);
	}
	return (lst);
}
