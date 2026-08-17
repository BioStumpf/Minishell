/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 13:52:42 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/17 19:31:43 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libft.h"
# include "args.h"

typedef struct s_env_tracker	t_env_tracker;
typedef struct s_pipe_manager	t_pipe_manager;

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

typedef struct s_ast
{
	enum e_token	type;
	union
	{
		t_arg		args;
		struct
		{
			bool	expand;
			int		fd;
			int		open_fd;
			char	*operand;
		} s_redir;
	} u_value;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct s_ast_buff
{
	size_t	idx;
	t_ast	*buf;
	t_ast	*root;
}			t_ast_buff;

enum e_err
{
	OK,
	ERR_SYS,
	EXIT_CALL,
	PARSE_ERR_UNCLOSED_QUOTES,
	PARSE_ERR_UNCLOSED_PARA,
	PARSE_ERR_REDIR,
	PARSE_ERR_TREE
};

typedef struct s_data
{
	int				heredoc_start;
	int				heredoc_end;
	int				ret;
	enum e_err		err;
	char			*input;
	char			**new_variable;
	char			*find_var;
	char			*newdir;
	char			ret_str[4];
	t_pipe_manager	*pipe_info;
	t_ast_buff		ast;
	t_env_tracker	*env_mp;
	void			(*read_input)(struct s_data *dat);
}					t_data;

typedef struct s_pipe_manager
{
	bool	cmd_found;
	bool	in_pipeline;
	char	*pathwcmd;
	pid_t	child[2];
	t_ast	*cmd_node;
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

#endif
