/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 15:16:05 by david             #+#    #+#             */
/*   Updated: 2026/07/27 16:40:32 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "readline_sigs.h"
#include <readline/readline.h>
#include "parsing.h"
#include "execution.h"
#include <err.h>
#include <env.h>

volatile sig_atomic_t	g_ret = 0;

static void	init(t_data *dat, int ac, char **av)
{
	(void)ac;
	(void)av;
	rl_event_hook = readline_hook;
	ft_bzero(dat, sizeof(t_data));
	if (isatty(STDIN_FILENO))
		dat->read_input = read_terminal;
	else
		dat->read_input = read_stdin;
}

static void	free_all(t_data *dat)
{
	rl_clear_history();
	cleanup_normal(dat);
	if ((!dat->input && dat->read_input == read_terminal)
		|| dat->err == EXIT_CALL)
		ft_printf(2, "exit\n");
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
		clean_ast(&dat.ast);
		free(dat.input);
		if (fatal_error(&dat) || !dat.input || dat.err == EXIT_CALL)
			return (free_all(&dat), g_ret);
		dat.ret = g_ret;
		g_ret = 0;
	}
}
