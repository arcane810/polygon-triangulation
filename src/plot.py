import matplotlib.pyplot as plt
f = open("in1", "r")
n = int(f.readline())
points = []
xs = []
ys = []
for i in range(n):
    x, y = map(int, f.readline().split())
    points.append([x, y])
    xs.append(x)
    ys.append(y)
    plt.annotate(str(i), [x, y])
plt.scatter(xs, ys)
for i in range(n):
    xvals = [points[i-1][0], points[i][0]]
    yvals = [points[i-1][1], points[i][1]]
    plt.plot(xvals, yvals)
f.close()
f = open("out1", "r")
m = int(f.readline())
for i in range(m):
    a, b = map(int, f.readline().split())
    xvals = [points[a][0], points[b][0]]
    yvals = [points[a][1], points[b][1]]
    plt.plot(xvals, yvals)

plt.show()
