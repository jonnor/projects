// Experiment in using FRP-like techniques for embedded systems,
// applied to some LED animations

#include <stdint.h>
#include <assert.h>
#include <stdio.h>

#ifdef DO_SIMULATION
#include <stdio.h>
#include <vector>
#include <string>
#endif

#ifdef HAVE_JSON11
#include <json11.hpp>
#include <json11.cpp>
#endif

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

    std::string to_string() {
        char buf[100];
        snprintf(buf, 100, "RgbColor(%d, %d, %d)", r, g, b);
        return std::string(buf);
    }

    bool operator==(const RgbColor &other) {
        const bool equals = \
            (r == other.r) &&
            (g == other.g) &&
            (b == other.b); 
        return equals;
    }
};

// Anything that may influence the system (cause state to change)
struct Input {
    long timeMs;

    int breathingPeriodMs;
    RgbColor breathingColor;

    int heartRate; // BPM
    RgbColor heartbeatColor;
    int heartbeatLengthMs;

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
    RgbColor ledColor;
};

struct Config {
    bool _;
};

static inline int
mix(uint8_t A, uint8_t B, int a, int b, int total) {
    return (A*a + B*b) / (total);
}

// 
RgbColor
mix(RgbColor a, RgbColor b, int balance) {
    const int total = 1000;
    const int bMix = balance;
    const int aMix = total-balance;
    RgbColor ret = {
        mix(a.r, b.r, aMix, bMix, total),
        mix(a.g, b.g, aMix, bMix, total),
        mix(a.b, b.b, aMix, bMix, total),
    };
    return ret;
}

#define between(val, lower, upper) (val >= lower && val <= upper) ? 1 : 0

State
nextState(const Input &input, const State& previous) {
    // FIXME: the integer math here is not sound, overflows or something
    const int period = input.breathingPeriodMs;
    const long pos = input.timeMs % period;
    
    // Breathing
    const long time = (input.timeMs) ? input.timeMs : 1; // prevent division by zero
    const long mod = (pos*255) / time;
    RgbColor breathing = {
      (uint8_t)(input.breathingColor.r*mod/255),
      (uint8_t)(input.breathingColor.g*mod/255),
      (uint8_t)(input.breathingColor.b*mod/255)
    };

    // Heartbeat
    RgbColor heartbeat = input.heartbeatColor;
    const long heartbeatPeriod = (1000*60)/input.heartRate;
    const long heartbeatPos = input.timeMs % heartbeatPeriod;
    const int heartbeatMix = ( between(heartbeatPos, 1, input.heartbeatLengthMs ) ) ?  1000 : 0;

    // Combine
    State s = previous;
    s.ledColor = mix(breathing, heartbeat, heartbeatMix);

    return s;
}

#ifdef DO_SIMULATION
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
    colorRenderTerminal(state.ledColor, "(#####)\n");
    return true;
}

// TODO: serialize inputs and outputs as a Flowtrace

bool
tests(void) {
    RgbColor midGray = { 100, 100, 100 };
    RgbColor pureRed = { 255, 0, 0 }; 
    
    RgbColor fullA = mix(midGray, pureRed, 0);
    assert(fullA == midGray);

    RgbColor fullB = mix(midGray, pureRed, 1000);
    assert(fullB == pureRed);

    RgbColor mid = mix(midGray, pureRed, 500);
    RgbColor midExpected{ 177, 50, 50 };
    //fprintf(stderr, "%s\n", mid.to_string().c_str());
    assert(mid == midExpected);

    RgbColor quarterA = mix(midGray, pureRed, 250);
    //fprintf(stderr, "%s\n", quarterA.to_string().c_str());
    assert(quarterA == (RgbColor{ 138, 75, 75 }));

    return true;
}

int
main(int argc, char *argv[]) {

    std::vector<Input> history;

    const int simulationInterval = 200;
    const int simulationTime = 5*1000;

    tests();

    int currentTime = 0;
    State previousState;
    Input in = {
        timeMs: currentTime,
        breathingPeriodMs: 2100,
        breathingColor: { 200, 200, 255 },
        heartRate: 80,
        heartbeatColor: { 255, 10, 10 },
        heartbeatLengthMs: 100,
    };
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
#endif
