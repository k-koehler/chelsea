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
6.  function
7.  type

The keyword `var` is available to infer the type of an expression:

    mut var x = 5;
    const var y = 5;

### Functions

Functions in Chelsea are declared using the `fn` keyword:

```
fn hello(){
  print("hello");
}

const var x = (fn (const int n) { return n; })(42);


int fn add(const int x, const int y) {
  return x + y;
}
```

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

    const type Person = struct {
       const string name;
       const uint age;
    }

They may be declared via the following literal syntax:

    const Person person = Person {
      name: "Bob Doe";
      age: 42;
    }

To access struct properties, we use the `.` operator.

    print(person.name);
    // prints the person's name

You may add a method to a struct in the usual way:

```
const type Person = struct {
  mut string name;
  void fn set_name(const string _name){
    name = _name;
    // or, this!.name = _name;
  }
}

const var person = Person { name: "Steve" };
print(person.name);
// "Steve"
person.set_name("Kev");
print(person.name);
// "Kev"
```

You may declare an anonymous struct easily.

```
const var anonymous = struct { const int x; } { x: 42 };
print(anonymous.x);
// 42
```

There are no constructors, but you can use the anonymous struct pattern to simulate them.

```
fn Person(const int age, const string name){
  return struct {
    const int age;
    const string name;
  } { age, name };
}
```

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

In Chelsea, there is no literal to represent `null`/`undefined`/etc. You may declare a variable to be optional, but it must be checked before use, via the `with` keyword. To declare a variable as optional, we use the `?` token.

```
mut int? x;
with x {
  print(x);
}
// does nothing
x = 3;
print(x)
// error, need to check existence
with x {
  print(x);
}
```

Many times you will want to check the existence of an expression, such as a function call. This can be done using the `with-as` construction.

```
int? fn get_even_number(const int[3] arr){
  loop(mut var i=0; i<lengthof arr; ++i){
    if(arr[i] % 2 == 0){
      return arr[i];
    }
  }
}

with get_even_number([1,2,3]) as n {
  print(n);
}
// prints 2
```

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
    
### Errors

You may throw an unrecoverable error with the `error` keyword.

```
const var index_arr = int(const int[10] arr, const int index){
  if(index < 0){
    error("Index must not be negative!");
  }
  return arr[index];
}
```

Many times, however, you will want to handle your error, such as opening a file. The idiomatic way to do this, is to use optional variables with the `with` keyword.

```
// some lib file
File*? fn open(const string fn){ ... }

// userland
with open("foo.txt") as fp {
  // succeeded
}
```

### Memory Management

In Chelsea, there is no garbage collector. You must explicitly allocate and free heap memory.

To allocate memory from the heap, you may use the `heap` keyword. You may give the `heap` operator a primitive, array, or scalar initialized struct as an argument.

```
const int* heap_int = heap(0);
print(heap_int!);
// 0
const int[10]* heap_int_arr = heap([0; 10]);
print_array(heap_int_arr!);
// 0,0,0,0,0,0,0,0,0,0
const Person* person = heap(Person { name: "Jane", age: 33 });
print(person!.name);
// "Jane"
```

To free memory, you may use the `free` keyword. If you a pointer to the stack, or memory which has already been freed, an unrecoverable error with be thrown.


```
const int x = 10;
free(&x);
// error, x not allocated on heap
const int* y = heap(42);
free(y);
// ok
free(y);
// error, already freed y
```

You may declare a destructor for structs with the `~` operator.

```
const type ReferenceHolder = struct {
  const int* ref;
  void fn ~(){
    free(ref);
  }
}
{
  const int* ref =  heap(10)
  const var ref = ReferenceHolder({ ref });
}
// ref is freed
```

You may use the `box` keyword to generate a RAII object for dynamic objects.

```
{
  const int* y = heap(10);
  const int y = box(x);
}
// y is freed
```

## Advanced Features

### Everything is an expression

Any block can yield an expression using the `yield` keyword:

```
const var calculated_value = {
  const var x = 3;
  const var y = 5;
  const var z = 7;
  yield x * y + z;
};
print(calculated_value);
// 22
```

We can use this feature in cool ways, like conditional assignments.

```
const var x = 2;
const var result = if (x % 2 == ) { yield "even"; } else { yield "odd; }
print(result);
// "even"
```

Or loop initializers.


```
const var sum = outer: loop (mut var i = mut var sum = 1; ; sum += ++i) {
  if(i>=100){
    yield outer sum; 
  }
  continue;
}
print(sum);
// 5050
```

We can even simulate pattern matching in this fashion.

```
const var x = 10;
const var result =
  if      (x < 0)  { yield "negative"; }
  else if (x == 0) { yield "zero"; }
  else             { yield "positive"; }
```

## Types as a type

In Chelsea, you may store types as a variable.

```
const int x = 3;
const type t = typeof x;
print(t);
// "int"
```

This allows us to declare generic data types.

```
type fn Node(const type T){
  return struct {
    const T value;
    const Node(T)*? next;
  }
}

const var node1 = Node(int) { value: 0 }
const var node2 = Node(int) { value: 1, next: &node1 }
```

### Declare Expressions

You may use the keyword `declare` to declare values in the following way:

```
declare <identifier> <value>
```

All declared variables are const. The value must be known at compile time. This can allow arbitrary compile-time resolution and make code more readable.

```
declare Vector struct {
  const int x;
  const int y;
  const int z;
}

const var vec = { x: 1, y: 2, z: 3 };

declare FAC_10 {
  fn fac(const int n){
    if(n == 1){
      return 1;
    }
    return n * fac(n-1);
  }
  yield fac(10);
}
```
