#!/usr/bin/env python


import sys
import os
import time
import serial

if __name__ == '__main__':
    import optparse

    # com0com should be used to forward from port N
    # (configured in Shopbot control sw) to -> COM @swport
    # the Shopbot itself should be connected to @deviceport
    swport = 6
    deviceport = 3
    baud = 962100
    timeout = 0.2

    # connect to serial port
    try:
        deviceSerial = serial.Serial(deviceport-1, baudrate=baud, timeout=timeout)
        swSerial = serial.Serial(swport-1, baudrate=baud, timeout=timeout)
    except serial.SerialException, e:
        sys.stderr.write("Could not open serial port: %s\n" % (e))
        sys.exit(1)

    print "Serial ports opened"
    while True:
        chunkSize = 128
        try:
            # sw -> device
            #print "starting read"
            data = swSerial.read(chunkSize)
            if data:
               deviceSerial.write(data)
               print "->", repr(data)
            # device -> sw
            #print "starting device read"
            data = deviceSerial.read(chunkSize)
            if data:
                swSerial.write(data)
                print "<-", repr(data)
            #print "done read cycle"
        except KeyboardInterrupt:
            break
        except Exception, msg:
            sys.stderr.write('ERROR: %s\n' % msg)


