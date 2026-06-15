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

### Stack & Heap:

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

> Use **malloc** for allocating memory in the heap and after getting done with that memory use **free** so that you don't run out of memory.

> **Big Endian & Little Endian**, when storing addresses there is 2 different philosophies to doing so, **Big Endian** stores the `most` significant byte at the start while **Little Endian** stores the `least` significant byte first.
> Note: **Big Endian** is mostly used for `networking(TCP/IP)`, while **Little Endian** is mostly used in `intel x86/AMD CPUs, and modern CPUs` too.

---

### Advanced pointers:

##### Example to understand pointer to pointer:

```c
int v1 = 1; int v2 = 2; int cp = 0;

int *ptr = &v1; int **ptr_ptr = &ptr;

cp = **ptr_ptr; // cp = 1

*ptr_ptr = &v2;
cp = **ptr_ptr //cp = 2
```

##### Memory representation

```
v1          0x04    1
v2          0x08    2
cp          0x12    2

ptr         0x20    0x08
ptr_ptr     0x028   0x20
```

#### Void Pointers

They are generally used to store any kind of value in memory without worrying much about the data type, and to use the value in that memory place you would first need to cast it into the data type required.

```C
int num = 1;
void *ptr = &num;
printf("%d", *(int*)ptr); // 1
```

---

### Stack Data Structure:

```c
typedef struct Stack {
    size_t count;       // number of elements
    size_t capacity;    // max number of elements before resizing.
    void **data;        // void ** so that we can store any data type in an array
} stack_t
```

> we can use `realloc` to reallocate a chunk of memory with a new size, with a worst complexity of $O(N)$.

> it is very easy to shoot yourself in the foot while working with void pointers, as you can push an int then an int pointer in the same stack, so take care of this point.

---

### Objects in C:

[header file](Sneklang/snekobject.h)
[C file](Sneklang/snekobject.c)

> `calloc(size_t num, size_t size)` is used for continous allocation and initializes all elements with `0`

---

### Garabage collection:

#### RefCounting (reference counting):

It is mainly adding a field to count how many times the variable is referenced, incrementing whenver a new object references it, and decrements whenver the object is freed.

> It can't track cycles, and it is expensive. (2 objects referencing each other)

#### Mark & Sweep:

It handles the reference marking by checking

We first DFS traversing starting at the Root, and mark all reachable objects `true`, then we Sweep by clearing any non-marked object from the *Heap*.

> Main problem is that the GC halts the program until it is done.
> Also another problem is running this algorithm multiple times would result in fragmentation, which would later on need compaction. 

> In this course, *Mark&Sweep* was demonstrated using a VM type.