1. In this assignment I suggested you use `fgets()` to get user input in the main while loop. Why is `fgets()` a good choice for this application?

    > **Answer**:  The reason fgets() is a good choice for this application is because fgets() will always read a full line including whitespace. This is good for an assignment like this since the commands a user can input can include a lot of whitespace or no whitespace. Which fgets() can handle either way. It can also detect EOF by returning NULL and not causing errors.

2. You needed to use `malloc()` to allocte memory for `cmd_buff` in `dsh_cli.c`. Can you explain why you needed to do that, instead of allocating a fixed-size array?

    > **Answer**:  Allocating memory using malloc has a few benefits. First when using malloc it allocates on the heap instead of the stack which avoids the possiblity of stack overflow. It also allows the memory to be accessed outside of this function in other function calls.


3. In `dshlib.c`, the function `build_cmd_list(`)` must trim leading and trailing spaces from each command before storing it. Why is this necessary? If we didn't trim spaces, what kind of issues might arise when executing commands in our shell?

    > **Answer**:  The build_cmd_list() function tokenizes each command through the whitespace separating the exe from the arguments. If we did not trim the trailing and leading whitespace it could interfere with the final results of our clist. Which would mess up the output.

4. For this question you need to do some research on STDIN, STDOUT, and STDERR in Linux. We've learned this week that shells are "robust brokers of input and output". Google _"linux shell stdin stdout stderr explained"_ to get started.

- One topic you should have found information on is "redirection". Please provide at least 3 redirection examples that we should implement in our custom shell, and explain what challenges we might have implementing them.

    > **Answer**:  command > file redirects stdout to file. command < file redirects stdin from file. command 2> file redirects stderr to file. Each of these have their own challenges. For the stdout commmands we would have to ensure the file exists and has write permissions. For the stdin commands we would have to make sure the file exists and be able to handle multiple redirections in one command.

- You should have also learned about "pipes". Redirection and piping both involve controlling input and output in the shell, but they serve different purposes. Explain the key differences between redirection and piping.

    > **Answer**:  Redirection will redirect stdin or stdout into/from a file for executing commands. Piping will redirect the stdout of one command directly into the stdin of another command.

- STDERR is often used for error messages, while STDOUT is for regular output. Why is it important to keep these separate in a shell?

    > **Answer**:  Having stderr and stdout be separate prevents mixing up errors from normal output. Also when it comes to redirecting having them be seperate means that you can redirect normal output to one file and errors to a different file. Helping with debugging.

- How should our custom shell handle errors from commands that fail? Consider cases where a command outputs both STDOUT and STDERR. Should we provide a way to merge them, and if so, how?

    > **Answer**:  Our shell to handle errors in a way that is informative to the user. In a case where a command has both STDOUT and STDERR we should make sure that the error and stdout are clearly defined from each other. I do not think they should be merged since that would prevent them from being clearly defined.