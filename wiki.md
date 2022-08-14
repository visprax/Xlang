The first step is **scanning** (**lexing** or **lexical analysis**) of the actual source code text. The lexer takes in the text and breaks it into seperate 
meaningful words, called **tokens**. The next is **parsing**, the **parser** takes the tokens and builds the **parse tree** or the **abstract syntax tree (AST)**
or just the **tree**. The parser also reports any **syntax errors**. 
The next step is *static analysis*, most languages will first do **binding** or **resolution**. The language should know where each **identifier** is defined, and 
what is the **scope** of that identifier. Once the identifiers are resolved, it can figure out the types also, and if for example for two identifier addition is 
not supported, it can throw **type error**.
All this semantic insight can be stored:
- on the abstract tree itself, as **attributes**, extra fields on the nodes of the tree that gets filled once the analysis is complete.
- as a lookup table with identifiers as keys, which is called a **symbol table**.
- or transform the tree into an entirely new data structure, that more directly expresses the semantics.
up until we were dealing with the **fron end** of our implementation. other parts are **middle end** and **back end**.

In the middle end we can represent the code in some **intermediate representation (IR)**, the IR acts as an interface between source code 
and destination architecture. At this stage we can also do **optimizations**.

In the backend we do the **code generation**, we can generate native code, instructions for the real CPU, that the OS can load directly onto the chip. 
Or we can generate one for a *virtual chip*, that generates *virtual* machine code, called **bytecode** because each instruction is often a single byte long.
