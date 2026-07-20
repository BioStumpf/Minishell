/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 13:52:42 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/20 10:09:13 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libft/libft.h"

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
		char		**av;
		struct
		{
			bool	quoted;
			int		fd;
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
	ERR_MALLOC,
	PARSE_ERR_UNCLOSED_QUOTES,
	PARSE_ERR_REDIR,
	PARSE_ERR_PIPE,
	PARSE_ERR_OR,
	PARSE_ERR_AND,
	PARSE_ERR_PARA,
	ERR_DUP,
	ERR_OPEN,
	ERR_READ,
	ERR_SIG,
	ERR_PIPE,
	ERR_FORK,
};

typedef struct s_data
{
	int				ret;
	enum e_err		err;
	char			*input;
	char			**new_variable;
	char			*find_var;
	char			*cwd;
	char			*newdir;
	enum e_err		err;
	int				ret_code;
	char			*ret_str;
	t_pipe_manager	*pipe_info;
	t_env_tracker	*env_mp;
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
