/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 17:06:36 by david             #+#    #+#             */
/*   Updated: 2026/05/14 17:08:24 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

size_t	get_word_len(char *input)
{
	size_t	i;

	i = 0;
	while (input[i] && !get_metachar(input[i]))
		i++;
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

