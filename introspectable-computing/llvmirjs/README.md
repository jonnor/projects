
# LL.js

Experiments in generating LLVM IR code from JavaScript.

Ideally this can be used in combination with the LLVM backends through
[LLVM.js](https://kripken.github.io/llvm.js/demo.html)),
and a frontend based on standard parser/lexer generators like
[Jison](http://zaach.github.com/jison)
/[PEG.js](http://pegjs.org/)
/[oMeta.js](https://github.com/alexwarth/ometa-js),
to implement programming languages toolchains that can run fully in a browser.

The primary motivation for [author](https://github.com/jonnor) is to have
embedded devices serve their entire toolchain to a standard mobile device;
to allow instant inspection and reprogramming by owner.

But it could also be used for implementing self-hosted languages which target the
browser/JavaScript, using LLVM.js+Emscripten for code generation.


## Backend

Ideally we'd also have native JavaScript compiler backend, instead of relying on cross-compiled LLVM.
It may make sense that this also takes LLVM IR, that way compatibility with existing frontend and tools are preserved,
making it quicker/easier to create something useful.

For embedded devices, ARM/Thumb instruction set is probably one of the most relevant target.

LLVM IR grammar

* [Stackoverflow: Is there BNF for LLVM IR](http://stackoverflow.com/questions/4581994/is-there-bnf-like-grammar-to-describe-llvm-ir)
* [Github: llir, Formal grammar](https://github.com/llir/llvm/issues/2)

Related projects

* [PeachPy](https://github.com/Maratyszcza/PeachPy), x86/x86-64 code generation in Python.
[Hackernews post, references related projects](https://news.ycombinator.com/item?id=10232025)
* [ppci](https://bitbucket.org/windel/ppci), compiler written in Python.
Includes assembler with backends for arm, avr, msp430
* [DynASM](https://github.com/luapower/dynasm/blob/master/dynasm.md)
Dynamic code generation in Lua, for x86/x86-64. (linker/encoder written in C)
