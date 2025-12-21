# 🐚 holbertonschool-simple_shell

A simple UNIX command line interpreter written in C, implementing basic shell functionality.

## 📝 Description

This project recreates a minimal shell that reads user commands, parses them, and executes the corresponding programs. It supports basic features like command execution, PATH resolution, and built-in commands. The shell provides an interactive interface similar to `/bin/sh` with essential command-line functionality.

## ✨ Features

- **Command parsing and execution** - Tokenizes input and manages command arguments
- **PATH environment variable handling** - Locates executables in system PATH directories
- **Built-in commands** - Implements exit, env, and cd natively
- **Error handling and exit status management** - Returns appropriate exit codes
- **Support for absolute and relative paths** - Executes programs with full or partial paths
- **Interactive and non-interactive modes** - Works as both interactive shell and script processor

## 🔄 How It Works

```
┌─────────────────┐
│   Start Shell   │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│  Read Command   │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│  Parse Command  │
└────────┬────────┘
         │
         ▼
┌──────────────────────┐
│ Is Built-in Command? │
└─────┬──────────┬─────┘
      │ Yes      │ No
      ▼          ▼
 ┌────────┐  ┌──────────────┐
 │Execute │  │ Search PATH  │
 │Built-in│  └──────┬───────┘
 └────┬───┘         │
      │             ▼
      │        ┌──────────────┐
      │        │ Execute Prog │
      │        └──────┬───────┘
      │               │
      └───────┬───────┘
              │
              ▼
        ┌──────────────┐
        │Return Status │
        └──────┬───────┘
               │
               ▼
        ┌──────────────┐
        │  Exit? (y/n) │
        └─┬────────────┘
          │ No
          └─────────┐
                    └─→ Read Command
```

## 📦 Installation

```bash
gcc -Wall -Wextra -Werror -pedantic *.c -o hsh
```

Compilation flags enforce strict code standards and enable all warnings.

## 🚀 Usage

```bash
./hsh
```

Interactive mode reads commands from standard input until exit is called or EOF is reached.

## 📁 Files

- `main.c` - Program entry point and initialization
- `shell.c` - Core shell loop and command processing logic
- `execute.c` - Handles command execution via fork and execve
- `parse.c` - Tokenizes and parses user input into command arguments
- `builtin.c` - Implements built-in commands (exit, env, cd)
- `helpers.c` - Utility functions for string manipulation and PATH searching

## 👤 Authors

- Gwendal Boisard

## 📄 License

Holberton School Project

