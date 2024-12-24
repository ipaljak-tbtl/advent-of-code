#!/usr/bin/env python3

import sys


def get(gates, in1, in2, op):
    if in1 > in2:
        in1, in2 = in2, in1
    return gates[in1, op, in2]


def exists(gates, in1, in2, op):
    if in1 > in2:
        in1, in2 = in2, in1
    return (in1, op, in2) in gates


def swap_outs(gates, out1, out2):
    for k, v in gates.items():
        if v == out1:
            gates[k] = out2
        elif v == out2:
            gates[k] = out1


inputs1 = []
inputs2 = []
outputs = []

line = next(sys.stdin).strip()
while line:
    wire = line.split(": ")[0]
    if wire.startswith('x'):
        inputs1.append(wire)
    elif wire.startswith('y'):
        inputs2.append(wire)
    line = next(sys.stdin).strip()

inputs1.sort()
inputs2.sort()

gates = {}
for line in sys.stdin:
    ins, out = line.strip().split(" -> ")
    ins = ins.split()
    if ins[0] > ins[2]:
        ins[0], ins[2] = ins[2], ins[0]
    gates[tuple(ins)] = out
    if out.startswith('z'):
        outputs.append(out)

outputs.sort()

print(len(inputs1), len(inputs2), len(outputs))

mixed = set()

in1, in2, out1 = inputs1[0], inputs2[0], outputs[0]
actual_out = get(gates, in1, in2, "XOR")
if actual_out != out1:
    mixed.add(actual_out)
    mixed.add(out1)
    swap_outs(gates, actual_out, out1)
cin = get(gates, in1, in2, "AND")

for in1, in2, out in zip(inputs1[1:], inputs2[1:], outputs[1:]):
    in1_xor_in2 = get(gates, in1, in2, "XOR")
    in1_and_in2 = get(gates, in1, in2, "AND")

    if not exists(gates, in1_xor_in2, cin, "XOR"):
        for k, v in gates.items():
            if v == out:
                assert k[1] == "XOR"
                if cin == k[0]:
                    mixed.add(k[2])
                    mixed.add(in1_xor_in2)
                    swap_outs(gates, in1_xor_in2, k[2])
                    in1_xor_in2 = k[2]
                elif cin == k[2]:
                    mixed.add(k[0])
                    mixed.add(in1_xor_in2)
                    swap_outs(gates, in1_xor_in2, k[0])
                    in1_xor_in2 = k[0]
                elif in1_xor_in2 == k[0]:
                    mixed.add(k[2])
                    mixed.add(cin)
                    swap_outs(gates, cin, k[2])
                    cin = k[2]
                else:
                    mixed.add(k[0])
                    mixed.add(cin)
                    swap_outs(gates, cin, k[0])
                    cin = k[0]
                break

    actual_out = get(gates, in1_xor_in2, cin, "XOR")
    if actual_out != out:
        mixed.add(actual_out)
        mixed.add(out)
        swap_outs(gates, actual_out, out)

    cin_and_in1_xor_in2 = get(gates, cin, in1_xor_in2, "AND")

    if not exists(gates, cin_and_in1_xor_in2, in1_and_in2, "OR"):
        for k, v in gates.items():
            if k[1] == "OR":
                if k[0] == cin_and_in1_xor_in2:
                    mixed.add(k[2])
                    mixed.add(in1_and_in2)
                    swap_outs(gates, k[2], in1_and_in2)
                    in1_and_in2 = k[2]
                elif k[2] == cin_and_in1_xor_in2:
                    mixed.add(k[0])
                    mixed.add(in1_and_in2)
                    swap_outs(gates, k[0], in1_and_in2)
                    in1_and_in2 = k[0]
                elif k[0] == in1_and_in2:
                    mixed.add(k[2])
                    mixed.add(cin_and_in1_xor_in2)
                    swap_outs(gates, k[2], cin_and_in1_xor_in2)
                    cin_and_in1_xor_in2 = k[2]
                elif k[2] == in1_and_in2:
                    mixed.add(k[0])
                    mixed.add(cin_and_in1_xor_in2)
                    swap_outs(gates, k[0], cin_and_in1_xor_in2)
                    cin_and_in1_xor_in2 = k[0]

    cin = get(gates, cin_and_in1_xor_in2, in1_and_in2, "OR")


print(','.join(sorted(mixed)))
