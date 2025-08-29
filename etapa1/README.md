# Lexical Analyzer (Etapa 1) - Compiler Project

A lexical analyzer (scanner) for a Portuguese-like programming language, built using Flex and C. This is the first stage of a compiler implementation that tokenizes source code and manages a symbol table.

## Table of Contents
- [Overview](#overview)
- [Language Features](#language-features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Building the Project](#building-the-project)
- [Running the Scanner](#running-the-scanner)
- [Input Format](#input-format)
- [Output Format](#output-format)
- [Project Structure](#project-structure)
- [Example Usage](#example-usage)
- [Troubleshooting](#troubleshooting)

## Overview

This project implements a lexical analyzer that processes source code written in a custom programming language with Portuguese keywords. The scanner identifies tokens such as keywords, identifiers, literals, operators, and comments, storing relevant symbols in a hash table for later compiler stages.

## Language Features

### Keywords
- `cara` - character type
- `inte` - integer type  
- `real` - real/float type
- `se` - if statement
- `entaum` - then
- `senaum` - else
- `enquanto` - while loop
- `entrada` - input operation
- `escreva` - output/write operation
- `retorne` - return statement

### Literals
- **Integers**: `42`, `123`, `0`
- **Floats**: `3.14`, `2.5`, `0.1`
- **Characters**: `'a'`, 'x'`, `'1'`
- **Strings**: `"Hello World"`, `"test string"`

### Operators
- Arithmetic: `+`, `-`, `*`, `/`
- Comparison: `<`, `>`, `<=`, `>=`, `==`, `!=`
- Assignment: `=`
- Logical: `&`, `|`, `~`

### Comments
- Single-line: `// comment text`
- Multi-line: `/// comment text \\\\\\`

### Other Tokens
- Identifiers: `variable_name`, `function.name`, `array_index`
- Punctuation: `(`, `)`, `{`, `}`, `[`, `]`, `;`

## Prerequisites

Before building and running the project, ensure you have:

- **Flex** (Fast Lexical Analyzer Generator)
- **GCC** (GNU Compiler Collection)
- **Make** utility
- Unix-like environment (Linux, macOS, WSL)

## Installation

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install flex gcc make
```

### macOS
```bash
# Using Homebrew
brew install flex gcc make
```

### CentOS/RHEL/Fedora
```bash
# CentOS/RHEL
sudo yum install flex gcc make

# Fedora
sudo dnf install flex gcc make
```

## Building the Project

1. **Clone or navigate to the project directory:**
```bash
cd etapa1
```

2. **Build using the provided Makefile:**
```bash
make
```

This command will:
- Generate `lex.yy.c` from `scanner.l` using Flex
- Compile all source files with GCC
- Create the executable `etapa1`

3. **Clean build files (optional):**
```bash
make clean
```

## Running the Scanner

### Basic Usage
```bash
./etapa1 <input_file>
```

### Example
```bash
./etapa1 input.txt
```

### Command Line Arguments
- `input_file`: Path to the source code file to be analyzed

## Input Format

Create text files with code written in the supported language syntax:

```text
inte contador = 0;
real pi = 3.14;
cara letra = 'A';

se contador <= 10 entaum
    escreva "Contador pequeno";
senaum
    escreva "Contador grande";

enquanto contador > 0
    contador = contador - 1;

retorne contador;
```

## Output Format

The scanner produces:

1. **Token Recognition Messages**: Shows each token found with its type
```
Achei token 257
Achei token 280
Achei token 61
...
```

2. **Line Count**: Total number of lines processed
```
Main done, file has 12 lines
```

3. **Symbol Table**: Hash table contents showing stored identifiers and literals
```
Table[45] = contador
Table[123] = 3.14
Table[78] = 'A'
...
```

## Project Structure

```
etapa1/
├── scanner.l          # Flex specification file (lexical rules)
├── tokens.h           # Token definitions and constants
├── hash.h             # Hash table header file
├── hash.c             # Hash table implementation
├── main.c             # Main program entry point
├── Makefile           # Build configuration
├── input.txt          # Sample input file
├── lex.yy.c           # Generated lexer (auto-generated)
└── etapa1             # Compiled executable (auto-generated)
```

### Key Components

- **scanner.l**: Defines lexical patterns and actions using Flex syntax
- **hash.h/hash.c**: Implements symbol table using hash table data structure
- **tokens.h**: Defines token constants and types
- **main.c**: Main program loop that processes tokens and displays results

## Example Usage

### Sample Input File (`test.txt`)
```text
inte x = 42;
real y = 3.14;
cara c = 'a';

/// This is a multi-line comment
/// with multiple lines
\\\\\\\

se x >= 10 entaum
    escreva "Number is large";
senaum
    escreva "Number is small";

enquanto x > 0
    x = x - 1;
    
// Single line comment
retorne x;
```

### Running the Scanner
```bash
./etapa1 test.txt
```

### Expected Output
```
Achei token 257
Achei token 280
Achei token 61
Achei token 281
...
Main done, file has 15 lines
Table[34] = x
Table[67] = 42
Table[123] = y
Table[89] = 3.14
...
```

## Troubleshooting

### Common Issues

**1. "flex: command not found"**
```bash
# Install flex
sudo apt-get install flex  # Ubuntu/Debian
brew install flex           # macOS
```

**2. "gcc: command not found"**
```bash
# Install GCC
sudo apt-get install gcc    # Ubuntu/Debian
brew install gcc            # macOS
```

**3. "Permission denied" when running executable**
```bash
# Make executable
chmod +x etapa1
./etapa1 input.txt
```

**4. "No such file or directory" for input file**
```bash
# Check if file exists
ls -la input.txt
# Or provide full path
./etapa1 /path/to/your/input.txt
```

**5. Build errors**
```bash
# Clean and rebuild
make clean
make
```

### Debug Mode

To see more detailed information during execution, you can modify the source code or add debug prints. The current implementation shows token numbers rather than descriptive names.

## Future Development

This lexical analyzer serves as the foundation for subsequent compiler stages:
- **Etapa 2**: Syntax Analysis (Parser)
- **Etapa 3**: Semantic Analysis
- **Etapa 4**: Code Generation

## Contributing

When extending this project:
1. Follow the existing code style
2. Update token definitions in `tokens.h`
3. Add corresponding patterns in `scanner.l`
4. Test with various input files
5. Update this README with new features

## License

This project was developed as part of a compiler course assignment. Refer to your institution's academic policies regarding code sharing and collaboration.
