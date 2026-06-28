/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:07:57 by david             #+#    #+#             */
/*   Updated: 2026/06/28 20:52:17 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
#include "libft.h"
#include "parsing.h"
// #include "env.h"
#include "structs.h"
#include "err.h"
#include <strings.h>

void	set_exp_info(t_exp *exp, char *arg, size_t *idx, bool quoted)
{
	(*idx)++;
	exp->start = *idx;
	exp->quoted = quoted;
	while (arg[*idx] && !is_quote(arg[*idx] && arg[*idx] != '$'))
		(*idx)++;
	exp->len = *idx - exp->start;
	// $var
	// $?
	// $$
}

static bool	is_expand_signal(char *arg, bool sngl_quotes)
{
	char	cur;
	char	next;

	cur = arg[0];
	next = arg[1];
	return (cur == '$' && !sngl_quotes &&
		!is_quote(next) && !is_whitespace_metachar(next));
}

static bool	find_expansions(t_exp_vec *exps, char *arg)
{
	t_quotes	quotes;
	size_t		i;
	size_t		num_exps;
	t_exp		exp_info;

	quotes.dbl = false;
	quotes.sngl = false;
	i = 0;
	num_exps = 0;
	while (arg[i])
	{
		handle_quotes(&quotes, arg[i]);
		if (is_expand_signal(&arg[i], quotes.sngl))
		{
			set_exp_info(&exp_info, arg, &i, quotes.dbl);
			if (!add_exp(exps, num_exps++, &exp_info))
				return (false);
			continue ;
		}
		i++;
	}
	return (true);
}

static bool	expand_arg(t_data *dat, t_compound *comp, size_t idx)
{
	t_exp_vec	expansions;
	t_arg		*args;

	args = comp_args(comp);
	bzero(&expansions, sizeof(t_exp_vec));
	if (!find_expansions(&expansions, args->av[idx]))
		return (set_error(dat, ERR_MALLOC), false);
	if (!remove_dollar_quotes(&expansions, args, idx))
		return (set_error(dat, ERR_MALLOC), false);
	if (!insert_expansions(&expansions, args, idx))
		return (set_error(dat, ERR_MALLOC), false);
	if (!word_split(&expansions, args, idx))
		return (set_error(dat, ERR_MALLOC), false);
	return (true);
}

void	expand_cmd(t_data *dat, t_compound *comp)
{
	size_t	i;

	i = 0;
	while (i < arg_size(comp))
		if (!expand_arg(dat, comp, i++))
			return ;
}

//notes:
//Word splitting only if outside ""/double quotes (for both redirs and commands)
//expandsion in general outside ''/single quotes only
//1. for redirections expand and check IFS, if any word splitting involved give back that redirection is ambigous (since there can not be 2 args to it) (note however IFS chars at beginning and end of character is allowed)
//2. for commands expand each word/argument, check if IFS present, if so crop them from beginning and end of the expanded variable, if IFS char in the middle of variable split the word
//3. tread $'' not as expansion but as normal single quotes
//4. tread $"" not as expansion but as a normal double quote
void	expand(t_data *dat, t_compound_arr *ca)
{
	size_t		i;
	t_compound	*comp;

	i = 0;
	while (i < ca->len)
	{
		comp = arr_get(ca, i);
		if (comp_type(comp) == CMD)
			expand_cmd(dat, comp);
		// else if (is_redir(comp_type(comp)))
		// 	expand_redir(dat, comp);
		if (!status_ok(dat))
			return ;
		i++;
	}
}
