/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_string_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 18:46:35 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/18 18:46:36 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "parsing.h"

char	char_in_str(char c, const char *str)
{
	size_t		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (c);
	}
	return ('\0');
}

char	is_single_metachar(char c)
{
	const char	*metachars;

	metachars = "|()<>";
	return (char_in_str(c, metachars));
}

char	is_whitespace_metachar(char c)
{
	const char	*no_token;

	no_token = SPCE;
	return (char_in_str(c, no_token));
}

char	is_double_metachar(char *input)
{
	char		current;
	char		next;
	const char	*double_metachars;

	current = *input;
	next = *(input + 1);
	double_metachars = "|&<>";
	return (char_in_str(current, double_metachars) && current == next);
}

char	is_quote(char c)
{
	const char	*quote;

	quote = "\"\'";
	return (char_in_str(c, quote));
}
