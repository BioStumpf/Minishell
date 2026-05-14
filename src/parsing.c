/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:14:19 by dstumpf           #+#    #+#             */
/*   Updated: 2026/04/23 16:19:28 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "main.h"

void	parse_input(t_data *dat)
{
	t_list	*tokens;
	//t_compound_tokens *compound_tokens;
	//t_compound_commands *compound_commands;

	set_error(OK, NOCHAR);
	tokens = tokenize(dat);
	ft_lstprint(tokens, print_token);
	ft_lstclear(tokens, free_token);
	//compound_tokens = compound_group(tokens);
	//expand(dat, compound_tokens);
	//dat->ast = parse_tokens(dat, compound_tokens);
}
