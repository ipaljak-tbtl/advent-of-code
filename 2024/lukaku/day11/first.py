import sys

with open(sys.argv[1], 'r') as file:
    stones = file.readlines()[0].strip().split()

stones = map(int, stones)

def blink(stones):
    new_stones = []

    for stone in stones:
        if stone == 0:
            new_stones.append(1)
            continue
        if len(str(stone)) % 2 == 0:
            stone = str(stone)
            new_stones.append(int(stone[:len(stone) // 2]))
            new_stones.append(int(stone[len(stone) // 2:]))
            continue

        new_stones.append(stone * 2024)

    return new_stones


for i in range(25):
    stones = blink(stones)

print(len(stones))
