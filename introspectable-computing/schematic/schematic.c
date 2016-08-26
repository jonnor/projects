
// Deserialize JSON into typed objects
// Supported types declared as JSON schema
// Correspnding C type declaration generated from the schema
// Parser takes

// References
// jsmn: Minimalistic C parser, string-token based https://github.com/zserge/jsmn
// jsmn examples, using state machine, https://alisdair.mcdiarmid.org/jsmn-example/
// js0n, return string, allows matching object/array https://github.com/quartzjer/js0n

// JSON Schema specs
// Core: http://json-schema.org/latest/json-schema-core.html
// Validation: http://json-schema.org/latest/json-schema-validation.html

// Different constraints
//
// Field existance
// Field type: array, boolean, integer, number, null, object, string
// Value equals
// Value
// Value is part of (enum)
// Number: maximum and minimum
// String length, maximum and minimum.
// Array length, maximum and minimum
// Object, number of properires. minProperties, maxProperties

// Skip for now:
// Regular expressions (pattern, patternProperies)
// Value uniquensss. (uniqueItems)
// Strict containment. (additionalProperties)
// Schema/property (dependencies)
// (anyOf)
// (oneOf)
// (not)

// What to do for optional fields?
// - Substitute default value, right away?
// - Mark as not present in generic structure?
// - 

int main() {

}
