/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 15:16:05 by david             #+#    #+#             */
/*   Updated: 2026/07/14 15:19:40 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "readline_sigs.h"
#include <readline/readline.h>
#include "parsing.h"
#include "execution.h"
#include <err.h>
#include <env.h>
#include <sys/wait.h>

volatile sig_atomic_t	g_ret = 0;

static void	init(t_data *dat, int ac, char **av)
{
	(void)ac;
	(void)av;
	ft_bzero(dat, sizeof(t_data));
	if (isatty(STDIN_FILENO))
		dat->read_input = read_terminal;
	else
		dat->read_input = read_stdin;
}

static void	free_all(t_data *dat)
{
	rl_clear_history();
	error_and_cleanup(dat, NULL, 0);
	if (!dat->input && dat->read_input == read_terminal)
		ft_printf(2, "exit\n");
}

//NOTES:
//readline history
//readline prompt?? does it have to be minishell what about directory?
//signals
//compound echo "$" doesnt print $ in the end
// execute(&dat) //kian part
void	fake_sleep(void)
{
	static int	flag;
	int			pid;

	pid = fork();
	if (pid == 0)
	{
		setup_signals(SIG_DFL, SIG_DFL);
		if (flag == 0)
			sleep(3);
		exit(0);
	}
	flag++;
	wait(NULL);
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
		dat.ret = g_ret;
		set_error(&dat, OK);
		dat.read_input(&dat);
		parse_input(&dat);
		coordinate_exec(&dat);
		clean_ast(&dat.ast);
		free(dat.input);
		if (fatal_error(&dat) || !dat.input)
			return (free_all(&dat), g_ret);
	}
}
//NOTES:
//readline history
//readline prompt?? does it have to be minishell what about directory?
//signals
//compound echo "$" doesnt print $ in the end
// execute(&dat) //kian part
//kian part
//since we run infinetly, clean up the ast after each loop iteration
