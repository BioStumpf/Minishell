*This project has been created as part of the 42 curriculum by knajmech, dstumpf.*

# Description
This project was a collaborative effort between Kian Najmechi (knajmech), and David Stumpf (dstumpf). It is a recreation of the Bash Terminal with a lot of the functionality included. Some behaviour deviates from the original bash and not everything is included (such as ';' or escape characters like /). But what you will find, is a terminal with builtins, expansion, signal handling, and parsing.

Due to the nature of including the bonus part of the project, we have included '&&' and '||' with paranthesis for priority (although the behaviour is recreated, we do not include a subshell). This means that we use an abstract syntax tree with recursive descent to go through each token, execute its step, and then move onto the next step. We prioritise pipes, forking for a write end and a write end. Then we can through the other steps, taking a look at the type of commands that need to be executed etc.

## Parsing, Heredocs, and Expansion

### Parsing

Our parsing is split into two main stages: tokenization and building the AST. The lexer walks through the raw input character by character, splitting it into tokens while keeping track of the quote state (single vs. double quotes behave differently, since single quotes block all expansion while double quotes still allow variable expansion to happen later). Redirections, pipes, and logical operators are all recognized at this stage and tagged with their own token types so the parser doesn't have to re-derive them.

After tokenization, tokens are grouped into compounds. Metacharacters like pipes, `&&`, `||`, parentheses, and redirections remain exactly the same, while word tokens are grouped into compound commands (commands meaning a group of words separated by metacharacters).

The compound list is then used to build an abstract syntax tree using recursive descent. Each grammar rule (command, pipeline, and/or expression, parenthesized group) maps to its own function, and the parser calls into itself for anything of higher precedence before combining the result into a node. Parentheses are handled by recursing back into the top level of the grammar, pipes bind more tightly than `&&` and `||`, and `&&`/`||` are left-associative, so we build the tree leaning left as we consume operators. Command nodes sit at the leaves, with their left children being essentially a list of redirections that will be traversed sequentially during execution.

If the parser hits anything it can't make sense of (unmatched quotes, a pipe with nothing on one side, a stray parenthesis), it throws a syntax error, and the whole line is discarded without attempting execution, in keeping with how we handle parsing errors elsewhere in the project.

### Heredocs

Heredocs are detected at the parsing stage. Once we hit a `<<` token, we read line by line from stdin until we see a line that matches the given delimiter exactly. If the delimiter was quoted in the original input, we skip expansion entirely and treat the body as a literal block. If it wasn't quoted, each line gets passed through the expansion logic during execution (described below).

We write the collected heredoc content into a temporary file. This file is opened with the `O_TMPFILE` flag, so it is never physically linked. The file descriptors and whether each heredoc requires expansion are saved since they are needed during expansion. After the entire input has been processed, all open heredoc FDs are closed collectively, both in the main process and in all child processes.

A Ctrl-C during heredoc input aborts the collection, discards whatever has already been typed, and returns control to the prompt rather than trying to execute a partial command.

### Expansion

Expansion of variables, the exit status (`$?`), and heredocs happens during execution when encountering the respective command node. Before executing the command itself, its arguments and redirections are scanned and expanded. This was necessary because Bash allows variables to be exported and expanded on the same line (`export var=hello && echo $var`).

## Signal Handling

Signals are handled in a unified manner across the parent process and all children. `SIGQUIT` is ignored entirely, while `SIGINT` is intercepted with a custom signal handler that sets the global return status to the signal's value. For external commands, `execve` will reset this behavior, causing descendants of our main process to be killed immediately.

Our execution logic, in combination with the `SA_RESTART` flag, ensures that the parent process always waits for all children, avoiding any zombie processes. Pressing Ctrl-C while inside the readline prompt simply causes readline to return an empty string, avoiding processing any content that has already been typed and triggering a new readline prompt.

## Execution

### Environment
The environment variable is saved internally inside our Minishell. It is saved using a hasmap that uses a version of djb2 by Daniel J. Bernstein. Within an array of 97 positions, we have our 'buckets'. The index to determine where a variable is placed is calculated using a hash key. To determine the hash key, we take the seed number 5381, this value is then updated by doing the following: at each nth position of the key array, we multiply the ascii value by 31 and then take the resulting number and multiply that by the seed number (which is still 5381 at the start). The number will change with each position we go through on the key. The number is also an unsigned int since if we overflow, it will be defined behaviour. Then we modulo by the number of buckets we have to determine the index which we will need to fill.

This env hash table can be updated, have buckets removed, and in the case of a collision, we then create a linked list. If we need to retrieve something from the hasmap, we brute force search the matching key if there were collisions. So in the case of a collision, the distance to find the matching value is still less resource intensive compared to if everything were to be in a linked list.

Note that our project did not include the functionality of adding to SHLLVL variable, nor did we add the functionality of the '_' variable. But we did include the setting and changing of the PWD variable as well as OLDPWD.

### Builtins
Due to the nature of how builtins are not necessarily running in child processes, we needed a safe way to handle the duping of variables in the case of chained redirections. This was handled recursively since once the command is executed (such as with echo calling the write function), we return back up the recursive stack calls to undo the dupes.

The builtins include the following:
* echo (with the -n flag functionality)
* export
* env
* unset
* pwd
* cd (including functionality for 'cd ~', 'cd -', and just 'cd')
* exit

Extra notes for the more important behaviours:
'export' calls on functions from our environment functions, and without arguments prints out the table.
'env' prints out just the table.
'unset' removes something from the table.
'pwd' calls on getcwd and prints that out onto the screen.
'cd' calls on chdir with a given path to change directory.
'exit' can take arguments to exit with certain exit codes or it will take the value of our global variable made for exit codes.

### Pipeline
Our pipeline uses a recursive descent structure that handles the different child processes to print out info out onto the screen. Every process that has been fed into a pipe, prioritises going down the left upon which when its job is done, it returns back up and then checks the right node to see if something is to be executed.

Note that in the case of a parsing error within any part of writing out the pipeline, our entire minishell returns because it is an invalid input.

In order to create the functionality of certain PATH behaviour, I did parse the PATH string and noted that '::' as well as : at either the start or the end represents check current directory. These are included as well.

Note that only the fds that are not stds are closed in the case of a child process before execve takes place. We decided that STD fds should be left open as a safer implementation of the shell.

# Instruction

As we have a make file, when you clone the repository, just type make to compile the files. When you do so, run the binary called minishell (with path included to be specific) and enjoy! You can experiment with the classic bash terminal commands.

Once done, you can exit using signals such as 'CTRL D', or by writing exit.

# Resources

https://ssojet.com/hashing/bernsteins-hash-djb2-in-c#bernsteins-hash-djb2-in-c   
https://www.gnu.org/software/bash/manual/bash.html
