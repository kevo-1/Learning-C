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

> Attribute order matters when constructing a **struct** in C.

> When using `char*` in a struct only 4-bits are allocated for the pointer address, while the string itself is stored somewhere else.

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

---

### Enums:

```c
typedef enum color {
    RED,
    BLUE,
    GREEN,
} color_t;

typedef enum color {
    RED = 200,
    BLUE,   //201
    GREEN,  //202
} color_t;
```

> By default enums are given number values by their order, but you can override it.

> using `sizeof` on enums usually returns the size of `int`, but if the value of the enum is greater than `int` it takes the next bigger datatype until it reaches the `int64` size.

---

### Unions:

It holds one and only one of it's attributes but can't hold the other, using the same memory to hold either of the elements.

```c
// Can either be age or name but not both at the same time.
typedef union AgeOrName {
    int age;
    char* name;
} age_or_name_t;

typedef union Pixels {
    struct {
        uint8_t R;
        uint8_t G;
        uint8_t B;
        uint8_t A;
    } colors_t;

    uint32_t rgba; // can access each of them without sacrificing memory
};
```

```
Memory Layout
            ┌──────────┬──────────┬──────────┬──────────┐
  struct  → │    R     │    G     │    B     │    A     │
            ├──────────┴──────────┴──────────┴──────────┤
uint32_t  → │               rgba (32-bit)               │
            └───────────────────────────────────────────┘
```

> a union takes the size of the largest attribute in it.

> a good convention to keep in mind is that you can use helper attributes in a union to access other components.

---

# Stack & Heap:

#### Stack:

A LIFO data structure used in memory layout.

```c
/* Reserves space in the stack by first moving the stack pointer to reserve space
for the function's return address, parameters, function body, and return type.
 After the function's body is done the stack pointer pops the function's reserved memory
 and returns the stack pointer to it's position before the function call.
*/
void function(int param1) {
    int num = 0;
    char str[8];
    return;
}
```

> **Tail call optimization** is when a compiler converts a recursive function to a loop to use the same current stack frame instead of allocating a new one, and it is triggered when the return statement of the recursive function only calls the function again without applying any operations to the result.

##### Examples:

```c
int fibo(int n, int prev1 = 0, int prev2 = 1) {
    if(n == 0) return prev1;
    if(n == 1) return prev2;
    return fibo(n-1, prev2, prev1+prev2);
}

int factorial(int n , int curr = 1) {
    if(n == 0) return curr;
    return factorial(n-1, curr*n);
}
```
