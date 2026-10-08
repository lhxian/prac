# 树的重心
设树的顶点数量为$n$。
树的中心满足以下性质：
1. 顶点x是树的重心当且仅当以x为根时，$size(y) \le \lfloor x/2\rfloor ,\forall y \in child(x)$。
2. 对于一棵树$T$，定义函数$F(T,x) =\sum w_i d(i,x), \forall i \in T$，其中$d(i,x)$表示顶**i**到**x**的距离，$w(i)$表示顶点**i**的点权，特别的，$d(x,x) =0$，对于树的重心，可以使得$F(T,x)$取值最小。

