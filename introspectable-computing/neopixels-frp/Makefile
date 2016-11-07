
CXXFLAGS:=-Wall -Werror -Wno-narrowing

build: neopixels

run: ./neopixels
	./neopixels

dev:
	PATH=${PATH}:/home/${USER}/.local/bin/ when-changed neopixels.cpp make run


