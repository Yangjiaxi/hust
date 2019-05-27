from ..graph import *

import numpy as np


class UllmannMatcher:
    def __init__(self, graph_g: Graph, graph_h: Graph):
        self.G1 = graph_g
        self.G2 = graph_h

        self.G1_adj = self.G1.get_adj_matrix()
        self.G2_adj = self.G2.get_adj_matrix()
        self.cnt = 0
        # 标记列的可用情况，True表示已用
        self.col_used = None
        self.init()

    def init(self):
        self.col_used = [False for _ in range(len(self.G2))]

    def init_m(self):
        # G1 -> G2的映射，V_G1*V_G2的矩阵
        # 匹配结果：
        # 每一行或每一列必须有且仅有一个1
        # M[i, j]=1 => G1中的i与G2中的j对应
        # 图的编号从1开始，M的下标也从0开始
        init_m = np.zeros((len(self.G1), len(self.G2)), dtype=np.int)

        # 初始化M_0
        # 对于每个(i, j)，如果G1_i的度等于G2_j的度，标记M[i, j]为1
        for i in self.G1.nodes():
            for j in self.G2.nodes():
                if self.G1.degree(i) == self.G2.degree(j):
                    init_m[i - 1, j - 1] = 1

        init_m = self.prune(init_m, 0)
        return init_m

    def is_isomorphic(self):
        """
        判断两图是否同构
        """

        if self.G1.order() != self.G2.order():
            return False
        d1 = sorted(d for n, d in self.G1.degree())  # 度序列
        d2 = sorted(d for n, d in self.G2.degree())  # 度序列
        if d1 != d2:
            return False
        try:
            next(self.isomorphisms_iter())
            return True
        except StopIteration:
            return False

    def isomorphisms_iter(self):
        """
        返回G1与G2间的同构匹配器
        """
        self.init()
        for mapping in self.match(self.init_m()):
            yield mapping

    def accept(self, test_m):
        compute_m: np.ndarray = test_m.dot((test_m.dot(self.G2_adj)).T)
        # print(C)
        return (compute_m == self.G1_adj).all()

    def match(self, current_m, depth=0):
        if depth == len(self.G1):
            if self.accept(current_m):
                self.cnt += 1
                rol, col = np.where(current_m == 1)
                res = {a + 1: b + 1 for a, b in zip(rol, col)}
                yield res
        else:
            current_m = self.prune(current_m, depth)
            for i in range(current_m.shape[1]):
                if current_m[depth, i] == 1 and not self.col_used[i]:
                    next_m = np.copy(current_m)
                    next_m[depth, :] = 0
                    next_m[depth, i] = 1
                    self.col_used[i] = True
                    for mapping in self.match(next_m, depth + 1):  # dfs
                        yield mapping

                    self.col_used[i] = False  # 回溯

    def prune(self, current_m, start):
        while True:
            changed = False
            for i in range(start, current_m.shape[0]):
                for j in range(current_m.shape[1]):
                    if current_m[i, j] == 0:
                        continue
                    find = True
                    for x in self.G1.edge_dict[i + 1]:
                        zero = False
                        for y in range(current_m.shape[1]):
                            if current_m[x - 1, y] == 1 and self.G2_adj[y][j] == 1:
                                zero = True
                                break
                        if not zero:
                            find = False
                            break
                    if not find:
                        current_m[i, j] = 0
            if not changed:
                break
        return current_m
