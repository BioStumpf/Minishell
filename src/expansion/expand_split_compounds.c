/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split_compounds.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 18:46:51 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/19 18:24:27 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <fcntl.h>
#include "libft.h"
#include "err.h"
#include "structs.h"
#include "get_next_line.h"
#include <errno.h>

static bool	open_fds(t_ast *node, int fds[2])
{
	fds[0] = reopen_heredoc(get_open_fd(node), O_RDONLY);
	if (fds[0] == -1)
		return (false);
	fds[1] = open("/tmp", O_TMPFILE | O_WRONLY | O_EXCL, 0600);
	if (fds[1] == -1)
		return (close(fds[0]), false);
	return (true);
}

static void	expand_heredoc(t_data *dat, t_ast *node)
{
	int			fds[2];
	char		*line;
	char		*expanded;
	t_exp_vec	exps;

	if (!open_fds(node, fds))
		return (set_error(dat, ERR_SYS, NULL));
	while (1)
	{
		errno = 0;
		line = get_next_line(fds[0]);
		expanded = expand_str(dat, line, KEEP_QUOTES, &exps);
		free(line);
		if (!expanded)
			break ;
		free(exps.expansions);
		ft_putstr_fd(expanded, fds[1]);
		free(expanded);
	}
	if (errno != 0)
		set_error(dat, ERR_SYS, NULL);
	if (dup2(fds[1], get_open_fd(node)) == -1 && status_ok(dat))
		set_error(dat, ERR_SYS, NULL);
	return (close(fds[0]), close(fds[1]), (void)0);
}

static void	expand_redir(t_data *dat, t_ast *node)
{
	char		*expanded_str;
	t_arg		new;
	t_exp_vec	exps;

	if (node->type == REDIR_HEREDOC && node->u_value.s_redir.expand)
		return (expand_heredoc(dat, node));
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
