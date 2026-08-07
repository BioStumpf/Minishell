/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split_compounds.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:07:57 by david             #+#    #+#             */
/*   Updated: 2026/08/07 10:14:36 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "err.h"
#include "structs.h"
#include "execution.h"

static void	expand_heredoc(t_data *dat, t_ast *node)
{
	bool		expand;
	char		*expanded_str;
	t_exp_vec	exps;

	ft_bzero(&exps, sizeof(t_exp_vec));
	expanded_str = remove_dollar_quotes(&exps, get_operand(node), RM_QUOTES);
	if (!expanded_str)
		return (set_error(dat, ERR_SYS, NULL));
	expand = ft_strlen(expanded_str) == ft_strlen(get_operand(node));
	free(get_operand(node));
	set_operand(node, expanded_str);
	return (heredoc(dat, node, expand));
}

void	prep_heredoc(t_ast *node, t_pipe_manager *pipe_info)
{
	if (pipe_info->in_pipeline == NO_PIPELINE)
	{
		if (!node)
			return ;
		else if (node->type == REDIR_HEREDOC)
		{
			expand_heredoc(pipe_info->data, node);
			prep_heredoc(node->left, pipe_info);
		}
		else if (node->type == CMD || is_redir(node->type))
			prep_heredoc(node->left, pipe_info);
		else if (node->type == PIPE)
		{
			prep_heredoc(node->left, pipe_info);
			prep_heredoc(node->right, pipe_info);
		}
	}
}

static void	expand_redir(t_data *dat, t_ast *node)
{
	char		*expanded_str;
	t_arg		new;
	t_exp_vec	exps;

	if (node->type == REDIR_HEREDOC)
		return ;
	ft_bzero(&new, sizeof(t_arg));
	expanded_str = expand_str(dat, get_operand(node), RM_QUOTES, &exps);
	if (!expanded_str)
		return ;
	if (!word_split(dat, &exps, &new, expanded_str))
		return (free_args(&new), free(exps.expansions), free(expanded_str));
	free(exps.expansions);
	if (new.size != 1)
	{
		free_args(&new);
		free(expanded_str);
		return (set_error(dat, PARSE_ERR_REDIR, get_operand(node)));
	}
	free_args(&new);
	free(get_operand(node));
	set_operand(node, expanded_str);
}

static void	expand_cmd(t_data *dat, t_ast *node)
{
	char		*expanded_str;
	size_t		i;
	size_t		arg_len;
	t_arg		new;
	t_exp_vec	exps;

	i = 0;
	ft_bzero(&new, sizeof(t_arg));
	arg_len = ast_arg_len(node);
	while (i < arg_len)
	{
		expanded_str = expand_str(dat, get_av(node)[i], RM_QUOTES, &exps);
		if (!expanded_str)
			return (free_args(&new));
		if (!word_split(dat, &exps, &new, expanded_str))
			return (free_args(&new), free(exps.expansions), free(expanded_str));
		free(exps.expansions);
		free(expanded_str);
		i++;
	}
	if (!add_arg(&new, new.size, NULL))
		return (set_error(dat, ERR_SYS, NULL));
	free_args(ast_args(node));
	set_args(node, &new);
}

void	expand(t_data *dat, t_ast *node)
{
	while (node && status_ok(dat)
		&& (is_redir(node->type) || node->type == CMD))
	{
		if (node->type == CMD)
			expand_cmd(dat, node);
		else if (is_redir(node->type))
			expand_redir(dat, node);
		node = node->left;
	}
}
