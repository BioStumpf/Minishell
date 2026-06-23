/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:07:57 by david             #+#    #+#             */
/*   Updated: 2026/06/23 16:36:12 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "env.h"

static void	set_quote_stat(char c, bool *s_quotes, bool *d_quotes)
{
	if (c == '\"' && !*s_quotes)
	{
		if (*d_quotes)
			*d_quotes = false;
		else
			*d_quotes = true;
	}
	else if (c == '\'' && !*d_quotes)
	{
		if (*s_quotes)
			*s_quotes = false;
		else
			*s_quotes = true;
	}
}

//1. nothing
//2. just remove quotes
//3. expand and keep in same argument
//4. expand and split into multiply arguments
//also keep in mind at this stage quotes should be perfect, you do allow "' rn which is wrong

//compute len of complete argument where expansions are joined with rest
//implement special split that considers quoting rules and IFS and adds as many arguments to av as needed
//now 
static void	expand_arg(t_compound *comp, size_t idx)
{
	char	*arg;
	bool	s_quotes;
	bool	d_quotes;

	s_quotes = false;
	d_quotes = false;
	arg = arg_av(comp)[idx];
	
	while (*arg)
	{
		set_quote_stat(*arg, &s_quotes, &d_quotes);
		if (must_expand(arg) && !s_quotes) 

	}
}

void	expand_cmd(t_data *dat, t_compound *comp)
{
	size_t	i;

	i = 0;
	while (i < arg_size(comp))
		expand_arg(comp, i++);
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
		else if (is_redir(comp_type(comp)))
			expand_redir(dat, comp);
		i++;
	}
}
