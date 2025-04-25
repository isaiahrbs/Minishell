# Minishell

A simplified Unix shell implementation built as part of the 42 school curriculum.  
Minishell supports basic shell functionalities including command execution, redirections, pipelines, environment variables, and more — all written in C, following strict 42 Norminette standards.

---

## 🛠 **Key Features**  

### 📜 **Commands Implemented**  
| **Category**       | **Implemented**                                                                 |
|--------------------|---------------------------------------------------------------------------------|
| **Builtins**       | `cd`, `echo -n`, `env`, `export`, `pwd`, `unset`, `exit` (with status codes)   |
| **Redirections**   | `<`, `>`, `>>`, **heredoc** (`<<`) with variable expansion suppression         |
| **Pipes**          | `|` (multi-pipe support)                                                       |
| **Variables**      | `$VAR`, `$?` (exit status), `SHLVL` (shell level tracking)                     |
| **Quotes**         | Full handling of `' '`, `" "`, nested quotes, and edge cases (`"''"`, `'""'`) |
| **Signals**        | `Ctrl+C` (SIGINT), `Ctrl+\` (SIGQUIT), `Ctrl+D` (EOF)                         |

---

## 📁 Project Structure

```bash
.
├── src/              # Main source code
│   ├── lexing/       # Tokenization of input
│   ├── parser/       # Building command structures
│   ├── executing/    # Command execution and pipes
│   ├── builtins/     # Built-in command functions
│   ├── functions/    # Utility functions
│   ├── cleaner/      # Setup the environment
│   ├── inc/          # Header files
│   └── signals/      # Handles signals
├── Makefile          # Build system
├── Main.c            # Entry point
└── README.md
```

---

## 🧠 **How It Works**  

1. **Input**: Displays a prompt and reads user input using `readline` (supports history navigation).  
2. **Lexing**: Splits input into tokens while handling:  
   - Quotes (`'...'`, `"..."`) and escapes (`\`).  
   - **Environment variables** (`$VAR`).  
   - **Metacharacters** (`|`, `>`, `<`, etc.).  
3. **Parsing**:  
   - **Creates a token list** from lexed input.  
   - **Merges tokens into commands** by splitting on metacharacters (e.g., `ls -l | grep test` → 2 commands).  
   - Builds an executable structure (AST) with redirections/pipes.  
4. **Execution**:  
   - Runs builtins directly (e.g., `cd`, `export`).  
   - Executes external binaries via `PATH` (e.g., `/bin/ls`).  
   - Handles pipes/redirections with `dup2` and `fork`.  
5. **Cleanup**: Frees memory, resets file descriptors, waits for next input.  

---

## 🚫 Not Implemented

- Logical operators (`||`, `&&`)
- Job control (`fg`, `bg`, etc.)
- File descriptor aggregation (`2>&1`, etc.)

---

## 📦 Compilation

```bash
make
```

To clean build artifacts:

```bash
make clean      # removes object files  
make fclean     # removes object files and binary  
make re         # rebuilds everything
```

---

## ▶️ Usage

```bash
./minishell
```

Once launched, you can start typing commands like:

```bash
> echo Hello World
> ls -la | grep Minishell
> export var=test
> cat << EOF
heredoc content
EOF
```

## 👨‍💻 Authors

> This project was developed as part of the 42 school curriculum by:

- [Yokio9](https://github.com/Yokio9)  
- [isaiahrbs](https://github.com/isaiahrbs)

---
 
Do not use this for cheating in the 42 program.
