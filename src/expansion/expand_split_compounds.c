/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split_compounds.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:07:57 by david             #+#    #+#             */
/*   Updated: 2026/07/03 14:28:45 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "err.h"
// #include "env.h"
// #include "structs.h"
// #include <stddef.h>
// #include <strings.h>

// static bool	is_expand_signal(char *str, bool sngl_quotes)
// {
// 	char	cur;
// 	char	next;
//
// 	cur = str[0];
// 	next = str[1];
// 	return (cur == '$' && !sngl_quotes && next
// 		&& !is_quote(next) && !is_whitespace_metachar(next));
// }

// static void	set_exp_info(t_exp *exp, char *str, size_t *idx, bool quoted)
// {
// 	(*idx)++;
// 	exp->start = *idx;
// 	exp->quoted = quoted;
// 	while (str[*idx] && ft_isalnum(str[*idx]))
// 		(*idx)++;
// 	if (exp->start == *idx)
// 		(*idx)++;
// 	exp->len = *idx - exp->start;
// }
//
// static void	update_expansion_info(t_exp *exp, size_t to_remove)
// {
// 	exp->start -= to_remove;
// }
//
// static bool	find_expansions(t_exp_vec *exps, char *str, bool quote_removal)
// {
// 	t_quotes	quotes;
// 	size_t		i;
// 	size_t		chars_to_remove;
// 	t_exp		exp_info;
//
// 	ft_bzero(&quotes, sizeof(t_quotes));
// 	i = 0;
// 	chars_to_remove = 0;
// 	while (str[i])
// 	{
// 		if (update_quote_status(&quotes, &str[i]) && quote_removal)
// 			chars_to_remove++;
// 		else if (is_expand_signal(&str[i], quotes.sngl))
// 		{
// 			chars_to_remove++;
// 			set_exp_info(&exp_info, str, &i, quotes.dbl);
// 			update_expansion_info(&exp_info, chars_to_remove);
// 			if (!add_exp(exps, exps->size, &exp_info))
// 				return (false);
// 			continue ;
// 		}
// 		i++;
// 	}
// 	return (true);
// }

// static size_t	trimmed_size(char *str, bool quote_removal)
// {
// 	t_quotes	quotes;
// 	size_t		size;
//
// 	bzero(&quotes, sizeof(t_quotes));
// 	size = 0;
// 	while (*str)
// 	{
// 		if (update_quote_status(&quotes, str) && quote_removal)
// 			str++;
// 		else if (is_expand_signal(str, quotes.sngl)
// 			&& is_expand_signal(++str, quotes.sngl))
// 		{
// 			str++;
// 			size++;
// 		}
// 		else
// 		{
// 			str++;
// 			size++;
// 		}
// 	}
// 	return (size);
// }
//
// static char	*trimm_str(size_t str_size, char *str, bool quote_removal)
// {
// 	t_quotes	quotes;
// 	size_t		i;
// 	char		*out;
//
// 	ft_bzero(&quotes, sizeof(t_quotes));
// 	out = malloc((str_size + 1) * sizeof(char));
// 	i = 0;
// 	if (!out)
// 		return (NULL);
// 	while (*str)
// 	{
// 		if (update_quote_status(&quotes, str) && quote_removal)
// 			str++;
// 		else if (is_expand_signal(str, quotes.sngl)
// 			&& is_expand_signal(++str, quotes.sngl))
// 			out[i++] = *str++;
// 		else
// 			out[i++] = *str++;
// 	}
// 	out[i] = '\0';
// 	return (out);
// }
//
// static char	*remove_dollar_quotes(t_exp_vec *exps, char *str,
// 	bool quote_removal)
// {
// 	size_t		new_str_size;
// 	char		*new_str;
//
// 	new_str_size = trimmed_size(str, quote_removal);
// 	new_str = trimm_str(new_str_size, str, quote_removal);
// 	if (!new_str)
// 		return (free(exps->expansions), NULL);
// 	return (new_str);
// }

// static char	*get_exp_value(t_data *dat, t_exp *exp, char *str)
// {
// 	char	tmp;
// 	char	*value;
// 	size_t	start;
// 	size_t	stop;
//
// 	start = exp->start;
// 	stop = start + exp->len;
// 	if (str[start] == '?')
// 		return (dat->ret_str);
// 	tmp = str[stop];
// 	str[stop] = '\0';
// 	value = get_env_val(dat, &str[start]);
// 	str[stop] = tmp;
// 	return (value);
// }
//
// static size_t	post_expansion_len(char *str, t_data *dat, t_exp_vec *exps)
// {
// 	size_t	exp_idx;
// 	size_t	len;
// 	size_t	str_idx;
//
// 	len = 0;
// 	str_idx = 0;
// 	exp_idx = 0;
// 	while (str[str_idx])
// 	{
// 		if (exp_idx < exps->size && str_idx == exp_start(exps, exp_idx))
// 		{
// 			len += ft_strlen(get_exp_value(dat,
// 						get_exp(exps, exp_idx), str));
// 			str_idx += exp_len(exps, exp_idx);
// 			exp_idx++;
// 		}
// 		else
// 		{
// 			len++;
// 			str_idx++;
// 		}
// 	}
// 	return (len);
// }
//
// static void	cpy_expansion(char *exp_value, char *expanded,
// 	size_t *idx, t_exp *exp_info)
// {
// 	if (!exp_value)
// 		return ;
// 	exp_info->start = *idx;
// 	while (*exp_value)
// 		expanded[(*idx)++] = *exp_value++;
// 	exp_info->len = *idx - exp_info->start;
// }
//
// static char	*merge_expansions(size_t len, char *str,
// 	t_data *dat, t_exp_vec *exps)
// {
// 	size_t	i;
// 	size_t	exp_idx;
// 	size_t	str_idx;
// 	char	*expanded;
// 	char	*exp_value;
//
// 	str_idx = 0;
// 	exp_idx = 0;
// 	i = 0;
// 	expanded = malloc((len + 1) * sizeof(char));
// 	if (!expanded)
// 		return (NULL);
// 	while (i < len)
// 	{
// 		if (exp_idx < exps->size && str_idx == exp_start(exps, exp_idx))
// 		{
// 			str_idx += exp_len(exps, exp_idx);
// 			exp_value = get_exp_value(dat, get_exp(exps, exp_idx), str);
// 			cpy_expansion(exp_value, expanded, &i, get_exp(exps, exp_idx++));
// 		}
// 		else
// 			expanded[i++] = str[str_idx++];
// 	}
// 	expanded[i] = '\0';
// 	return (expanded);
// }
//
// static char	*insert_expansions(t_data *dat, t_exp_vec *exps, char *str)
// {
// 	size_t	expanded_len;
// 	char	*expanded;
//
// 	expanded_len = post_expansion_len(str, dat, exps);
// 	expanded = merge_expansions(expanded_len, str, dat, exps);
// 	if (!expanded)
// 		return (free(exps->expansions), NULL);
// 	return (expanded);
// }

// static bool	in_splittable_expansion(size_t idx, t_exp *exp)
// {
// 	return (exp->start <= idx && idx < exp->start + exp->len
// 		&& !exp->quoted);
// }
//
// static bool	expansion_used(size_t idx, t_exp *exp)
// {
// 	return (exp->start + exp->len <= idx || exp->quoted);
// }
//
// static char	*get_ifs(t_data *dat)
// {
// 	char	*ifs;
//
// 	ifs = get_env_val(dat, "IFS");
// 	if (!ifs)
// 		ifs = SPCE;
// 	return (ifs);
// }
//
// static bool	new_field(t_arg *arg, char *str, size_t *str_idx)
// {
// 	str[*str_idx] = '\0';
// 	*str_idx = 0;
// 	if (!add_arg(arg, arg->size, str))
// 		return (false);
// 	return (true);
// }
//
// static bool	split_signal(t_word_split *ws, t_exp *exp)
// {
// 	return (ws->to_split[ws->splt_idx]
// 		&& char_in_str(ws->to_split[ws->splt_idx], ws->ifs)
// 		&& in_splittable_expansion(ws->splt_idx, exp));
// }

// static void	skip_exp_whitespace(t_word_split *ws, t_exp *exp)
// {
// 	while (split_signal(ws, exp)
// 		&& is_whitespace_metachar(ws->to_split[ws->splt_idx]))
// 		ws->splt_idx++;
// }

// static bool	expansion_split(t_word_split *ws, t_arg *new, t_exp *exp)
// {
// 	if (!new_field(new, ws->tmp, &ws->tmp_idx))
// 		return (false);
// 	skip_exp_whitespace(ws, exp);
// 	if (split_signal(ws, exp))
// 	{
// 		(ws->splt_idx)++;
// 		skip_exp_whitespace(ws, exp);
// 	}
// 	return (true);
// }
//
// static bool	init_word_split(t_word_split *ws, t_data *dat, char *to_split)
// {
// 	ft_bzero(ws, sizeof(t_word_split));
// 	ws->to_split = to_split;
// 	ws->ifs = get_ifs(dat);
// 	ws->tmp = malloc((ft_strlen(to_split) + 1) * sizeof(char));
// 	if (!ws->tmp)
// 		return (set_error(dat, ERR_MALLOC), false);
// 	return (true);
// }
//
// static bool	word_split(t_data *dat, t_exp_vec *exps,
// 	t_arg *new, char *to_split)
// {
// 	size_t			exp_idx;
// 	t_word_split	ws;
//
// 	exp_idx = 0;
// 	if (!init_word_split(&ws, dat, to_split))
// 		return (false);
// 	if (exps->expansions)
// 		skip_exp_whitespace(&ws, get_exp(exps, exp_idx));
// 	while (to_split[ws.splt_idx])
// 	{
// 		while (exp_idx < exps->size
// 			&& expansion_used(ws.splt_idx, get_exp(exps, exp_idx)))
// 			exp_idx++;
// 		if (exp_idx < exps->size && split_signal(&ws, get_exp(exps, exp_idx)))
// 		{
// 			if (!expansion_split(&ws, new, get_exp(exps, exp_idx)))
// 				return (set_error(dat, ERR_MALLOC), free(ws.tmp), false);
// 		}
// 		else
// 			ws.tmp[ws.tmp_idx++] = to_split[ws.splt_idx++];
// 	}
// 	if (ws.tmp_idx)
// 		if (!new_field(new, ws.tmp, &ws.tmp_idx))
// 			return (set_error(dat, ERR_MALLOC), free(ws.tmp), false);
// 	return (free(ws.tmp), true);
// }

// static char	*expand_str(t_data *dat, char *str,
// 	bool quote_removal, t_exp_vec *exps)
// {
// 	char		*trimmed_str;
// 	char		*expanded_str;
//
// 	ft_bzero(exps, sizeof(t_exp_vec));
// 	if (!find_expansions(exps, str, quote_removal))
// 		return (set_error(dat, ERR_MALLOC), NULL);
// 	trimmed_str = remove_dollar_quotes(exps, str, quote_removal);
// 	if (!trimmed_str)
// 		return (set_error(dat, ERR_MALLOC), NULL);
// 	expanded_str = insert_expansions(dat, exps, trimmed_str);
// 	free(trimmed_str);
// 	if (!expanded_str)
// 		return (set_error(dat, ERR_MALLOC), NULL);
// 	return (expanded_str);
// }

static void	expand_cmd(t_data *dat, t_compound *comp)
{
	char		*expanded_str;
	size_t		i;
	size_t		arg_len;
	t_arg		new;
	t_exp_vec	exps;

	i = 0;
	ft_bzero(&new, sizeof(t_arg));
	arg_len = arg_size(comp);
	while (i < arg_len)
	{
		expanded_str = expand_str(dat, arg_av(comp)[i], RM_QUOTES, &exps);
		if (!expanded_str)
			return (free_args(&new));
		if (!word_split(dat, &exps, &new, expanded_str))
			return (free_args(&new), free(exps.expansions), free(expanded_str));
		free(exps.expansions);
		free(expanded_str);
		i++;
	}
	free_args(comp_args(comp));
	*comp_args(comp) = new;
}

static void	expand_redir(t_data *dat, t_compound *comp)
{
	char		*expanded_str;
	t_exp_vec	exps;
	t_arg		new;

	ft_bzero(&new, sizeof(t_arg));
	expanded_str = expand_str(dat, comp_filename(comp), RM_QUOTES, &exps);
	if (!expanded_str)
		return ;
	if (!word_split(dat, &exps, &new, expanded_str))
		return (free_args(&new), free(exps.expansions), free(expanded_str));
	free(exps.expansions);
	if (new.size != 1)
	{
		free_args(&new);
		free(expanded_str);
		return (set_error(dat, PARSE_ERR_REDIR));
	}
	free_args(&new);
	free(comp_filename(comp));
	comp->u_value.s_redir.filename = expanded_str;
}

void	expand(t_data *dat, t_compound_arr *ca)
{
	size_t		i;
	t_compound	*comp;

	if (!ca)
		return ;
	i = 0;
	while (i < ca->len)
	{
		comp = arr_get(ca, i);
		if (comp_type(comp) == CMD)
			expand_cmd(dat, comp);
		else if (is_redir(comp_type(comp)))
			expand_redir(dat, comp);
		if (!status_ok(dat))
			return ;
		i++;
	}
}
