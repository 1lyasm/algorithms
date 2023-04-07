from numpy import *
from numpy.testing import *
from numpy.random import *
from time import *
import matplotlib.pyplot as plt
from termcolor import colored

def myConv(x, n, y, m):
    s = empty(n + m - 1)
    if (n < m): x, y, m, n = y, x, n, m
    ws, ts, len_ = 0, 0, 1
    for i in range(n + m - 1):
        inv_dot = 0
        for j in range(len_): inv_dot += x[ws + j] * y[ts - j]
        b0, b1, b2 = (i <= m - 2), (m - 1 <= i <= n - 2), (i >= n - 1)
        s[i], ws, ts, len_ = inv_dot, ws + b1 + b2, ts + b0, len_ + b0 - b2
    return s

def test_conv():
    NTEST, SSCALE, MSCALE = int(1), int(1e3), int(1e6)
    inp_shapes = array([randint(1, int(SSCALE) + 1, size=2) for i in range(NTEST)])
    inp = array([(rand(inp_shapes[i][0]) * MSCALE, inp_shapes[i][0], \
            rand(inp_shapes[i][1]) * MSCALE, inp_shapes[i][1]) \
                for i in range(NTEST)], dtype=object)
    for i in inp: assert_allclose(myConv(*i), convolve(i[0], i[2]))
    print("test_conv: OK")


class Signal:
    def __init__(self, name):
        self.name = name
        self.zero_point = None
        self.len_ = None
        self.vals = None

    def print(self):
        print(f"\n{self.name}: [ ", end="")
        for i in range(self.len_):
            if i == self.zero_point: print(colored(self.vals[i], "red"), end=" ")
            else: print(self.vals[i], end=" ")
        print(" ]")
    
    def plot(self):
        pass

        
    def input_len(self):
        self.len_ = int(input(f"{self.name} dizisinin boyutu: "))
    
    def input_vals(self):
        print("\n")
        self.vals = empty(self.len_)
        for i in range(self.len_):
            self.vals[i] = float(input(f"{self.name}[{i}]: "))
        self.zero_point = int(input(f"{self.name}-in sifir noktasi: "))

    def align(self, sig):
        dif = self.zero_point - sig.zero_point
        if dif > 0:
            sig.vals = insert(sig.vals, 0, [0 for i in range(dif)])
            sig.zero_point = self.zero_point
            sig.len_ += dif
        elif dif < 0: 
            dif = abs(dif)
            self.vals = insert(self.vals, 0, [0 for i in range(dif)])
            self.zero_point = sig.zero_point
            self.len_ += dif

def main():
    x, y = Signal("x"), Signal("y")
    x.input_len(), y.input_len()
    x.input_vals(), y.input_vals()
    x.align(y)
    x.print(), y.print()
    print("\n")
    s = Signal("Output signal")
    s.vals = myConv(x.vals, x.len_, y.vals, y.len_)
    s.len_ = len(s.vals)
    s.zero_point = x.zero_point
    s.print()

    test_conv()

main()
