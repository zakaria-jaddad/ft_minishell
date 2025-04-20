# minishell 

## 📚 Project Description

This project consists of creating a minimalistic shell that can:

- Parse and execute user commands
- Handle redirections (`<`, `>`, `>>`)
- Handle pipes (`|`)
- Support environment variable expansion (`$`)
- Manage built-in commands
- Implement basic signal handling (`ctrl + C`, `ctrl + \`, `ctrl + D`)
- Execute commands with correct file descriptor handling and child processes


## 📦 Dependencies

- Language: C
- Compilation: `cc` with flags `-Wall -Wextra -Werror -lreadline`


## 📁 Project Structure

```
ft_minishell/
│
├── minishell.c        # Main file
├── includes/          # Header files
├── execution/          # execution files
├── parcing/          # execution files
├── Makefile
└── README.md
```

## ⚙️ How to Use

### 1. Clone the repository

```bash
git clone https://github.com/zakaria-jaddad/ft_minishell.git
cd ft_minishell
```

### 2. Compile

```bash
make
```

### 3. Run

```bash
./minishell
```
You'll see a prompt where you can start typing commands



## 🧠 Concepts Learned
- Process creation with `fork`, `execve`, and `wait`


