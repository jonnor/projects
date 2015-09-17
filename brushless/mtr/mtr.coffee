if window?.Module
  mtr = window.Module
if not mtr?
  mtr = require './browser/mtr.js'

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

mtr.MachineXY = MachineXY

if module? and module.exports?
  module.exports = mtr
if window?
  window.mtr = mtr


