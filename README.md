type_switch
===========

A simple static type-switch / pattern matching library.

WARNING: Do not use mutable lambdas with this, the overloads will sometimes not be properly selected.

API:
- overload( < list of single-argument lambdas > );
Returns a callable object that will select the appropriate lambda depending on the static type of the argument,
using the usual overload resolution rules (beware of implicit conversions).

- match( < object > );
Returns a callable object that takes a list of single-argument lambdas (same as overload) and forwards the received
object to the appropriate lambda based on the static type. It's simply a convenience function to match the usual
functional "match" syntax.

- otherwise( < void() lambda > );
Creates a callable object taking one generic argument that will ignore its argument and call the passed lambda instead.
Plays nicely with overload and match. Note that the position of otherwise in the lambda list does not matter, it will
not shadow other cases even if it is placed before them.

Usage:
main.cpp contains examples.
