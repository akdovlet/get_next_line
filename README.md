# get_next_line

A 42 School project. Implementation of a function that reads one line at a time from a file descriptor.

---

## Goal

The C standard library offers no convenient way to read a file line by line without loading it entirely into memory. The goal of this project is to implement `get_next_line`, a function that can be called repeatedly on a file descriptor and returns one line per call — including the trailing newline when present — until the end of the file is reached.

The project also requires writing it without any forbidden functions, using only `read`, `malloc`, and `free`, and managing memory without leaks across calls.

---

## Files

| File | Description |
|---|---|
| `get_next_line.c` | Core logic: reading, extracting and cleaning the line |
| `get_next_line_utils.c` | Helper functions: `ak_strlen`, `ak_strchr`, `ak_strjoin` |
| `get_next_line.h` | Header for the standard version |
| `get_next_line_bonus.c` | Bonus version supporting multiple file descriptors simultaneously |
| `get_next_line_utils_bonus.c` | Helper functions for the bonus version |
| `get_next_line_bonus.h` | Header for the bonus version |

---

## How it works

A `static` buffer is declared inside `get_next_line`. Because it is static, it persists its value between calls, which is how the function remembers where it left off between calls.

Each call goes through three steps:

1. **Read into the buffer** (`read_to_newline`) — reads from the fd in chunks of `BUFFER_SIZE` bytes, accumulating data into a temporary string until a newline character is found or the fd is exhausted.
2. **Extract the line** (`extract_line`) — copies everything up to and including the first `'\n'` into a new heap-allocated string, which is returned to the caller.
3. **Clean the static buffer** (`clean_static`) — shifts the content of the buffer forward past the newline, so the leftover data (the start of the next line) is preserved for the next call.

The **bonus version** replaces the single static buffer with a 2D array indexed by file descriptor (`buffer[fd]`), allowing independent state to be maintained for up to `FD_MAX` file descriptors at the same time.

---

## Usage

### Compilation

There is no Makefile for this project — it is meant to be compiled directly into your own project. Add the source files and pass `BUFFER_SIZE` if you want to override the default:

```bash
# Standard version (single fd)
cc -Wall -Wextra -Werror -D BUFFER_SIZE=64 get_next_line.c get_next_line_utils.c

# Bonus version (multiple fds)
cc -Wall -Wextra -Werror -D BUFFER_SIZE=64 get_next_line_bonus.c get_next_line_utils_bonus.c
```

### Integration

Include the header and call the function in a loop:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Function signature

```c
char *get_next_line(int fd);
```

- Returns the next line from `fd`, newline included.
- Returns `NULL` when the file ends or on error.
- The returned string is heap-allocated — the caller is responsible for freeing it.

### BUFFER_SIZE

`BUFFER_SIZE` controls how many bytes are read from the fd in a single `read` call. It defaults to `1024` in the standard version and `42` in the bonus version. Larger values reduce the number of syscalls; smaller values use less stack space per call. Both extremes are handled correctly.

---

## Constraints

- No global variables.
- Static variables are allowed (one per function).
- No dynamic allocation of the buffer itself — the static buffer is a fixed-size array in static storage, not a heap allocation. This is a deliberate choice: if the caller stops reading before reaching EOF, there is no opportunity to free a heap-allocated buffer, which would cause a guaranteed memory leak. A static array requires no cleanup and carries no allocation that could be leaked.
- Only `read`, `malloc`, and `free` from the C standard library.
- No `lseek` or equivalent — the fd position must advance naturally.

---

## AI Disclosure

No AI tool was used during the development, implementation, or research of this project. AI assistance was used solely for the redaction of this README.
