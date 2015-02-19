#!/usr/bin/env python

from serial import Serial

class EnhancedSerial(Serial):
    def __init__(self, *args, **kwargs):
        #ensure that a reasonable timeout is set
        timeout = kwargs.get('timeout',0.1)
        if timeout < 0.01: timeout = 0.1
        kwargs['timeout'] = timeout
        Serial.__init__(self, *args, **kwargs)
        self.buf = ''
        
    def readline(self, maxsize=None, timeout=1):
        """maxsize is ignored, timeout in seconds is the max time that is way for a complete line"""
        tries = 0
        while 1:
            b = self.read(512)
            self.buf += b
            if len(b):
                print b
            pos = self.buf.find('\n')
            if pos >= 0:
                line, self.buf = self.buf[:pos+1], self.buf[pos+1:]
                return line
            tries += 1
            if tries * self.timeout > timeout:
                break
        line, self.buf = self.buf, ''
        return line

    def readlines(self, sizehint=None, timeout=1):
        """read all lines that are available. abort after timout
        when no more data arrives."""
        lines = []
        while 1:
            line = self.readline(timeout=timeout)
            if line:
                lines.append(line)
            if not line or line[-1:] != '\n':
                break
        return lines

def fake_firmware():
    COMPORT = 6
    baud = 962100
    timeout = 3
    s = EnhancedSerial(COMPORT-1, baudrate=baud)

    # firmware handshake response
    fw_init_resp = '\xda\x0f\x03\x00\x00\x00\xe0\x00\x08\x1b\x02\xf2\x00\x00\x00\x00\xff\xff\x00\x00i\xad\x00\x00\xcei\x00\x00\x14\t\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'

    # fw_query1_resp = '\xda\x0f\x03\x00\x00\x00`\x00\x08\x18\x02\xfd\x00\x00\x00\x00\xff\xff\x00\x00i\xad\x00\x00\xcei\x00\x00\x14\t\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
    # seems to be wrong?
    fw_query1_resp = '\xda\x0f\x03\x00\x00\x00\xe0\x00\x08\x17\x03\x01\x00\x00\x00\x00\xff\xff\x00\x01}\xd5\x00\x00\x00\x00\x00\x00\x16\xe9\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'

    # values gotten when sending wrong query1 resp?
    # ['\xf9\x07\x03\xff\xff\xff']
    # ['\xe1\x11\x11\x11\xff\xff\xf9\x07\x03\xff\xff\xff']
    # ['\xe0\xff\xff\xff\xff\xff\xf9\x07\x03\xff\xff\xff']
    # ['\xe1UU\x05\xff\xff\xf9\x07\x03\xff\xff\xff']
    # ['\xe1UU\x05\xff\xff\xf9\x07\x03\xff\xff\xff']
    # ['\xe0\xff\xff\xff\xff\xff\xf9\x07\x03\xff\xff\xff']

    print 'FW response:', len(fw_init_resp), fw_init_resp
    s.write(fw_init_resp)
    print 'SW:', s.readlines(timeout=timeout)

    print 'FW query1 resp:', len(fw_query1_resp), fw_query1_resp
    s.write(fw_query1_resp)
    print 'SW:', s.readlines(timeout=timeout)
    
def fake_software():
    COMPORT = 3
    baud = 962100
    timeout = 3

    s = EnhancedSerial(COMPORT-1, baudrate=baud)

    # software handshake init
    # repeated four times
    sw_init = '\xe0\xff\xff\xff\xff\xff'

    sw_query1 = '\x81\xff\xff\xff\xff\xff\x00\x00i\xad\x00\x00\xcei\x00\x00\x14\t\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
    sw_query1 = '\x81\xff\xff\xff\xff\xff\x00\x01}\xd5\x00\x00\x00\x00\x00\x00\x16\xe9\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'


    
    print 'Init:', len(sw_init), sw_init
    s.write(sw_init)
    print 'Init response:', s.readlines(timeout=timeout)

    print 'Query: ', len(sw_query1), sw_query1
    s.write(sw_query1)
    print 'Query response:', s.readlines(timeout=timeout)

if __name__=='__main__':


    # fake_software()
    fake_firmware()
