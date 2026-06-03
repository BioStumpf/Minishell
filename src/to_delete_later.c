/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_delete_later.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 17:02:23 by david             #+#    #+#             */
/*   Updated: 2026/06/02 15:15:14 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "parsing.h"

void	print_token(void *content)
{
	if (!content)
		return ;
	char *token_map[253];
	token_map[T_WORD] = "WORD";
	token_map[T_PIPE] = "PIPE";
	token_map[T_AND] = "AND";
	token_map[T_OR] = "OR";
	token_map[T_REDIR_INFILE] = "REDIR_INFILE";
	token_map[T_REDIR_OUTFILE] = "REDIR_OUTFILE";
	token_map[T_REDIR_HEREDOC] = "REDIR_HEREDOC";
	token_map[T_REDIR_APPEND] = "REDIR_APPEND";
	token_map[T_LEFT_PARA] = "LEFT_PARA";
	token_map[T_RIGHT_PARA] = "RIGHT_PARA";
	t_token *tok = (t_token *)content;
	printf("Type: %s  ", token_map[tok->type]);
	if (tok->type == T_WORD)
		printf("Word: %s", tok->word);
	printf("\n");
}

void	print_compound(t_compound_arr *compounds)
{
	if (!compounds)
		return ;
	char *token_map[253];
	token_map[CMD] = "CMD";
	token_map[T_WORD] = "WORD";
	token_map[T_PIPE] = "PIPE";
	token_map[T_AND] = "AND";
	token_map[T_OR] = "OR";
	token_map[T_REDIR_INFILE] = "REDIR_INFILE";
	token_map[T_REDIR_OUTFILE] = "REDIR_OUTFILE";
	token_map[T_REDIR_HEREDOC] = "REDIR_HEREDOC";
	token_map[T_REDIR_APPEND] = "REDIR_APPEND";
	token_map[T_LEFT_PARA] = "LEFT_PARA";
	token_map[T_RIGHT_PARA] = "RIGHT_PARA";
	size_t	i = 0;
	size_t	j;
	t_compound *comp;
	while (i < compounds->len)
	{
		j = 0;
		comp = &compounds->arr[i++];
		printf("Compound type: %s\n", token_map[comp->type]);
		while (j < comp->args.size)
			printf("%s  ", comp->args.av[j++]);
		printf("\n");
	}
}
