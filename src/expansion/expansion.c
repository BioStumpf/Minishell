/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:07:57 by david             #+#    #+#             */
/*   Updated: 2026/06/23 21:53:52 by david            ###   ########.fr       */
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
	//char *current;
	//t_arg *args = comp_args(comp);
	//t_arg *new_args = comp_args(comp);
	while (*arg)
	{
		//current = fetch_string() -> will 1. count how long it is 2. malloc 3. fill it (checks quotes, checks $)
		//current may be emtpy;
		// if (must_expand(arg)) 
			//expanded = expand_split(&arg);
			//for i in len(expanded):
				// current = ft_strjoin(current, expanded[i]);
				//add_arg(new_args, i, new);
				//current = ""; //set current to nothing again
		//current.append(*arg);

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
