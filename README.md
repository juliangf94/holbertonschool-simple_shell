<<<<<<< HEAD
# holbertonschool-simple_shell

A simple UNIX command line interpreter written in C. This project is a functional recreation of the `sh` shell, designed to interface between the user and the Linux kernel.

## Description

This shell implements the fundamental **Read-Parse-Execute** loop. It captures user input, tokenizes it into arguments, resolves the command location through the system `PATH`, and manages process creation using `fork`, `execve`, and `wait`.

## Logic Flow

The following diagram illustrates the internal architecture of the shell, from the initial prompt to the execution of built-ins and external programs.

```mermaid
graph TD
    Start([Start]) --> Init[Initialize: last_status=0, counter=0]
    Init --> Ac["(void)ac;"]
    Ac --> Signal["Set Signal Handler: signal(SIGINT, handle_sigint)"]
    
    %% Main Loop
    Signal --> Loop{"While (1)"}
        Loop --> Inc[counter++]
        Inc --> Prompt[Call print_prompt]
        Prompt --> Read[/Input: getline/]

        %% EOF Handling
        Read --> EOFCheck{Is getline == -1?}
        EOFCheck -- Yes --> IsTTY{isatty?}
        IsTTY -- Yes --> PrintNL[Print \n]
        PrintNL --> Exit[/Free line & Exit last_status/]
        IsTTY -- No --> Exit
        
        %% handle_line Detailed Logic
        EOFCheck -- No --> Logic[Call handle_line]
        
        Logic --> Strip[Remove \n]
        Strip --> Token[Tokenize: strtok into argv]
        Token --> Builtin{handle_builtins?}
        
            %% Built-ins
            Builtin -- "exit/env" --> ExecBI[handle_builtins]
            ExecBI --> Update[Update last_status]
            
            %% Path Resolution
            Builtin -- "Not Found" --> Resolve[Call _resolve_path]
            Resolve --> PathCheck{Found?}
            
                %% Execution
                PathCheck -- Yes --> Exec[execute_command: fork/execve]
                Exec --> Update
                
                %% Error
                PathCheck -- No --> Error["fprintf stderr: not found"]
                Error --> Status127[last_status = 127]
                Status127 --> Loop

            Update --> Loop

    %% Style
    classDef start fill:#EB892D,stroke:#1D4ED8,stroke-width:2px,color:white;
    classDef process fill:#079C40,stroke:#1D4ED8,stroke-width:2px,color:white;
    classDef decision fill:#BE22DD,stroke:#1D4ED8,stroke-width:2px,color:white;
    classDef data fill:#8FABFA,stroke:#1D4ED8,stroke-width:2px,color:white;

    class Start start;
    class Init,Ac,Signal,Inc,Prompt,PrintNL,Update,Strip,Logic,Token,Resolve,ExecBI,Error,Exec,Status127 process;
    class Loop,EOFCheck,IsTTY,Builtin,PathCheck decision;
    class Read,Exit data;
```

## ✨ Features

- **Interactive & Non-Interactive Modes**: Operates via terminal or piped input (e.g., `echo "ls" | ./hsh`).
- **Command Execution**: Runs executable programs from the `PATH` or using absolute/relative paths.
- **Built-in Commands**: Includes native support for `exit` (terminates shell) and `env` (prints environment).
- **PATH Resolution**: Locates executables automatically in system directories.
- **Signal Handling**: Gracefully handles `Ctrl+C` (`SIGINT`) to prevent unexpected exits.
- **Error Handling**: Displays error messages similar to `/bin/sh` with command counters.
- **Robust Memory Management**: Zero memory leaks verified via Valgrind.

## 📁 Files

- `shell.c` - Core shell loop and command processing logic
- `shell.h` - Header file with function declarations and structures
- `exec_functions.c` - Handles command execution via `fork` and `execve`
- `builtins.c` - Implements built-in commands (`exit`, `env`)
- `path_functions.c` - PATH resolution and executable search
- `signals.c` - Custom signal handling logic
- `_strlen.c` - String length utility
- `_strcmp.c` - String comparison utility
- `_strdup.c` - String duplication utility

## 🛠️ Requirements & Compilation

- **OS**: Ubuntu 20.04 LTS.
- **Compiler**: `gcc`.
- **Standards**: Compiled using `-std=gnu89`.
- **Style**: Follows the Betty coding standard.

To compile the shell, use the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## 🚀 Usage
Interactive Mode:
```bash
./hsh
#cisboring$ ls
#cisboring$ exit
```
Non-Interactive Mode:
```bash
$ echo "ls" | ./hsh
```

## 👤 Authors

- Gwendal Boisard
- Julian Gonzalez
- Djibril Tamsir Niang

## 📄 License

Holberton School Project