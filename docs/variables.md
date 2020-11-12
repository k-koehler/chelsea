# Variables in Chelsea

Initializing a variable in chelsea is simple.

```c
int my_variable = 42;
```

Variables can also be `const`.

```c
const int my_const_value = 10;
my_const_value = 20; // ERROR: cannot reassign const variable "my_const_value"
```

You can infer the type of a variable with the keyword `var`. 

```c
var name = "Bob";
name = 42; // ERROR: cannot assign type "numeric" to type "string"
const var immutable = "abc";
hi += "def"; // ERROR: cannot reassign const variable "immutable"
```
