#!/usr/bin/env python3

import sys

def parse_line(line):
    module, outputs = line.strip().split(' -> ')
    outputs = outputs.strip().split(', ')
    mod_type = None
    if module[0] in '%&':
        mod_type = module[0]
        module = module[1:]
    return module, (mod_type, outputs)

modules = map(parse_line, sys.stdin)
print('digraph {')
for m, (mod_type, outputs) in modules:
    shape = {'&': 'house', '%': 'box'}
    if mod_type in shape:
        print(f'\t{m} [shape="{shape[mod_type]}"]')
    edge_style = ''
    if mod_type == '&':
        edge_style = '[style="dashed"]'
    print(f'\t{m} -> {{ {" ".join(outputs)} }}', edge_style)
print('}')

