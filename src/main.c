/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 18:21:16 by dstumpf           #+#    #+#             */
/*   Updated: 2026/05/07 17:24:48 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
#include <stdio.h>
#include "libft.h"
#include "parsing.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "main.h"

void	free_envp(t_data *dat)
{
	(void)dat;
}


int main(int argc, char **argv, char **envp)
{
	t_data	dat;

	ft_bzero(&dat, sizeof(t_data));
	(void)argc;
	(void)argv;
	(void)envp; //remove this since we dont need to cast it, for now we dont use it so i void it
	//init_dat(&dat, envp); //copy envp into our own environment/envp (we should not change the original one)
	while (1)
	{
		dat.input = readline("minishell$ "); //here ensure that it does not always print minishell but also tha path right???? I am unsure though) i.e. instead of minishell as argument for readline use envp's pwd concatenated with minishell
		parse_input(&dat);
		//execute_input(dat) //kian part
		//clean_ast(dat.ast); //since we run infinetly, clean up the ast after each loop iteration
		free(dat.input);
		//set_last_return(&dat); //this is to fetch dat->return and set envp $? to this return
		if (dat.quit == QUIT)
			return (free_envp(&dat), 1);
	}
}
