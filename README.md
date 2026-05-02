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
    %p  -> pointer

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

---

### Pointers:

```c
struct *Struct;
Struct->x = 3;
// is just the same as
(*Struct).x;


int arr[3] = {1, 2, 3};
int val = arr[2];
// is the same as
int val = *(arr + 2);


// to reference a struct in the struct attributes you should forward declare it
typedef struct Node node_t;

typedef struct Node {
    int value;
    node_t *next;
} node_t;

// and it is actually preferred to be done in the following format
typedef struct Node node_t;

struct Node {
    int value;
    node_t *next;
};
```

> accessing the attributes of a pointer is done through the `S->attribute` operator, and has a work around using `(*S).attribute` too.

> Arrays decay into `int*` when passed as a function param, which makes it lose the `sizeof` accurate representation.
