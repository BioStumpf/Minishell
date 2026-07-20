/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 17:05:45 by david             #+#    #+#             */
/*   Updated: 2026/07/07 16:11:41 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "readline_sigs.h" 
#include <unistd.h>
#include <err.h>

//NOTE:
//sigint readline set before readline to reprompt; sigquite deactivated
//sigint and sigquit execute only in main process,
//children need to handle it differently depending on the type of child:
//1. pipe: if (in_pipeline) then: ignore sigint and sigquit
//(it needs to wait for children)
//         else then: do nothing, it must be the main process
//which should have main process behavior
//2. builtin: if (in_pipeline) then: default sigint and sigquit
//(it needs to be killed)
//			  else then: nothing, it must be main process.
//3. extern: if (in_pipelin) then: default sigint and sigquit
//			 else then: default sigint and sigquit
//(in both cases this will be child process which needs killing)

void	sigint_readline(int sig)
{
	g_ret = (128 + sig) % 256;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// printf("handler in pid %d\n", getpid());
void	sigint_execute(int sig)
{
	g_ret = (128 + sig) % 256;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
}

void	sigquit_execute(int sig)
{
	g_ret = (128 + sig) % 256;
	write(STDOUT_FILENO, "Quit\n", 5);
	rl_on_new_line();
}

void	setup_signals(void (*sigquit)(int sig), void (*sigint)(int sig))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sigint;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = sigquit;
	sigaction(SIGQUIT, &sa, NULL);
}
