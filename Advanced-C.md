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