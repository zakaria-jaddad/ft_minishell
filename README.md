# Minishell

## 📖 Overview

**Minishell** is a simplified implementation of a Unix shell, developed as part of the **42 School curriculum**.  
It replicates core functionalities of `bash` while offering a controlled environment to explore **process management**, **command parsing**, **file descriptors**, and **signal handling** in C.

Our version achieved **full score** and supports **robust command execution**, including pipes, redirections, variable expansion, and built-in commands.

---

## ✨ Features

- **Command Parsing & Execution**
  - Executes both built-in and external commands.
  - Handles multiple arguments, quoting, and special characters.
- **Redirections**
  - Input redirection: `<`
  - Output redirection: `>`
  - Append redirection: `>>`
- **Pipes**
  - Supports multiple chained commands using `|`.
- **Environment Variable Expansion**
  - `$VAR` expansion based on current environment.
- **Built-in Commands**
  - `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Signal Handling**
  - `Ctrl + C` — Interrupt current command without exiting the shell.
  - `Ctrl + \` — Quit signal handling.
  - `Ctrl + D` — Exit shell gracefully.
- **Error Management**
  - Syntax checks for unclosed quotes, invalid redirections, etc.
  - Proper file descriptor cleanup to prevent leaks.

---

## 📦 Dependencies

- **Language:** C  
- **Compiler:** `cc`  
- **Flags:** `-Wall -Wextra -Werror -lreadline`  
- **Libraries:** [GNU Readline](https://tiswww.case.edu/php/chet/readline/rltop.html) for input handling.

---

## 📂 Project Structure

```
ft_minishell/
│
├── minishell.c                # Entry point
├── execution/                  # Command execution logic
├── includes/                   # Header files
│   └── parsing/
├── libft/                      # Custom C standard library functions
│   └── ft_fprintf/
├── parsing/                    # Parsing and tokenizing
│   ├── ast/                    # Abstract Syntax Tree
│   ├── env/                    # Environment variable handling
│   ├── expansion/              # Variable and wildcard expansion
│   │   └── wildcards/
│   ├── pre_ast/
│   ├── syntx_check/            # Syntax validation
│   └── tokenize/               # Token generation
├── Makefile
└── README.md
```

---

## ⚙️ Installation & Usage

### 1️⃣ Clone the repository
```bash
git clone https://github.com/zakaria-jaddad/ft_minishell.git
cd ft_minishell
```

### 2️⃣ Compile
```bash
make
```

### 3️⃣ Run
```bash
./minishell
```
You will see a **custom prompt** where you can type commands, e.g.:
```bash
ft_minishell$ echo "Hello World"
Hello World
```

---

## 🧠 Key Concepts Learned

- **Process Management**  
  - Using `fork()`, `execve()`, and `wait()` for command execution.
- **Pipes & File Descriptors**  
  - Redirecting input/output between processes.
- **Signals**  
  - Handling asynchronous events with `signal()` and `sigaction()`.
- **Parsing & Tokenization**  
  - Building a shell parser from scratch (tokens → AST → execution).
- **Memory Management**  
  - Avoiding leaks and ensuring safe cleanup.
- **Environment Handling**  
  - Modifying and expanding environment variables dynamically.

---

## 🏆 Authors
- **[Zakaria Jaddad](https://github.com/zakaria-jaddad)**
- **[Mouad Ait El Aouad](https://github.com/LawKmu/)**  

> This project is part of the **42 curriculum** and adheres to its coding and formatting standards.
