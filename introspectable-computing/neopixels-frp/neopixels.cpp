// Experiment in using FRP-like techniques for embedded systems,
// applied to some LED animations

#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <string>


static const int NUMBER_OF_LEDS = 4;

// Anything that may influence the system (cause state to change)
// Since this is a non-interactive animation, only time
struct Input {
    int timeMs;
};

// State of system
struct RgbColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};
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
    const int period = 1700;
    const float pos = input.timeMs % period;
    
    State s = previous;
    /*
    const float mod = pos/period;
    s.ledColors[0] = { 255*mod, 255*mod, 100*mod };
    s.ledColors[1] = { 255, 20, 255 };
    s.ledColors[2] = { 10, 20+(100*mod), 255 };
    s.ledColors[3] = { 10, 255, 1 };
    */
    const float fromLeft = pos/(period/2.0);
    const float fromRight = 2.0f-(pos/(period/2.0));
    const bool moveRight = ( pos/period > 0.5f );
    const float dist = moveRight ? fromRight : fromLeft;
//    printf("pos=%.2f left=%.2f right=%.2f posp=%.2f moveRight=%s\n",
//        pos, fromLeft, fromRight, pos/period, moveRight ? "true" : "false");
    for (int i=0; i<NUMBER_OF_LEDS; i++) {
        const float mod = onInsideSegment(dist, i, NUMBER_OF_LEDS);
        s.ledColors[i] = { 255*mod, 255*mod, 0 };
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
    for (int i=0; i<config.ledNumber; i++) {
        colorRenderTerminal(state.ledColors[i], "("+std::to_string(i)+")");
    }
    printf("%s\n", "");
    return true;
}

// TODO: create live/interactive debugger in webui using MsgFlo+FBP-protocol?

int
main(int argc, char *argv[]) {

    std::vector<Input> history;

    int currentTime = 0;
    State previousState = { currentTime };
    Config config;
    while (currentTime < 7*1000) {
        const Input in = { currentTime };
        const State state = nextState(in, previousState);
        realizeState(state, config);
        history.push_back(in);
        previousState = state;
        currentTime += 200;
    }

}
