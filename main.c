/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 18:21:16 by dstumpf           #+#    #+#             */
/*   Updated: 2026/04/19 17:57:22 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv, char **envp)
{
	//t_data	dat;
	char	*input;

	(void)argc;
	(void)argv;
	(void)envp; //remove this since we dont need to cast it, for now we dont use it so i void it
	//init_dat(&dat, envp); //copy envp into our own environment/envp (we should not change the original one)
	while (1)
	{
		input = readline("minishell$ "); //here ensure that it does not always print minishell but also tha path right???? I am unsure though) i.e. instead of minishell as argument for readline use envp's pwd concatenated with minishell
		//parse_input(dat) //david part ->make sure readline input is inside dat struct (only use one struct for everything: errors, etc...)
		//execute_input(dat) //kian part
		//clean_ast(dat.ast); //since we run infinetly, clean up the ast after each loop iteration
		//free(dat.input); //readline return value must also be freed always 


		//these are just for now remove them when not needed anymore
		printf("%s\n", input);
		free(input);
	}
}
