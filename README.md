# Brainfuck Interpreter

A fast and efficient Brainfuck interpreter written in C.

## Overview

This is a feature-rich Brainfuck interpreter that supports:
- Executing Brainfuck code from files
- Direct execution of code via command line
- Error handling with meaningful messages
- Memory bounds checking
- Special flag for instantly displaying "I use Arch btw!"

## Installation

### Prerequisites

- GCC or another C compiler
- Make (optional, for easier compilation)

### Compiling

Clone the repository and compile the interpreter:

```bash
git clone https://github.com/yuvan0309/brainfuck-interpreter.git
cd brainfuck-interpreter
gcc -o brainfuk brainfuk.c
```

## Usage

The interpreter can be used in several ways:

### Execute a Brainfuck file

```bash
./brainfuk path/to/file.bf
```

### Execute Brainfuck code directly

```bash
./brainfuk -c "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++."
```

### Display "I use Arch btw!"

```bash
./brainfuk -d
```

### Show help

```bash
./brainfuk -h
# or
./brainfuk --help
```

## Included Example Files

- `hello_world.bf` - A classic "Hello World!" program
- `im_using_arch_btw.bf` - Prints "I'm using Arch btw!"
- `final_approach.bf` - Another program that prints "I use Arch btw!"

## Brainfuck Language Reference

Brainfuck consists of eight commands:
- `>` Increment the data pointer
- `<` Decrement the data pointer
- `+` Increment the value at the data pointer
- `-` Decrement the value at the data pointer
- `.` Output the value at the data pointer as an ASCII character
- `,` Accept one byte of input and store it at the data pointer
- `[` If the value at the data pointer is zero, jump to the matching `]`
- `]` If the value at the data pointer is non-zero, jump to the matching `[`

## Error Handling

The interpreter provides detailed error messages for common issues:
- Memory pointer out of bounds
- Unmatched brackets
- Loop stack overflow
- File read errors

## Git Configuration

### Recommended .gitignore

```
# Compiled binary
brainfuk
brainfuk_*

# Object files
*.o

# Editor files
.vscode/
.idea/
*.swp
*~

# OS-specific files
.DS_Store
Thumbs.db
```

### Commit Messages

When contributing to this project, please use the following format for commit messages:

```
[type]: Short description (max 50 chars)

Longer description (max 72 chars per line)
```

Where `type` is one of:
- `feat`: A new feature
- `fix`: A bug fix
- `docs`: Documentation changes
- `style`: Formatting, missing semicolons, etc; no code change
- `refactor`: Refactoring production code
- `test`: Adding tests, refactoring test; no production code change
- `chore`: Updating build tasks, package manager configs, etc; no production code change

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Thanks to Urban Müller for creating the Brainfuck language in 1993.
- I use Arch btw!
