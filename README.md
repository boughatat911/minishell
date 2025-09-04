# Minishell

A minimal implementation of a shell program written in C, developed as part of the 42 curriculum. This project recreates the basic functionality of bash, including command parsing, execution, built-in commands, and environment variable management.

## Authors

- **[ayameur](https://profile.intra.42.fr/users/ayameur)** - 42 Network
- **[nbougrin](https://profile.intra.42.fr/users/nbougrin)** - 42 Network

## Overview

Minishell is a command-line interpreter that provides a subset of bash functionality. It supports command execution, pipes, redirections, environment variables, and several built-in commands.

## Features

### Core Functionality
- **Command Line Interface**: Interactive shell with prompt (`minishell>`)
- **Command History**: Uses readline library for command history and line editing
- **Signal Handling**: Proper handling of SIGINT (Ctrl+C) and other signals
- **Memory Management**: Custom memory management system with leak detection

### Parsing & Tokenization
- **Lexical Analysis**: Tokenizes input into words, pipes, redirections, and operators
- **Syntax Error Detection**: Validates command syntax before execution
- **Quote Handling**: Supports single quotes (`'`) and double quotes (`"`)
- **Variable Expansion**: Expands environment variables within double quotes

### Redirections
- **Input Redirection**: `<` (redirect input from file)
- **Output Redirection**: `>` (redirect output to file)
- **Append Redirection**: `>>` (append output to file)
- **Here Document**: `<<` (heredoc) for multi-line input

### Pipes
- **Pipe Support**: `|` operator for chaining commands
- **Multiple Pipes**: Support for complex pipe chains
- **Process Management**: Proper fork/exec for each command in pipeline

### Built-in Commands
- **`echo`**: Print text with `-n` flag support
- **`cd`**: Change directory with `~` and `-` support
- **`pwd`**: Print current working directory
- **`export`**: Set environment variables with `+=` support
- **`unset`**: Remove environment variables
- **`env`**: Display environment variables
- **`exit`**: Exit the shell with optional status code

### Environment Management
- **Environment Variables**: Full support for environment variable manipulation
- **PATH Resolution**: Automatic command path resolution
- **Variable Expansion**: `$VAR` and `${VAR}` syntax support

## Project Structure

```
minishell/
├── minishell.h          # Main header file with all structures and prototypes
├── minishell.c          # Main program entry point
├── Makefile             # Build configuration
├── builtins/            # Built-in command implementations
│   ├── echo.c
│   ├── cd.c
│   ├── pwd.c
│   ├── export.c
│   ├── unset.c
│   ├── env.c
│   └── exit.c
├── parsing/             # Command parsing and tokenization
│   ├── token/           # Tokenization logic
│   ├── cmd/             # Command structure building
│   └── expand/          # Variable expansion
├── execution/           # Command execution and process management
│   ├── execution.c
│   ├── exec.c
│   └── builtins.c
└── tools/               # Utility functions and memory management
    ├── ft_malloc.c
    └── tools_*.c
```

## Data Structures

### Main Shell Structure (`t_shell`)
```c
typedef struct s_shell
{
    char        *content;
    t_token     *token;         // Tokenized input
    t_env       *env;           // Environment variables
    t_cmd       *cmd;           // Command list
    char        **path_splited; // PATH directories
    int         nbr_cmd;        // Number of commands
    pid_t       *pid;           // Process IDs
    int         exit_status;    // Last exit status
} t_shell;
```

### Token Structure (`t_token`)
```c
typedef struct s_token
{
    char            *content;
    t_token_type    type;       // WORD, PIPE, REDIR_IN, etc.
    int             ex_space_flag;
    int             index;
    struct s_token  *next;
} t_token;
```

### Command Structure (`t_cmd`)
```c
typedef struct s_cmd
{
    char        **cmd;           // Command and arguments
    int         in;              // Input file descriptor
    int         out;             // Output file descriptor
    int         pipe_fd[2];      // Pipe file descriptors
    int         is_builtin;      // Built-in command flag
    struct s_cmd *next;
} t_cmd;
```

## Installation & Usage

### Prerequisites
- GCC compiler
- GNU Readline library
- macOS or Linux system

### Building
```bash
git clone <repository-url>
cd minishell
make
```

### Running
```bash
./minishell
```

### Testing
```bash
# Basic commands
echo "Hello World"
ls -la
pwd

# Environment variables
export MY_VAR="test"
echo $MY_VAR

# Redirections
echo "test" > file.txt
cat < file.txt

# Pipes
ls -la | grep ".c" | wc -l

# Built-in commands
cd /tmp
pwd
export PATH=$PATH:/new/path
unset MY_VAR
env
exit
```

## Key Features Implementation

### Memory Management
- Custom `ft_malloc()` function with leak detection
- Address sanitizer enabled for debugging
- Proper cleanup on exit

### Signal Handling
- SIGINT handling for Ctrl+C
- Signal restoration in child processes
- Proper cleanup on signal reception

### Error Handling
- Comprehensive error checking
- Proper exit status codes
- User-friendly error messages

### Quote Handling
- Single quotes: literal interpretation
- Double quotes: variable expansion enabled
- Nested quote support

## Technical Details

### Compilation Flags
- `-Wall -Wextra -Werror`: Strict compilation warnings
- `-g3`: Debug information
- `-fsanitize=address`: Address sanitizer for memory debugging

### Dependencies
- **readline**: Command line editing and history
- **libc**: Standard C library functions

## Limitations

- No wildcard expansion (`*`, `?`)
- No command substitution (`` `command` ``)
- No arithmetic expansion (`$((expression))`)
- No job control (background processes)
- Limited error message formatting compared to bash

## Development Notes

This project was developed following 42's coding standards:
- No global variables
- No forbidden functions (system, fork, execve are allowed)
- Proper memory management
- Clean code structure
- Comprehensive error handling

## License

This project is part of the 42 curriculum and follows the school's guidelines and restrictions.

---

**Note**: This is an educational project created as part of the 42 curriculum. It's not intended for production use but serves as a comprehensive learning exercise in systems programming, shell implementation, and C programming.
