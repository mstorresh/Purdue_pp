import numpy as np

print("file name:   ")
file1 = "datos.txt"
in_filetxtlist = open(file1, 'r')

linetx = in_filetxtlist.readlines()

linestxt = linetx[0].strip()

l1 = []

# print(linetx)
for num in linetx:
    # print(str(linetx[num].strip()))
    # l1.append(int(str(linetx[num].strip())))
    # a = linetx[num].strip()
    try: 
        l1.append(int(float(num)))
    except ValueError:
        pass
    # if(a[1]==" "):
    #     pass
    # else:
    #     l1.append(int(a))
  
l1.sort()
b = set(l1)
c = list(b)
# print(set(l1))
# print(len(b))
c.sort()
print(c)

for i in c:
    print(i)
