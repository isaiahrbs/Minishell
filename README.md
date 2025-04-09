# Minishell

A simplified Unix shell implementation built as part of the 42 school curriculum.  
Minishell supports basic shell functionalities including command execution, redirections, pipelines, environment variables, and more — all written in C, following strict 42 Norminette standards.

---

## 🛠 Features

- **Prompt & input parsing** (with quote and escape handling)
- **Command execution**
  - Builtins: `cd`, `echo`, `pwd`, `env`, `export`, `unset`, `exit`
  - External binaries using `PATH`
- **Redirections**
  - Input `<`, output `>`, append `>>`, and heredoc `<<`
- **Pipes** (`|`) with proper file descriptor handling
- **Environment variable expansion** (`$VAR`)
- **Signal handling** (`Ctrl+C`, `Ctrl+\`, etc.)
- **Exit status management**
- **Strict Norminette compliance**
- **No use of `for`, `switch`, or banned functions**

---

## 📁 Project Structure

```bash
.
├── src/              # Main source code
│   ├── lexer/        # Tokenization of input
│   ├── parser/       # Building command structures
│   ├── executor/     # Command execution and pipes
│   ├── builtins/     # Built-in command functions
│   ├── utils/        # Utility functions
│   └── main.c        # Entry point
├── include/          # Header files
├── Makefile          # Build system
└── README.md
```

---

## 🧠 How it Works

1. **Input Handling**: A prompt is displayed and user input is read using `readline`.
2. **Lexing**: The input is split into tokens while respecting quotes and special characters.
3. **Parsing**: Tokens are parsed into executable commands with proper structure.
4. **Execution**: Commands are executed, handling redirections, pipes, and environment.
5. **Cleanup**: Memory is freed and the shell waits for the next command.

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
> ls -la | grep minishell
> VAR=test ./script.sh
> cat << EOF
heredoc content
EOF
```

---

## 🧪 Testing

Use your own test scripts or command sequences. Some suggestions:
- Complex pipes and redirections
- Builtin behavior with edge cases
- Variable expansion inside quotes
- Heredocs with variable suppression (`<<` vs `<<'EOF'`)

---

## 👨‍💻 Authors

> This project was developed as part of the 42 school curriculum by:

- [Yokio9](https://github.com/Yokio9)  
- [isaiahrbs](https://github.com/isaiahrbs)

---
 
Do not use this for cheating in the 42 program.
