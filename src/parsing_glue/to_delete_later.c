/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_delete_later.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 17:02:23 by david             #+#    #+#             */
/*   Updated: 2026/07/05 11:56:05 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "parsing.h"
#include "structs.h"

void	print_token(void *content)
{
	if (!content)
		return ;
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
	t_token *tok = (t_token *)content;
	printf("Type: %s  ", token_map[tok->type]);
	if (tok->type == WORD)
	{
		printf("Word: %s", tok->u_value.s_word.word);
		printf(" Space: %d", tok->u_value.s_word.space);
	}
	else if (tok->type == REDIR_APPEND || tok->type == REDIR_OUTFILE
			|| tok->type == REDIR_HEREDOC || tok->type == REDIR_INFILE)
	{
		printf("fd: %d    ", tok->u_value.s_redir.fd);
		printf("filename: %s", tok->u_value.s_redir.filename);
	}
	printf("\n");
}

void	print_compound(t_compound_arr *compounds)
{
	if (!compounds)
		return ;
	char *token_map[253];
	token_map[CMD] = "CMD";
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
	size_t	i = 0;
	size_t	j;
	t_compound *comp;
	while (i < compounds->len)
	{
		j = 0;
		comp = arr_get(compounds, i++);
		printf("Compound type: %s;   ", token_map[comp_type(comp)]);
		while (comp_type(comp) == CMD && j < arg_size(comp))
		// while (comp_type(comp) == CMD && arg_av(comp)[j])
			printf("[%s] ", arg_av(comp)[j++]); 
		if (is_redir(comp_type(comp))) {
			printf("Fd: %d;File: %s;quoted: %d", comp_fd(comp), comp_filename(comp), comp->u_value.s_redir.quoted);
		}
		printf("\n");
	}
}

void	print_tree_node(t_ast *node)
{
	if (!node)
		return ;
	char *token_map[253];
	token_map[CMD] = "CMD";
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
	printf("%s; ", token_map[node->type]);
	size_t i = 0;
	while (node->type == CMD && get_av(node)[i])
		printf("[%s] ", get_av(node)[i++]); 
	if (is_redir(node->type)) {
		printf("FD:%d FILE:%s QUOTED:%d", get_fd(node), get_operand(node), get_quoted(node));
	}
	printf("\n");
}

void print_tree(t_ast *root, int depth) {
    if (root == NULL)
        return;

    // Print right subtree first
    print_tree(root->left, depth + 1);

    // Indentation
    for (int i = 0; i < depth; i++) {
        printf("    ");
	}

    // Print current node
	print_tree_node(root);

    // Print left subtree
    print_tree(root->right, depth + 1);
}


