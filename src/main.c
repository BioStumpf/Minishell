/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 14:04:09 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/06 12:28:28 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "readline_sigs.h"
#include <readline/readline.h>
#include "parsing.h"
#include "execution.h"
#include "structs.h"
#include <err.h>
#include <env.h>
#include <errno.h>

volatile sig_atomic_t	g_ret = 0;

static void	init(t_data *dat, int ac, char **av)
{
	(void)ac;
	(void)av;
	rl_event_hook = readline_hook;
	ft_bzero(dat, sizeof(t_data));
	errno = 0;
	if (isatty(STDIN_FILENO))
		dat->read_input = read_terminal;
	else if (errno == ENOTTY)
		dat->read_input = read_stdin;
	else
		exit (1);
}

static void	free_all(t_data *dat)
{
	rl_clear_history();
	cleanup_normal(dat);
	/*if ((!dat->input && dat->read_input == read_terminal)
		|| dat->err == EXIT_CALL)
		ft_printf(2, "exit\n");*/
}

static void	reset(t_data *dat)
{
	clean_ast(&dat->ast);
	free(dat->input);
	close_heredocs(dat);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	dat;

	init(&dat, argc, argv);
	process_env(&dat, envp);
	if (fatal_error(&dat))
		return (free_all(&dat), 1);
	while (1)
	{
		set_error(&dat, OK);
		dat.read_input(&dat);
		parse_input(&dat);
		coordinate_exec(&dat);
		reset(&dat);
		if (fatal_error(&dat))
			return (free_all(&dat), g_ret);
		if (!dat.input || dat.err == EXIT_CALL)
			return (free_all(&dat), dat.ret);
		dat.ret = g_ret;
		g_ret = 0;
	}
}
