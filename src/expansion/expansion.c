/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:07:57 by david             #+#    #+#             */
/*   Updated: 2026/06/26 15:24:49 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "env.h"
#include "structs.h"
#include "err.h"

static bool	is_expand_char(char c)
{
	return (c == '$');
}

static bool	skip_char(char *arg, t_quotes *quotes)
{
	if (*arg == '\"' && !quotes->sngl)
	{
		if (quotes->dbl)
			quotes->dbl = false;
		else
			quotes->dbl = true;
		return (true);
	}
	if (*arg == '\'' && !quotes->dbl)
	{
		if (quotes->sngl)
			quotes->sngl = false;
		else
			quotes->sngl = true;
		return (true);
	}
	if (is_expand_char(*arg) && !is_quote(arg[1]) && !quotes->sngl && !quotes->dbl)
		return (true);
	return (false);
}

//1. nothing
//2. just remove quotes
//3. expand and keep in same argument
//4. expand and split into multiply arguments
//also keep in mind at this stage quotes should be perfect, you do allow "' rn which is wrong

static size_t	get_arg_len(char *arg, t_quotes *quotes)
{
	size_t	len;

	len = 0;
	while (*arg)
	{
		if (skip_char(arg, quotes))
		{
			arg++;
			continue ;
		}
		if (is_expand_char(*arg) && !quotes->sngl) //should distinguish between $ and $'' $"" since the last two in my case just mean quotes and should be skipped
			break ;
		len++;
		arg++;
	}
	return (len);
}

static void	copy_arg(char *dest, char *src, size_t len, t_quotes *quotes)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		if (skip_char(src, quotes))
		{
			src++;
			continue ;
		}
		dest[i] = *src;
		i++;
		src++;
	}
	dest[i] = '\0';
}

static char	*fetch_non_expand(char **arg, t_quotes *quotes)
{
	size_t		len;
	char		*out;
	t_quotes	quotes_cpy;

	ft_memcpy(&quotes_cpy, quotes, sizeof(t_quotes));
	len = get_arg_len(*arg, quotes);
	out = malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	copy_arg(out, *arg, len, &quotes_cpy);
	(*arg) = (*arg) + len;
	return (out);
}

static char	*get_expansion_var(char **arg)
{
	size_t	len;
	char	*var;

	len = 0;
	(*arg)++; //skip $
	while (**arg && ft_isalnum(**arg))
		++len;
	var = malloc(sizeof(char) * (len + 1));
	if (!var)
		return (NULL);
	ft_strlcpy(var, *arg, len + 1);
	*arg += len; //skip the expansion key
	return (var);
}

static t_split	*fetch_expansion(t_data *dat, char **arg, t_quotes *quotes)
{
	char	*to_expand;
	char	*expanded;
	char	*ifs;
	t_split	*splitted;

	if (!**arg)
		return (NULL);
	ifs = get_env_val(dat, "IFS");
	if (quotes->dbl)
		ifs = "\0";
	else if (!ifs) //its unset
		ifs = " \t\n";
	to_expand = get_expansion_var(arg); // allocated
	expanded = get_env_val(dat, to_expand);
	if (!expanded || !*expanded)
		return (free(to_expand), NULL);
	splitted = expand_split(expanded, ifs); //make special split because we need to not completely ignore whitespaces, we need blanks in front and back to indicate 
	if (!splitted)
		set_error(dat, ERR_MALLOC);
	return (splitted);
}

static bool	merge_expansion(t_arg *args, size_t idx
		char *current, t_split *expanded)
{
	if (expanded->len)
}

static bool	expand_arg(t_data *dat, t_compound *comp, size_t idx)
{
	char		*arg;
	char		*current;
	t_arg		*args;
	t_quotes	quotes;
	t_split		*expanded;

	args = comp_args(comp);
	arg = arg_av(comp)[idx];
	quotes.dbl = false;
	quotes.sngl = false;
	//t_arg *args = comp_args(comp);
	//t_arg *new_args = comp_args(comp);
	while (*arg)
	{
		current = fetch_non_expand(&arg, &quotes); //-> will 1. count how long it is 2. malloc 3. fill it (checks quotes, checks $)
		if (!status_ok(dat))
			return (false);
		expanded = fetch_expansion(dat, &arg, &quotes); //this doesnt change quote status, it just needs to know if it should do word splitting or not
		if (!status_ok(dat))
			return (false);
		merge_expansion(args, current, expanded);
		//
		//current may be emtpy;
		// if (must_expand(arg)) 
			//expanded = expand_split(&arg);
			//for i in len(expanded):
				// current = ft_strjoin(current, expanded[i]);
				//add_arg(new_args, i, new);
				//current = ""; //set current to nothing again
		//current.append(*arg);

	}
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
