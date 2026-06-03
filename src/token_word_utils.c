/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 17:06:36 by david             #+#    #+#             */
/*   Updated: 2026/05/17 21:32:43 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

static bool	is_metachar(char *input)
{
	return (is_double_metachar(input)
		|| is_single_metachar(*input)
		|| is_whitespace_metachar(*input));
}

size_t	get_word_len(char *input, t_data *dat)
{
	bool	in_quotes;
	size_t	i;

	i = 0;
	in_quotes = false;
	while (input[i] && (in_quotes || !is_metachar(input + i)))
	{
		if (is_quote(input[i]) && !in_quotes)
			in_quotes = true;
		else if (is_quote(input[i]) && in_quotes)
			in_quotes = false;
		i++;
	}
	if (in_quotes)
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

