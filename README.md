# Learning-C

## References:

- https://www.youtube.com/watch?v=rJrd2QMVbGM
- https://www.boot.dev/courses/learn-memory-management-c

### Print formatting:

    %d  -> integer
    %f  -> float
    %c  -> char
    %s  -> string/char*
    %zu -> size_t

---

### Type sizes:

    char    -> 1 byte
    int     -> 4 bytes (for 32-bit int)
    float   -> 4 bytes
    double  -> 8 bytes

---

### Struct basic syntax:

```c
    struct Something {
        int number;
        char character;
        float floating;
    };

    struct Something DoSomething(int param) { Does Something }

    struct Something something_instance = {
        .number = 1,
        .character = 'c',
        .floating = 1.0,
    };

    struct Something another_something = {1, 'c', 1.0};

    // We can use typedef instead of struct Something everytime.
    typedef struct Something {
        ...
    } something_t;

    something_t another_another_something = {1, 'c', 1.0};
```

> [!Tip]
> Attribute order matters when constructing a struct in C.

> [!Note]
> When using char\* in a struct only 4-bits are allocated for the pointer address, while the string itself is stored somewhere else.

> [!Tip]
> A naming convention while working with typedef is **struct_name_t**
