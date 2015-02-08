
# npm install fdjs coffee-script
# ./node_modules/.bin/coffee fd.coffee

fdjs = require 'fdjs'

solveAll = (space) ->
  search = fdjs.search.depth_first;

  state =
    space: space

  solutions = []
  maxSolutions = 10
  for round in [0...maxSolutions]
    state = search state
    console.log round, state.status
    if state.space.is_solved()
      console.log state.space.solution()
      break

main = () ->
  
  sp = new fdjs.space
  sp.num 'X', 4
    .num 'Z', 5
    .decl 'Y' # unconstrained
    .plus 'X', 'Y', 'Z'
  solveAll sp

main()


