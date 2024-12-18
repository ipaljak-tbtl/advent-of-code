import sys

with open(sys.argv[1], 'r') as file:
    stones = file.readlines()[0].strip().split()

stones = map(int, stones)

mem = dict()
def blink(stone, i):
    if (stone, i) in mem:
        return mem[(stone, i)]
    if i == 75:
        return 1

    if stone == 0:
        mem[(stone, i)] = blink(1, i+1)
        return mem[(stone, i)]
    if len(str(stone)) % 2 == 0:
        stone = str(stone)

        mem[(stone, i)] = blink(int(stone[:len(stone) // 2]), i+1)
        mem[(stone, i)] += blink(int(stone[len(stone) // 2:]), i+1)
        return mem[(stone, i)]

    mem[(stone, i)] = blink(stone * 2024, i+1)

    return mem[(stone, i)]

sol = 0
for stone in stones:
    sol += blink(stone, 0)

print(sol)

