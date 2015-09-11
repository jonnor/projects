
# Alphabet = Set of possible symbols. { A, B, C }
# Ruleset. Role = symbol -> symbols
# Axiom. Initial symbol string
#
# Actionset. Action = Function (symbol) -> statechange

def lsystem(ruleset, axiom):
    next = []
    if isinstance(axiom, basestring):
        axiom = [ axiom ]
    for a in axiom:
        for s in a:
            new = ruleset.get(s, s)
            next.append(new)
    return next

def draw(sequence, actions):
    import Tkinter as tk
    import turtle
    turtle.reset()
    turtle.speed(0)
    turtle.tracer(1, 0)
    turtle.bgcolor('black')
    turtle.color('white')

    def noop(turtle):
        pass

    for s in sequence:
        for c in s:
            action = getattr(actions, c, noop)
            action(turtle)

    turtle.mainloop()

rot = 360/4
class Actions:
    @staticmethod
    def r(turtle):
        turtle.right(rot)
    @staticmethod
    def l(turtle):
        turtle.left(rot)
    @staticmethod
    def F(turtle):
        turtle.forward(8)

    @staticmethod
    def a(turtle):
        turtle.color("red")
        turtle.circle(10,90)
    @staticmethod
    def b(turtle):
        from math import sqrt
        turtle.color("black")
        l = 5/sqrt(2)
        turtle.forward(l)
        turtle.circle(l, 270)
        turtle.forward(l)
    @staticmethod
    def f(turtle):
        turtle.color("green")
        turtle.forward(10)

def main():
    ruleset = {
        'A': 'frBfr',
        'B': 'AffflfA'
    }
    axiom = 'A'

    #ruleset = {"a" : "afbfa", "b" : "afbfbfbfa" }
    #axiom = "fbfbfbfb"

    max_generation = 100
    target = 8000
    symbols = axiom
    for gen in range(0, max_generation):
        symbols = lsystem(ruleset, symbols)
        nsymbols = len(symbols)
        #print 'gen', gen, 'symbols', nsymbols
        if nsymbols > target:
            break

    draw(symbols, Actions())

if __name__ == '__main__':
    main()
