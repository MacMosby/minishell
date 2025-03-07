# Minishell

*A minimal shell implementation in C.*

## Table of Contents

- [About the Project](#about-the-project)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Technologies Used](#technologies-used)
- [Acknowledgments](#acknowledgments)

---

## About the Project

Minishell is a project that involves creating a simple shell similar to Bash. The goal is to understand how shells work by implementing process management, redirections, pipes, and built-in commands.

## Features

- Displays a prompt and waits for user commands
- Supports command execution using PATH or absolute/relative paths
- Handles input/output redirection (`<`, `>`, `>>`, `<<`)
- Implements pipes (`|`)
- Supports environment variables (`$VAR_NAME`)
- Handles exit status `$?`
- Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)

## Installation

```sh
# Clone the repository
git clone https://github.com/MacMosby/minishell.git minishell
cd minishell

# Compile the project
make
```

## Usage

Run the shell:

```sh
./minishell
```

Exit the shell:

```sh
exit
```

## Built-in Commands

Minishell implements the following built-in commands:

- `echo` (supports `-n` option)
- `cd` (changes directory)
- `pwd` (prints the current directory)
- `export` (sets environment variables)
- `unset` (removes environment variables)
- `env` (prints environment variables)
- `exit` (exits the shell)

## Technologies Used

- **C** (standard libraries and system calls)
- **GNU Readline** (for input handling)

## Acknowledgments

This project is based on an assignment at 42 Berlin to deepen understanding of process management and shell behavior. If you have any questions, feel free to reach out!

---

Happy coding! 🚀

