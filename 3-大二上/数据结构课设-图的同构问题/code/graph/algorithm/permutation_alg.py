from itertools import permutations
from ..graph import *
from ..utils import *


class PermutationMatcher:
    def __init__(self, G1: Graph, G2: Graph):
        self.G1 = G1
        self.G2 = G2

    def is_isomorphic(self):
        """
        判断两图是否同构
        """

        # 先进行快速的检查，都是一些最基本的条件

        # 1. 检查节点数是否相同
        if self.G1.order() != self.G2.order():
            return False

        # 2. 检查度序列是否相同
        d1 = sorted(d for n, d in self.G1.degree())  # 度序列
        d2 = sorted(d for n, d in self.G2.degree())  # 度序列
        if d1 != d2:
            return False

        # 3. 尝试返回一个可行解
        try:
            x = next(self.isomorphisms_iter())
            return True
        # 如果一个都不能返回，那完了
        except StopIteration:
            return False

    def isomorphisms_iter(self):
        """
        返回G1与G2间的同构匹配器
        """
        for mapping in self.match():
            yield mapping

    def match(self):
        G_idx = [i + 1 for i in range(len(self.G1.edge_dict))]

        adj_matrix_G2 = self.G2.get_adj_matrix()

        self.G1.edge_dict_backup()
        for current_permutation in iter(permutations(G_idx)):
            self.G1.edge_dict_load()
            current_dict = idx_mapping(current_permutation)
            self.G1.do_permutation(current_dict)
            if self.G1.get_adj_matrix() == adj_matrix_G2:
                self.G1.edge_dict_load()
                yield current_dict
