Why this project ?
=================


Why
---

Dynamic language does not generate machine level code, which make them slow.
Static language such as C generate mechine level code, but development speed
is very slow.

I want a language which is fast to **write**, fast to **execute**, as well
as **extensive** to multiple platforms easily.


So, meta programming seems fit this need, thus named to **Meta**.



The main idea of **Meta** is the following:
-----------------------------------------


-  A limited set of **basic functions** is defined, most of which is written
in assembly code including some c_calling_functions and take addresses or
registers as input/outputs.

-  Functions in source code is parsed. Syntax tree, sementic table is built.

-  **Statements** are transformed to series of **basic functions**, leaving
addresses or registers unfilled. In this phase, the parser will try maximize
effort to express as much **basic functions** as possible, giving the greatest
possiblity to generate low level machine code.

-  



