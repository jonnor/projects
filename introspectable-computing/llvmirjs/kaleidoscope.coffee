## Kaledeioscope language
# From the LLVM tutorial
# References for the grammar
# https://github.com/hauptmech/my-lil-compiler/blob/master/src/kaleidoscope/kscope.peg (PEG for Narwhal parsergen)
# http://saroth.bitbucket.org/ptyas/tutorial_kaleidoscope.html#parsing (partial PEG for Python)
# https://github.com/wglass/kscope/blob/master/src/parsing/grammar.yy (BNF for bison/flex)
#
# Indent-significant blocks in PEG.js
# https://www.bountysource.com/issues/1362807-support-parsing-of-indentation-based-languages
# https://gist.github.com/dmajda/04002578dd41ae8190fc
#
# CoffeScript parser with Jison, with indent-based blocks
# http://maxtaco.github.io/coffee-script/documentation/docs/grammar.html

peg = require 'pegjs'
ll = require './ll'
fs = require 'fs'
path = require 'path'

grammarFile = path.join __dirname, 'kaleidoscope.peg'
grammar = fs.readFileSync grammarFile, 'utf-8'

parser = peg.buildParser grammar

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
      it 'should parse without error', ->
        parsed = parser.parse fib40
        chai.expect(parsed[0]).to.have.key 'comment'
        chai.expect(parsed[1]).to.include.key 'def'
      it 'should generate LLVM IR'
      it 'LLVM IR should be valid'
      it 'executing the program returns fib(40)'

tests()
