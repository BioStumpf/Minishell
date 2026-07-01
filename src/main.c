/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 11:35:41 by david             #+#    #+#             */
/*   Updated: 2026/07/03 12:51:46 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 11:02:46 by dstumpf           #+#    #+#             */
/*   Updated: 2026/06/30 16:01:45 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "parsing.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <err.h>
#include <env.h>

void	free_all(t_data *dat)
{
	// rl_clear_history();
	error_and_cleanup(dat, NULL, 0);
	free(dat->ret_str);
}

static void	set_return_str(t_data *dat)
{
	free(dat->ret_str);
	dat->ret_str = ft_itoa(dat->ret_code);
	if (!dat->ret_str)
		set_error(dat, ERR_MALLOC);
}

//NOTES:
//1. env_value accessor needs to take care of null input (what if env is NULL?)
//2. i added checks into env accessor for NULLs
//3. env leaks
int main(int argc, char **argv, char **envp)
{
	t_data	dat;

	ft_bzero(&dat, sizeof(t_data));
	(void)argc;
	(void)argv;
	process_env(&dat, envp);
	if (fatal_error(&dat))
		return (1);
	set_return_str(&dat);
	if (fatal_error(&dat))
		return (free_all(&dat), 1);
	while (1)
	{
		set_error(&dat, OK);
		// dat.input = "1<$var | echo $var\"hi\""; //echo hihello world
		// dat.input = "$var"; //echo hihello world
		// dat.input = "echo var"; //echo hihello world
		// dat.input = "<< \"lim\" | && $$$?$var ||| echo hi$var"; //echo hihello world
		dat.input = readline("minishell$ "); //here ensure that it does not always print minishell but also tha path right???? I am unsure though) i.e. instead of minishell as argument for readline use envp's pwd concatenated with minishell
		if (!dat.input)
			set_error(&dat, ERR_MALLOC);
		parse_input(&dat);
		// execute(&dat) //kian part
		//clean_ast(dat.ast); //since we run infinetly, clean up the ast after each loop iteration
		free(dat.input);
		set_return_str(&dat);
		return (free_all(&dat), 1);
		// if (fatal_error(&dat))
		// 	return (free_all(&dat), dat.ret_code);
	}
}
