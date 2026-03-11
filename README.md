*This project has been created as part of the 42 curriculum by masenche, algasnie.*

## Description
Minishell is a project that recreates a simple shell, a small version of Bash.
It includes redirections (input, output, heredoc), pipes, environment variables, signals and some of built-ins. 

## Instructions
### Compilation
To compile the mandatory part:
```make```

To clean all object files (.o):
```make clean```

To clean all object files and executables:
```make fclean```

### Execution
Launch the shell with:
```./minishell```

## How it works

Minishell works with a while(1) loop that reads the user input with the readline() function.

### 1. Initialization
At launch, minishell initializes its own environment by copying the env into a linked list so it can be easily modified later. This list contains structs s_env that separate the key from the value.

### 2. Lexing
When the user enters a command, the prompt is passed into a lexer. The lexer's job is to split this single string into a linked list of tokens. This list contains structs s_token that associate the token with a type (WORD, PIPE, INPUT, OUTPUT, HEREDOC). 

### 3. Parsing and Syntax Validation
The token list is then analyzed to check for syntax errors, such as a pipe at the beginning of a line, unclosed quotes, or a redirection operator without a following file name. If a syntax error is detected, the current prompt returns an error message, sets the exit status to 2. 

### 4. Expansion
If there are no syntax errors, minishell handles tokens containing '\$' symbol. It finds the value associated in the the environement and replace the key with it's value. If there is no value it simply leaves a blank.
The expansion method also handles the '$?', replacing its value by the exit status of the last executed command. 

After this expansion work, it remakes the token list to handle expansions that contain command prompt properly. It removes all the quotes at the end.

### 5. Command Building
The parser converts the token list into a linked list of s_cmd that contains all the neccessary information for the execution.
It contains the array of all command's arguments, the absolute path of the executable found into the env or written by the user.
It also contains, if present, the fd of open file / heredoc.

### 6. Execution
The execution part is separated into two parts. 
If there is a single command and this is a built-in, it is executed directly in the parent process.

Else, if there are multiple commands or this is not a built-in command, minishell use pipe() to create a communication channel between two fd. 
For each command a new child process is created for each command with fork().
In each child process, the dup2() is used to redirect the standard input/ouput into the right side of the pipe created. It allow to each child process to comminicate input/output between them.
After the dup2(), each child process replace its process by the target executable using the execve().

During this phases, the parent process waits all children with waitpid() and retain the return of the last process. 

## Resources
* Subject: 42 minishell
* Compare with bash shell
