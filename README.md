# 🖥️ Minishell

> Forked from the original 42 Berlin project repository (team of two)

A custom Unix shell implemented in C, inspired by bash.

This project focuses on understanding how command-line interpreters work internally, including process management, command execution, and inter-process communication.

---

## 🧑‍💻 My Contributions

This project was developed in a team of two.

* My partner implemented the **command parser**
* I implemented the **execution layer and core shell behavior**

### Core Responsibilities

* Designed and implemented the command execution pipeline
* Managed process creation using `fork`, `execve`, and `wait`
* Implemented support for pipes (`|`) and input/output redirections (`<`, `>`, `>>`)
* Built environment variable handling (`env`, `export`, `unset`)
* Implemented built-in commands (e.g. `cd`, `pwd`, `echo`, `exit`)
* Handled signal management (`Ctrl+C`, `Ctrl+D`, etc.)
* Ensured proper memory management and error handling

---

## ⚙️ Features

* Execution of system commands
* Support for pipelines and redirections
* Environment variable expansion
* Built-in shell commands
* Signal handling for interactive use
* Error handling for invalid input and edge cases

---

## 🧠 How It Works

The shell operates in three main stages:

1. **Parsing** *(implemented by my partner)*

   * Transforms user input into a structured representation of commands

2. **Execution Pipeline** *(my responsibility)*

   * Creates processes using `fork`
   * Connects them using pipes
   * Executes commands using `execve`

3. **Process Coordination**

   * Waits for child processes
   * Handles exit statuses
   * Maintains shell state across executions

---

## 🛠️ Tech Stack

* C
* Unix system calls (`fork`, `execve`, `pipe`, `dup2`, `wait`)
* Standard C library

---

## 🚀 Getting Started

### Compile

```bash
make
```

### Run

```bash
./minishell
```

---

## 🧪 What I Learned

* How Unix processes and shells work internally
* Managing multiple processes and inter-process communication
* Handling edge cases in command execution
* Writing robust, low-level C code with proper memory management
* Designing systems that separate parsing from execution

---

## 📌 Notes

This project was built as part of the 42 Berlin curriculum.
