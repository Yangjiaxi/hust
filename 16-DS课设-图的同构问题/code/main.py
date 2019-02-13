from copy import deepcopy

import numpy as np

import graph.algorithm as alg
import graph_database as g_db
from graph.graph import Graph
from graph.utils import *

import pickle


def alg_tester(alg_name, graph_g, graph_h, name="None", output=False):
    matcher = alg_name(graph_g, graph_h)
    outer = RunTimer()
    inner = RunTimer()

    cnt = 0
    time_list = []

    ntl = None

    if matcher.is_isomorphic():
        outer.tic()
        inner.tic()
        print(name, "- 两图同构")
        print("字典序映射(G -> H):")
        for res in matcher.isomorphisms_iter():
            cnt += 1
            res = sort_dict_by_key(res)
            inner.toc()
            time_list.append(inner.how())
            if output:
                print("#{:03d}  -  {:.15f}\t{}".format(cnt, time_list[-1], res))
            inner.tic()
        print("可能映射数: ", cnt)
        ntl = np.array(time_list)
        print("\tmean :\t{}\n\tstd  :\t{}".format(ntl.mean(), ntl.std()))
    else:
        print(name, "- 两图不同构")
    outer.toc()
    outer.show()
    return {"total": outer.how(), "mean": ntl.mean(), "std": ntl.std()}


if __name__ == "__main__":
    # edge_dict = {
    #     1: [6, 7, 8, 9],
    #     2: [5, 7, 8],
    #     3: [5, 6, 8],
    #     4: [5, 6, 7],
    #     5: [2, 3, 4],
    #     6: [1, 3, 4],
    #     7: [1, 2, 4],
    #     8: [3, 2, 1],
    #     9: [1]
    # }

    # edge_dict = {
    #     1: [2, 6, 7],
    #     2: [1, 3],
    #     3: [2, 4],
    #     4: [3, 5, 7],
    #     5: [4, 6, 7],
    #     6: [1, 5],
    #     7: [1, 4, 5]
    # }

    # edge_dict = {
    #     1: [8, 9, 10, 11, 13],
    #     2: [8, 9, 10, 14, 15],
    #     3: [8, 9, 12, 13, 14],
    #     4: [8, 9, 12, 13, 15],
    #     5: [10, 11, 12, 14, 15],
    #     6: [10, 11, 13, 14, 15],
    #     7: [11, 12, 13, 14, 15],
    #     8: [16, 1, 2, 3, 4],
    #     9: [16, 1, 2, 3, 4],
    #     10: [16, 1, 2, 5, 6],
    #     11: [16, 1, 5, 6, 7],
    #     12: [16, 3, 4, 5, 7],
    #     13: [1, 3, 4, 6, 7],
    #     14: [2, 3, 5, 6, 7],
    #     15: [2, 4, 5, 6, 7],
    #     16: [8, 9, 10, 11, 12],
    # }

    times = {}
    for name, edge_dict in g_db.graphs:
        print("testing -", name)
        ee = g_db.parse_data(edge_dict)
        times[len(ee)] = {}
        G = Graph(ee)
        # H = Graph(edge_dict_2)
        H = deepcopy(G)
        per = np.random.permutation(list(H.edge_dict.keys()))
        H.do_permutation(idx_mapping(per))
        times[len(ee)]["VF2"] = alg_tester(alg.VF2Matcher, G, H, "VF2", output=False)
        if len(ee) < 30:
            print("-" * 40)
            times[len(ee)]["Ullmann"] = alg_tester(alg.UllmannMatcher, G, H, "Ullmann", output=False)
        print("-" * 80)
        print("\n\n")

    format_print_dict(times)

    pickle.dump(times, open("times_record.svz", "wb"))

    # alg_tester(alg.VF2Matcher, G, H, "VF2", output=True)
    # print("-" * 40)
    # alg_tester(alg.UllmannMatcher, G, H, "Ullmann", output=True)
    # print("-" * 40)
    # alg_tester(alg.PermutationMatcher, G, H, "全排列", output=True)
