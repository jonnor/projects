// Experiment in using FRP-like techniques for embedded systems,
// applied to some LED animations

#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <string>

#ifdef HAVE_JSON11
#include <json11.hpp>
#include <json11.cpp>
#endif

static const int NUMBER_OF_LEDS = 10;

struct RgbColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;
#ifdef HAVE_JSON11
    json11::Json to_json() const {
    using namespace json11;
    return Json::object {
            {"r", r},
            {"g", g},
            {"b", b},
    };
}
#endif
};

// Anything that may influence the system (cause state to change)
// Since this is a non-interactive animation, only time
struct Input {
    int timeMs;
    int periodMs;
    RgbColor color;
#ifdef HAVE_JSON11
    json11::Json to_json() const {
    using namespace json11;
    return Json::object {
            {"timeMs", timeMs},
            {"periodMs", periodMs},
            {"color", color.to_json()},
    };
}
#endif
};

// State of system
struct State {
    RgbColor ledColors[NUMBER_OF_LEDS];
};

// Configuration of system
struct LedConfig {
    int pinNumber;
};
struct Config {
    int ledNumber = NUMBER_OF_LEDS;
    LedConfig leds[NUMBER_OF_LEDS];
};

float
onInsideSegment(float position, int index, int steps) {
    const float size = 1.0f/steps;
    const float start = size*index;
    const float end = start+size;
    //printf("light pos=%.2f index=%d, steps=%d size=%.2f, start=%.2f end=%.2f\n",
    //        position, index, steps, size, start, end);
    return (position > start && position < end) ? 1.0f : 0.0f;
}

State
nextState(const Input &input, const State& previous) {
    const int period = input.periodMs;
    const float pos = input.timeMs % period;
    
    State s = previous;


    // TODO: model one point moving back and forth, allow to calculate distance and effects based on this
    // ie. trailing color, with/or without color shift

    const float fromLeft = pos/(period/2.0);
    const float fromRight = 2.0f-(pos/(period/2.0));
    const bool moveRight = ( pos/period > 0.5f );
    const float dist = moveRight ? fromRight : fromLeft;
//    printf("pos=%.2f left=%.2f right=%.2f posp=%.2f moveRight=%s\n",
//        pos, fromLeft, fromRight, pos/period, moveRight ? "true" : "false");
    for (int i=0; i<NUMBER_OF_LEDS; i++) {
        const float mod = onInsideSegment(dist, i, NUMBER_OF_LEDS);
        s.ledColors[i] = { input.color.r*mod, input.color.g*mod, input.color.b*mod };
    }

    return s;
}

// Render using console Truecolor https://gist.github.com/XVilka/8346728
void
colorRenderTerminal(RgbColor color, const std::string &text) {
    const int background = 2;
    printf("\x1b[38;%d;%d;%d;%dm%s\x1b[0m",
           background, color.r, color.g, color.b, text.c_str());

}

bool
realizeState(const State& state, const Config &config) {
    // TODO: implement for hardware
    // TODO: implement via MsgFlo, sending MQTT message to HW-unit
    printf("|%s", "");
    for (int i=0; i<config.ledNumber; i++) {
        colorRenderTerminal(state.ledColors[i], "("+std::to_string(i)+")");
    }
    printf("%s|\n", "");
    return true;
}

// TODO: serialize inputs and outputs as a Flowtrace

int
main(int argc, char *argv[]) {

    std::vector<Input> history;

    const int simulationInterval = 100;
    const int simulationTime = 7*1000;

    int currentTime = 0;
    State previousState;
    Input in = { currentTime, 2100, { 255, 255, 0 } };
#ifdef HAVE_JSON11
    printf("%s", in.to_json().dump().c_str());
#endif
    Config config;
    while (currentTime < simulationTime) {
        in.timeMs = currentTime;
        const State state = nextState(in, previousState);
        realizeState(state, config);
        history.push_back(in);
        previousState = state;
        currentTime += simulationInterval;
    }

}
