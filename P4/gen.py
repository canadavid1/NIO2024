
import itertools
import random

N = 10
M = 30
K = 12

cities = range(10)

pairs = list(itertools.combinations(cities,2))
planes = random.sample(pairs,M)
trains = random.sample(pairs,K)

print(N,M,K)
print(*[f"{a} {b}" for a,b in planes],sep="\n")
print(*[f"{a} {b}" for a,b in trains],sep="\n")