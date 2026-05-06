/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_string_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 17:04:19 by david             #+#    #+#             */
/*   Updated: 2026/05/06 16:32:22 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static char	char_in_str(char c, const char *str)
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

char	get_metachar(char c)
{
	const char	*metachars;

	metachars = "|&;()<> \t\n";
	return (char_in_str(c, metachars));
}

char	invalid_metachar(char c)
{
	const char	*invalid_token;

	invalid_token = "&;\\";
	return (char_in_str(c, invalid_token));
}

char	skip_metachar(char c)
{
	const char	*no_token;

	no_token = " \t\n";
	return (char_in_str(c, no_token));
}

char	is_double_metachar(char c)
{
	const char	*double_metachars;

	double_metachars = "|&<>";
	return (char_in_str(c, double_metachars));
}
