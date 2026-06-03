/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 13:37:33 by david             #+#    #+#             */
/*   Updated: 2026/06/03 13:46:39 by dstumpf          ###   ########.fr       */
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
		if (fetch_token(cur)->type != T_WORD) 
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

static void	add_words(t_compound *compound, t_node **token)
{
	void	*s;

	while (*token && fetch_token(*token)->type == T_WORD)
	{
		s = add_arg(&compound->args, compound->args.size, fetch_token(*token)->word);
		if (!s)
			return ;
		*token = (*token)->next;
	}
}

static void	make_compound_arr(t_compound_arr *ca, t_list *tokens)
{
	size_t	i;
	t_node	*cur;

	i = 0;
	cur = tokens->head;
	while (i < ca->len)
	{
		if (fetch_token(cur)->type != T_WORD)
		{
			ca->arr[i].type = fetch_token(cur)->type;
			cur = cur->next;
		}
		else
		{
			ca->arr[i].type = CMD;
			add_words(&ca->arr[i], &cur);
		}
		i++;
	}
}

t_compound_arr	*compound_group(t_data *dat, t_list *tokens)
{
	(void)dat;
	t_compound_arr	*ca;

	if (!tokens)
		return (NULL);
	ca = malloc(sizeof(t_compound_arr));
	if (!ca)
		return (NULL);
	ca->len = count_compounds(tokens);
	ca->arr = malloc(sizeof(t_compound) * ca->len);
	if (!ca->arr)
		return (free(ca), NULL);
	if (!init_args(&ca->arr->args))
		return (free(ca), NULL);
	make_compound_arr(ca, tokens);
	return (ca);
}
