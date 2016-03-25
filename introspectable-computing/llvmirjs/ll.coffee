
## LLVM IR generation

# LLVM IR reference, http://llvm.org/docs/LangRef.html
# http://llvm.lyngvig.org/Articles/Mapping-High-Level-Constructs-to-LLVM-IR

# IDEA: allow to pass function, which gets # ref https://msdn.microsoft.com/en-us/magazine/ee291514.aspx

# TODO: support raw() for raw LLVMIR strings

class Builder
  constructor: () ->
  

exports.Builder = Builder




ll = exports


## Kaledeioscope language
# From the LLVM tutorial
# References for the grammar
# https://github.com/hauptmech/my-lil-compiler/blob/master/src/kaleidoscope/kscope.peg (PEG for Narwhal parsergen)
# http://saroth.bitbucket.org/ptyas/tutorial_kaleidoscope.html#parsing (partial PEG for Python)
# https://github.com/wglass/kscope/blob/master/src/parsing/grammar.yy (BNF for bison/flex)


tests = () ->
  chai = require 'chai'

  describe 'Kaleidoscope examples', ->
    describe 'fibonnaci 40', ->
      fib40 = """
      # Compute the x'th fibonacci number.
      def fib(x)
        if x < 3 then
          1
        else
          fib(x-1)+fib(x-2)

      # This expression will compute the 40th number.
      fib(40)
      """
      it 'should parse without error'


      it 'should generate LLVM IR'

      it 'LLVM IR should be valid'

      it 'executing the program returns fib(40)'



main = () ->
  tests()


main()
