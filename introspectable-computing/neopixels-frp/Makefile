
#DEPS_CXXFLAGS=-I./thirdparty/json11 -DHAVE_JSON11
CXXFLAGS:=-Wall -Werror -Wno-narrowing ${DEPS_CXXFLAGS}
CXXFLAGS+=-g

build: neopixels

run: ./neopixels
	./neopixels

dev:
	PATH=${PATH}:/home/${USER}/.local/bin/ when-changed neopixels.cpp make run


