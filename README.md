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
- Evaluate conversion from delegate<_ReturnType(_Params...)> to std::function<_ReturnType(_Params...)>
  - If possible add std::function support to events
