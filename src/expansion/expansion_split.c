/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 12:30:26 by dstumpf           #+#    #+#             */
/*   Updated: 2026/06/25 14:36:31 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

static void	find_word(const char *s, char *sep, unsigned int *start, size_t *len)
{
	*start += *len;
	*len = 0;
	while (s[*start] && in_charset(s[*start], sep))
		(*start)++;
	while (s[*start + *len] && !in_charset(s[*start + *len], sep))
		(*len)++;
}

static void	free_splt(t_split *splt, size_t idx)
{
	while (idx)
		free(splt->splt[--idx]);
	free(splt->splt);
	free(splt);
}

static bool	fill_array(const char *s, char *sep, t_split *splt)
{
	size_t			i;
	size_t			len;
	unsigned int	start;

	i = 0;
	start = 0;
	len = 0;
	while (i < splt->len)
	{
		find_word(s, sep, &start, &len);
		splt->splt[i] = ft_substr(s, start, len);
		if (!splt->splt[i])
		{
			free_splt(splt, i);
			return (false);
		}
		i++;
	}
	return (true);
}

t_split *expand_split(char *s, char *sep)
{
	t_split			*splt;

	splt = malloc(sizeof(t_split));
	splt->len = count_words(s, sep);
	if (splt->len && in_charset(s[0], sep))
		splt->len++;
	if (splt->len && in_charset(s[ft_strlen(s) - 1], sep))
		splt->len++;
	splt->splt = malloc(sizeof(char *) * (splt->len));
	if (!splt->splt)
		return (NULL);
	if (splt->len && in_charset(s[0], sep))
		splt->splt[0] = NULL;
	if (splt->len && in_charset(s[ft_strlen(s) - 1], sep))
		splt->splt[splt->len - 1] = NULL;
	if (!fill_array(s, sep, splt))
		return (NULL);
	return (splt);
}
