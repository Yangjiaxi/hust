from time import time


def format_print_dict(dd: dict, depth: int = 0) -> None:
    for k, v in dd.items():
        print("\t" * depth, end="")
        print(k, "\t: ", end="")
        if not isinstance(v, dict):
            print(v)
        else:
            print()
            format_print_dict(v, depth + 1)


def sort_dict_by_key(dd: dict) -> dict:
    return dict(sorted(dd.items(), key=lambda kv: kv[0]))


def idx_mapping(ll):
    '''
        Giving [idx...], for each a_i = idx,
        make idx = i
        ATTENTION : label start from 1
    '''
    mapping = {}
    for i, idx in enumerate(ll):
        mapping[idx] = i + 1
    return mapping


class RunTimer:
    """
        计时器
    """

    def __init__(self):
        self.b = 0
        self.e = 0

    def tic(self):
        self.b = time()

    def toc(self):
        self.e = time()

    def show(self):
        print("Time usage: {}".format(self.how()))

    def how(self):
        return self.e - self.b
