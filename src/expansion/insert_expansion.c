/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:13:00 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/03 14:14:10 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "env.h"

static char	*get_exp_value(t_data *dat, t_exp *exp, char *str)
{
	char	tmp;
	char	*value;
	size_t	start;
	size_t	stop;

	start = exp->start;
	stop = start + exp->len;
	if (str[start] == '?')
		return (dat->ret_str);
	tmp = str[stop];
	str[stop] = '\0';
	value = get_env_val(dat, &str[start]);
	str[stop] = tmp;
	return (value);
}

static size_t	post_expansion_len(char *str, t_data *dat, t_exp_vec *exps)
{
	size_t	exp_idx;
	size_t	len;
	size_t	str_idx;

	len = 0;
	str_idx = 0;
	exp_idx = 0;
	while (str[str_idx])
	{
		if (exp_idx < exps->size && str_idx == exp_start(exps, exp_idx))
		{
			len += ft_strlen(get_exp_value(dat, get_exp(exps, exp_idx), str));
			str_idx += exp_len(exps, exp_idx);
			exp_idx++;
		}
		else
		{
			len++;
			str_idx++;
		}
	}
	return (len);
}

static void	cpy_expansion(char *exp_value, char *expanded,
	size_t *idx, t_exp *exp_info)
{
	if (!exp_value)
		return ;
	exp_info->start = *idx;
	while (*exp_value)
		expanded[(*idx)++] = *exp_value++;
	exp_info->len = *idx - exp_info->start;
}

static char	*merge_expansions(size_t len, char *str,
	t_data *dat, t_exp_vec *exps)
{
	size_t	i;
	size_t	exp_idx;
	size_t	str_idx;
	char	*expanded;
	char	*exp_value;

	str_idx = 0;
	exp_idx = 0;
	i = 0;
	expanded = malloc((len + 1) * sizeof(char));
	if (!expanded)
		return (NULL);
	while (i < len)
	{
		if (exp_idx < exps->size && str_idx == exp_start(exps, exp_idx))
		{
			str_idx += exp_len(exps, exp_idx);
			exp_value = get_exp_value(dat, get_exp(exps, exp_idx), str);
			cpy_expansion(exp_value, expanded, &i, get_exp(exps, exp_idx++));
		}
		else
			expanded[i++] = str[str_idx++];
	}
	expanded[i] = '\0';
	return (expanded);
}

char	*insert_expansions(t_data *dat, t_exp_vec *exps, char *str)
{
	size_t	expanded_len;
	char	*expanded;

	expanded_len = post_expansion_len(str, dat, exps);
	expanded = merge_expansions(expanded_len, str, dat, exps);
	if (!expanded)
		return (free(exps->expansions), NULL);
	return (expanded);
}
