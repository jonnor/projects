
mtr = require '../browser/mtr.js'
chai = require 'chai'

# TODO: move into library
class MachineXY
  constructor: () ->
    @instance = mtr.ccall 'mtr_machine_xy_new', 'number', [], []

  send: (gcode) ->
    mtr.ccall 'mtr_machine_xy_sendgcode', null, ['number', 'string'], [@instance, gcode]
  position: () ->
    str = mtr.ccall 'mtr_machine_xy_current_position', 'string', ['number'], [@instance]
    pos =
      x: parseFloat str.slice(2, 2+9)
      y: parseFloat str.slice(14, 14+9)
    return pos

cases = [
  { gcode: "G1 X1100 ", x: 1100, y: 0 }
  { gcode: "G1 Y3300 ", x: 1100, y: 3300 }
  { gcode: "G1 X2200 ", x: 2200, y: 3300 }
  { gcode: "G1 Y2200 ", x: 2200, y: 2200 }
]

describe 'XY machine', ->
  machine = new MachineXY

  describe 'sending serial of gcode commands', ->
    cases.forEach (tcase, idx) ->
      describe "#{tcase.gcode}", () ->

        it "should move to #{tcase.x}, #{tcase.y}", ->
          machine.send tcase.gcode
          pos = machine.position()
          delta = 34
          chai.expect(pos.x).to.be.closeTo tcase.x, delta
          chai.expect(pos.y).to.be.closeTo tcase.y, delta
