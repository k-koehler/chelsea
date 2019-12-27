# chelsea

## Getting Started

### Hello World

```
print("Hello World");
```

## Highlights

### Default Immutable Variables

```
var x = 5;
x = 6;
// error, x is not mutable 
mut i = 0;
print(++i);
// 1
```

### No Null

In Chelsea there is no concept of null/undefined/etc. To mimic optional values via nullity, we can use optional types. 

```
int? find_idx(string[] arr, int len, string flag){
  loop(mut i=0; i<len; ++i){
    if(arr[i] == flag)
      return i;
  }
}

...

var idx = find_idx(some_arr, some_flag);
if(check(idx))
  print(idx);
else 
  print("no match!");
```

## Why Chelsea?

Chelsea is being developed to create a very simple language, which maps readily to machine code, but also encourages good programming principles. Chelsea is inspired by C, but aims to avoid many of the problems that C programmers encounter. 

## Basics

### Variables 

In Chelsea, variables are default immutable. To declare a variable, we can allow the compiler to infer the type, or we can explicitly declare it. 

```
int x = 3; // explicit 
var y = 4; // implicit
```

Mutable values have a similar pattern. 

```
mut string foo = "bar;
mut baz = "bax";
```

Optional values are default mutable, and have the following syntax. 

``` 
int? optional;
```
