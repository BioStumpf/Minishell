*This project has been created as part of the 42 curriculum by knajmech, dstumpf.*

# Description
This project was a collaborative effort between Kian Najmechi (knajmech), and David Stumpf (dstumpf). It is a recreation of the Bash Terminal with a lot of the functionality included. Some behaviour deviates from the original bash and not everything is included (such as ';' or escape characters like /). But what you will find, is a terminal with builtins, expansion, signal handling, and parsing.

Due to the nature of including the bonus part of the project, we have included '&&' and '||' with paranthesis for priority (although the behaviour is recreated, we do not include a subshell). This means that we use an abstract syntax tree with recursive descent to go through each token, execute its step, and then move onto the next step. We prioritise pipes, forking for a write end and a write end. Then we can through the other steps, taking a look at the type of commands that need to be executed etc.

### Parsing

## Parsing

Our parsing is split into two main stages: tokenization and building the AST. The lexer walks through the raw input character by character, splitting it into tokens while keeping track of quote state (single vs double quotes behave differently, since single quotes block all expansion while double quotes still allow variable expansion to happen later). Redirections, pipes, and the logical operators are all recognised at this stage and tagged with their own token types so the parser doesn't have to re-derive them.

Once we have a token stream, we build an abstract syntax tree using recursive descent. Each grammar rule (command, pipeline, and/or expression, parenthesised group) maps to its own function, and the parser calls into itself for anything of lower precedence before combining the result into a node. This gave us a clean way to encode precedence without having to write a separate precedence table: parentheses are handled by recursing back into the top level of the grammar, pipes bind tighter than '&&' and '||', and '&&'/'||' are left-associative so we build the tree leaning left as we consume operators.

Every node in the tree carries a type (command, pipe, and, or, subshell) along with left and right children where relevant, so a command sits at a leaf and everything above it is control flow. Execution later just walks this same tree, which is why the pipeline and the logical operators share so much of the same traversal logic.

Expansion of variables, exit status ('$?'), and tilde happens after the tree is built rather than during tokenization, since we need the quote context preserved per-token to decide what should and shouldn't be expanded. This also let us keep the parser itself fairly dumb about the meaning of the words it's grouping, it only cares about structure.

If the parser hits anything it can't make sense of (unmatched quotes, a pipe with nothing on one side, a stray parenthesis), it throws a syntax error and the whole line is discarded without attempting execution, in keeping with how we handle parsing errors elsewhere in the project.

Heredocs

Heredocs are detected at the parsing stage but resolved separately from the rest of the tree, since they need to consume input before execution ever starts. Once we hit a '<<' token, we read line by line from stdin until we see a line that matches the given delimiter exactly. If the delimiter was quoted in the original input, we skip expansion entirely and treat the body as a literal block; if it wasn't quoted, each line gets passed through the same expansion logic as everything else before being written out.

We write the collected heredoc content into a pipe rather than a temp file, so the reading end can be handed directly to the command as its stdin once execution starts. This avoids leaving stray files around and keeps cleanup simpler.

Because heredoc collection happens before we fork anything, it also needs to be interruptible on its own. A Ctrl-C during heredoc input aborts the collection, discards whatever was already been typed, and returns control back to the prompt rather than trying to execute a partial command.

### Signal Handling

We handle signals differently depending on whether we're sitting at the prompt, waiting on a heredoc, or waiting on a child process, since bash itself behaves differently in each of those states and we wanted to stay close to that.

At the prompt, Ctrl-C (SIGINT) doesn't kill the shell. It prints a newline, discards whatever's currently on the input line, and redraws the prompt as if nothing happened. Ctrl-D (EOF) at an empty prompt line exits the shell the same way calling 'exit' with no arguments would, but if there's already text typed on the line, Ctrl-D is ignored, matching bash's behaviour of only exiting on EOF when the line is empty.

While a child process is running (a builtin isn't run in a child, so this only really applies to piped/forked commands), we set SIGINT and SIGQUIT back to their default dispositions in the child before execve, so the child can be interrupted normally, while the parent shell itself ignores those signals and just waits on the child. Once the child dies from a signal, we make sure the reported exit status reflects that (128 + signal number), same as bash does.

During heredoc collection, SIGINT is handled separately again since we're not in a child process and not at the main prompt either, so it needed its own handler to break out of the read loop cleanly and set the exit status to 130 without leaving a half-built heredoc pipe behind.

Because signal handlers can only safely touch a very limited set of operations, we rely on a single global variable to record which signal was caught, and the actual handling logic (reprinting the prompt, adjusting exit status, breaking a read loop) happens outside the handler itself once control returns to the main loop.

## Execution

### Environment
The environment variable is saved internally inside our Minishell. It is saved using a hasmap that uses a version of djb2 by Daniel J. Bernstein. Within an array of 97 buckets, we have our buckets. The index to determine where a variable is placed is calculated using a hash key. To determine the hash key, we take the seed number 5381. This value is then updated by doing the following. At each nth position of the key array, we multiply the ascii value by 31 and then take the number and multiply that by the seed number (which is still 5381 at the start). The number will change with each position we go through on the key. The number is also an unsigned int since if we overflow, it will be defined behaviour. Then we modulo by the number of buckets we have to determine the index which we will need to fill.

This env hash table can be updated, have buckets removed, and in the case of a collision, we then create a linked list which is brute forced to find the matching key variable. So in the case of a collision, the distance to find the matching value is still less resource intensive compared to if everything were to be in a linked list.

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
