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

If we generate bytecode, we have to either translate (compile) this bytecode to every architectures native code we plan to support, or we can write a 
**virtual machine (VM)** that emulates a virtual architecture at runtime. This is slower than native code generation because each instruction must be simulated 
at runtime.

If we compiled to machine code we tell the OS to directly load it to the chip, otherwise we have to start the VM and load the program onto it. 
At *runtime* we will probably need a garbage collector if we're automatically doing it. In compiled languages, like Go, the runtime code gets inserted 
directly into the executable, if the language is run through a VM or an interpreter, like Java or Python, the runtime is there.

The **single-pass compilers** don't allocate any syntax trees or IRs, and generate code directly in parser. These restrict the design of the language, they don't 
revisit any previously parsed part of the code, and as soon as they see and expression they have to know enough about it to correctly compile it, examples include 
C and Pascal.

**Tree-walk interpreters** begin executing code right after parsing it to and AST (with maybe some static analysis). The interpreter traverses the syntax tree one 
branch and leaf at a time, evaluating each node as it goes. This is not widely used in more general-purpose languages since it tends to be slow.

A **Transpiler**, **transcompiler**, or **source-to-source compiler** treats another language as it's target intermediate representation and uses it's 
tools to compile the code, e.g. JavaScript is the machine code of browsers and almost every language out there has a compiler that targets JS since it's 
the main way to run your code in a browser.

The fastest way to execute code is by compiling it to machine code, but you might not know what architecture your end user's machine supports.
We can do what Java Virtual Machine (JVM) and most JavaScript interpreters do. When the program is loaded, either from the source (JavaScript) 
or platform-independent bytecode from JVM, you compile it to native code for the target architecture, this is called **just-in-time compilation**.

### The Xlang specifications

*syntax*: TODO: explanation about the syntax of Xlang. Later change probably to mimic Julia.

*Dynamically typed*: variables can store values of any type, the type errors are detected at runtime. 
A statically typed language is a much larger project to imeplement here.

*Automatic memory management*: Two main techniques for managing memory: **reference counting** and **tracing garbage collection** (or just **GC**), 
Ref counters are simpler to implement, while a GC takes a lot of work.

*Data types*: 
- **Booleans** (*true* or *false*) 
- TODO: **integers**
- **double-precision floating point**
- TODO: hexadecimal, scientific notation, octal, ..., 
- **strings**
- **nil** value, TODO: change it to *null*
- TODO: other data types like *dict*

*Variables*:
- `let a = 1;`
- TODO: more on this later.

*control flow*:
- if else statements
- while loop
- for loop
- TODO: examples for each

*functions*:
- `fn printSum(a, b) { print(a+b); }`

*closures*:
- functions are first class, we can get a reference to, store in variables, pass around, etc.

- ```
fn addPair(a, b) {
    return a+b;
}

fn identity(x) {
    return x;
}

print identity(addPair)(a, b);
```

- ```
fn returnFunction() {
  let outside = "outside";

  fun inner() {
    print outside;
  }

  return inner;
}

let fun = returnFunction();
fun();
```

*classes*:
- we will use classes as opposed to prototypes (though easier to implement they push the complexity to the end user)
- ```
class Breakfast {
  init(meat, bread) {
    this.meat = meat;
    this.bread = bread;
  }

  // ...
}

var baconAndToast = Breakfast("bacon", "toast");
baconAndToast.serve("Dear Reader");
// "Enjoy your bacon and toast, Dear Reader."
```

- TODO: instantiation and initialization, inheritance

*standard library*
- TODO: implement a minimal standard library: string manipulation, math functions, file I/O, networking ...
