
## Hosted service
In principle pay per function execution.
Initially through monthly plans with a capped number of executions.

Very limited freemium for testing and easy services.

Premium features:
Dedicated instance, better execution latency and throughput.
Longer log retention.
Bigger/unlimited function size.
Longer execution timeout.
Team ownership for app.
Custom Drivers

Stage 2: Support on-edge usecases.
Open-source exectution engine, connects to managed service
Challenge: Event logs contain a lot of data

## External resources

Lots of work to enable each new type.
Can one piggyback on AWS or Heroku?

# Programming model

## Functions

Pure functions. Gets Input and current State, can return Output and new State.

Functions are cancellable and resumable.

Side-effects are verboten in functions.
Including writing to the file system.

State (Input,Output) can be parametrized based on some (string) identifier. For instance per-device.

State is automatically stored to a backing store.
For instance in Redis.

Inputs,Output are tagged with a schema/type. For example JSON schema and a URL.
Relative type URLs implies a project-local schema,
fully qualified is for 'public' types
 
Input,Output messages are stored in a message queue.
Encapulation. Functions do not know where Input come from, where Output goes, how State is stored.
Or anything about other function executions.

## Drivers

Drivers can (and typically do) perform side-effects.
Sources produce data, based on some external event.
Sinks consume data.
Initial targets: HTTP, MQTT, InfluxDB, Postgres
Drivers have a (static) configuration.
Driver configuration may contain secrets like authentication tokens.
Secrets are automatically encrypted with per-project key.

## Error handling
It is an error to send output not matching schema
It is an error when
Errors have a dedicated schema/type.
By default aborts flow, gets put in dedicated error queue.
? if next consumer

Error types. PreconditionFailed,PostconditionFailed,Exception,UnspecifiedError

## Open questions

Should one allow multiple inputs?
Usecase: combining two or more pieces of data
Challenges: Multiple ways to merge the input streams.
What logic to use/support, how to configure/declare
Workaround: components can persist externally, then query

Should one allow multiple outputs?
Usecase: sending data to multiple places
Challenges:
Need to declare number of 'ports'?
Schema/types need to be per-port?
Workaround 1: each component should ACK with input data
Workaround 2: special-cased splitter functions

Should one allow multiple connections to input?
Usecase: ?
Should one allow multiple connections to output?
Usecase: ?

Should one allow function to output multiple messages?
Usecase: ?
Workaround: special Splitter function


# Execution model

Code executes in an environment, nominally sandboxed.
Code execution support is provided by plugins.
Initial targets: JavaScript, Python

## Project

Git repository backs project
Each function stored in its own file
Each driver configuration is stored in its own file
Input and output drivers are provided by plugins
Plugins are installed via the standard mechanism.
Example: NPM, PyPi
Updates are done atomically as a new git commit.

## Logging

Environment traces the execution as a log of events.
Events contain identifiers for: project, revision, function
Events contain Input,State,Output mappings
In case of errors, this is available for debugging
Event trace is stored initially with full data
When hitting retention limits, thinned to only metadata
When hitting keep limit, event itself is removed


# User interface

Functions and Drivers are connected after eachother
Connected presented as a vertically stack of blocks

    plugin.FunctionName (instance) (logo)
    > (Configuration)
    > (Code)
    
Example:

    http.Request
    >
      method: POST
      path: /endpoint/$deviceid/action


    js.Function
    >
       input: faas:any
       output: FooBar
    >
      const lib = require('foo');
      function entrypoint(input, state) {
        output = foo.bar(input);

        return output;
      }

    http.Response
    >

Next to stack should be statistics for monitoring
Error rate, Time to execute.

Allow to filtering view of stacks/blocks. By search, by selecting
Allow to see a particular execution stream.

UI also allows editing other resources, like schema definitions, code files.
Where resource is used, appears as a link.

Deploying changes
Apply/Update button -> commit message

## Later

Deploying: Propose a change -> creates Pull Request

Should one support a customizable build process?
Usecase: Utilizing existing tools
Challenge: Need hookable build process.
Harder to cache properly

How should one integrate CI and automated tests?
Show external CI status. Can require passing before deploy?

Multiple authentication methods

# Proof of Concept

# Testcases

## IoT device service
    Accept data from multiple devices. MQTT
    Store data to database. InfluxDB?
    Detect events realtime, send notification. Webhook->Slack?
    Query historical data. http.Request

##
Webapp TODOMVC

## Implementation

Executor
One per compute machine
Connects to broker.
Has (weak) affinity to a project. Sharding
Isolates different executions/projects from eachother

DriverRunner
One per compute machine
Connects to broker
Keeps long-running Driver processes up

Manager
One per hosted site
Controls many executor/DriverRunner instances

On new data to function

    Executor gets message from broker
    Executor starts, function execution process
       using process isolation. Ex: nsjail, https://github.com/google/nsjail
       passes input,state to process
       captures stdout,stderr
    

On updating project/app from UI

    Manager pushes code to git
    Manager sends new code (git SHA)

    DriverRunner signals drivers to stop
    DriverRunner kills drivers

    Executor temporarily stops listening for input
    Executor kills in-flight function executions
    Executor updates code on-disk
    Executor resumes listening for input


# Minimal Viable Product
Login/authentication
Payment
??

# Rollout
By invitation.
Request invitation.
Enable paid.

# Security

## Rewards
Function execution credits

