/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:10:42 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/03 08:35:58 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

bool	is_expand_signal(char *str, bool sngl_quotes)
{
	char	cur;
	char	next;

	cur = str[0];
	next = str[1];
	return (cur == '$' && !sngl_quotes && next
		&& (ft_isalnum(next) || next == '?'));
}

static void	set_exp_info(t_exp *exp, char *str, size_t *idx, bool quoted)
{
	(*idx)++;
	exp->start = *idx;
	exp->quoted = quoted;
	while (str[*idx] && (ft_isalnum(str[*idx]) || str[*idx] == '_'))
		(*idx)++;
	if (exp->start == *idx)
		(*idx)++;
	exp->len = *idx - exp->start;
}

static void	update_expansion_info(t_exp *exp, size_t to_remove)
{
	exp->start -= to_remove;
}

bool	find_expansions(t_exp_vec *exps, char *str, bool quote_removal)
{
	t_quotes	quotes;
	size_t		i;
	size_t		chars_to_remove;
	t_exp		exp_info;

	ft_bzero(&quotes, sizeof(t_quotes));
	i = 0;
	chars_to_remove = 0;
	while (str[i])
	{
		if (update_quote_status(&quotes, &str[i]) && quote_removal)
			chars_to_remove++;
		else if (is_expand_signal(&str[i], quotes.sngl))
		{
			chars_to_remove++;
			set_exp_info(&exp_info, str, &i, quotes.dbl);
			update_expansion_info(&exp_info, chars_to_remove);
			if (!add_exp(exps, exps->size, &exp_info))
				return (false);
			continue ;
		}
		i++;
	}
	return (true);
}
