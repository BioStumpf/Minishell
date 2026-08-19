/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_metachar_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 18:46:27 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/18 18:46:28 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	double_tok_type(char metachar)
{
	return (metachar * 2 + 1);
}

char	skip_whitespace(char **str)
{
	while (is_whitespace_metachar(**str))
		++(*str);
	return (**str);
}

//note for tokens: &&, ||, >> or <<
//the actual numeric enum value/type variable inside the token
//refers to 2 * token + 1 which is passed to new_token_node
