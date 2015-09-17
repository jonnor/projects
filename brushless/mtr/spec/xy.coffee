
mtr = require '../mtr.coffee'
chai = require 'chai'

cases = [
  { gcode: "G1 X1100 ", x: 1100, y: 0 }
  { gcode: "G1 Y3300 ", x: 1100, y: 3300 }
  { gcode: "G1 X2200 ", x: 2200, y: 3300 }
  { gcode: "G1 Y2200 ", x: 2200, y: 2200 }
]

describe 'XY machine', ->
  machine = new mtr.MachineXY

  describe 'sending serial of gcode commands', ->
    cases.forEach (tcase, idx) ->
      describe "#{tcase.gcode}", () ->

        it "should move to #{tcase.x}, #{tcase.y}", ->
          machine.send tcase.gcode
          pos = machine.position()
          delta = 34 # FIXME: make a lot lower when moving to mm instead of machinecords
          chai.expect(pos.x).to.be.closeTo tcase.x, delta
          chai.expect(pos.y).to.be.closeTo tcase.y, delta
