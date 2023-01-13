# Python-like C++ decorator
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

One exemple is [examples/safe_operations_with_threads.cpp](examples/safe_operations_with_threads.cpp). Where we define a functions to change the value of some variable and another that if its value is equal to 5, print 2 this variable. This functions are executed in differents threads causing a race condition:

```cpp

void write(){
    sharedVariable += 1;
}

void read(){
    if (sharedVariable == 5){
        usleep(10);
        cout << "2 * 5 = " << 2 * sharedVariable << endl;
    }
}
```
The output of the complete code is

```
2 * 5 = 14
```
This happens because the variable `sharedVariable` changes between the if statement and the print of the twice of its value;

But just adding the decorator:

```cpp
mutex _mutex;

void safeOperation(void (*func)(Args...), Args... args){
    _mutex.lock();
    (*func)(args...);
    _mutex.unlock();
}
```

and the decorators macros **after** functions definition:

```cpp
#define write() safeOperation(write);
#define read() safeOperation(read);
```

**Without any aditional code change**, the output of the program is:

```
2 * 5 = 10
```

This exemple is really simple, but shows how this kind of implementation improve the code maintainability and readbility.