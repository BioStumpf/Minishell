/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 11:35:41 by david             #+#    #+#             */
/*   Updated: 2026/07/06 11:32:50 by david            ###   ########.fr       */
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
#include "execution.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <err.h>
#include <env.h>

void	free_all(t_data *dat)
{
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

int	main(int argc, char **argv, char **envp)
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
		dat.input = readline("minishell$ ");
		if (!dat.input)
			set_error(&dat, ERR_MALLOC);
		parse_input(&dat);
		coordinate_exec(&dat);
		clean_ast(&dat.ast);
		free(dat.input);
		set_return_str(&dat);
		if (fatal_error(&dat))
			return (free_all(&dat), dat.ret_code);
	}
}
//NOTES:
//readline history
//readline prompt?? does it have to be minishell what about directory?
//signals
//compound echo "$" doesnt print $ in the end
// execute(&dat) //kian part
 //kian part\
//since we run infinetly, clean up the ast after each loop iteration
