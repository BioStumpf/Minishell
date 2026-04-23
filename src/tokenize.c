/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:15:50 by dstumpf           #+#    #+#             */
/*   Updated: 2026/04/23 16:38:38 by dstumpf          ###   ########.fr       */
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

t_list	*tokenize(t_data *dat)
{
	(void)dat;
	t_list *lst = ft_lstnew();
	if (!lst)
		exit(1);

	t_node *tok = new_token_node(WORD, NONE, "hello"); 
	if (!tok)
		cleanup(lst);
	ft_lstadd_back(lst, tok);

	tok = new_token_node(PIPE, NONE, "you"); 
	if (!tok)
		cleanup(lst);
	ft_lstadd_back(lst, tok);

	return (lst);
}

//remove this funciton since its not relevant just for debugging
#include "stdio.h"
void	print_token(void *content)
{
	char *token_map[] = {
	"WORD",
	"PIPE",
	"AND",
	"OR",
	"REDIR_INFILE",
	"REDIR_OUTFILE",
	"REDIR_HEREDOC",
	"REDIR_APPEND",
	"LEFT_PARA",
	"RIGHT_PARAN"
	};
	t_token *tok = (t_token *)content;
	printf("Type: %s  ", token_map[tok->type]);
	if (tok->type == WORD)
		printf("Word: %s", tok->word->lexeme);
	printf("\n");
}
