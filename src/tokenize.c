/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:15:50 by dstumpf           #+#    #+#             */
/*   Updated: 2026/04/24 18:03:53 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "stdlib.h"
#include "libft.h"

static t_word	*word_new(enum e_quote quote, char *lexeme)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	word->quote = quote;
	word->lexeme = lexeme;
	return (word);
}

static t_token	*token_new(enum e_token type, t_word *word)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->word = word;
	return (token);
}

void	free_token(void *token)
{
	free(((t_token *)token)->word);
	free(token);
}

static void	cleanup(t_list *lst)
{
	ft_lstclear(lst, free_token);
	exit(1);
}

t_node	*new_token_node(enum e_token type, enum e_quote quote, char *lexeme)
{
	t_token	*token;
	t_word	*word;
	t_node	*node;

	word = NULL;
	if (type == WORD)
	{
		word = word_new(quote, lexeme);
		if (!word)
			return (NULL);
	}
	token = token_new(type, word);
	if (!token)
		return (free(word), NULL);
	node = ft_nodenew(token);
	if (!node)
		return (free(word), free(token), NULL);
	return (node);
}

static char	char_in_str(char c, const char *str)
{
	size_t		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (c);
	}
	return ('\0');
}

static char	get_metachar(char c)
{
	const char	*metachars;

	metachars = "|&;()<> \t\n";
	return (char_in_str(c, metachars));
}

static char	is_double_metachar(char c)
{
	const char	*double_metachars;

	double_metachars = "|&<>";
	return (char_in_str(c, double_metachars));
}

//note for tokens: &&, ||, >> or << the actual numeric enum value/type variable inside the token
//refers to 2 * token + 1 which is passed to new_token_node
static t_node	*meta_token(char **input, char metachar)
{
	if (is_double_metachar(**input) && (*input)[1] == metachar)
	{
		(*input) = (*input) + 2;
		return (new_token_node(metachar	* 2 + 1, NONE, NULL));
	}
	(*input)++;
	return (new_token_node(metachar, NONE, NULL));
}

static t_node	*word_token(char **input)
{
	(void)input;
	while (**input && !get_metachar(**input))
		(*input)++;
	return (new_token_node(WORD, NONE, "test_word"));
}

t_node	*find_next_token(char **input)
{
	char	metachar;

	metachar = get_metachar(**input);
	if (metachar)
		return (meta_token(input, metachar));
	return (word_token(input));
}

t_list	*tokenize(t_data *dat)
{
	char	*input;
	t_node	*new_node;
	t_list	*lst;

	input = dat->input;
	lst = ft_lstnew();
	if (!lst)
		cleanup(lst);
	while (*input)
	{
		new_node = find_next_token(&input);
		if (!new_node)
			cleanup(lst);
		ft_lstadd_back(lst, new_node);
	}
	return (lst);
}

//remove this funciton since its not relevant just for debugging
#include "stdio.h"

void	print_token(void *content)
{
	char *token_map[253];
	token_map[WORD] = "WORD";
	token_map[PIPE] = "PIPE";
	token_map[AND] = "AND";
	token_map[OR] = "OR";
	token_map[REDIR_INFILE] = "REDIR_INFILE";
	token_map[REDIR_OUTFILE] = "REDIR_OUTFILE";
	token_map[REDIR_HEREDOC] = "REDIR_HEREDOC";
	token_map[REDIR_APPEND] = "REDIR_APPEND";
	token_map[LEFT_PARA] = "LEFT_PARA";
	token_map[RIGHT_PARA] = "RIGHT_PARA";
	token_map[' '] = "SPACE";
	t_token *tok = (t_token *)content;
	printf("Type: %s  ", token_map[tok->type]);
	if (tok->type == WORD)
		printf("Word: %s", tok->word->lexeme);
	printf("\n");
}
