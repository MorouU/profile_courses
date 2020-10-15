import csv
import random, math
from collections import Counter
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

# 生成数据文件
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
                * abs((math.ceil(pos/1.5) + random.randint(0, pos) - win * (pos + 1)).__int__())
                / 3.5
            )
            + (pos + 1)/2.5
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
            + random.randint(0, ((pos + 1)/1.75 * 2 + types).__int__() * 3 + 5 - pos) * abs(win - 1)
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
                abs((kills * (.5 + random.random() * 1)).__int__()).__str__(),
                abs((dead * (.5 + random.random() * 1)).__int__()).__str__(),
                abs((a * (.5 + random.random() * 1)).__int__()).__str__(),
                win.__str__(),
                hero + " | " + postion[pos],
            ]
        )

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
    return pow(sum(pow(int(i) - int(j),2) for i, j in zip(p, q)),.5)


# KNN算法
def KNN(test: list, all: list, k: int, show_sort: bool = False):
    key_dict = {}
    min_dict = {}
    result = []

    for line in all:
        if line[-1] not in key_dict.keys():
            key_dict.update({line[-1]: []})
        key_dict[line[-1]].append(get_distances(test, line[:-1]))

    for key, value in key_dict.items():
        min_dict.update({key: min(value)})

    count_of_select = k if not show_sort else len(all)

    for i in range(count_of_select):
        if len(min_dict) != 0:
            minx = min(min_dict, key=min_dict.get)
            result.append(minx)
            key_dict[minx].remove(min_dict[minx])
            if len(key_dict[minx]) != 0:
                min_dict.update({minx: min(key_dict[minx])})
            else:
                del min_dict[minx]

    if k > 0 and k <= count_of_select:
        c = Counter(result[:k]).most_common(k)
        text = c[0][0]
        for i in range(len(c) - 1):
            if c[i][1] > c[i + 1][1]:
                break
            text += "，" + c[i + 1][0]
    else:
        return ""

    return text if not show_sort else (test, result)


"""
def auto_set(value:list):
    length=len(value[0])
    elements={i:[] for i in range(length)}
    minx=[]
    maxx=[]
    for i in range(length):
        elements[i]=[each[i] for each in value]
        minx.append(min(int(each[i]) for each in value))
        maxx.append(max(int(each[i]) for each in value))

    mrange=[j-i for i,j in zip(minx,maxx)]
    auto_list=[[(int(value[i][j])-minx[j])/mrange[j] for j in range(length)] for i in range(len(value))]

    return auto_list,mrange,minx


def test_(file_name:str):
    label_value, label_key, label_all = get_csv_data(file_name)

    test_value=.1

    auto_list, mrange, minx = auto_set(value = label_value)
    auto_list2=[]



    m = len(auto_list)

    for i in range(m):
        auto_list2.append(auto_list[i])
        auto_list2[i].append(label_key[i])

    t_number=int(m*test_value)

    errorc=.0


    for i in range(t_number):
        print(auto_list[i])
        t_result=KNN(test = auto_list[i],all = auto_list2[t_number:],k = 4)
        print("{分类结果：%s \t 真实类别：%s}"%(t_result,label_key[i]))
        if(t_result!=label_key[i]):
            errorc+=1
    print("错误率：%f%%"%((errorc/t_number)*100))


"""

if __name__ == "__main__":

    # 记录数
    rows = 150000

    # 数据文件名称
    file_name = "DOTA2_data_.csv"

    # k值，最好为数据类别的数倍，但得小于等于总行数
    k = int(len(contents) * 2.3333)

    print("\n数据创建中·····")
    create_file_start = time()
    create_file(file_name="DOTA2_data_.csv", lines=contents, rows=rows)
    print("\n创建完毕( %.6fs )·····\n" % (time() - create_file_start))

    print("\n预载数据中·····")
    preload_start = time()
    label_value, label_key, label_all = get_csv_data(file_name=file_name)
    print("\n预载完毕( %.6fs )·····\n" % (time() - preload_start))

    while True:
        try:
            questions = ["击杀数", "死亡数", "助攻数", "输赢情况(输 = 0 | 赢 = 1)"]
            lable_test = [input("请输入 " + each + "：") for each in questions]

            calc_start = time()
            # 可以把 show_sort=True 以看排列全部的顺序，时间可能会久一些
            print(
                "\n你很有可能玩的英雄："
                + KNN(test=lable_test, all=label_all, k=k, show_sort=False)
            )
            print("\n总共耗时：%.6fs ·····" % (time() - calc_start))

            print()
        except Exception as e:
            print("Error => ", e)
        except KeyboardInterrupt:
            break
