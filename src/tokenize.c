/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:15:50 by dstumpf           #+#    #+#             */
/*   Updated: 2026/05/06 22:16:04 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "unistd.h"

static int	double_ttype(char metachar)
{
	return (metachar * 2 + 1);
}

//note for tokens: &&, ||, >> or << the actual numeric enum value/type variable inside the token
//refers to 2 * token + 1 which is passed to new_token_node

//make sure to check error code after returning from find_token function (if skip or invalid you need to free the current node, for invalid cleanup, for skip you continue the loop with the next token)


static void	meta_token(char **input, t_node *new, char metachar)
{
	if (is_double_metachar(**input) && (*input)[1] == metachar)
	{
		(*input) = (*input) + 2;
		set_token_node(new, double_ttype(metachar), Q_NONE, NULL);
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
		set_token_node(new, metachar, Q_NONE, NULL);
	}
}

static void	word_token(char **input, t_node *new)
{
	(void)input;
	while (**input && !get_metachar(**input))
		(*input)++;
	set_token_node(new, T_WORD, Q_NONE, "test_word");
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

t_list	*tokenize(t_data *dat)
{
	char		*input;
	t_node		*new_node;
	t_list		*lst;

	input = dat->input;
	lst = ft_lstnew();
	if (!lst)
	{
		set_error(PARSE_ERR_MALLOC, 0);
		token_cleanup(lst);
	}
	while (*input)
	{
		new_node = new_token_node();
		if (!new_node)
		{
			set_error(PARSE_ERR_MALLOC, 0);
			token_cleanup(lst);
		}
		find_next_token(&input, new_node);
		ft_lstadd_back(lst, new_node);
	}
	return (lst);
}
