/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:07:57 by david             #+#    #+#             */
/*   Updated: 2026/06/29 17:57:35 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "env.h"
#include "structs.h"
#include "err.h"
#include <stddef.h>
#include <strings.h>

static bool	is_expand_signal(char *arg, bool sngl_quotes)
{
	char	cur;
	char	next;

	cur = arg[0];
	next = arg[1];
	return (cur == '$' && !sngl_quotes && next &&
		!is_quote(next) && !is_whitespace_metachar(next));
}

static void	set_exp_info(t_exp *exp, char *arg, size_t *idx, bool quoted)
{
	(*idx)++;
	exp->start = *idx;
	exp->quoted = quoted;
	while (arg[*idx] && arg[*idx] != '$')
		(*idx)++;
	if (exp->start == *idx)
		while (arg[*idx] == '$')
			(*idx)++;
	exp->len = *idx - exp->start;
	// $var$$ 
	// $?
	// $$
	// $$$
	// "hi"$var$var first $ = -3 second = -4
	// hivarvar
}

static void	update_expansion_info(t_exp *exp, size_t to_remove)
{
	exp->start -= to_remove;
}

static bool	find_expansions(t_exp_vec *exps, char *arg)
{
	t_quotes	quotes;
	size_t		i;
	size_t		chars_to_remove;
	t_exp		exp_info;

	bzero(&quotes, sizeof(t_quotes));
	i = 0;
	chars_to_remove = 0;
	while (arg[i])
	{
		if (update_quote_status(&quotes, arg[i]))
			chars_to_remove++;
		if (is_expand_signal(&arg[i], quotes.sngl))
		{
			chars_to_remove++;
			set_exp_info(&exp_info, arg, &i, quotes.dbl);
			update_expansion_info(&exp_info, chars_to_remove);
			if (!add_exp(exps, exps->size, &exp_info))
				return (false);
			continue ;
		}
		i++;
	}
	return (true);
}

static size_t	no_quote_size(char *arg)
{
	t_quotes	quotes;
	size_t		size;

	bzero(&quotes, sizeof(t_quotes));
	size = 0;
	while (*arg)
	{
		if (update_quote_status(&quotes, *arg))
			arg++;
		else if (is_expand_signal(arg, quotes.sngl))
		{
			arg++;
			while (arg[0] == '$' && arg[1] == '$')
			{
				arg++;
				size++;
			}
		}
		else
		{
			arg++;
			size++;
		}
	}
	return (size);
}

static char	*get_no_quote(size_t arg_size, char *arg)
{
	t_quotes	quotes;
	size_t		i;
	char		*out;

	bzero(&quotes, sizeof(t_quotes));
	out = malloc((arg_size + 1) * sizeof(char));
	i = 0;
	if (!out)
		return (NULL);
	while (*arg)
	{
		if (update_quote_status(&quotes, *arg))
			arg++;
		else if (is_expand_signal(arg, quotes.sngl))
		{
			arg++;
			while (arg[0] == '$' && arg[1] == '$')
				out[i++] = *arg++;
		}
		else
			out[i++] = *arg++;
	}
	out[i] = '\0';
	return (out);
}

static bool	remove_dollar_quotes(t_exp_vec *exps, t_arg *args, size_t idx)
{
	size_t		new_arg_size;
	char		*new_arg;

	new_arg_size = no_quote_size(args->av[idx]);
	new_arg = get_no_quote(new_arg_size, args->av[idx]);
	if (!new_arg)
		return (free(exps), false);
	args->av[idx] = new_arg;
	return (true);
}

static bool	insert_expansions(t_data *dat, t_exp_vec *exps,
	t_arg *args, size_t idx)
{
	size_t	i;
	size_t	expanded_len;
	char	*expanded;
	char	*arg;

	i = 0;
	arg = args->av[idx];
	expanded_len = post_expansion_len(arg, dat, exps); 
	expanded = merge_expansions(expanded_len, arg, dat, exps);
	if (!expanded)
		return (free(exps), false);

	// while (*arg)
	// {
	// 	expanded_tmp = expanded;
	// 	start = exp_start(exps, i);
	// 	stop = start + exp_len(exps, i);
	// 	tmp = arg[stop];
	// 	arg[stop] = '\0';
	// 	expansion_var = get_env_val(dat, &arg[start]);
	// 	arg[stop] = tmp;
	// 	arg[start] = '\0';
	// 	expanded = ft_strjoin(expanded_tmp, expansion_var);
	// 	free(expanded_tmp);
	// }
	// free(args->av[idx]);
	args->av[idx] = expanded;
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
