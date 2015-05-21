peg = require 'pegjs'
fs = require 'fs'

express = peg.buildParser fs.readFileSync 'expressfbp.peg', {encoding: 'utf-8'}


test = () ->
  fbp = require 'fbp'
  chai = require 'chai'

  describe 'empty input', ->
    it.skip 'should give empty output', ->
      input = ''
      expect = ''
      graph = express.parse input
      expectGraph = fbp.parse expect
      chai.expect(expectGraph).to.eql graph

  describe 'hello world', ->
    it 'should become graph', ->
      input = '40*10'
      expect = """
        '40' -> A 1(Multiply)
        '10' -> B 1
      """
      graph = express.parse input
      expectGraph = fbp.parse expect
      chai.expect(expectGraph).to.eql graph

  describe 'math expression', ->
    it.skip 'should become graph with Multiply and Subtract', ->
      input = '(40*10)-12'
      expect = """
        '40' -> A mul
        '10' -> B mul
        mul OUT -> A sub
        '12' -> B sub
      """
      graph = express.parse input
      expectGraph = fbp.parse expect
      chai.expect(expectGraph).to.eql graph

  describe 'expression with variable', ->
    it 'should become exported port'

test()


