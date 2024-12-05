import sys

def increasing(nums):
    for a, b in zip(nums[:-1], nums[1:]):
        if b - a <= 0 or b - a > 3:
            return False

    return True

cnt = 0
with open(sys.argv[1], 'r') as file:
    for line in file:
        nums = [int(x) for x in line.split()]

        for i in range(len(nums)):
            tmp = nums[:i] + nums[i+1:]

            if increasing(tmp) or increasing(list(reversed(tmp))):
                cnt += 1
                break

print(cnt)
