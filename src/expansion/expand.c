/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:24:21 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/18 18:46:55 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "err.h"

char	*expand_str(t_data *dat, char *str,
	bool quote_removal, t_exp_vec *exps)
{
	char		*trimmed_str;
	char		*expanded_str;

	if (!str)
		return (NULL);
	ft_bzero(exps, sizeof(t_exp_vec));
	if (!find_expansions(exps, str, quote_removal))
		return (set_error(dat, ERR_SYS, NULL), NULL);
	trimmed_str = remove_dollar_quotes(exps, str, quote_removal);
	if (!trimmed_str)
		return (set_error(dat, ERR_SYS, NULL), NULL);
	expanded_str = insert_expansions(dat, exps, trimmed_str);
	free(trimmed_str);
	if (!expanded_str)
		return (set_error(dat, ERR_SYS, NULL), NULL);
	return (expanded_str);
}
