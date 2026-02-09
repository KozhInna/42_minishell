# Minishell

A Unix shell implementation built from scratch in C, recreating core Bash functionality including pipes, redirections, and process management.

**Team project at Hive Helsinki (42 School)** – forked from the original team repository.

## Team Contributions

This was a pair programming project with clear role division.

### My Work (Execution Layer)

* **Command execution logic** – Designed and implemented the full execution flow, from single commands to complex pipelines
* **Built-in commands** – `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
* **Pipes** – Multi-command pipeline execution with correct file descriptor handling
* **Redirections** – Full support for `<`, `>`, `<<`, `>>`
* **Process management** – Child process creation, waiting for child processes and capturing exit codes, and graceful cleanup
* **Environment variables** – Variable storage, updates, and passing to child processes
* **Signal handling** – Interactive mode behavior (`ctrl-C`, `ctrl-D`, `ctrl-\`)
* **Exit status tracking (`$?`)** – Capture and expose the exit code of the last executed command

### My Partner's Work (Parsing Layer)

* Parsing and tokenization
* Quote handling (single and double quotes)
* Environment variable expansion (`$VAR`, `$?`)
* Input validation and syntax checks

## Implementation Strategy

I approached the execution design incrementally to control complexity:

1. **Single-command execution** – Implemented full support for redirections, here-docs, file I/O, error handling
2. **Pipeline execution** – Extended the same execution logic to support multiple commands connected by pipes

**Result:** A scalable execution architecture that remains understandable and reliably executes pipelines of 100+ commands within system limits, demonstrating robustness under stress testing.

This staged approach made debugging easier and prevented the system from becoming fragile as features were added.

## Requirements

- C compiler (gcc/clang)

## Installation
```bash
git clone https://github.com/KozhInna/42_minishell.git minishell
cd minishell
make
```

## Usage
```bash
./minishell
```

Then use it like a regular shell:
```bash
minishell$ echo "Hello World"
minishell$ ls -la | grep minishell
minishell$ cat < input.txt > output.txt
minishell$ exit
```

---

*42 School Team Project – 2025*  