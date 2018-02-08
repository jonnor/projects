

Input,State

Inputs stream. Comes from hardware normally, but simulated inputs are very useful for testing.
Inputs includes things like current time.
In energy-sensitive and/or high-performance applications input comes from a set of interrupts/timers.
In the common minimal-ISR architecture the interrupt just wakes up device, fetches puts event into an event queue.
The event queue is then processed in mainloop. 
The device then goes back to sleep. 

Nearly always composed of multiple 'sub-streams' of the different inputs.

Sometimes one might want to keep latest input value even if not current.
Maybe people then should need to transfer it into State?


## Requirement / goals

* C++11 without stdlib. Exception-free and no-dynamic-allocations
* Strongly-typed, plain-data objects going in/out of the application code 
* Declarative input/output setup. With reference implementation, at least for Arduino
* Easy (de)serialization of in/out data
* 

Decisions:

* IO modules statically declared.
Solution: Put them into main file as a class

* Avoid dynamic dispatch?
Solution: Using convention that inputs have `get()`, outputs have `update(Foo)`,
but not using a baseclass with virtualfunctions

* How to handle interrupt / non-poll input sources?
IO implementation registers interrupt in setup, has memory internally for storing
Use something like `std::optional` to indicate no-data-available?

* Update generated code without special IDE integration
Use a filesystem watcher on the application file(s),
when input updated, delete old generated file, re-generate and write to disk 

```
class Setupable {
    virtual bool setup() = 0
}
class NoSetup : public Setupable {
    override bool setup() { return true; }
}

template class Result<StateT, OutputT> {
    
}

// Arduino I/O implementations
class TimeMicros : public NoSetup {
    long get() { return micros();  }

}

class DigitalInInterrupt : public Setupable {
    next::optional<bool> data;

public:
    static _isr() {
        data = true;
        //next_input_data_updated();
    }

public:
    DigitalInInterrupt(int pin) {

    }
    virtual bool setup() {
        setupPin(pin, INPUT);
        attachInterrupt(pin, _isr);
        return true;
    }

    optional<bool> get() { 
        const auto current = data;
        data = None;
        return data;
    }
};

class AnalogIn : public Setupable {

public:
    AnalogIn(int pin, bool pullup = false) {

    }
    virtual bool setup() {
        pinSetup(pin, INPUT);
        return true;
    }

    long get() {  return analogRead(pin)  }
};

class DigitalOut : public Setupable {

    virtual bool setup() {
        pinSetup(pin, OUTPUT)
        return true;
    }

    
};

#define NEXT_DEFAULT_SETUP()
void setup() {
    _g_next_io.setup();
}
#endif

#define NEXT_DEFAULT_MAIN(ConfigT, IoDeviceT, StateT, input_func, next_func, output_func)

static IoDeviceT _g_next_io;

void loop() {
    static const ConfigT config;
    static StateT current_state;

    auto in = input_func(io);
    auto next = next_func(config, current_state, in);
    output_func(io, next.outputs);
    current_state = next.state;
}
#endif


#define NEXT_SERIALIZE_IMPLEMENT(...)
#endif
```

## Application code

```
class IoDevices : public Setupable {
public:
    TimeMicros time;
    DigitalIn buttonA(11, true);
    AnalogIn waterLevel(10, true);
    DigitalOut motorOn(0);

    Setupable &setups[] = {
        time,
        buttonA,
        buttonB,
        motorOn,
    };

public:
    override bool setup() {
        for thing : setups {
            thing.setup();
        }
        return true;
    }
};

class Inputs {
    long current_time;
    bool button_a;
    long input_b;
};

Inputs
get_inputs(IoDevices &io)
{
    return {
        current_time: time.get(),
        buttonA: buttonA.get(),
        inputB: buttonB.get(),
    };
}

class Outputs {
    bool motor_on;
};

bool
set_outputs(IoDevices &io, const Outputs &out)
{
    io.motorOn.set(out.motor_on);
    return true;
}
```

Application code
```
#define NEXT_DEBUG_ENABLE

#include <next.hpp>
#include "./next_gen.hpp"

NEXT_AUTO_IODEVICES(IoDevices)
NEXT_AUTO_INPUTS(Inputs, get_input, {
    long time : TimeMicros,
    long water_level : AnalogIn(11),
})
NEXT_AUTO_OUTPUTS(Outputs, set_outputs, {
    bool pump_on : DigitalOut(22),
})

class Config {
    long threshold = 100;
};
class State {
    bool was_on = 100;
};
NEXT_SERIALIZE_IMPLEMENT(State, Config);

Result<State, Outputs>
next(const Config &config, const State &current_state, const Inputs &in)
{ 
    State state = current_state;

    const Outputs out = {
        pump_on: in.water_level > config.threshold;
    };

    return { state: state, outputs: out };
}

NEXT_DEFAULT_SETUP();
NEXT_DEFAULT_MAIN(Config, IoDevices, State, get_inputs, next, set_outputs);
```




## Related

* [C++ support in Jupyter](https://blog.jupyter.org/interactive-workflows-for-c-with-jupyter-fe9b54227d92),
literate programming with live block eval using Xeus/Cling, integrated visualization and widget support.
* [xtensor](https://github.com/QuantStack/xtensor/), C++14 numeric vector processing library.
Numpy-like broadcasting support, lazy-eval support. Python/Numpy integration out-of-box.
* 
