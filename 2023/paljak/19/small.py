import re

input = open("in", "r").read()

rules, ratings = input.split("\n\n")


def parse_rule(rule):
    ret = []
    tokens = rule.split(",")
    for token in tokens:
        if ":" not in token:
            ret.append(("True", token))
        else:
            ret.append(tuple(token.split(":")))

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

print(sum([is_accepted(*rating) * sum(rating) for rating in ratings]))
