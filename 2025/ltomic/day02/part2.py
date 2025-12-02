import sys

with open(sys.argv[1], 'r') as f:
    lines = f.readlines()

ranges = lines[0].split(',')

ranges = [list(map(int, i.split('-'))) for i in ranges]

def invalid(x):
    divisors = []

    x = str(x)

    for i in range(1, len(x)):
        if len(x) % i == 0:
            divisors.append(i)

    for d in divisors:
        yes = True
        for i in range(len(x) // d - 1):
            if x[i*d:(i+1)*d] != x[(i+1)*d:(i+2)*d]:
                yes = False
                break

        if yes == True:
            return True
            
    return False


sol = 0
for a, b in ranges:
    for x in range(a, b+1):
        if invalid(x):
            sol += x

print(sol)
