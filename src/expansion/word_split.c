/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:15:18 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/18 18:37:15 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "err.h"

static void	skip_exp_whitespace(t_word_split *ws, t_exp *exp)
{
	while (split_signal(ws, exp)
		&& is_whitespace_metachar(ws->to_split[ws->splt_idx]))
		ws->splt_idx++;
}

static bool	expansion_split(t_word_split *ws, t_arg *new, t_exp *exp)
{
	if (!new_field(new, ws->tmp, &ws->tmp_idx))
		return (false);
	skip_exp_whitespace(ws, exp);
	if (split_signal(ws, exp))
	{
		(ws->splt_idx)++;
		skip_exp_whitespace(ws, exp);
	}
	return (true);
}

static bool	init_word_split(t_word_split *ws, t_data *dat, char *to_split)
{
	ft_bzero(ws, sizeof(t_word_split));
	ws->to_split = to_split;
	ws->ifs = get_ifs(dat);
	ws->tmp = malloc((ft_strlen(to_split) + 1) * sizeof(char));
	if (!ws->tmp)
		return (set_error(dat, ERR_SYS, NULL), false);
	return (true);
}

bool	word_split(t_data *dat, t_exp_vec *exps,
	t_arg *new, char *to_split)
{
	size_t			exp_idx;
	t_word_split	ws;

	exp_idx = 0;
	if (!init_word_split(&ws, dat, to_split))
		return (false);
	if (exps->expansions)
		skip_exp_whitespace(&ws, get_exp(exps, exp_idx));
	while (to_split[ws.splt_idx])
	{
		while (exp_idx < exps->size
			&& expansion_used(ws.splt_idx, get_exp(exps, exp_idx)))
			exp_idx++;
		if (exp_idx < exps->size && split_signal(&ws, get_exp(exps, exp_idx)))
		{
			if (!expansion_split(&ws, new, get_exp(exps, exp_idx)))
				return (set_error(dat, ERR_SYS, NULL), free(ws.tmp), false);
		}
		else
			ws.tmp[ws.tmp_idx++] = to_split[ws.splt_idx++];
	}
	if (ws.tmp_idx || !exps->expansions)
		if (!new_field(new, ws.tmp, &ws.tmp_idx))
			return (set_error(dat, ERR_SYS, NULL), free(ws.tmp), false);
	return (free(ws.tmp), true);
}
