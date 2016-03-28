
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
