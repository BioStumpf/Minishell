/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 12:30:26 by dstumpf           #+#    #+#             */
/*   Updated: 2026/06/26 15:14:50 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

static void	find_word(const char *s, char *sep,
		unsigned int *start, size_t *len)
{
	*start += *len;
	*len = 0;
	while (s[*start] && in_charset(s[*start], sep))
		(*start)++;
	while (s[*start + *len] && !in_charset(s[*start + *len], sep))
		(*len)++;
}

void	free_exp_splt(t_split *splt, size_t len)
{
	while (len > 0)
	{
		--len;
		if (splt->leading_sep && len == 0)
			continue ;
		if (splt->trailing_sep && len == splt->len - 1)
			continue ;
		free(splt->splt[len]);
	}
	free(splt->splt);
	free(splt);
}

static bool	fill_array(const char *s, char *sep, t_split *splt)
{
	size_t			i;
	size_t			splt_len;
	size_t			len;
	unsigned int	start;

	i = 0;
	splt_len = splt->len;
	if (splt->leading_sep)
		i += 1;
	if (splt->trailing_sep)
		splt_len -= 1;
	start = 0;
	len = 0;
	while (i < splt_len)
	{
		find_word(s, sep, &start, &len);
		splt->splt[i] = ft_substr(s, start, len);
		if (!splt->splt[i])
		{
			free_exp_splt(splt, i);
			return (false);
		}
		i++;
	}
	return (true);
}

t_split	*expand_split(char *s, char *sep)
{
	t_split			*splt;

	splt = malloc(sizeof(t_split));
	if (!splt)
		return (NULL);
	splt->len = count_words(s, sep);
	splt->leading_sep = splt->len && in_charset(s[0], sep);
	splt->trailing_sep = splt->len && in_charset(s[ft_strlen(s) - 1], sep);
	if (splt->leading_sep)
		splt->len++;
	if (splt->trailing_sep)
		splt->len++;
	splt->splt = malloc(sizeof(char *) * (splt->len));
	if (!splt->splt)
		return (free(splt), NULL);
	if (splt->leading_sep)
		splt->splt[0] = "";
	if (splt->trailing_sep)
		splt->splt[splt->len - 1] = "";
	if (!fill_array(s, sep, splt))
		return (NULL);
	return (splt);
}

// #include "ft_printf.h"
// int main(void){
// 	char *arg = " hello     you     ";
// 	t_split *splt = expand_split(arg, " ");
// 	if (!splt)
// 		return (1);
// 	for (size_t i = 0; i < splt->len; i++){
// 		ft_printf(1, "%s\n", splt->splt[i]);
// 	}
// 	free_exp_splt(splt, splt->len);
// 	return (0);
// }
