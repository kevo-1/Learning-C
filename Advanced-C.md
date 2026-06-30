# Advanced C

## Reference:

- https://www.youtube.com/watch?v=g7CCaRwRVBQ&list=PL71Y0EmrppR0KyZvQWj63040UEzKQU7n8

### Function Pointers:

Syntax: `return type (* functionName)(parameter type, ...) = func()`

> The syntax might be counter intuitive to the C variable declaration style

Example: 

```c
int foo(int a, int b) {
    return a + b;
}

void main() {
    int (*f)(int, int) = foo();
    printf("%d", f(1, 2));
}
```

### Bit flags:

It is to make code more readable and neater

```c
#define F_A (1 << 0) // 00000001
#define F_B (1 << 1) // 00000010
#define F_C (1 << 2) // 00000100

// or

typedef enum {
    F_A = (1 << 0),
    F_B = (1 << 1),
    F_C = (1 << 2)
} flags;

int f(int x, unsigned int flag) {
    if(flag & F_A) //
    if(flag & F_B) //
    if(flag & F_C) //
    if(flag & F_A & F_B) //
    return x;
}

int main(void) {
    f(23, 0);                 // 00000000
    f(23, F_A);               // 00000001
    f(23, F_A | F_B);         // 00000011
    f(23, F_A | F_B | F_C);   // 00000111
}
```

> To turn off the bit we could do `flag &= ~F_A`

### Long Number separator:

It is done by using the `'` between each set of digits.

> Arguably one of the worst I have ever seen too

```C
int x = 1'000'000;
```

### Small fact:

Near and Far pointers are a thing of legacy computer systems, where near pointers would be used for programs that could fit in a `64 KB` memory segment (They are of size `2 bytes`), while Far pointers where `4 bytes` and could point anywhere in RAM; however they are slower as they store offset and segment separately.

### Look-up tables:

You can mimic the hashmap behaviour in C using the following pattern

```C
// Enumeration
enum foo {
    foo2 = 0,
    foo3,
    foo4
};

static int arr[] = {
    [foo2] = 4, // A good way of initialization
    [foo3] = 9,
    [foo4] = 16,
};
// And now you can access any element of the array using the enum values

// Straight value access
static char arr2[] = {
    ['a'] = 'A',
    ['b'] = 'B',
    ['c'] = 'C',
}
```

> If the key grows in size the array will leave huge chunks in memory.
> `arr2` for example takes up space until 100 bytes ('c' = 100)
> while `arr` takes up to 12 bytes reserving space for only 3 elements starting from 0 index until 12 bytes.
