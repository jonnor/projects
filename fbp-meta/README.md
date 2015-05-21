
Some experiments in meta operations on FBP programs(graphs),
both in [.JSON format](http://noflojs.org/documentation/json)
and using the [FBP runtime protocol](http://noflojs.org/documentation/protocol)

Expressions DSL
--------------
Takes math-like expressions, parses and 'compiles' it into a FBP graph.

For what is currently implemented, see the tests

    npm test

Refactoring
------------

Possible libraries for doing search/replace on the program in order to
provide large-scale / automated refactoring.

* [JsonPath](http://goessner.net/articles/JsonPath)
* [ObjectPath](http://objectpath.org/)
* [JsPath](https://github.com/dfilatov/jspath)
* [json:select](http://jsonselect.org)
* [JSON Pointer](https://github.com/alexeykuzmin/jsonpointer.js) and [JSON Patch](http://jsonpatch.com/)


