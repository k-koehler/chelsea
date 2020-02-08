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

Functions _ONLY_ have access to variables which are passed in. For example:

    const var y = 10;
    int square(const int x){
      return x * y;
    }
    //error, cannot find reference to variable 'y'

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

They may be declared on the stack:

    const Person person = Person {
      name = "Bob Doe";
      age = 42;
    }

Or on the heap:

    const Person = new Person {
      name = "Bob Doe";
      age = 42;
    }

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
      mut Node? next;
    }

    void print_list(const Node head){
      mut var cur = head;
      loop {
        print(cur.value);
        if(check(cur.next)){
          cur = cur.next;
        } else {
          break;
        }
      }
    }
