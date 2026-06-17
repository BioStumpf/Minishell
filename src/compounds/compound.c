/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 13:37:33 by david             #+#    #+#             */
/*   Updated: 2026/06/17 18:17:09 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <stdlib.h>
// #include <stdbool.h>

static size_t	count_compounds(t_list *tokens)
{
	size_t	count;
	t_node	*cur;
	bool	in_cmd;

	count = 0;
	cur = tokens->head;
	in_cmd = false;
	while (cur)
	{
		if (tok_type(cur) != WORD) 
		{
			in_cmd = false;
			count++;
		}
		else if (!in_cmd)
		{
			in_cmd = true;
			count++;
		}
		cur = cur->next;
	}
	return (count);
}

static bool	add_words(t_compound *comp, t_node **token)
{
	void	*s;

	while (*token && tok_type(*token) == WORD) 
	{
		s = add_arg(comp_args(comp), arg_size(comp), tok_word(*token));
		if (!s)
			return (false);
		*token = (*token)->next;
	}
	return (true);
}

static void	add_redir(t_compound *comp, t_node *redir)
{
	comp->u_value.s_redir.fd = tok_fd(redir);
	comp->u_value.s_redir.filename = tok_filename(redir);
}

static bool	make_compound_arr(t_compound_arr *ca, t_list *tokens)
{
	size_t	i;
	t_node	*cur;

	i = 0;
	cur = tokens->head;
	while (i < ca->len)
	{
		if (tok_type(cur) == WORD)
		{
			ca->arr[i].type = CMD;
			if (!add_words(&ca->arr[i], &cur))
				return (false);
		}
		else
		{
			if (is_redir(tok_type(cur)))
				add_redir(&ca->arr[i], cur);
			ca->arr[i].type = tok_type(cur);
			cur = cur->next;
		}
		i++;
	}
	return (true);
}

t_compound_arr	*compound_group(t_data *dat, t_list *tokens)
{
	(void)dat;
	t_compound_arr	*ca;

	if (!tokens)
		return (NULL);
	ca = malloc(sizeof(t_compound_arr));
	if (!ca)
		return (free_compound(ca, ERR_MALLOC, dat), NULL);
	ca->len = count_compounds(tokens);
	ca->arr = malloc(sizeof(t_compound) * ca->len);
	if (!ca->arr)
		return (free_compound(ca, ERR_MALLOC, dat), NULL);
	ft_bzero(ca->arr, ca->len * (sizeof(t_compound)));
	if (!make_compound_arr(ca, tokens))
		return (free_compound(ca, ERR_MALLOC, dat), NULL);
	return (ca);
}
