# pw-event-cpp
Fast, header-only C++11 events and delegates
  
## Usage

// todo

## Features
- Usage of variadic templates to allow generic parameter-lists
- const_delegate-type to only allow const-member-functions

## Inspired by

- [The Impossibly Fast C++
  Delegates](http://www.codeproject.com/Articles/11015/The-Impossibly-Fast-C-Delegates),
  author: Sergey Ryazanov

## TODO

- Reallow Events with return value (return last value -- like c# does)
- Improve template-args style (<_ReturnValue(_Params...)> over <_ReturnValue, _Params...>)
- Add const_event? (even though i doubt the need of it)
