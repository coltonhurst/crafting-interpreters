# Notes

I've been waiting a long time to go through this book. Now I'm waiting no longer - time to enjoy!

## Challenges

### 1. There are at least six domain-specific languages used in the little system I cobbled together to write and publish this book. What are they?

Six DSL's used:

- Markdown
- SASS
- Jinja
- Make
- HTML
- CSS

To add to this... according to [Crafting Crafting Interpreters](https://journal.stuffwithstuff.com/2020/04/05/crafting-crafting-interpreters) (excellently written, a great read), here are some things Bob accomplished in actually building the book:

- The Java interpreter you write in the book
- The C compiler you write in the book
- The script that builds programs from the book snippets
- A makefile takes the programs from the above script and creates a separate interpreter for each chapter
- A test runner that runs tests on the interpreter created in each chapter
- The static generator that generates the HTML from the markdown

### 2. Get a “Hello, world!” program written and running in Java. Set up whatever makefiles or IDE projects you need to get it working. If you have a debugger, get comfortable with it and step through your program as it runs.

Note: I'll be using Rust, at least for the interpreter part of the book

- The hello world program (using Cargo as the build system) is [here](./hello-world-rust/main.rs)
- I've debugged the hello world program, for now I'll use the Zed editor which has a debugger built in

### Do the same thing for C. To get some practice with pointers, define a doubly linked list of heap-allocated strings. Write functions to insert, find, and delete items from it. Test them.

- The hello world program is [here](./hello-world-c/main.c)
- I am building with `clang -g` and debugging with Zed (see [debug.json](./.zed/debug.json))
- `DoublyLinkedStringList` implemented [here](./doubly-linked-list/main.c)
