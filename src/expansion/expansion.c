/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:07:57 by david             #+#    #+#             */
/*   Updated: 2026/06/24 17:13:12 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "env.h"
#include "structs.h"
#include "err.h"

static bool	skip_char(char *arg, bool *s_quotes, bool *d_quotes)
{
	if (*arg == '\"' && !*s_quotes)
	{
		if (*d_quotes)
			*d_quotes = false;
		else
			*d_quotes = true;
		return (true);
	}
	if (*arg == '\'' && !*d_quotes)
	{
		if (*s_quotes)
			*s_quotes = false;
		else
			*s_quotes = true;
		return (true);
	}
	if (*arg == '$' && !is_quote(arg[1]) && !s_quotes && !d_quotes)
		return (true);
	return (false);
}

//1. nothing
//2. just remove quotes
//3. expand and keep in same argument
//4. expand and split into multiply arguments
//also keep in mind at this stage quotes should be perfect, you do allow "' rn which is wrong

static bool	is_expand_char(char c)
{
	return (c == '$');
}

static size_t	get_arg_len(char *arg)
{
	size_t	len;
	bool	s_quote;
	bool	d_quote;

	len = 0;
	s_quote = false;
	d_quote = false;
	while (*arg)
	{
		if (skip_char(arg, &s_quote, &d_quote))
		{
			arg++;
			continue ;
		}
		if (is_expand_char(*arg) && !s_quote) //should distinguish between $ and $'' $"" since the last two in my case just mean quotes and should be skipped
			break ;
		len++;
		arg++;
	}
	return (len);
}

static void	copy_arg(char *dest, char *src, size_t len)
{
	size_t	i;
	bool	s_quote;
	bool	d_quote;

	i = 0;
	s_quote = false;
	d_quote = false;
	while (i < len)
	{
		if (skip_char(src, &s_quote, &d_quote))
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

static char	*fetch_arg(char **arg)
{
	size_t	len;
	char	*out;

	len = get_arg_len(*arg);
	out = malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	copy_arg(out, *arg, len);
	(*arg) = (*arg) + len;
	return (out);
}

static char	*get_expansion_var(char **arg)
{

}

static char	**expand_split(t_data *dat, char **arg, int split)
{
	char	*to_expand;
	char	*expanded;
	char	*ifs;
	char	**splitted;

	ifs = get_env_val(dat, "IFS");
	to_expand = get_expansion_var(arg);
	expanded = get_env_val(dat, to_expand);
	if (!expanded || !*expanded)
		return (NULL);
	splitted = ft_split(expanded, ifs);
	if (!splitted)
		set_error(dat, ERR_MALLOC);
	return (splitted);
}

static bool	expand_arg(t_data *dat, t_compound *comp, size_t idx)
{
	char	**expanded;
	char	*arg;
	char	*current;

	arg = arg_av(comp)[idx];
	//t_arg *args = comp_args(comp);
	//t_arg *new_args = comp_args(comp);
	while (*arg)
	{
		current = fetch_arg(&arg); //-> will 1. count how long it is 2. malloc 3. fill it (checks quotes, checks $)
		if (!status_ok(dat))
			return (false);
		expanded = expand_split(dat, &arg);
		if (!status_ok(dat))
			return (false);
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
