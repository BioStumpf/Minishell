/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:47:35 by david             #+#    #+#             */
/*   Updated: 2026/05/20 10:43:35 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

#define NO_PIPELINE 0
#define IN_PIPELINE 1

enum e_token
{
	NONE,
	CMD_BUILTIN,
	CMD_EXTERN,
	// CMD, //this will be the real thing
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
	int				redir_fd;
	char			*redir_file;
	char			**cmd_argv;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct s_ast_buff
{
	size_t	idx;
	t_ast	*start; //root
}			t_ast_buff;

typedef struct s_data
{
	// char		quit;
	// char		*input;
	// int		ret_code;
	t_ast_buff	ast;
	char		**envp; //this needs to be changed to whatever the envp struct is
}				t_data;

t_ast_buff	ast_init(size_t size)
{
	t_ast_buff	buff;

	buff.idx = 0;
	buff.start = malloc(sizeof(t_ast) * size);
	return (buff);
}

typedef struct s_dummy {
	enum e_token	type;
	int				redir_fd_target;
	char			*redir_file;
	char			**cmd_argv;
}					t_dummy;

t_ast	*new_ast_node(t_ast_buff *buff, t_dummy *node)
{
	t_ast	*new;

	new = &buff->start[buff->idx];
	buff->idx++;
	new->type = node->type;
	new->redir_fd = node->redir_fd_target;
	new->redir_file = node->redir_file;
	new->cmd_argv = node->cmd_argv;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void	free_ast(t_ast_buff *buff)
{
	free(buff->start);
}

void	print_token(void *content)
{
	char *token_map[253];
	token_map[CMD_EXTERN] = "CMD_EXTERN";
	token_map[CMD_BUILTIN] = "CMD_BUILTIN";
	token_map[WORD] = "WORD";
	token_map[PIPE] = "PIPE";
	token_map[AND] = "AND";
	token_map[OR] = "OR";
	token_map[REDIR_INFILE] = "REDIR_INFILE";
	token_map[REDIR_OUTFILE] = "REDIR_OUTFILE";
	token_map[REDIR_HEREDOC] = "REDIR_HEREDOC";
	token_map[REDIR_APPEND] = "REDIR_APPEND";
	token_map[LEFT_PARA] = "LEFT_PARA";
	token_map[RIGHT_PARA] = "RIGHT_PARA";
	t_ast *ast = (t_ast *)content;
	printf("Type: %s  ", token_map[ast->type]);
	if (ast->type == CMD_EXTERN || ast->type == CMD_BUILTIN)
		printf("CMD: %s", ast->cmd_argv[0]);
	if (ast->type == REDIR_OUTFILE || ast->type == REDIR_INFILE || ast->type == REDIR_APPEND)
	{
		printf("file: %s  ", ast->redir_file);
		printf("fd: %d", ast->redir_fd);
	}
	printf("\n");
}

void print_tree(t_ast *root, int depth) {
    if (root == NULL)
        return;

    // Print right subtree first
    print_tree(root->left, depth + 1);

    // Indentation
    for (int i = 0; i < depth; i++) {
        printf("    ");
	}

    // Print current node
	print_token(root);

    // Print left subtree
    print_tree(root->right, depth + 1);
}

int	execute(t_ast *node, bool in_pipeline, t_data *dat);

static int	exec_and(t_ast *node, bool in_pipeline, t_data *dat)
{
	int	status;

	status = execute(node->left, NO_PIPELINE, dat);
	if (status == 0)
		return (execute(node->right, NO_PIPELINE, dat));
	if (in_pipeline)
		exit (status);
	return (status);
}

static int	exec_or(t_ast *node, bool in_pipeline, t_data *dat)
{
	int	status;

	status = execute(node->left, NO_PIPELINE, dat);
	if (status != 0)
		return (execute(node->right, NO_PIPELINE, dat));
	if (in_pipeline)
		exit (status);
	return (status);
}

static void	close_pipefd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

//nothing protected here this also needs to be splitted into multi functions
static int	exec_pipe(t_ast *node, int in_pipeline, t_data *dat)
{
	pid_t	child1;
	pid_t	child2;
	int		status;
	int		fd[2];

	pipe(fd);
	child1 = fork();
	if (child1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_pipefd(fd);
		status = execute(node->left, IN_PIPELINE, dat);
		exit(status);
	}
	child2 = fork();
	if (child2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close_pipefd(fd);
		status = execute(node->right, IN_PIPELINE, dat);
		exit(status);
	}
	close_pipefd(fd);
	waitpid(child1, NULL, 0); 
	waitpid(child2, &status, 0); 
	if (in_pipeline)
		exit (WEXITSTATUS(status));
	return (WEXITSTATUS(status));
}

//currently just handles ouput redirections
//TODO: INPUT, HEREDOC, APPEND
//TODO: Protect dup and open
static void	redirect(t_ast *redirection)
{
	int	fd;

	while (redirection)
	{
		fd = open(redirection->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, redirection->redir_fd);
		close(fd);
		redirection = redirection->left;
	}
}

//TODO: make free and exit/ cleanup instead of just exit incase redirect() function or execve fails
static int	exec_extern(t_ast *node, bool in_pipeline, t_data *dat)
{
	//if we are inside pipeline, we dont need to fork since exec_pipe was ran before, which always forks
	pid_t	child;
	int		status;

	if (in_pipeline)
	{
		redirect(node->left);
		execve(node->cmd_argv[0], node->cmd_argv, dat->envp);
		exit(1); //free and exit though
	}
	//if not inside pipeline, we are in parent which we do not want to erase, hence we manually fork
	else
	{
		child = fork();
		if (child == 0)
		{
			redirect(node->left);
			execve(node->cmd_argv[0], node->cmd_argv, dat->envp);
			exit(1); //free and exit though
		}
		waitpid(child, &status, 0);
		return (WEXITSTATUS(status));
	}
}

static int	which_builtin(char **argv)
{
	(void)argv;
	write(STDOUT_FILENO, "This is the builtin\n", 20); 
	return (0);
}

typedef struct s_fd_backup
{
	int	stdin_cpy;
	int	stdout_cpy;
	int	stderr_cpy;
}		t_fd_backup;

//TODO: set error inside dat so we can later identify what went wrong (dup failure)
static int	save_std_fds(t_fd_backup *fds)
{
	fds->stdin_cpy = dup(STDIN_FILENO);
	fds->stdout_cpy = dup(STDOUT_FILENO);
	fds->stderr_cpy = dup(STDERR_FILENO);
	if (fds->stdin_cpy == -1 || fds->stdout_cpy == -1 || fds->stderr_cpy == -1)
		return (1);
	return (0);
}


//TODO: pass dat here and set error if dup2 failure
//so also protect for dup2 failure
static int	restore_std_fds(t_fd_backup *fds)
{
	dup2(fds->stdin_cpy, STDIN_FILENO);
	dup2(fds->stdout_cpy, STDOUT_FILENO);
	dup2(fds->stderr_cpy, STDERR_FILENO);
	close(fds->stdin_cpy);
	close(fds->stdout_cpy);
	close(fds->stderr_cpy);
	return (0);
}

//TODO: protections for redirect
static int	exec_builtin(t_ast *node, bool in_pipeline, t_data *dat)
{
	t_fd_backup	fds;
	int			status;

	//for builtin, if we are in the pipeline we need to exit after executing the command (we dont want the child to be running anything else other then the actual command)
	if (in_pipeline)
	{
		redirect(node->left);
		status = which_builtin(node->cmd_argv);
		free_ast(&dat->ast);
		exit(status);
	}
	//if we are in the parent process, we do not want to exit, since that would quit the shell all together, so just return to the calling function
	else
	{
		//note i think saving the fds is not save, if we backup e.g. stdout into say fd == 4, and user specified sth like echo hello 4>file, then later during redirect, fd 4 will be redirected to the file and upon restoring stdout, stdout will also point to file after (since fd4 now points to file and restore sets stdout to whatever fd4 points to). 
		//so during redirection, we should check if a redirection affects any of the backups we made, and incase it does, we should redo the backup
		//so pass backup fds into redirect:
		//redirect(node->left, fds);
		//inside redirect:
		//if (node-redir_fd is in backup_fds)
		//	new_backup = dup(backed_up_colliding_fd)
		//	close(backed_up_colliding_fd);
		if (node->left)
		{
			save_std_fds(&fds);
			redirect(node->left);
		}
		status = which_builtin(node->cmd_argv);
		if (node->left)
			restore_std_fds(&fds);
		return (status);
	}
}

int	execute(t_ast *node, bool in_pipeline, t_data *dat)
{
	if (node->type == AND)
		return (exec_and(node, in_pipeline, dat));
	else if (node->type == OR)
		return (exec_or(node, in_pipeline, dat));
	else if (node->type == PIPE)
		return (exec_pipe(node, in_pipeline, dat));
	else if (node->type == CMD_EXTERN) //note here i will just have a token for CMD not distinguishing between external or builtin there needs to be a function called is_builtin incase a command token node is read
		return (exec_extern(node, in_pipeline, dat));
	// else if (node->type == CMD && !is_bultin(node->cmd_argv[0])) //so sort of like this
	// 	return (exec_extern(node, in_pipeline, dat));
	else 
		return (exec_builtin(node, in_pipeline, dat));
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_dummy pipe_node = {
		.type = PIPE,
		.redir_file = NULL,
		.redir_fd_target = -1,
		.cmd_argv = NULL
	};
	t_dummy buitin_node = {
		.type = CMD_BUILTIN,
		.redir_file = NULL,
		.redir_fd_target = -1,
		.cmd_argv = (char *[]){"echo", "hello", NULL}
	};
	t_dummy extern_node = {
		.type = CMD_EXTERN,
		.redir_file = NULL,
		.redir_fd_target = -1,
		//.cmd_argv = (char *[]){"/nix/store/vzx1mi9c0xfadmsm9dhd83d005cb1qs9-coreutils-9.8/bin/cat", "infile", NULL}
		.cmd_argv = (char *[]){"/usr/bin/cat", NULL}
	};
	t_dummy left_redir1_node = {
		.type = REDIR_OUTFILE,
		.redir_file = "file",
		.redir_fd_target = 4,
		.cmd_argv = NULL 
	};
	t_dummy left_redir2_node = {
		.type = REDIR_OUTFILE,
		.redir_file = "file2",
		.redir_fd_target = STDOUT_FILENO,
		.cmd_argv = NULL 
	};
	t_dummy right_redir_node = {
		.type = REDIR_OUTFILE,
		.redir_file = "file3",
		.redir_fd_target = STDOUT_FILENO,
		.cmd_argv = NULL 
	};
	t_dummy and_node = {
		.type = AND,
		.redir_file = NULL,
		.redir_fd_target = -1,
		.cmd_argv = NULL 
	};
	t_dummy or_node = {
		.type = OR,
		.redir_file = NULL,
		.redir_fd_target = -1,
		.cmd_argv = NULL 
	};
	//init dummy data struct
	t_data dat;
	dat.envp = envp;

	//init the ast buffer (like the arena containing as many ast node slots as needed
	size_t nodes = 6;
	dat.ast = ast_init(nodes);

	//make some dummy nodes for testing
	t_ast	*root = new_ast_node(&dat.ast, &pipe_node);
	//t_ast	*root = new_ast_node(&dat.ast, &buitin_node);
	// t_ast	*root = new_ast_node(&dat.ast, &extern_node);
	// t_ast	*root = new_ast_node(&dat.ast, &or_node);
	t_ast	*left_cmd = new_ast_node(&dat.ast, &buitin_node);
	t_ast	*right_cmd = new_ast_node(&dat.ast, &extern_node);
	//t_ast	*left_redir1 = new_ast_node(&dat.ast, &left_redir1_node);
	// t_ast	*left_redir2 = new_ast_node(&dat.ast, &left_redir2_node);
	// t_ast	*right_redir = new_ast_node(&dat.ast, &right_redir_node);
	root->left = left_cmd;
	//root->left = left_redir1;
	root->right = right_cmd;
	// left_cmd->left = left_redir1;
	// left_redir1->left = left_redir2;
	// right_cmd->left = right_redir;

	//do execution of the dummy tree to test out execute() function
	// print_tree(dat.ast.start, 0);
	execute(dat.ast.start, NO_PIPELINE, &dat);
	//write(STDOUT_FILENO, "Backup should be in terminal\n", 29); 
	free_ast(&dat.ast);
}
