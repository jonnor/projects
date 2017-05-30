
# LiveMetal

Note: name totally arbitrary so far

## Idea

Live-programming microcontrollers-based devices,
by having the microcontroller serve tools/frontend in JS/HTML
over HTTP to a standard browser.

## Possible implementations

* Rebuild app, reflash whole program memory, reload application state
* Virtual machine with bytecode interpreter, reload a 'script'
* Virtual machine with transactional mutable AST
* Partial program memory updates, like swapping out functions

All of these requires a toolchain that can be embedded onto
the microcontroller itself, possibly hosted partially on the microcontroller
and partially in JavaScript (executed in browser).

## Stack based VM
Many of these exists already. Forth-like systems are very popular,
and are often self-hosted with a text-based 'programming environment built-in'.
The most advanced even have built-in assemblers for their targets.

Learning to program in Forth however, is quite a barrier, perhaps especially
for programmers experienced ALGOL/C-decendent languages.
There is also very little tooling apart from the low-level text ones.

### References

Microcontroller virtual machines

* [EmbedVM](http://www.clifford.at/embedvm/), with C-like language frontend.
3kB of program memory on AVR8, about 75k VM ops/second at 16MHz.
* [NanoVM](http://www.harbaum.org/till/nanovm/index.shtml), Java (subset) virtual machine for AVR.
* [DAN64](https://www.usebox.net/jjm/dan64/), building a 8-bit microcomputer with a 6502 VM,
including video output and loading/saving programs as audio files.
* [Stack Overflow: List of low-memory interpreters](http://stackoverflow.com/questions/1082751/what-are-the-available-interactive-languages-that-run-in-tiny-memory)

Forth

* [Practical minimal opcode set](http://newsgroups.derkeiler.com/Archive/Comp/comp.lang.forth/2005-09/msg00337.html).
Arithemetic `+ - * /`, binary `AND XOR OR` comparison `= < >` and binary ! `NEGATE`,
and for control-structures `JUMP_IF_ZERO JUST_JUMP`.
* [ForthRight](http://www.esp8266.com/viewtopic.php?f=6&t=7800), Forth for ESP8266 including TCP shell
* [MbedForth](https://developer.mbed.org/cookbook/MbedForth) for ARM Cortex M3,
based on [Riscy Pygness](http://pygmy.utoh.org/riscy/cortex/)
* [MeCrisp](http://mecrisp.sourceforge.net/), a Forth for MSP430 and ARM Cortex like Stellaris/Tiva/Teensy3.1,
with a tutorial [Dive into Forth](http://jeelabs.org/2016/02/dive-into-forth/)
* [J1a SwapForth on ICE40 FPGA with open toolchain](http://www.excamera.com/sphinx/article-j1a-swapforth.html)
* [CoreForth](https://github.com/ekoeppen/CoreForth), for ARM Cortex M0/M3, originally based on JonesForth
* Simple Forth [using C as intermediate languge](http://yosefk.com/blog/c-as-an-intermediate-language.html).
Very simple & pragmatic integration.
* A more practical Forth-like language would probably benefit a lot from:
a) declaration and checking of the stack effects of words,
b) data-driven unit-tests: Put testdata to stack, execute word, check stack. Integrated with word declaration, Python doctest style

Ethereum VM

* [Original paper](http://gavwood.com/paper.pdf)
* [Ethereum Script 2.0](https://blog.ethereum.org/2014/02/03/introducing-ethereum-script-2-0/)


## Mutable ASTs
Have a VM which has an AST of the currently running program,
which can then be *changed* from user interface/terminal.
Probably the most crazy/esoteric idea?

Would probably have to use some language with a minimal syntax that closely corresponds to emitted code?
Like a LISP or maybe a FORTH.

`TODO: research`

MicroFlo graph commands work in this way, but this is not a general purpose mechanism.
Unless one also allows uploading of machine/VM code to (re)define components.

## Full-app rebuild
Conceptually the most straight-forward.

Need a full-fledged compiler for the source language.
Challenge is that there are very few, if any, compilers which can be self-hosted in an uC/JS context.

Also most traditional languages are not very suited for deeper 'introspection'.

Also need some sort of tools/best-practices for doing reloadable apps.
Redux and module-reloading from JavaScript might serve some inspiration here.

## Compiler as JavaScript eDSL

Instead of inventing a new programming language, and a compiler for it,
use JavaScript as the language to program in, and then generate machine code directly from this.
The most basic level would be assembly instructions, then one could build (JS) libraries with higher-level
constructs on top.

For some degree of static checking, should use TypeScript to implement core library.

An existing compiler, like GCC or LLVM could be used as an oracle to test against.
Executing (possibly in an emulator) can provide additional verification.
Data-driven and property-based testing techniques can be used for wide coverage.

It may be interesting to track the effects of instructions/snippets in the DSL,
for instance on registers, stack, memory, program counter.

For testing, can be useful to implement basic supports for asm mnemonics,
easy to keep stable and understandable for unit-tests.

## Dataflow with component compiler

Could use MicroFlo (or similar) dataflow engine as component and cross-component communication mechanism.
Then allow custom components to be implemented using a dedicated compiler.
Such a compiler/language can be relatively simple, due to the limited scope of implementing a component.
Interpreting input packet data, storing internal state, processing data and creating new output packets.
Can we even disallow general reading/writing to memory? At least for most components

Components can be hot-reloaded individually, updating done by removing the old component instance(s),
replacing component code, creating new instances. 

### Resources

Loading code at runtime

* [TockOS: Dynamic code loading on MCU](https://www.tockos.org/blog/2016/dynamic-loading/),
explains position-independent-code (PIC) with relative addresses to support multiple "apps".
* The rad1o CCCamp badge could load different apps from Flash. Flash was also accessible over USB
* [ArduinoOTA](http://esp8266.github.io/Arduino/versions/2.0.0/doc/ota_updates/ota_updates.html), over-the-air update
for ESP8266 chips based on Arduino.

ARM Cortex-M assembly

* [Blinking LEDs in Assembly](http://pygmy.utoh.org/riscy/cortex/led-stm32.html)
* [ARM Cortex-M instruction sets](https://en.wikipedia.org/wiki/ARM_Cortex-M#Instruction_sets).
Thumb1/2 combo, several optional extensions depending on family
* [ARM: Cortex-M4 reference manual](http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0439b/CHDDIGAC.html)
* [Stack Overflow: Software divide/multiply](https://stackoverflow.com/questions/2390354/where-can-i-find-soft-multiply-and-divide-algorithms)
* [Whirlwind tour of ARM Assembly](https://www.coranac.com/tonc/text/asm.htm)

## References

JavaScript compilers.

* [LLVM.js](https://kripken.github.io/llvm.js/demo.html), experimental port of LLVM to JS using Emscripten. Takes LLVM IR as input
* [Keystone.js](https://alexaltea.github.io/keystone.js/), Emscripten port of Keystone assembler. Supports many archs. GPLv2
* [assembler.js](https://www.npmjs.com/package/ass-js), x86 assembler as JavaScript library. Goal of supporting ARM

JavaScript transpilers (to C or similar)

* [LiteScript](https://github.com/luciotato/LiteScript) compile-to-C and compile-to-JS.

JavaScript parser generators

* [language.js](https://github.com/tolmasky/language) emits SyntaxError nodes instead of causing exception

Retargeting compilers

* [LLC: Retargetable ANSI C compiler](https://sites.google.com/site/lccretargetablecompiler/), can maybe be compiled to JS via Emscripten?

JavaScript-based emulators

* [Unicorn.js](https://alexaltea.github.io/unicorn.js/). Emscripten port of Unicorn, a C-based emulator framework.
Supports many architectures, incl ARM. GPLv2


## Related

Related motivations

> Which is where we stand today, in 2016: tethered software development,
> with the source code and tools living in one world (our laptops or the web),
> and the µC being sent a firmware upload to perform the task we’ve coded up for it,
> after translation by our toolchain
> ...
> What if we just want to investigate the hardware, check out a few settings in the chip,
> briefly toggle a pin or adjust a hardware register setting?
> Tough luck: you have to leave the flow of design and implementation,
> and enter the (completely different) world of remote debugging.
[Forget what you know, please](http://jeelabs.org/article/1608a/)


## Dream design programming language

* indent- for blocks, instead of brackets/keyword
* Variables are constants by default, mutable is opt-in

* Easy creation of DSLs. TODO: define more clearly

