k=lambda:map(int,input().split())
N,M=k()
n=[[i]for i in range(N)]
for i in" "*M:
 a,b=k()
 n[a]+=[n[b]]
 n[b]+=[n[a]]
o=[]
for i in n:
 if len(i)<3:o+=[i]
while o:
 k=o.pop()
 if len(k)>1:
  k[1].remove(k)
  if len(k[1])<3:o+=[k[1]]
for i in n:
 if len(i)<3:print(i[0])