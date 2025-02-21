1. Can you think of why we use `fork/execvp` instead of just calling `execvp` directly? What value do you think the `fork` provides?

    > **Answer**:  When execp is called it creates a new process image which replaces the current process. Without using fork this would give the output but the shell would not continue to run. With fork it creates a child process to run the command from execp and continue the shell loop.

2. What happens if the fork() system call fails? How does your implementation handle this scenario?

    > **Answer**:  If the fork() system call fails then there is no child process created which would result in the command running but then the shell loop would end. My implementation handles this by checking if the pid value is equal to 0 otherwise the command is not run.

3. How does execvp() find the command to execute? What system environment variable plays a role in this process?

    > **Answer**:  When execvp() is run it searches through a list of directories which is specified in the system's PATH environment variable.

4. What is the purpose of calling wait() in the parent process after forking? What would happen if we didn’t call it?

    > **Answer**:  If we don't wait the fork() and our loop will run at the same time. Which would result in a new prompt appearing before the output of the command we input.

5. In the referenced demo code we used WEXITSTATUS(). What information does this provide, and why is it important?

    > **Answer**:  WEXITSTATUS provides the exit code of a child process after it terminates. It's important for determining if the command executed properly.

6. Describe how your implementation of build_cmd_buff() handles quoted arguments. Why is this necessary?

    > **Answer**:  It handles quoted arugments by taking the entirety of what is quoted and using that as one arugment. It's necessary for things like echo so you can print full sentences with spaces.

7. What changes did you make to your parsing logic compared to the previous assignment? Were there any unexpected challenges in refactoring your old code?

    > **Answer**:  I had to completely change my parsing logic since strtok wasn't working for what this assignment required. Now my parsing manually tokenizes the input command so it can parse be either quotes or spaces.

8. For this quesiton, you need to do some research on Linux signals. You can use [this google search](https://www.google.com/search?q=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&oq=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&gs_lcrp=EgZjaHJvbWUyBggAEEUYOdIBBzc2MGowajeoAgCwAgA&sourceid=chrome&ie=UTF-8) to get started.

- What is the purpose of signals in a Linux system, and how do they differ from other forms of interprocess communication (IPC)?

    > **Answer**:  Signals are a form of IPC that are used to notify processes of different events occurring within a system. They differ from other IPCs since they are limited to simple predefined actions.

- Find and describe three commonly used signals (e.g., SIGKILL, SIGTERM, SIGINT). What are their typical use cases?

    > **Answer**:  SIGKILL: this signal will immediately kill a process and cannot be caught, ignored, or handled by the process. typically used when a process is unresponsive or stuck. SIGTERM: default termination signal that can be stopped by the process and allows it to cleanup. typically used in scripts for a graceful shutdown SIGINT: sent when a user interrupts a process and is catchable. typically used for stopping a process manually.

- What happens when a process receives SIGSTOP? Can it be caught or ignored like SIGINT? Why or why not?

    > **Answer**:  When a process receives SIGSTOP it immediately pauses the process until it is explicitly resumed. It cannot be stopped since unlike SIGINT it is a non-maskable singal which means the kernel forces it to stop immediately.