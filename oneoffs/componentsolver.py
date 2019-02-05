
import math

import z3

# Return the first "M" models of formula list of formulas F 
# https://stackoverflow.com/questions/11867611/z3py-checking-all-solutions-for-equation
def get_models(F, M):
    result = []
    s = z3.Solver()
    s.add(F)

    print(s)

    while len(result) < M and s.check() == z3.sat:
        m = s.model()
        result.append(m)
        # Create a new constraint the blocks the current model
        block = []
        for d in m:

            # XXX: hack. Should not be possible to change f without R,C changes...
            if str(d).startswith('f_'):
                continue

            # d is a declaration
            if d.arity() > 0:
                raise z3.Z3Exception("uninterpreted functions are not supported")
            # create a constant from declaration
            c = d()
            if z3.is_array(c) or c.sort().kind() == z3.Z3_UNINTERPRETED_SORT:
                raise z3.Z3Exception("arrays and uninterpreted sorts are not supported")
            block.append(c != m[d])
        s.add(z3.Or(block))
    return result


def filter_cutoff(r, c, scale=1.0):
    return scale*1.0/(math.pi*r*c)

def opamp_gain_ni(ri, rf):
    return 1+(rf/ri)

def opamp_gain_inv(ri, rf):
    return rf/ri

e6_series = (1.0, 1.5, 2.2, 3.3, 4.7, 6.8)
e12_series = (1.0, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2, 10.0)

def e_values(start_decade=1, end_decade=6, series=e12_series):
    values = []
    for decade in range(start_decade, end_decade):
        values += [ int(v*10)*10**(decade-1) for v in series ]    
    
    return values

def test_e12_r():

    r = e_values()
    #print(r)


def check_e12():

    r120 = z3.IntVal(120)
    r444 = z3.IntVal(444)
    r1_2 = z3.RealVal(1.2)
    r2_1 = z3.RealVal(2.1)

    # segfaults
    e12 = z3.SetSort(z3.IntSort())
    z3.SetAdd(e12, 12)

    constraints = [
        #z3.IsMember(r1_2, e12), 
        #z3.IsMember(r2_1, e12),
    ]

    s = z3.Solver()
    for c in constraints:
        s.add(c)

    print('checking', s, s.check())
    satisfied = str(s.check()) == 'sat'
    assert satisfied, s

def component_value_constraint(value, valid):
    options = [ value == v for v in valid ]
    return z3.Or(options)
    

# Select components for a 
def opamp_components():

    # Components of our system
    components = dict(
        r_in = z3.Int('r_in'),
        r_f = z3.Int('r_f'),
        c_in = z3.Int('c_in'),
        c_out = z3.Int('c_out'),
        c_f = z3.Int('c_f'),
    )

    # XXX: capacitors in picofarad, to keep them integer valued

    # The foreign systems we are connecting to
    # for example a piezo element on input,
    # and a line-level amplifier on output
    input_z = 1e6
    output_z = 10e3

    # Actual selected
    f_upper = z3.Real('f_upper')
    f_lower = z3.Real('f_lower')
    gain = z3.Real('gain')

    # Functional requirements for our amplifier
    gain_desired = z3.RealVal(22.0)
    gain_tolerance = z3.RealVal(0.05) # relative
    functional_requirements = [
        (gain*(1+gain_tolerance) >= gain_desired),
        (gain*(1-gain_tolerance) <= gain_desired),
        #f_upper > z3.RealVal(10e3),
        #f_upper < z3.RealVal(20e3),
        f_lower < z3.RealVal(10.0),
        f_lower > z3.RealVal(1.0),
    ]

    # How the amplifier circuit works
    # XXX: assumes that the filters are independent (no interactions)
    # reasonable in many practical cases, but not guaranteed
    f_in = z3.Real('f_in')
    f_out = z3.Real('f_out')
    c = components
    circuit_constraints = [
        c['r_f'] == 3300,
        #c['c_f'] > 1,
        c['c_f'] != 0,
        gain == opamp_gain_ni(c['r_in'], c['r_f']),
        #f_in == filter_cutoff(input_z, c['c_in']*z3.RealVal(1e-6)),
        #f_out == filter_cutoff(output_z, c['c_out']*z3.RealVal(1e-6)),
        f_lower < f_in,
        f_lower < f_out,
        f_upper == filter_cutoff(c['r_f'], c['c_f'], z3.RealVal(1e-6)),
    ]
    # TODO: constraint


    # all components must be in E12
    component_values = e_values()
    component_constraints = []
    #component_constraints = [ v > 0 for v in components.values() ]
    #component_constraints += [ v < 1000000000 for v in components.values() ]
    #component_constraints = [ component_value_constraint(v, component_values) for v in components.values() ]
    

    # TODO: match components against others on the board
    # EX: decoupling capacitors

    constraints = functional_requirements + \
        circuit_constraints + \
        component_constraints


    zmodels = get_models(constraints, M=100)

    models = []
    for model in zmodels:
        results = {}
        for var in model:
            results[str(var)] = model[var]
    
        models.append(results) 

    resistors = set([ v for v in models[0].keys() if v.startswith('r_') ])
    capacitors = set([ v for v in models[0].keys() if v.startswith('c_') ])
    print(resistors, capacitors)
    def unique_component_values(res):
        r_values = set(v for k,v in res.items() if k in resistors)
        c_values = set(v for k,v in res.items() if k in capacitors)
        #print(r_values, c_values)
        print()
        return len(r_values) + len(c_values)

    preferred = sorted(models, key=lambda r: unique_component_values(r))

    print(preferred[0])


if __name__ == '__main__':
    opamp_components()


