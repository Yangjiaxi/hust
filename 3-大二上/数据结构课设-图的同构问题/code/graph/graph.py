import numpy as np

# 全局计数
GRAPH_COUNT = 'A'


class Graph:
    """
        图
    """

    def __init__(self, edge_dict: dict = {}):
        global GRAPH_COUNT
        self.graph_number = GRAPH_COUNT
        GRAPH_COUNT = chr(ord(GRAPH_COUNT) + 1)

        # 边的字典集，字典元素 节点:[邻接的节点们]
        self.edge_dict = edge_dict
        # 图的节点
        self._nodes = list(edge_dict.keys())
        # 检查 1.标签是连续的自然数 2.无向图的双向连通性
        self.__check_all()
        # 排序标签，以便之后的字典序查找
        self.__sort_adjlist()

    def edge_dict_backup(self):
        self.ed_backup = self.edge_dict

    def edge_dict_load(self):
        self.edge_dict = self.ed_backup

    def __get_name(self):
        return "Graph-{}".format(self.graph_number)

    def __check_label(self, lbl, total_points):
        if not isinstance(lbl, int):
            raise ValueError("Label must be an integer")
        if lbl <= 0:
            raise ValueError("Label should start from 1")
        if lbl > total_points:
            raise ValueError("Label should be continuously and start from 1")

    def __check_all(self):
        _total_points = len(self.edge_dict)
        for u, vs in self.edge_dict.items():
            # check from point as int
            self.__check_label(u, _total_points)

            for v in vs:
                if not u in self.edge_dict.get(v):
                    raise ValueError(
                        "Error input, make sure every edge is undirected")
                # check end point as int
                self.__check_label(v, _total_points)

        # print(self.__get_name(), " All checked!")

    def __sort_adjlist(self):
        self.edge_dict = dict(
            sorted(self.edge_dict.items(), key=lambda item: item[0]))
        for u, vs in self.edge_dict.items():
            self.edge_dict[u] = sorted(vs)

    def do_permutation(self, canlab: dict):
        """
            进行重新打标
        """
        new_one = {}
        for u, vs in self.edge_dict.items():
            new_u = canlab.get(u)
            new_one[new_u] = []
            for v in vs:
                new_one[new_u].append(canlab.get(v))
        self.__check_all()
        self.edge_dict = new_one
        self.__sort_adjlist()

    def get_adj_matrix(self):
        _am = np.zeros((len(self.edge_dict), len(self.edge_dict)),
                       dtype=np.int).tolist()
        for u, vs in self.edge_dict.items():
            for v in vs:
                _am[u - 1][v - 1] = 1
        return _am

    def nodes(self):
        """
            返回节点序列
        """
        return self._nodes

    def number_of_edges(self, u, v):
        """
            返回u与v之间的边数，其实就是判断有没有边，毕竟一个边重复几遍也没用
        """
        if v in self.edge_dict[u]:
            return 1
        return 0

    def order(self):
        return len(self._nodes)

    def degree(self, us=None):
        if us is None:
            us = self._nodes
        if isinstance(us, list):
            res = []
            for u in us:
                res.append((u, len(self.edge_dict[u])))
            return res
        elif isinstance(us, int):
            return len(self.edge_dict[us])

    def __iter__(self):
        return iter(self._nodes)

    def __len__(self):
        return len(self._nodes)

    def __getitem__(self, n):
        return self.edge_dict[n]

    def __repr__(self):
        s = ""
        s += "Graph-{}:\n".format(self.graph_number)
        s += "\t#Vertex : {}\n".format(len(self.edge_dict))
        s += "\t#Edge : {}\n".format(
            sum([len(u) for u in self.edge_dict.values()]))
        s += "\tAdjacency matrix:\n"
        s += "".join(
            ["\t\t" + str(line) + "\n" for line in self.get_adj_matrix()])
        # print(adjmatrix.get_adj_matrix(self.edge_dict))
        return s
