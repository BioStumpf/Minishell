/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 13:52:42 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/04 10:40:05 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libft/libft.h"

typedef struct s_env_tracker t_env_tracker;

enum e_token
{
	NONE,
	CMD,
	WORD,
	PIPE = '|',
	AND	= '&' * 2 + 1,
	OR = '|' * 2 + 1,
	REDIR_INFILE = '<',
	REDIR_OUTFILE = '>',
	REDIR_HEREDOC = '<' * 2 + 1,
	REDIR_APPEND = '>' * 2 + 1,
	LEFT_PARA = '(',
	RIGHT_PARA = ')',
};
/*
enum e_token
{
	T_NONE,
	CMD,
	T_WORD,
	T_PIPE = '|',
	T_AND	= '&' * 2 + 1,
	T_OR = '|' * 2 + 1,
	T_REDIR_INFILE = '<',
	T_REDIR_OUTFILE = '>',
	T_REDIR_HEREDOC = '<' * 2 + 1,
	T_REDIR_APPEND = '>' * 2 + 1,
	T_LEFT_PARA = '(',
	T_RIGHT_PARA = ')',
	SPACE = ' ',
	TAB = ' ',
	NEWLINE = ' '

};*/

typedef struct s_ast
{
	enum e_token	type;
	int				in_redir_fd;
//	int				out_redir_fd;
	char			*out_redir_file;
	char			**cmd_argv;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct s_ast_buff
{
	size_t	idx;
	t_ast	*start; //root
}			t_ast_buff;

enum e_err
{
    OK,
    ERR_MALLOC,
    // PARSE_ERR_INVALID_CHAR,
    PARSE_ERR_UNCLOSED_QUOTES
};

typedef struct s_data
{
	// char		quit;
	// char		*input;
	// int		ret_code;
	t_ast_buff		ast;
	char			*input;
	char			**new_variable;
	char			*find_var;
	char			*cwd;
	char			*newdir;
	enum e_err		err;
	int				ret_code;
	t_env_tracker	*env_mp;
}				t_data;
/*
	// char		quit;
	// char		*input;
	// int		ret_code;
	t_ast_buff		ast;
	char			*input;
	char			**new_variable;
	char			*find_var;
	char			*cwd;
	char			*newdir;
	t_env_tracker	*env_mp;
	//char		**envp; //this needs to be changed to whatever the envp struct is
}				t_data;*/

typedef struct s_pipe_manager
{
	bool	cmd_found;
	bool	in_pipeline;
	char	*pathwcmd;
	pid_t	child[2];
	t_data	*data;
}				t_pipe_manager;

typedef enum e_builtin
{
	ECHO,
	CD,
	PWD,
	EXPO,
	UNSET,
	ENV,
	EXIT
}			t_builtin;

typedef struct s_env_tracker
{
	int		capacity;
	int		elem_num;
	t_list	*env_ptr;
}			t_env_tracker;

typedef struct s_env
{
	char	*key;
	char	*key_w_equal;
	char	*value;
}			t_env;

/*typedef struct s_data
{
	char			*input;
	char			**new_variable;
	char			*find_var;
	char			*cwd;
	char			*newdir;
	t_env_tracker	*env_mp;
}			t_data;*/

#endif
