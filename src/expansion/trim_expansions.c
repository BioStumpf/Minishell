/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:12:02 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/03 14:14:38 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	trimmed_size(char *str, bool quote_removal)
{
	t_quotes	quotes;
	size_t		size;

	ft_bzero(&quotes, sizeof(t_quotes));
	size = 0;
	while (*str)
	{
		if (update_quote_status(&quotes, str) && quote_removal)
			str++;
		else if (is_expand_signal(str, quotes.sngl)
			&& is_expand_signal(++str, quotes.sngl))
		{
			str++;
			size++;
		}
		else
		{
			str++;
			size++;
		}
	}
	return (size);
}

static char	*trimm_str(size_t str_size, char *str, bool quote_removal)
{
	t_quotes	quotes;
	size_t		i;
	char		*out;

	ft_bzero(&quotes, sizeof(t_quotes));
	out = malloc((str_size + 1) * sizeof(char));
	i = 0;
	if (!out)
		return (NULL);
	while (*str)
	{
		if (update_quote_status(&quotes, str) && quote_removal)
			str++;
		else if (is_expand_signal(str, quotes.sngl)
			&& is_expand_signal(++str, quotes.sngl))
			out[i++] = *str++;
		else
			out[i++] = *str++;
	}
	out[i] = '\0';
	return (out);
}

char	*remove_dollar_quotes(t_exp_vec *exps, char *str,
	bool quote_removal)
{
	size_t		new_str_size;
	char		*new_str;

	new_str_size = trimmed_size(str, quote_removal);
	new_str = trimm_str(new_str_size, str, quote_removal);
	if (!new_str)
		return (free(exps->expansions), NULL);
	return (new_str);
}
