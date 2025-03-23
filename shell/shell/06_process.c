//How shells start processes
//Now, we’re really at the heart of what a shell does. Starting processes is the main function of shells. So writing a shell means that you need to know exactly what’s going on with processes and how they start. That’s why I’m going to take us on a short diversion to discuss processes in Unix-like operating systems.

//There are only two ways of starting processes on Unix. The first one (which almost doesn’t count) is by being Init. You see, when a Unix computer boots, its kernel is loaded. Once it is loaded and initialized, the kernel starts only one process, which is called Init. This process runs for the entire length of time that the computer is on, and it manages loading up the rest of the processes that you need for your computer to be useful.

//Since most programs aren’t Init, that leaves only one practical way for processes to get started: the fork() system call. When this function is called, the operating system makes a duplicate of the process and starts them both running. The original process is called the “parent”, and the new one is called the “child”. fork() returns 0 to the child process, and it returns to the parent the process ID number (PID) of its child. In essence, this means that the only way for new processes is to start is by an existing one duplicating itself.

//This might sound like a problem. Typically, when you want to run a new process, you don’t just want another copy of the same program – you want to run a different program. That’s what the exec() system call is all about. It replaces the current running program with an entirely new one. This means that when you call exec, the operating system stops your process, loads up the new program, and starts that one in its place. A process never returns from an exec() call (unless there’s an error).

//With these two system calls, we have the building blocks for how most programs are run on Unix. First, an existing process forks itself into two separate ones. Then, the child uses exec() to replace itself with a new program. The parent process can continue doing other things, and it can even keep tabs on its children, using the system call wait().

//Phew! That’s a lot of information, but with all that background, the following code for launching a program will actually make sense:
#include "file.h"
int lsh_launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("lsh");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}
//Alright. This function takes the list of arguments that we created earlier. Then, it forks the process, and saves the return value. Once fork() returns, we actually have two processes running concurrently. The child process will take the first if condition (where pid == 0).

//In the child process, we want to run the command given by the user. So, we use one of the many variants of the exec system call, execvp. The different variants of exec do slightly different things. Some take a variable number of string arguments. Others take a list of strings. Still others let you specify the environment that the process runs with. This particular variant expects a program name and an array (also called a vector, hence the ‘v’) of string arguments (the first one has to be the program name). The ‘p’ means that instead of providing the full file path of the program to run, we’re going to give its name, and let the operating system search for the program in the path.

//If the exec command returns -1 (or actually, if it returns at all), we know there was an error. So, we use perror to print the system’s error message, along with our program name, so users know where the error came from. Then, we exit so that the shell can keep running.

//The second condition (pid < 0) checks whether fork() had an error. If so, we print it and keep going – there’s no handling that error beyond telling the user and letting them decide if they need to quit.

//The third condition means that fork() executed successfully. The parent process will land here. We know that the child is going to execute the process, so the parent needs to wait for the command to finish running. We use waitpid() to wait for the process’s state to change. Unfortunately, waitpid() has a lot of options (like exec()). Processes can change state in lots of ways, and not all of them mean that the process has ended. A process can either exit (normally, or with an error code), or it can be killed by a signal. So, we use the macros provided with waitpid() to wait until either the processes are exited or killed. Then, the function finally returns a 1, as a signal to the calling function that we should prompt for input again.