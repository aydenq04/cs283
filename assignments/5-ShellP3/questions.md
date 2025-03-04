1. Your shell forks multiple child processes when executing piped commands. How does your implementation ensure that all child processes complete before the shell continues accepting user input? What would happen if you forgot to call waitpid() on all child processes?

My shell tracks the number of child processes created and then runs a for loop to wait for each child process to complete. Which allows each command to execute correctly and without issues. If I had forgot to call waitpid on a child process it's possible that best case the output of the command would print after the shell prompt reappears. But worst case it could attempt to pipe a command that hasn't completed into another command.

2. The dup2() function is used to redirect input and output file descriptors. Explain why it is necessary to close unused pipe ends after calling dup2(). What could go wrong if you leave pipes open?

If a pipe is not closed then it's possible that the pipe could not signal an EOF. This could cause the reading process to wait indefinitely for input or the writing may not consume data properly. Also each pipe consumes resources meaning leaving them will consume file descriptors indefinitely which could prevent creation of more pipes.

3. Your shell recognizes built-in commands (cd, exit, dragon). Unlike external commands, built-in commands do not require execvp(). Why is cd implemented as a built-in rather than an external command? What challenges would arise if cd were implemented as an external process?

The cd command is implemented as a built-in command due to the fact that external commands have a child process from their fork. Due to the commands being run in a child process if cd were to be run in a child process it would change the directory of the child. But the directory of the shell itself would remain unchanged. That would be the largest challenge with implemeting it as an external command. Any workaround would involve modifying the state of the shell manually after the command runs.

4. Currently, your shell supports a fixed number of piped commands (CMD_MAX). How would you modify your implementation to allow an arbitrary number of piped commands while still handling memory allocation efficiently? What trade-offs would you need to consider?

For each command line argument input I would parse the string and count the number of piped commands. Then with that number I could dynamically allocate space in a struct. I would have to change around some of the variables inside the structures so that I can use malloc to allocate their memory. I would also have to create a function for storing the list of commands inside of the struct and allocating the memory for it.