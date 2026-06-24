/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:18:11 by dstumpf           #+#    #+#             */
/*   Updated: 2026/06/24 15:32:41 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static int	word_count(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static int	word_len(const char *s, char delimitter)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != delimitter)
		i++;
	return (i);
}

static char	**freedom(char **list, int times)
{
	while (times >= 0)
	{
		free(list[times]);
		list[times] = 0;
		times--;
	}
	free(list);
	list = 0;
	return (0);
}

static char	**mallocing(char const *s, char **list, char c)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	if (!list)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
		{
			list[k] = ft_substr(s, i, word_len(&s[i], c));
			if (!list[k])
				return (freedom(list, k));
			k++;
			while (s[i] != c && (s[i]))
				i++;
		}
		else
			i++;
	}
	list[k] = 0;
	return (list);
}

char	**ft_split(char const *s, char c)
{
	char	**list;

	if (!s)
		return (0);
	list = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!list)
		return (0);
	list = mallocing(s, list, c);
	return (list);
}*/

static void	find_word(const char *s, char *sep, unsigned int *start, size_t *len)
{
	*start += *len;
	*len = 0;
	while (s[*start] && in_charset(s[*start], sep))
		(*start)++;
	while (s[*start + *len] && !in_charset(s[*start + *len], sep))
		(*len)++;
}

static void	free_out(char **out, size_t len)
{
	while (len)
		free(out[--len]);
	free(out);
}

static int	fill_array(const char *s, char *sep, char **out, size_t wc)
{
	size_t			i;
	size_t			len;
	unsigned int	start;

	i = 0;
	start = 0;
	len = 0;
	while (i < wc)
	{
		find_word(s, sep, &start, &len);
		out[i] = ft_substr(s, start, len);
		if (!out[i])
		{
			free_out(out, i);
			return (0);
		}
		i++;
	}
	out[i] = 0;
	return (1);
}

char	**ft_split(char const *s, char *sep)
{
	char			**out;
	size_t			wc;

	wc = count_words(s, sep);
	if (!s || !*s || wc == 0)
		wc = 0;
	out = malloc(sizeof(char *) * (wc + 1));
	if (!out)
		return (0);
	if (!fill_array(s, sep, out, wc))
		return (0);
	return (out);
}
