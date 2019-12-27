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

## Why Chelsea

Chelsea is being developed to create a very simple language, which maps readily to machine code, but also encourages good programming principles. Chelsea is inspired by C, but aims to avoid many of the problems that C programmers encounter. 


