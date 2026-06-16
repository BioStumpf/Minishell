/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_metachar_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 17:05:21 by david             #+#    #+#             */
/*   Updated: 2026/06/16 13:37:37 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//note for tokens: &&, ||, >> or << the actual numeric enum value/type variable inside the token
//refers to 2 * token + 1 which is passed to new_token_node
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
