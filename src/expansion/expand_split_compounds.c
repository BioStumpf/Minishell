/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split_compounds.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:07:57 by david             #+#    #+#             */
/*   Updated: 2026/07/03 17:04:26 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "err.h"

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

static bool	filename_quoted(char *filename)
{
	while (*filename && !is_quote(*filename))
		filename++;
	if (is_quote(*filename))
		return (true);
	return (false);
}

static void	expand_redir(t_data *dat, t_compound *comp)
{
	char		*expanded_str;
	t_exp_vec	exps;
	t_arg		new;

	ft_bzero(&new, sizeof(t_arg));
	comp->u_value.s_redir.quoted = filename_quoted(comp_filename(comp));
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
