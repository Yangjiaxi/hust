import numpy as np
import seaborn as sb
import matplotlib.pyplot as plt
import subprocess
from tqdm import tqdm


def show(x, y, name="plot", func=None, fit=True):
    if func is not None:
        mx = np.array([func(ix) for ix in x])

    print(x[::int(len(x)/10)])
    print(mx[::int(len(x)/10)])
    print(y[::int(len(x)/10)])

    plt.scatter(mx, y, color='grey', label='Original data(mapped)', s=5)
    if fit:
        A = np.vstack([mx, np.ones(len(x))]).T
        k, b = np.linalg.lstsq(A, y, rcond=None)[0]
        plt.plot(mx, k * mx + b, color='black',
                 label='Fitted line, y = kx + b, k={:.5f}, b={:.2f}'.format(k, b))
    else:
        plt.plot(mx, y, color='grey')
    plt.legend()
    plt.title(name)
    plt.show()


if __name__ == "__main__":
    sb.set()
    plt.rcParams['figure.figsize'] = [8, 4]
    plt.rcParams['figure.dpi'] = 144
    plt.rcParams['font.family'] = "Arial Unicode MS"
    plt.rcParams['axes.unicode_minus'] = False
    sb.set_style("ticks")

    cmd1 = "gcc sum.c -o a.o"
    cmd2 = "./a.o"
    cmd3 = "rm a.o"

    subprocess.call(cmd1, shell=True)

    def run_test(cmd, size, method):
        res = {}
        for mth in method:
            res[mth] = {"size": [], "ticks": []}
            for sz in tqdm(size):
                cmd_s = cmd + " " + str(sz) + " " + str(mth)
                tmp = 0
                times = 20
                for _ in range(times):
                    tmp += int(subprocess.check_output(cmd_s.split(" ")
                                                       ).decode("utf-8"))
                res[mth]["size"].append(sz)
                res[mth]["ticks"].append(tmp / times)
            res[mth]["size"] = np.array(res[mth]["size"])
            res[mth]["ticks"] = np.array(res[mth]["ticks"])
        return res

    res = run_test(cmd2, np.arange(100, 100001, 100), [0])
    show(res[0]["size"], res[0]["ticks"],
         "Integer Sum", lambda t: t, fit=True)
