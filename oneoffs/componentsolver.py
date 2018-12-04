
import z3


def filter_cutoff(r, c):
    return 1/(math.pi*r*c)

def opamp_gain_ni(ri, rf):
    return 1+(rf/ri)

def opamp_gain_inv(ri, rf):
    return rf/ri

e6_series = [1.0, 1.5, 2.2, 3.3, 4.7, 6.8]
e12_series = [1.0, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2, 10.0]

def z3_abs(x):
    return z3.If(x >= 0,x,-x)    

# Broken,  no logarithms in Z3...
# https://stackoverflow.com/questions/38605639/how-to-represent-logarithmic-formula-in-z3py
def is_e12(v):
    dec = z3.floor(z3.log(v, 10))
    norm = v/(10**dec)
    return (norm-z3.RealVal(1.2)) == (0.0)

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

    # FIXME: capacitors in picofarad

    # The foreign systems we are connecting to
    # for example a piezo element on input,
    # and a line-level amplifier on output
    input_z = 1e6
    output_z = 10e3

    # Functional requirements for our amplifier
    gain_desired = z3.RealVal(22.0)
    gain_tolerance = z3.RealVal(0.05) # relative
    functional_requirements = [
        ((gain - z3.abs(gain_desired))/gain_desired) < gain_tolerance,
        f_upper < z3.RealVal(10e3),
        f_lower > z3.RealVal(10.0),
    ]

    # How the amplifier circuit works
    # XXX: assumes that the filters are independent (no interactions)
    # reasonable in many practical cases, but not guaranteed
    f_in = z3.RealVal('f_in')
    f_out = z3.RealVal('f_out')
    c = components
    circuit_constraints = [
        gain == opamp_gain_ni(c['r_in'], c['r_f']),
        f_in == filter_cutoff(input_z, c['c_in']),
        f_out == f_filter_cutoff(output_z, c['c_out']),
        f_lower == z3.Min(f_in, f_out),
        f_upper == f_filter_cutoff(c['r_f'], c['c_f']),
    ]

    # all components must be in E12
    component_constraints = [ e12_component(v) for v in components.values() ]

    # TODO: match components against others on the board
    # EX: decoupling capacitors
    # Can z3 minimize unique values? if not, must be done as Python post-process

    constraints = functional_requirements + \
        circuit_constraints + \
        component_constraints

    # Solve
    s = z3.Solver()
    for c in constraints:
        s.add(c)

    satisfied = s.check()
    assert satisfied, s
    model = s.model()    

    for var in model:
        print('{}={}'.format(var, model[var]))


if __name__ == '__main__':
    check_e12()
    #opamp_components()


