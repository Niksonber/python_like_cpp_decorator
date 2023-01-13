# Python like C++ decorator
This repository presents some samples of how to implement and use a Python-like decorator using C++.

To do this, we use template and function pointer:

```cpp
template<typename T, typename... Args>
T decorator((T *function)(Args...), Args... args){
    // <Pre-operation code>
    T result (*function)(args...);
    // <Pos-operation code>
    return result;
}
```

Then, **after** the function definition, define a macro:

```cpp

#define some_function(args) = decorator(some_function, args)
```

So, every `some_function` call, will execute the pré-operation first, then the `some_function` scope and, at end, the pós-operation, without any aditional code change.

This is similar to the Python's decorator:

```python
def decorator(function):
    def wrapper(*args, **kwargs):
        # <Pre-operation code>
        result = function(*args, **kwargs)
        # <Pos-operation code>
        return result

    return wrapper
```

```python
@decorator
def some_function(*args):
    # <function scope>
```
