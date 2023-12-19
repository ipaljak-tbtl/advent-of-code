from tqdm import tqdm

import re

LO, HI = 0, 4000

input = open("in", "r").read()
# input = open("small_in", "r").read()

rules, ratings = input.split("\n\n")
pivots = {char: [LO, HI] for char in "xmas"}


def parse_rule(rule):
    global pivots
    ret = []
    tokens = rule.split(",")
    for token in tokens:
        if ":" not in token:
            ret.append(("True", token))
        else:
            ret.append(tuple(token.split(":")))
            delim = "<" if "<" in token else ">"
            char, val = token.split(":")[0].split(delim)
            pivots[char].append(int(val) - (delim == "<"))

    return ret


def parse_rules(rules):
    rule_dict = {}
    for rule in rules.splitlines():
        key, value = rule.strip().split("{")
        rule_dict[key] = parse_rule(value[:-1])
    assert "in" in rule_dict
    return rule_dict


def parse_ratings(ratings):
    ret = []
    for rating in ratings.splitlines():
        x, m, a, s = map(int, re.findall(r"\d+", rating))
        ret.append((x, m, a, s))
    return ret


def is_accepted(x, m, a, s):
    global rules
    curr = "in"
    while curr not in "RA":
        for expr, nxt in rules[curr]:
            if eval(expr):
                curr = nxt
                break
    return curr == "A"


rules = parse_rules(rules)
ratings = parse_ratings(ratings)


def pivots_to_intervals(p):
    return [(l + 1, r - l) for (l, r) in zip(sorted(p), sorted(p)[1:])]


I = [pivots_to_intervals(pivots[char]) for char in "xmas"]

sol = 0
for px, lx in tqdm(I[0]):
    for pm, lm in tqdm(I[1]):
        for pa, la in I[2]:
            for ps, ls in I[3]:
                sol += is_accepted(px, pm, pa, ps) * lx * lm * la * ls

print(sol)
