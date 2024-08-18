# TPOSLC
A LibC implementation.


## Introduction
TPOSLC (Testing and Prototyping Operating System Library C) is a study into how to implement a c17 libc.

The Libc is written for TPOS and Windows, with Windows being a study into how a libc can be implemented in it.

The Libc aims to follow the specification as closely as possible.

The Libc is currently incomplete, some functions are not fully implemeneted, such as printf/scanf variations.

The Libc support only x86_AMD64.

On Windows only the debug build will reliably work as the compiler will use its own inline functions for some of the libc signatures.

## Compiling

[!]The Libc was build using clang on visual studio and wont compile with msvc, as it doesnt support inline assembly.
Simply open the solution file located in the cstdlib folder and it should compile out of the box.
