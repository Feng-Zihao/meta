**Meta** : Programming language based on function expansion
===========================================================


Why?
---

I have use C/C++, Java, Python in my past. Also, I have learnt a little
Ruby, Lua and Go. But none of them exactly feed my need.

Dynamic language are just too dynamic, which make them slow to execute, hard
to offer code complement and code hint for editors.

C/C++, Java are faster, relatively. But writing them is a nightmare. Dealing
with pointers in C/C++, boring syntax of Java, reduce my happiness of coding.

Go language is excellent in most of things, but still, can improve on reverse
type speculation.

I want a language which is fast to **write**, fast to **execute**, as well
as **extensive** to multiple platforms easily.


The main idea of **Meta** is the following:
-------------------------------------------

- A limited set of **basic functions** is defined, most of which is written
  in assembly code including some c_calling_functions and take addresses or
  registers as input/outputs.

- Functions in source code is parsed. Syntax tree, sementic table is built.

- **Statements** are finally transformed to series of **basic functions**,
  leaving addresses or registers unfilled. In this phase, the parser will try
  maximize effort to **express**(instead of simply **call** and **jump**) 
  as much **basic functions** as possible, giving the greatest possiblity to
  generate low level machine code.

- Registers and addresses are filled into the holes and optimization is done.


So, from the overall level, the basic concept can be expressed like this:

basic_functions = {tpl1, tpl2, tpl3 .., tplX} 
programs = [tpl1, tplX, tpl3, tpl4 ...]

If we can expand programs into series basic_functions, programs are fixed.

The parser or compiler is a program that treat source code as input,
pre-defined machine code template as output, thus fits the idea of meta
programming.


Main features of **Meta** in my head
------------------------------------

**Meta** is designed to be a typed language. However, the syntax look like
dynamic. To fullfill this, **type speculation**, especially **reverse type
speculation** technique is applied.

- Dynamic way to write.
- Multiple return value.
- Configurable memory allocation and deallocation strategy at compile phase.
- Intelligent type speculation. Most of time, you can save your time on
  writing type information. If it can not judge your time, it will guide
  you.
- Build-in package management system.


On the road
----------

I am not sure who far I can go. But try!

First stage task:

Confirm the way it works.

- build-in type      : **int, char, array**
- build-in operation : **+ -**
- build-in function  : **read write**
- support feature    :

-  - declare struct
   - declare functions
   - type speculation


Don NOT think about currently:

- struct in C. Implement char[] first, later, you know struct in C.
- multithread support. 


