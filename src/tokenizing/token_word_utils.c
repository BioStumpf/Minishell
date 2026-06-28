/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 17:06:36 by david             #+#    #+#             */
/*   Updated: 2026/06/27 14:30:35 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "err.h"

static bool	is_metachar(char *input)
{
	return (is_double_metachar(input)
		|| is_single_metachar(*input)
		|| is_whitespace_metachar(*input));
}

static	bool	in_quotes(t_quotes *quotes)
{
	return (quotes->sngl || quotes->dbl);
}

size_t	get_word_len(char *input, t_data *dat)
{
	t_quotes	quotes;
	size_t		i;

	i = 0;
	quotes.dbl = false;
	quotes.sngl = false;
	while (input[i] && (in_quotes(&quotes) || !is_metachar(input + i)))
	{
		if (input[i] == '\"' && !quotes.sngl)
			quotes.dbl = !quotes.dbl;
		else if (input[i] == '\'' && !quotes.dbl)
			quotes.sngl = !quotes.sngl;
		i++;
	}
	if (in_quotes(&quotes))
		set_error(dat, PARSE_ERR_UNCLOSED_QUOTES);
	return (i);
}

void	set_word(char **input, char *word, size_t word_len)
{
	size_t	i;

	i = 0;
	while (i < word_len)
	{
		word[i] = **input;
		i++;
		(*input)++;
	}
	word[i] = '\0';
}
