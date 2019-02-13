from ..graph import Graph


class VF2Matcher:
    def __init__(self, G1: Graph, G2: Graph):
        # 传入两个图G1 & G2
        self.G1 = G1
        self.G2 = G2

        # 获得两个图的所有节点 (list)
        self.G1_nodes = set(G1.nodes())
        self.G2_nodes = set(G2.nodes())

        # 获取一个字典序(意义上)比较器
        self.key = ({n: i for i, n in enumerate(G2)}).__getitem__

        # 初始化匹配器
        self.init()

    def candidate_pairs_iter(self):
        """
        候选节点对迭代器
        """

        G1_nodes = self.G1_nodes
        G2_nodes = self.G2_nodes

        # 所有不在M_1(s)中的inout_1节点放入T_1^{inout}
        T1_inout = [node for node in self.inout_1 if node not in self.core_1]
        T2_inout = [node for node in self.inout_2 if node not in self.core_2]

        # 如果T1_inout和T2_inout都非空
        # P(s) = T1_inout x {min T2_inout}
        if T1_inout and T2_inout:
            node_2 = min(T2_inout, key=self.key)
            for node_1 in T1_inout:
                yield node_1, node_2

        # 如果T1_inout和T2_inout都空
        # P(s) = (N_1 - M_1) x {min (N_2 - M_2)}
        else:
            other_node = min(G2_nodes - set(self.core_2), key=self.key)
            for node in self.G1:
                if node not in self.core_1:
                    yield node, other_node

        # 对于其他情况，比如只有一个为空，这时没必要再判断，因为一定不能有可以被匹配的节点对了

    def init(self):
        """
        初始化状态表示器

        """

        # core_1是一个字典，core_1[a]=b，表示图G2中节点b与G1中的a相映射
        # core_2亦然
        self.core_1 = {}
        self.core_2 = {}

        # 论文：
        # We define the out-terminal set T_1^{out}(s) as the set of nodes of
        # G1 that are not in M_1(s) but are successors of a node in M_1(s),
        # and define the in-terminal set T_1^{in}(s) as the set of nodes that
        # are not in M1_(s) but are predecessors of a node in M_1(s).
        # Analogously we define T_2^{out}(s) and T_2^{in}(s).

        # 这里定义了四个向量，对于节点(m, n) in 候选节点对
        # T_1^{out}(s)  所有节点p，满足：存在边m->p，且p不在core_1(也就是M_1(s))中
        # T_1^{in}(s)   所有节点p，满足：存在边p->m，且p不在core_1(也就是M_1(s))中
        # T_2^{out}(s)  所有节点q，满足：存在边n->q，且1不在core_2(也就是M_2(s))中
        # T_2^{in}(s)   所有节点q，满足：存在边p->n，且1不在core_2(也就是M_2(s))中

        # 但考虑到我所处理的是无向图的同构匹配问题，将in和out向量合并为inout向量
        # 于是定义
        # 向量序列T_1^{inout}与T_1^{inout}，进行无向图的存储

        # 此处的inout_1与inout_2不是T_x^{inout}
        # 这里的每一个元素或者保存在core_1中，或者保存在T_1^{inout}中，是一个并集
        self.inout_1 = {}
        self.inout_2 = {}

        # 搜索状态表示
        self.state = SSRNode(self)

        # 直接通过mapping来获取
        self.mapping = self.core_1.copy()

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
        # 如果一个都不能返回，那完犊子了
        except StopIteration:
            return False

    def isomorphisms_iter(self):
        """
        返回G1与G2间的同构匹配器
        """
        self.init()
        for mapping in self.match():
            yield mapping

    def match(self):
        """
        递归地搜索可行解，如果找到了，就yield这个可行映射
        每一层递归完成后(下面会标出来)会返回上一层，这时候需要恢复现场
        """

        if len(self.core_1) == len(self.G2):
            # 回溯算法走到了最后的叶子，说明找到了一个可行解，通过yield逐层返回
            self.mapping = self.core_1.copy()
            yield self.mapping
        else:
            # 还没到最深
            # 对于每一个可行的节点对
            for G1_node, G2_node in self.candidate_pairs_iter():
                # 如果他们满足feasibility条件
                if self.feasibility(G1_node, G2_node):
                    newstate = SSRNode(self, G1_node, G2_node)
                    for mapping in self.match():
                        yield mapping
                    # 当前层的递归结束，恢复上一层进入递归前的状态，美名其曰恢复现场
                    newstate.restore()

    def feasibility(self, G1_node, G2_node):
        """
        判断加入(G1_node, G2_node)后会不会无法继续搜索
        """

        # 按照规则一步一步检查，返回false如果任一个条件不被满足，全部满足返回true(在最后)

        # 0. 检查节点的自环数，虽然这是对于无向图的检查算法，但还是加上吧
        if self.G1.number_of_edges(
                G1_node, G1_node) != self.G2.number_of_edges(G2_node, G2_node):
            return False

        # 1. 检查邻居的匹配
        # 对于要检查的两个节点m与n进行匹配检查：
        # 对于所有连接到m的节点p，如果p已经在core_1中，
        # 检查n是不是有这样类似的邻居q (m-p <-类比于-> n-q)
        # 如果没有就返回false
        # 再检查m与p之间的边数是否等于n与q之间的边数
        # 不相等就返回false
        # 1.1 检查m的邻居->n
        for neighbor in self.G1[G1_node]:
            if neighbor in self.core_1:
                if not (self.core_1[neighbor] in self.G2[G2_node]):
                    return False
                elif self.G1.number_of_edges(
                        neighbor, G1_node) != self.G2.number_of_edges(
                            self.core_1[neighbor], G2_node):
                    return False
        # 1.2 检查n的邻居->m
        for neighbor in self.G2[G2_node]:
            if neighbor in self.core_2:
                if not (self.core_2[neighbor] in self.G1[G1_node]):
                    return False
                elif self.G1.number_of_edges(
                        self.core_2[neighbor],
                        G1_node) != self.G2.number_of_edges(neighbor, G2_node):
                    return False

        # 2. 检查m在T_1^{inout}中的邻居数是否与n在T_2^{inout}中的邻居数相同，反过来也查
        cnt1 = 0
        for neighbor in self.G1[G1_node]:
            if (neighbor in self.inout_1) and (neighbor not in self.core_1):
                cnt1 += 1
        cnt2 = 0
        for neighbor in self.G2[G2_node]:
            if (neighbor in self.inout_2) and (neighbor not in self.core_2):
                cnt2 += 1
        if cnt1 != cnt2:
            return False

        # 3. 检查m的邻居中   既 不在core_1中 也 不在T_1^{inout}中 的数量
        # 是不是等于n的邻居中 既 不在core_2中 也 不在T_2^{inout}中 的数量
        cnt1 = 0
        for neighbor in self.G1[G1_node]:
            if neighbor not in self.inout_1:
                cnt1 += 1
        cnt2 = 0
        for neighbor in self.G2[G2_node]:
            if neighbor not in self.inout_2:
                cnt2 += 1
        if cnt1 != cnt2:
            return False

        # 所有条件都满足，这两个节点满足feasibility条件
        return True


class SSRNode:
    """
    用来表示当前的搜索状态，实际上就是一个State Space Representation (SSR树)中的一个搜索节点 
    """

    def __init__(self, matcher, node_g=None, node_h=None):
        """
        初始化状态表示
        传入匹配器与待添加的节点对
        """

        self.matcher = matcher

        # 清空上一次传入的节点对
        self.node_G = None
        self.node_h = None

        # depth是当前的搜索深度
        self.depth = len(matcher.core_1)

        # 初始化
        if node_g is None or node_h is None:
            matcher.core_1 = {}
            matcher.core_2 = {}
            matcher.inout_1 = {}
            matcher.inout_2 = {}

        if node_g is not None and node_h is not None:
            # 添加刚刚传入的这对节点，构成相互映射
            matcher.core_1[node_g] = node_h
            matcher.core_2[node_h] = node_g

            # 用self把这对节点保存起来
            self.node_g = node_g
            self.node_h = node_h

            # 更新两个inout向量
            self.depth = len(matcher.core_1)

            # 先添加传入的两个节点
            if node_g not in matcher.inout_1:
                matcher.inout_1[node_g] = self.depth
            if node_h not in matcher.inout_2:
                matcher.inout_2[node_h] = self.depth

            # 然后添加其他所有节点（与m n邻接且不在映射字典中的）

            # 更新T_1^{inout}向量
            new_nodes = set([])
            for node in matcher.core_1:
                new_nodes.update(  # update: Update a set with the union of itself and others
                    [
                        neighbor
                        for neighbor in matcher.G1[node]  # 列表推导式，对于node的所有邻居a，
                        if neighbor not in matcher.
                        core_1  # 如果邻居a不在core_1(也就是M_1(s))中，就准备添加
                    ])
            # 更新inout_1向量
            for node in new_nodes:
                if node not in matcher.inout_1:
                    matcher.inout_1[node] = self.depth

            # 更新T_2^{inout}向量
            new_nodes = set([])
            for node in matcher.core_2:
                new_nodes.update([
                    neighbor for neighbor in matcher.G2[node]
                    if neighbor not in matcher.core_2
                ])
            for node in new_nodes:
                if node not in matcher.inout_2:
                    matcher.inout_2[node] = self.depth

    def restore(self):
        """
        恢复上一层的状态
        """

        # 删除当前节点对的结果
        if self.node_g is not None and self.node_h is not None:
            del self.matcher.core_1[self.node_g]
            del self.matcher.core_2[self.node_h]

        # 删除进入这一层而添加的新层数
        # 由于使用DFS+回溯来搜索，所以我们相信在进入d层前的
        # 状态中不可能有大于d-1的层数
        for vector in (self.matcher.inout_1, self.matcher.inout_2):
            for node in list(vector.keys()):
                if vector[node] == self.depth:
                    del vector[node]
