
## LiveMetalVM

Note: name totally arbitrary so far

## Idea

Live-programming microcontrollers-based devices,
by having the microcontroller serve tools/frontend in JS/HTML
over HTTP to a standard browser.

* Reflash program memory, reload application state
* Virtual machine with bytecode interpreter, reload a 'script'
* Virtual machine with transactional mutable AST
* Partial program memory updates, like swapping out functions


## Possible implementations

### Stack based VM
Forth style

Each cell of the stack has

* a size (in bytes)
* buffer of N bytes
* (maybe) some type annotation? or maybe that should be done by boxing into a cell

Opcodes

* read memory, N bytes starting at P
* write memory, N bytes starting at P

FFI to C code?


## References

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

Ethereum VM

* [Original paper](http://gavwood.com/paper.pdf)
* [Ethereum Script 2.0](https://blog.ethereum.org/2014/02/03/introducing-ethereum-script-2-0/)

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
