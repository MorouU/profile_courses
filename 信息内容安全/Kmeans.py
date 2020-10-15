import csv
import random, math, os
from time import time

contents = [
    "小牛",
    "SV",
    "小小",
    "船长",
    "兽王",
    "龙骑",
    "发条",
    "全能",
    "神灵",
    "炼金",
    "熊猫",
    "大树",
    "小精灵",
    "人马",
    "伐木机",
    "刚被",
    "海民",
    "大牛",
    "军团",
    "土猫",
    "凤凰",
    "马尔斯",
    "骑手",
    "FW",
    "TF",
    "SK",
    "大鱼",
    "潮汐",
    "SNK",
    "小狗",
    "夜魔",
    "末日",
    "白牛",
    "狼人",
    "SK",
    "尸王",
    "猛犸",
    "LOA",
    "大屁股",
    "DF",
    "小黑",
    "剑圣",
    "POM",
    "水人",
    "猴子",
    "VS",
    "隐刺",
    "火枪",
    "TA",
    "月骑",
    "BH",
    "拍拍",
    "飞机",
    "熊德",
    "小娜迦",
    "巨魔",
    "火猫",
    "大圣",
    "滚滚",
    "血魔",
    "SF",
    "电魂",
    "剧毒",
    "FV",
    "PA",
    "毒龙",
    "骨弓",
    "蜘蛛",
    "蚂蚁",
    "UG",
    "米波",
    "NA",
    "小鱼",
    "大娜迦",
    "魂守",
    "电狗",
    "CM",
    "帕克",
    "蓝猫",
    "WR",
    "宙斯",
    "火女",
    "萨满",
    "TK",
    "先知",
    "小鹿",
    "双头龙",
    "陈",
    "沉默",
    "蓝胖",
    "拉比克",
    "萨尔",
    "光法",
    "天怒",
    "神谕",
    "炸弹人",
    "小仙女",
    "紫猫",
    "祸乱",
    "LICH",
    "LION",
    "WD",
    "谜团",
    "NEC",
    "WLK",
    "QOP",
    "死亡先知",
    "骨法",
    "暗牧",
    "TS",
    "兔子",
    "蝙蝠",
    "AA",
    "卡尔",
    "黑鸟",
    "毒狗",
    "死灵龙",
    "冰龙",
    "墨客",
]

# 创建样本
def create_file(file_name: str, lines: list, rows: int = 15000):
    title = ["击杀", "死亡", "助攻", "输/赢", "所使用英雄/位置"]
    postion = ["1号位", "2号位", "3号位", "4号位", "5号位"]
    heroes = [
        [each for each in lines[:49]],
        [each for each in lines[49 : 49 + 37]],
        [each for each in lines[49 + 37 :]],
    ]

    c = open(
        file_name
        if (file_name.rfind(".") > 0 and file_name.rsplit(".")[1] == "csv")
        else str(time()) * (len(file_name) == 0) + file_name + ".csv",
        "w",
        newline="",
    )
    csv_wirte = csv.writer(c)
    csv_wirte.writerow(title)

    for row in range(rows):
        types = random.randrange(2)
        win = random.randrange(2)
        pos = random.randrange(5)

        kills = (
            (types + win + 2) * ((win / (pos + 1)) * (1 / (pos + 1)))
            + ((5 - pos * win) * (types + pos // 3 + 1)) * (1 / (pos / 3 + 1))
        ) * (win * 1.5) + random.randint(
            0, (5 - pos + types) * random.randint(pos + 1, (pos + 1) * 2)
        ) * abs(
            win - 1
        )
        dead = (
            (
                ((random.randint(0, (pos // 2 + types) * 2)))
                * abs(
                    (
                        math.ceil(pos / 1.5) + random.randint(0, pos) - win * (pos + 1)
                    ).__int__()
                )
                / 3.5
            )
            + (pos + 1)
            / 2.5
            * random.randint(1, math.ceil((pos + 0.5) / 2.75))
            * ((pos + 1) / (((kills + 1) / 1.5) * 2.75))
            + random.randint(0, (5 - pos + types) * 2 + 1) * abs(win)
            + random.randint(0, (5 - pos + types) * 3 + 1) * abs(win - 1)
        )
        a = (
            (
                (kills + random.randint(win, pos + 1) * abs(win - 1))
                / ((dead + 1) * (5 - pos))
            )
            * (win + 1)
            + random.randint(0, ((pos + 1) * (pos / 1.75) * 2 + 1).__int__()) * abs(win)
            + random.randint(0, ((pos + 1) / 1.75 * 2 + types).__int__() * 3 + 5 - pos)
            * abs(win - 1)
        )

        hero = heroes[types][
            (
                (
                    ((kills + a) / (dead + 1)) ** random.randint(0, win + types + 1)
                    + (pos + 1) * (kills * a)
                ).__int__()
                + len(heroes[types])
            )
            % len(heroes[types])
        ]
        csv_wirte.writerow(
            [
                abs((kills * (0.5 + random.random() * 1)).__int__()).__str__(),
                abs((dead * (0.5 + random.random() * 1)).__int__()).__str__(),
                abs((a * (0.5 + random.random() * 1)).__int__()).__str__(),
                win.__str__(),
                hero + " | " + postion[pos],
            ]
        )

    c.close()


# 输出分类结果
def out_file(file_name: str, result: list):
    title = ["分类序号", "击杀", "死亡", "助攻", "输/赢", "所使用英雄/位置"]
    c = open(
        file_name
        if (file_name.rfind(".") > 0 and file_name.rsplit(".")[1] == "csv")
        else str(time()) * (len(file_name) == 0) + file_name + ".csv",
        "w",
        newline="",
    )
    csv_wirte = csv.writer(c)
    csv_wirte.writerow(title)
    tag = 0

    for part in result:
        for row in part:
            row.insert(0, str(tag))
            csv_wirte.writerow(row)
        tag += 1

    c.close()


# 获取csv文件内容
def get_csv_data(file_name: str):
    with open(file_name, "rt") as f:
        read = csv.reader(f)
        readlist = list(read)
        readlist.pop(0)

    return (
        [each[:-1] for each in readlist],
        [each[-1] for each in readlist],
        [each for each in readlist],
    )


# 计算欧几里德度量
def get_distances(p: list, q: list):
    return pow(sum(pow(int(i) - int(j), 2) for i, j in zip(p, q)), 0.5)


# 再计算新质心
def get_average(p: list):
    length = len(p[0]) - 1
    rows = len(p)
    result = [0 for i in range(length)]
    for row in p:
        for i in range(length):
            result[i] += int(row[i])
    return [each / rows for each in result]


# K-MEANS算法
def K_MEANS(all: list, k: int, n: int = 10, f=0.01):
    all_set = []
    finish_set = []
    select_set = all.copy()
    k_set = []
    for i in range(k):
        all_set.append([])
        finish_set.append(False)
        k_set.append(select_set[random.randrange(len(all))][:-1])

    for each in all:
        calc_list = [get_distances(each[:-1], value) for value in k_set]
        all_set[calc_list.index(min(calc_list))].append(each)

    while n > 0:
        for i in range(k):
            if not finish_set[i] and len(all_set[i]) > 0:
                center_ = get_average(all_set[i])
                if (
                    get_distances(center_, k_set[i])
                    / pow(sum(pow(int(each), 2) for each in k_set[i]), 0.5)
                    <= f
                ):
                    finish_set[i] = True
                    continue
                k_set[i] = center_

        all_set = [[] for i in range(k)]
        for each in all:
            calc_list = [get_distances(each[:-1], value) for value in k_set]
            all_set[calc_list.index(min(calc_list))].append(each)

        n -= 1

    return all_set


if __name__ == "__main__":

    # 记录数
    rows = 100

    # 数据文件名称
    file_name = "DOTA2_data_1.csv"

    # 正确阈值(质心值变化率 %)
    f = 0.01

    # 输出文件名称
    ofile_name = "DOTA2_data_out_1.csv"

    print("\n数据创建中·····")
    create_file_start = time()
    create_file(file_name="DOTA2_data_1.csv", lines=contents, rows=rows)
    print("\n创建完毕( %.6fs )·····\n" % (time() - create_file_start))

    print("\n预载数据中·····")
    preload_start = time()
    label_value, label_key, label_all = get_csv_data(file_name=file_name)
    print("\n预载完毕( %.6fs )·····\n" % (time() - preload_start))

    while True:
        try:
            questions = ["K值"]
            lable_test = [input("请输入 " + each + "：") for each in questions]

            calc_start = time()

            print("\n分类数据中·····")
            result = K_MEANS(all=label_all, k=int(lable_test[0]), n=10, f=f)
            print("\n总共耗时：%.6fs ·····" % (time() - calc_start))

            output_start = time()
            print("\n开始输出分类结果·····")
            out_file(file_name=ofile_name, result=result)
            print("\n总共耗时：%.6fs ·····" % (time() - output_start))

            print()
        except Exception as e:
            print("Error => ", e)
        except KeyboardInterrupt:
            break
