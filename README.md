# Chelsea

## What is Chelsea?

Chelsea is a simple, c-like language, which aims to encourage good programming principles, map readily and understandably to machine code, and be so simple, one can master it in hours.

## Main Philosophy

There is only one way to do each thing.

# Getting Started

## Installation

To install Chelsea on unix-like systems, you use the install script:

    enter code here

## Hello World

Let's write our first Chelsea program. In a file called "hello_world.ch", enter the following:

    print("hello world");

That's it! In Chelsea, print is a global function.

## Basics

### Variables

In Chelsea, in each variable declaration, a mutability qualifier is always required. There are only two: `const` and `mut`.

    int x = 5;
    // error: no mutability qualifier
    const int x = 5;
    // ok, value must not be reassigned
    mut int x = 5;
    //ok, may reassign x

Variables must be given a value. In Chelsea, there are no uninitialized variables.

The following primitives are available:

1.  int
2.  uint
3.  float
4.  string
5.  void

The keyword `var` is available to infer the type of an expression:

    mut var x = 5;
    const var y = 5;

### Functions

Functions are declared with the following syntax:

    void hello_world(){
      print("hello world");
    }

They may be declared in any scope.

    int cube(const int x){
       int square(const int x){
         return x * x;
       }
       return square(square(x));
     }

### Arrays

Arrays are fixed size are may be declared in two ways.

As a literal:

    const int[3] int_arr = [1,2,3];

Or with an initializer:

    const int[100] int_arr = [0; 100];

Arrays may be accessed by index:

    const var arr = [1, 2, 3];
    print(arr[0]);
    //prints 1

That's it!

### Structs

Structs contain arbitrary fields.

They must first be declared.

    struct Person {
       const string name;
       const uint age;
    }

They may be declared via the following literal syntax:

    const Person person = Person {
      name = "Bob Doe";
      age = 42;
    }

To access struct properties, we use the `.` operator.

    const Person person = some_person();
    print(person.name);
    // prints the person's name

### Control Flow

To conditionally execute a block, you can use the `if`statement. If statements only accept a single boolean expression as an argument.

    if(1){
      ...
    }
    // error, expected bool but got int
    const var x = 5;
    if(x == 5){
      print("five!");
    }
    //prints 5

There is just one way to loop, the `loop` keyword.

    loop {
      print("pineapple goes on pizza");
    }
    // infinitely loops

You may specify an initializer, loop guard, and post-loop expression, similar to the `for`loop in most C-like languages.

    const var arr = [0; 10];
    loop (mut var i=0; i<10; ++i){
      print(i);
    }
    // prints 0,1,2,3,4,5,6,7,8,9

### Optional Variables

In Chelsea, there is no literal to represent `null`/`undefined`/etc. You may declare a mutable variable to be optional, but it must be checked before use, via the `check` keyword. To declare a variable as optional, we use the `?` token.

    const int? x;
    // error, const cannot be optionat
    mut int? x;
    const var y = x * 2;
    // error, must check optional variable x
    if(check(x)){
      print(x);
    }
    // will not execute the block, x is not yet initialized
    x = 10;
    if(check(x)){
      print(x);
    }
    //prints 10

To help illustrate the usage optional variables, we will make a basic linked list.

    struct Node {
      const int value;
      mut Node*? next;
    }

    void print_list(const Node* head){
      mut var cur = head;
      loop {
        print(cur!.value);
        if(check(cur.next)){
          cur = cur.next;
        } else {
          break;
        }
      }
    }

### Pointers

You may point to a specific piece of memory with a pointer.

    const int foo = 10;
    const int* foo_ptr = &foo;

Pointers must always point to something; there is no null pointer. Unlike in C/C++, where the `*` operator is used both to indicate a variable is a pointer, and to deference said pointer, Chelsea has a separate symbol for dereferencing: `!`.

The following code in C/C++:

    int a = 10;
    int* a_ptr = &a;
    int b = *a_ptr;

Could be constructed in Chelsea as follows:

    const int a = 10;
    const int* a_ptr = &a;
    const int b = a_ptr!;

### Import/Export

You may import a symbol from another file via the `import`/`export` keywords.

In `foo.ch`:

    export int square(const int x){
      return x * x;
    }

In `bar.ch`:

    import square from "./foo.ch";
    print(square(5));
    //prints 25

### Memory Management

You may allocate memory from the stack, but you must do it explicitly via the `heap` and `memalloc`keywords.

    const int some_int = 1;
    // allocated on the stack
    const heap int* some_other_int = memalloc 1;
    // allocated on the heap

There is no garbage collector, and heap allocated memory must be freed with the `delete`keyword. You may no longer access a variable after deleting it.

    const var bob = memalloc Person { name = "Bob"; age = 42; }
    delete bob;
    print(bob!.name);
    // error, cannot find symbol bob

You may only delete a resource within the scope that it was declared:

    void del(const heap int* x){
      delete x;
    }
    // error, cannot delete x because it was declared out of scope

To ensure your heap allocated memory is freed at the end of the current scope, the `membox` keyword may be used before any block.

    loop (mut int i=0; i<10; ++i) {
      const int heap_int = membox(memalloc i);
    }
    // memory is freed here, after the loop scope closes

The `membox` keyword is internally implemented to adhere to the RAII pattern, but only for heap allocated memory, using `delete` as the destructor.
