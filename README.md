= Aegis C++ Library

Copyright &copy; 2001-2015 Sophic Studios, LLC

== Introduction

This directory and its subdirectories contain the Aegis C++ Library. Aegis is
a software library that can be used to create robust, error-free,
high-performance applications. Although the library contains a number of
elements that are geared for game programming, all of the core elements are
useful for any type of application. The foundation components, combined with
the concurrency and networking components provide the basic building blocks
for the most common types of applications a developer may wish to create.


== Library directory structure

* doc           Documentation for the source code included in this distribution
* src           All source code for the library
  * src/aft     Aegis Foundation Toolkit
  * src/act     Aegis Concurrency Toolkit
  * src/agt     Aegis Game Toolkit
  * src/aunit   Aegis Unit Testing

=== Aegis Foundation Toolkit (aft)

* aft/aftc      Containers
* aft/aftfs     Filesystem directories, files, reading and writing
* aft/afth      Hashing and CRC
* aft/aftio     Input/Output utilities
* aft/aftipc    Interprocess communication and shared memory
* aft/aftm      Math routines
* aft/aftma     Memory allocation
* aft/afts      System conditionals
* aft/aftt      Date and time
* aft/aftu      General utilities

=== Aegis Concurrency Toolkit (act)

* act/actp      Primitives: mutexes, conditions, semaphores and threads
* act/acts      System conditionals

=== Aegis Game Toolkit (agt)

* agt/agta      Game application and Entity-Component-System
* agt/agtg      Graphics rendering
* agt/agtm      Matrix and vector math
* agt/agtr      Resource objects and loading
* agt/agtui     User interface

