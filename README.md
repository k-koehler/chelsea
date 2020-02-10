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

The keyword `var` is available to infer the type of an expression:

    mut var x = 5;
    const var y = 5;

### Functions

In Chelsea, functions are values. They must be assigned to a variable. They have a similar declaration syntax to C/C-like languages.

```
const var foo = void () {
  print("foo");
}
```

Functions are type declared with the template `type (arg type 1, arg type 2, ..., arg type n)`.

```
const int(int) square = int (const int x) {
  return x * x;
}
```

Functions may only access variables declared within the scope of the function itself.

```
const str = "Hello World!";
const var print_string = void () {
  print(str);
}
// err, cannot find symbol str
```

However, you may capture variables into function scope using the `captures` keyword.

```
const var cat = "cat";
const var with_cat = void (const string x) captures cat {
  print(cat, " ", x);
}
with_cat("dog");
// prints "cat dog"
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

    struct Person {
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

You may add a method to a struct with the `::` operator.

```
struct Person {
  const string name;
}

const var set_name = Person :: void (const Person* this, const string name) {
  this!.name = name;
}

const var person = Person { name: "Steve" };
print(person.name);
// "Steve"
person.set_name("Kev");
print(person.name);
// "Kev"
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

In Chelsea, there is no literal to represent `null`/`undefined`/etc. You may declare a variable to be optional, but it must be checked before use, via the `check` keyword. To declare a variable as optional, we use the `?` token.

```
mut int? x;
print(x * 3);
// error, didn't check x
if(check(x)){
  print(x * 3);
}
// will never run, check is false
x = 10;
if(check(x)){
  print(x * 3);
}
// prints 30
```

The `check` function allows a pointer to the variable that it checks, and will reassign the pointer to the value checked on success. The compiler is smart enough to allow you to use an optional value which has been passed as an argument to the `check` operator.

```
const var square_if_even = int? (const int x) {
  if(x % 2 == 0) {
    return x * x;
  }
}

mut int? num;
if(check(square_if_even(2), &num){
  print(num);
}
// prints 4
if(check(square_if_even(3), &num){
  print(num);
}
//does nothing
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

Many times, however, you will want to handle your error, such as opening a file. The idiomatic way to do this, is to use optional variables with the `check` keyword.

```
const File*? fp = open("foo.txt");
if(check(fp)){
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
struct ReferenceHolder {
  const int* ref;
}
const var ~ = Point :: void (const ReferenceHolder* this) {
  free(this!.ref);
}
const var ref = heap(10);
{
  const var ref_holder = ReferenceHolder { ref };
}
// scope for ref_holder ends, destructor is called
print(ref);
// error, already freed ref
```

You may use the `box` keyword to generate a RAII object for dynamic objects.

```
{
  const int* y = heap(10);
  const int y = box(x);
}
// y is freed
```

### Async/Await

You may declare blocks to be async and await them. You may not use an async value until awaited. You may not await an async value unless inside an async block.

```
import get from 'net';

const var hit_server = void (const string url) async {
   const var result = await get(url);
   print(result.status_code);
}

hit_server("google.com")
// error, must await async function "hit_server"
await hit_server("google.com")
// error, not inside an async block
async {
  await hit_server("google.com");
}
// prints 200
async {
  hit_server("google.com");
  print("foo");
  await hit_server("server-that-returns-500.com");
}
// probably prints foo then 200 then 500
```
   
## Example REST Server

main.ch

```
import server from 'net';
import square from './hello.ch';

const var num_cores = 4;
const var app = server(8080);

app.post("/square", square);

async {
  app.run();
}
```

square.ch

```
import Response from 'net';
import parse, stringify from 'json';
import strtoi from 'string';

const int? (string) parse_body_for_int = int? (const string body) {
  mut string? x;
  mut int? num;
  if(check(parse(body).get("x"), &x) && check(stroi(x), &num)){
    return num;
  }
}
  
export const async Response(Context*) hello = void (const Context* ctx) async {
  mut int? x;
  if(check(parse_body_for_int(ctx!.body), &x)){ 
    return Response {
      status_code: 200,
      body: stringify(x*x)
    }
  }
  return Response {
    status_code: 422,
    body: "Invalid Request."
  }
}
```
