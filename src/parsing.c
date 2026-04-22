/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:14:19 by dstumpf           #+#    #+#             */
/*   Updated: 2026/04/22 13:53:45 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

void	parse_input(t_data *dat)
{
	t_token *tokens;
	//t_compound_tokens *compound_tokens;
	//t_compound_commands *compound_commands;
	//t_ast *ast;

	tokens = tokenize(dat);
	print_tokens(tokens);
	//compound_tokens = compound_group(tokens);
	//expand(dat, compound_tokens);
	//make_parsetree = parse(dat, compound_tokens);
}
