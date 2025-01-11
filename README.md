# Base64 Decoding in C

This repository contains a C program that decodes Base64-encoded strings into their original ASCII format. The program demonstrates essential concepts in binary manipulation, string handling, and memory management in C. It accepts input via command-line arguments or standard input and outputs the decoded string.

## Features

- Decodes Base64 strings back into ASCII format.
- Accepts input from:
  - Command-line arguments
  - Standard input
- Maps Base64 characters to their binary representation using a predefined Base64 decoding table.
- Converts binary data into ASCII characters.
- Handles memory allocation and cleanup robustly.
- Includes a cross-platform implementation of `strcpy_s` for non-Windows systems.

## Use Cases

- Practice decoding Base64-encoded data in C.
- Understand how binary data is processed and transformed into characters.
- Learn techniques for dynamic memory management in C programs.
- Explore cross-platform development practices.

## How It Works

1. **Input Handling**:
   - Reads input as either a command-line argument or from standard input.
   - Dynamically allocates memory when using standard input.

2. **Base64 Decoding**:
   - Maps Base64 characters to 6-bit binary arrays using a predefined table.
   - Groups binary data into 8-bit chunks to reconstruct ASCII characters.

3. **Output**:
   - Prints the decoded ASCII string to standard output.

## Build Instructions

### Windows

1. Open Microsoft Visual Studio.
2. Create a new **Console Application** project:
   - Click **Create a new project**.
   - Select **Console App (C++)** (it works for C code as well).
   - Click **Next** and configure the project name and location.
3. Add the provided `.c` file to the project:
   - Right-click on the **Source Files** folder in Solution Explorer.
   - Select **Add** → **Existing Item...** and choose the `.c` file.
4. Set the project to compile as C:
   - Right-click on the project in Solution Explorer → **Properties**.
   - Navigate to **Configuration Properties** → **C/C++** → **Advanced**.
   - Set **Compile As** to **Compile as C Code (/TC)**.
5. Build the project:
   - Press `Ctrl + Shift + B` or select **Build** → **Build Solution**.
6. Run the program:
   - Press `F5` or select **Debug** → **Start Debugging**.

### Linux

1. Open a terminal.
2. Navigate to the directory containing the `.c` file:
   ```bash
   cd /path/to/your/project
   ```
3. Use `gcc` to compile the program:
   ```bash
   gcc -o base64_decoder main.c -lm
   ```
   - `-o base64_decoder`: Specifies the output binary name.
   - `-lm`: Links the math library (required for `pow()`).
4. Run the program:
   ```bash
   ./base64_decoder SGVsbG8=
   ```
   or
   ```bash
   echo SGVsbG8= | ./base64_decoder
   ```

## Example

### Input (Command-line argument)

```bash
./base64_decoder SGVsbG8gV29ybGQ=
```

### Output

```plaintext
Hello World
```

### Input (Standard input)

```bash
./base64_decoder
SGVsbG8gQmFzZTY0
```

### Output

```plaintext
Hello Base64
```

## Custom Implementation

- **Cross-platform `strcpy_s`**:
  - Ensures safe copying of strings.
  - Prevents buffer overflows for non-Windows platforms.

## Error Handling

The program includes comprehensive error handling:
- Detects and handles invalid input strings.
- Manages memory allocation errors gracefully.
- Ensures proper cleanup of dynamically allocated memory.

Feel free to clone, explore, and contribute to this repository! 