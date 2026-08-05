/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split_compounds.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:07:57 by david             #+#    #+#             */
/*   Updated: 2026/07/30 12:17:34 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "err.h"
#include "structs.h"

static void	expand_heredoc(t_data *dat, t_compound *comp)
{
	bool		expand;
	char		*expanded_str;
	t_exp_vec	exps;

	ft_bzero(&exps, sizeof(t_exp_vec));
	expanded_str = remove_dollar_quotes(&exps, comp_filename(comp), RM_QUOTES);
	if (!expanded_str)
		return (set_error(dat, ERR_MALLOC));
	expand = ft_strlen(expanded_str) == ft_strlen(comp_filename(comp));
	free(comp_filename(comp));
	comp->u_value.s_redir.filename = expanded_str;
	return (heredoc(dat, comp, expand));
}

static void	expand_other_redir(t_data *dat, t_compound *comp)
{
	char		*expanded_str;
	t_arg		new;
	t_exp_vec	exps;

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

static void	expand_redir(t_data *dat, t_compound *comp)
{
	if (comp_type(comp) == REDIR_HEREDOC)
		return (expand_heredoc(dat, comp));
	else
		return (expand_other_redir(dat, comp));
}

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
	if (!add_arg(&new, new.size, NULL))
		return (set_error(dat, ERR_MALLOC));
	free_args(comp_args(comp));
	*comp_args(comp) = new;
}

void	expand(t_data *dat, t_compound_arr *ca)
{
	size_t		i;
	t_compound	*comp;

	if (!ca || !status_ok(dat))
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
