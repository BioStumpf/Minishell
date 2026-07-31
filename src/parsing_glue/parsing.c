/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:14:19 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/27 21:05:58 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "structs.h"

void	parse_input(t_data *dat)
{
	t_list			*tokens;
	t_compound_arr	*compound_tokens;

	if (!dat->input)
		return ;
	tokens = tokenize(dat);
	compound_tokens = compound_group(dat, tokens);
	// print_compound(compound_tokens);
	ft_lstclear(tokens, free_token);
	expand(dat, compound_tokens);
	// print_compound(compound_tokens);
	built_ast(dat, compound_tokens);
	free_compound(compound_tokens, OK, dat);
	// print_tree(dat->ast.root, 0);
}

	//print_tree(dat->ast.root, 0);
// #include "ft_printf.h"
	// ft_lstprint(tokens, print_token);
	// ft_printf(1, "number of compounds: %d\n", compound_tokens->len);
	// print_compound(compound_tokens);
	// print_compound(compound_tokens);
	// free_compound(compound_tokens, OK, dat);
