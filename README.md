# pw-event-cpp
Fast, header-only C++11 events and delegates w/o any need for inheritance to use events. (also supports MSVC)
  
## Usage

### Delegates

Delegates are more or less like simple function-pointer, but can also contain member functions (additionally to the object they're called on) without changing their type. Unlike with std::function, the object on which member functions are called is also contained inside the delegate-object.

A delegate can always only 'contain' one function (in the example below further calls to ~.bind overwrite the previously bound one)

```cpp

#include "delegate.hpp"

void free_function(int _i) {}

class A
{
public:
    void member_function(int _i) {}
    void const_member_function(int _i) const {}
};

int main()
{
    A a;
    pw::delegate<void(int)> delegate;
    
    // we can bind a simple function-pointer
    delegate.bind<&free_function>();
    
    // but we can also bind member-functions to the same delegate-type
    delegate.bind<A, &A::member_function>(&a);
    
    // as well as const-member-functions
    delegate.bind<A, &A::const_member_function>(&a);
    
    // call the currently bound function
    delegate.invoke(0);
    
    // we can also create a delegate in one line
    auto one_line_delegate = pw::delegate<void(int)>::create<A, &A::member_function>(&a);
    one_line_delegate(0); // invoke with ()-operator
    
    return 0;
}
```

### Events

Events can contain several delegates, which can easily be invoked in one go.

```cpp

#include "event.hpp"

class A
{
public:
    pw::event<void(float, float)> onMouseMove;
    pw::event<void()> onUpdate;
};

class B
{
public:
    void do_something() {}
    void do_something_else() {}
    void do_something_utterly_different(float _x, float _y) {}
};

void do_something_with_parameters(float _x, float _y) {}

int main()
{
    A a;
    B b;
    auto delegate = pw::delegate<void()>::create<B, &B::do_something>(&b);
    
    // add a delegate to an event
    a.onUpdate.add(delegate);
    
    // adding a function without creating a delegate first
    // the same rules as for creating delegates apply here
    a.onUpdate.add<B, &B::do_something_else>(&b);
    
    // invoke the event
    a.onUpdate.invoke(); // calls b.do_something() and b.do_something_else()
    
    // we can also have events with parameters
    a.onMouseMove.add<&do_something_with_parameters>();
    a.onMouseMove.add<B, &B::do_something_utterly_different>(&b);
    
    // all bound delegates are called with the parameters
    a.onMouseMove(0.0f, 1.0f);
    
    return 0;
}
```

## Inspired by

- [The Impossibly Fast C++
  Delegates](http://www.codeproject.com/Articles/11015/The-Impossibly-Fast-C-Delegates),
  author: Sergey Ryazanov

## TODO
- Evaluate conversion from delegate<_ReturnType(_Params...)> to std::function<_ReturnType(_Params...)>
  - If possible add std::function support to events
