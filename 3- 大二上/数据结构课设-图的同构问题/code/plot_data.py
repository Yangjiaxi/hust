import matplotlib.pyplot as plt
import pickle
from graph.utils import format_print_dict

plt.rcParams["figure.figsize"] = 10, 5
plt.rcParams["figure.dpi"] = 144

if __name__ == "__main__":
    res = pickle.load(open("times_record.svz", "rb"))
    format_print_dict(res)
    VF2_size = [size for size, dd in res.items()]
    VF2_list = [dd["VF2"]["total"] for size, dd in res.items()]
    Ullmann_size = [size for size, dd in res.items() if "Ullmann" in dd]
    Ullmann_list = [dd["Ullmann"]["total"] for size, dd in res.items() if "Ullmann" in dd]
    # plt.scatter(VF2_size, VF2_list, marker="o", label="VF2", c="black")
    plt.scatter(Ullmann_size, Ullmann_list, marker="^", label="Ullmann", c="grey")
    plt.legend()
    plt.show()
