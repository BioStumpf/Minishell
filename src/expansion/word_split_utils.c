/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:21:01 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/03 14:21:48 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "env.h"

bool	in_splittable_expansion(size_t idx, t_exp *exp)
{
	return (exp->start <= idx && idx < exp->start + exp->len
		&& !exp->quoted);
}

bool	expansion_used(size_t idx, t_exp *exp)
{
	return (exp->start + exp->len <= idx || exp->quoted);
}

char	*get_ifs(t_data *dat)
{
	char	*ifs;

	ifs = get_env_val(dat, "IFS");
	if (!ifs)
		ifs = SPCE;
	return (ifs);
}

bool	new_field(t_arg *arg, char *str, size_t *str_idx)
{
	str[*str_idx] = '\0';
	*str_idx = 0;
	if (!add_arg(arg, arg->size, str))
		return (false);
	return (true);
}

bool	split_signal(t_word_split *ws, t_exp *exp)
{
	return (ws->to_split[ws->splt_idx]
		&& char_in_str(ws->to_split[ws->splt_idx], ws->ifs)
		&& in_splittable_expansion(ws->splt_idx, exp));
}
