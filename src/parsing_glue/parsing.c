/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:14:19 by dstumpf           #+#    #+#             */
/*   Updated: 2026/06/16 12:56:02 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "err.h"
#include "structs.h"
// #include "ft_printf.h"

void	parse_input(t_data *dat)
{
	t_list	*tokens;
	// t_compound_arr *compound_tokens;
	//t_compound_commands *compound_commands;

	if (!dat->input)
		return ;
	tokens = tokenize(dat);
	ft_lstprint(tokens, print_token);
	// compound_tokens = compound_group(dat, tokens);
	// ft_printf(1, "number of compounds: %d\n", compound_tokens->len);
	ft_lstclear(tokens, free_token);
	// print_compound(compound_tokens);
	// free_compound(compound_tokens, OK, dat);
	//expand(dat, compound_tokens);
	//dat->ast = parse_tokens(dat, compound_tokens);
}
