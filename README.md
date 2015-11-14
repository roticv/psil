# psil
This is just my feeble attempt to learn more about compilers. To give credits,
this was inspired after skimming through [www.buildyourownlisp.com] and doing
more of my own research.

## Reverse polish notation
I started off with the implementation of parsing (and evaluating) reverse polish
notation because that should be the simplest to implement. It uses a
hard-written parser invoked by a REPL.

The language used is

```
<operator> := '-' | '+' | '/' | '*'
<num> := [0-9]+
<expr> := <num> | '(' <symbol> <expr>+ ')'
```
