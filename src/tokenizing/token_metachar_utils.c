/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_metachar_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 17:05:21 by david             #+#    #+#             */
/*   Updated: 2026/08/18 14:32:00 by knajmech         ###   ########.fr       */
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