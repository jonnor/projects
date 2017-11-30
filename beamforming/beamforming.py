

def check_feasibility_microcontroller():

    # Possible interfaces would be:
    # Sending raw samples over USB
    # Sending N phase-corrected channel data over USB audio class
    # Sending beamformed mono mixdown over USB audio class
    #   using a configurable position setting
    #   or adaptive "voice-tracking"

    mcu_clock = 72e6
    bandwidth_telephone_speech = 3.4e3
    audio_bandwidth = bandwidth_telephone_speech
    sample_rate = 16e3 # samples/second
    microphones = 10
    buffer_time = 5e-3 # seconds
    sample_size = 2 # bytes

    # Bandwidth reqs
    print('Bandwidth', (audio_bandwidth*2) / sample_rate )

    # Sending requirements
    samples_per_second = microphones*sample_rate

    # https://www.pjrc.com/teensy/usb_serial.html
    transferrate_usbserial = 1000e3
    send_capacity = transferrate_usbserial

    bandwidth_utilization = (samples_per_second*sample_size) / send_capacity
    print('send utilization', bandwidth_utilization)

    # CPU capacity
    sample_store_cycles = 100 # how many cycles takes to store one sample into buffer
    buffer_send_cycles = 1000 # how many cycles to send entire buffer (over USB/SPI etc)

    store_cycles_per_second = sample_store_cycles * samples_per_second
    send_cycles_per_second = buffer_send_cycles * (1/buffer_time)
    used_cycles = store_cycles_per_second + send_cycles_per_second
    print('cpu utilization', used_cycles / mcu_clock )

    # Memory requirements
    # http://www.st.com/en/microcontrollers/stm32f103.html?querycriteria=productId=LN1565
    ram_stm32f103r6 = 10e3
    ram_stm32f103rd = 64e3
    ram_available = ram_stm32f103r6

    buffer_size = sample_size * samples_per_second * buffer_time
    buffers = 3 # receiving, waiting, sending

    ram_utilization = (buffers*buffer_size) / ram_available 

    print('ram utilization', ram_utilization)


# TODO: calculate expected phase offset for different sources at different positions

if __name__ == '__main__':
    check_feasibility_microcontroller()

