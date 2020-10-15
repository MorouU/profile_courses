import random, D_b64

'''
@Description: RSA
@Author: DQ
@LastEditors  : DQ
@Date: 2020-01-04 22:15:21
@LastEditTime : 2020-01-07 17:01:23
'''


class RSA_value(object):
    def __init__( self ):

        self.small_primes = [ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53,
                              59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127,
                              131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191,
                              193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263,
                              269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347,
                              349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421,
                              431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
                              503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593,
                              599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
                              661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751,
                              757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839,
                              853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937,
                              941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013,
                              1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069,
                              1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151,
                              1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223,
                              1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291,
                              1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373,
                              1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451,
                              1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511,
                              1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583,
                              1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657,
                              1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733,
                              1741, 1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811,
                              1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889,
                              1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987,
                              1993, 1997, 1999, 2003, 2011, 2017, 2027, 2029, 2039, 2053,
                              2063, 2069, 2081, 2083, 2087, 2089, 2099, 2111, 2113, 2129,
                              2131, 2137, 2141, 2143, 2153, 2161, 2179, 2203, 2207, 2213,
                              2221, 2237, 2239, 2243, 2251, 2267, 2269, 2273, 2281, 2287,
                              2293, 2297, 2309, 2311, 2333, 2339, 2341, 2347, 2351, 2357,
                              2371, 2377, 2381, 2383, 2389, 2393, 2399, 2411, 2417, 2423,
                              2437, 2441, 2447, 2459, 2467, 2473, 2477, 2503, 2521, 2531,
                              2539, 2543, 2549, 2551, 2557, 2579, 2591, 2593, 2609, 2617,
                              2621, 2633, 2647, 2657, 2659, 2663, 2671, 2677, 2683, 2687,
                              2689, 2693, 2699, 2707, 2711, 2713, 2719, 2729, 2731, 2741,
                              2749, 2753, 2767, 2777, 2789, 2791, 2797, 2801, 2803, 2819,
                              2833, 2837, 2843, 2851, 2857, 2861, 2879, 2887, 2897, 2903,
                              2909, 2917, 2927, 2939, 2953, 2957, 2963, 2969, 2971, 2999,
                              3001, 3011, 3019, 3023, 3037, 3041, 3049, 3061, 3067, 3079,
                              3083, 3089, 3109, 3119, 3121, 3137, 3163, 3167, 3169, 3181,
                              3187, 3191, 3203, 3209, 3217, 3221, 3229, 3251, 3253, 3257,
                              3259, 3271, 3299, 3301, 3307, 3313, 3319, 3323, 3329, 3331,
                              3343, 3347, 3359, 3361, 3371, 3373, 3389, 3391, 3407, 3413,
                              3433, 3449, 3457, 3461, 3463, 3467, 3469, 3491, 3499, 3511,
                              3517, 3527, 3529, 3533, 3539, 3541, 3547, 3557, 3559, 3571,
                              3581, 3583, 3593, 3607, 3613, 3617, 3623, 3631, 3637, 3643,
                              3659, 3671, 3673, 3677, 3691, 3697, 3701, 3709, 3719, 3727,
                              3733, 3739, 3761, 3767, 3769, 3779, 3793, 3797, 3803, 3821,
                              3823, 3833, 3847, 3851, 3853, 3863, 3877, 3881, 3889, 3907,
                              3911, 3917, 3919, 3923, 3929, 3931, 3943, 3947, 3967, 3989,
                              4001, 4003, 4007, 4013, 4019, 4021, 4027, 4049, 4051, 4057,
                              4073, 4079, 4091, 4093, 4099, 4111, 4127, 4129, 4133, 4139,
                              4153, 4157, 4159, 4177, 4201, 4211, 4217, 4219, 4229, 4231,
                              4241, 4243, 4253, 4259, 4261, 4271, 4273, 4283, 4289, 4297,
                              4327, 4337, 4339, 4349, 4357, 4363, 4373, 4391, 4397, 4409,
                              4421, 4423, 4441, 4447, 4451, 4457, 4463, 4481, 4483, 4493,
                              4507, 4513, 4517, 4519, 4523, 4547, 4549, 4561, 4567, 4583,
                              4591, 4597, 4603, 4621, 4637, 4639, 4643, 4649, 4651, 4657,
                              4663, 4673, 4679, 4691, 4703, 4721, 4723, 4729, 4733, 4751,
                              4759, 4783, 4787, 4789, 4793, 4799, 4801, 4813, 4817, 4831,
                              4861, 4871, 4877, 4889, 4903, 4909, 4919, 4931, 4933, 4937,
                              4943, 4951, 4957, 4967, 4969, 4973, 4987, 4993, 4999, 5003,
                              5009, 5011, 5021, 5023, 5039, 5051, 5059, 5077, 5081, 5087,

                              5099, 5101, 5107, 5113, 5119, 5147, 5153, 5167, 5171, 5179,
                              5189, 5197, 5209, 5227, 5231, 5233, 5237, 5261, 5273, 5279,
                              5281, 5297, 5303, 5309, 5323, 5333, 5347, 5351, 5381, 5387,
                              5393, 5399, 5407, 5413, 5417, 5419, 5431, 5437, 5441, 5443,

                              5449, 5471, 5477, 5479, 5483, 5501, 5503, 5507, 5519, 5521,
                              5527, 5531, 5557, 5563, 5569, 5573, 5581, 5591, 5623, 5639,
                              5641, 5647, 5651, 5653, 5657, 5659, 5669, 5683, 5689, 5693,
                              5701, 5711, 5717, 5737, 5741, 5743, 5749, 5779, 5783, 5791,

                              5801, 5807, 5813, 5821, 5827, 5839, 5843, 5849, 5851, 5857,
                              5861, 5867, 5869, 5879, 5881, 5897, 5903, 5923, 5927, 5939,
                              5953, 5981, 5987, 6007, 6011, 6029, 6037, 6043, 6047, 6053,
                              6067, 6073, 6079, 6089, 6091, 6101, 6113, 6121, 6131, 6133,

                              6143, 6151, 6163, 6173, 6197, 6199, 6203, 6211, 6217, 6221,
                              6229, 6247, 6257, 6263, 6269, 6271, 6277, 6287, 6299, 6301,
                              6311, 6317, 6323, 6329, 6337, 6343, 6353, 6359, 6361, 6367,
                              6373, 6379, 6389, 6397, 6421, 6427, 6449, 6451, 6469, 6473,

                              6481, 6491, 6521, 6529, 6547, 6551, 6553, 6563, 6569, 6571,
                              6577, 6581, 6599, 6607, 6619, 6637, 6653, 6659, 6661, 6673,
                              6679, 6689, 6691, 6701, 6703, 6709, 6719, 6733, 6737, 6761,
                              6763, 6779, 6781, 6791, 6793, 6803, 6823, 6827, 6829, 6833,

                              6841, 6857, 6863, 6869, 6871, 6883, 6899, 6907, 6911, 6917,
                              6947, 6949, 6959, 6961, 6967, 6971, 6977, 6983, 6991, 6997,
                              7001, 7013, 7019, 7027, 7039, 7043, 7057, 7069, 7079, 7103,
                              7109, 7121, 7127, 7129, 7151, 7159, 7177, 7187, 7193, 7207,

                              7211, 7213, 7219, 7229, 7237, 7243, 7247, 7253, 7283, 7297,
                              7307, 7309, 7321, 7331, 7333, 7349, 7351, 7369, 7393, 7411,
                              7417, 7433, 7451, 7457, 7459, 7477, 7481, 7487, 7489, 7499,
                              7507, 7517, 7523, 7529, 7537, 7541, 7547, 7549, 7559, 7561,

                              7573, 7577, 7583, 7589, 7591, 7603, 7607, 7621, 7639, 7643,
                              7649, 7669, 7673, 7681, 7687, 7691, 7699, 7703, 7717, 7723,
                              7727, 7741, 7753, 7757, 7759, 7789, 7793, 7817, 7823, 7829,
                              7841, 7853, 7867, 7873, 7877, 7879, 7883, 7901, 7907, 7919,

                              7927, 7933, 7937, 7949, 7951, 7963, 7993, 8009, 8011, 8017,
                              8039, 8053, 8059, 8069, 8081, 8087, 8089, 8093, 8101, 8111,
                              8117, 8123, 8147, 8161, 8167, 8171, 8179, 8191, 8209, 8219,
                              8221, 8231, 8233, 8237, 8243, 8263, 8269, 8273, 8287, 8291,

                              8293, 8297, 8311, 8317, 8329, 8353, 8363, 8369, 8377, 8387,
                              8389, 8419, 8423, 8429, 8431, 8443, 8447, 8461, 8467, 8501,
                              8513, 8521, 8527, 8537, 8539, 8543, 8563, 8573, 8581, 8597,
                              8599, 8609, 8623, 8627, 8629, 8641, 8647, 8663, 8669, 8677,

                              8681, 8689, 8693, 8699, 8707, 8713, 8719, 8731, 8737, 8741,
                              8747, 8753, 8761, 8779, 8783, 8803, 8807, 8819, 8821, 8831,
                              8837, 8839, 8849, 8861, 8863, 8867, 8887, 8893, 8923, 8929,
                              8933, 8941, 8951, 8963, 8969, 8971, 8999, 9001, 9007, 9011,

                              9013, 9029, 9041, 9043, 9049, 9059, 9067, 9091, 9103, 9109,
                              9127, 9133, 9137, 9151, 9157, 9161, 9173, 9181, 9187, 9199,
                              9203, 9209, 9221, 9227, 9239, 9241, 9257, 9277, 9281, 9283,
                              9293, 9311, 9319, 9323, 9337, 9341, 9343, 9349, 9371, 9377,

                              9391, 9397, 9403, 9413, 9419, 9421, 9431, 9433, 9437, 9439,
                              9461, 9463, 9467, 9473, 9479, 9491, 9497, 9511, 9521, 9533,
                              9539, 9547, 9551, 9587, 9601, 9613, 9619, 9623, 9629, 9631,
                              9643, 9649, 9661, 9677, 9679, 9689, 9697, 9719, 9721, 9733,

                              9739, 9743, 9749, 9767, 9769, 9781, 9787, 9791, 9803, 9811,
                              9817, 9829, 9833, 9839, 9851, 9857, 9859, 9871, 9883, 9887,
                              9901, 9907, 9923, 9929, 9931, 9941, 9949, 9967, 9973 ]

    # 递归求逆元
    def gcd( self, a, b ):  # 扩展欧几里算法优化版
        if (b == 0):
            return 1, 0
        else:
            x0, y0 = self.gcd(b, a % b)  # 递归计算a*x0 + b*y0=1(a与b互质)中的x0与y0值
            return y0, x0 - a // b * y0

    # 快速幂模算法
    def mod_quick( self, a, b, c ):  # a b c依次为基数 幂数 以及 模数
        array = bin(b)[ 2: ][ ::-1 ]  # 取幂数的二进制，并将其倒叙（从左到右→从小到大）
        n = len(array)  # 获取二进制数位数（也就是b的bits）
        result = 1  # 初始化结果
        if (array[ 0 ] == '1'):  # 这里以字符串的思想去判断，规避了int()的时间，若 b 的二进制首位为 1，将 a 填入列表
            result = a

        for _ in range(1, n):  # 循环遍历 b 的所有二进制位数
            next = (a * a) % c  # 循环幂模运算
            if (array[ _ ] == '1'):  # 若 b 的该二进制位值为 1，则进行计算
                result = (result * next) % c
            a = next  # a 重定向幂模结果
        result %= c
        return result  # 返回结果

    # 判断大质数(拉宾米勒素性判断)
    def bool_p( self, N, X = 5 ):
        M = (N - 1) // 2  # N=(2**r)*M+1的反算
        r = 1
        while (not M % 2):  # 保证取到奇数M
            M //= 2
            r += 1
        for _ in range(X):
            A = random.randint(2, N - 1)  # 取随机数A
            get = self.mod_quick(A, M, N)  # 第四步测试 A**M%N==1则算通过1次测试
            if (get != 1):  # 此时get=(A**M)%N
                i = 0  # 进行第三步测试 A**((2**i)*M)%N=N-1 i<r
                while (get != N - 1):
                    if (i >= r - 1):  # 若i>=r则不通过
                        return False
                    else:
                        i += 1
                        get = (get * get) % N  # get=(A**(M*2**i))%N
        return True

    # 大质数生成(取P或Q的值)
    def get_p( self, size = 1024, seed = 0 ):
        random.seed = seed  # 设置随机种子保证取值广泛性
        while True:
            bool = False
            n = random.randint(2 ** (size - 2), 2 ** (size - 1)) * 2 + 1  # 保证奇数
            if (n % 6 != 5 and n % 6 != 1):  # 6左右判断法，大于4的素数必然是6的倍数-1或+1
                continue
            for _ in self.small_primes:  # 模小质数表判断
                if (not n % _):  # 若能模进则不为质数
                    bool = True
                    break
            if (not bool):
                if (self.bool_p(n)):  # 进行拉宾米勒的素性判断
                    return n

    def q( self, size = 1024, seed = 0 ):
        return self.get_p(size = size, seed = seed)

    def p( self, size = 1024, seed = 0 ):
        return self.get_p(size = size, seed = seed)

    # 求E值与D值
    def e_d( self, N, size = 16, seed = 0 ):
        if (N != 0):
            random.seed = (seed)  # 设置随机种子
            while True:
                e = self.get_p(size = size)  # 生成指定位的质数E，直至能够满足要求为止
                d = self.gcd(e, N)[ 0 ]
                if (d < 0):  # 若E与M(P-1)*(Q-1)组合不存在正确的D值则继续生成E
                    continue
                else:
                    return e, d  # 若存在正确的D值则返回E值和D值
        else:
            return 0


def modq( a, b, c ):
    array = bin(b)[ 2: ][ ::-1 ]
    n = len(array)
    result = 1
    if (array[ 0 ] == '1'):
        result = a
    for _ in range(1, n):
        next = (a * a) % c
        if (array[ _ ] == '1'):
            result = (result * next) % c
        a = next
    result %= c
    return result


def hex_add_zero( i, byte = False ):  # 补0 同时返回2进制流
    h = hex(i)[ 2: ]
    result = bytes( )

    if (len(h) % 2):
        h = "0" + h

    if (byte):
        for _ in range(len(h) // 2):
            result += bytes(chr(int(h[ _ * 2:(_ + 1) * 2 ], 16)).encode("latin1"))
        return result
    else:
        return h


def add_zero( group = [ "", b"", 0 ] ):
    if (int(group[ 0 ][ 0:2 ], 16) > 0x80):
        group[ 0 ] = "00" + group[ 0 ]
        group[ 1 ] = bytes("\x00".encode("latin1")) + group[ 1 ]
        group[ 2 ] += 1
    return group[ 0 ], group[ 1 ], group[ 2 ]


def output_public( data = { 'n': 0, 'e': 0 } ):  # 这个是公钥的pem

    if (data[ 'e' ] == 0 or data[ 'n' ] == 0):
        return -1

    const = "\x06\x09\x2a\x86\x48\x86\xf7\x0d\x01\x01\x01\x05\x00"  # 固定值
    tag = "\x02"  # 数据flag
    tagh = "\x30"  # 标注flag
    tagh2 = "\x03"

    ec = hex_add_zero(data[ 'e' ])
    nc = hex_add_zero(data[ 'n' ])

    e = hex_add_zero(data[ 'e' ], byte = True)
    n = hex_add_zero(data[ 'n' ], byte = True)

    e_len = len(ec) // 2
    n_len = len(nc) // 2

    nc, n, n_len = add_zero([ nc, n, n_len ])

    # 求e部分
    if (e_len < 0x80):
        publicE = bytes((tag + chr(int("0x%02x" % e_len, 16))).encode("latin1"))
    else:
        publicE = bytes(
            (tag + chr(int("0x8%d" % ((len(hex(e_len)[ 2: ]) + 1) // 2), 16))).encode("latin1")) + hex_add_zero(e_len,
                                                                                                                byte = True)

    publicE = publicE + e

    # 求n部分
    if (n_len < 0x80):
        publicN = bytes((tag + chr(int("0x%02x" % n_len, 16))).encode("latin1"))
    else:
        publicN = bytes(
            (tag + chr(int("0x8%d" % ((len(hex(n_len)[ 2: ]) + 1) // 2), 16))).encode("latin1")) + hex_add_zero(n_len,
                                                                                                                byte = True)

    publicN = publicN + n

    publicMain = publicN + publicE

    # 求头4部分
    h4_len = len(publicMain)
    if (h4_len < 0x80):
        publich4 = bytes((tagh + chr(int("0x%02x" % h4_len, 16))).encode("latin1"))
    else:
        publich4 = bytes(
            (tagh + chr(int("0x8%d" % ((len(hex(h4_len)[ 2: ]) + 1) // 2), 16))).encode("latin1")) + hex_add_zero(
            h4_len, byte = True)

    # 求头3部分
    h3_len = len(publicMain) + len(publich4) + 1
    if (h3_len < 0x80):
        publich3 = bytes((tagh2 + chr(int("0x%02x" % h3_len, 16))).encode("latin1"))
    else:
        publich3 = bytes(
            (tagh2 + chr(int("0x8%d" % ((len(hex(h3_len)[ 2: ]) + 1) // 2), 16))).encode("latin1")) + hex_add_zero(
            h3_len, byte = True) + bytes("\x00".encode("latin1"))

    # 求头2部分
    h2_len = 0x0d
    publich2 = bytes((tagh + chr(int("0x%02x" % h2_len, 16)) + const).encode("latin1"))

    # 求头1部分
    h1_len = len(publicMain) + len(publich4) + len(publich3) + len(publich2)
    if (h1_len < 0x80):
        publich1 = bytes((tagh + chr(int("0x%02x" % h1_len, 16))).encode("latin1"))
    else:
        publich1 = bytes(
            (tagh + chr(int("0x8%d" % ((len(hex(h1_len)[ 2: ]) + 1) // 2), 16))).encode("latin1")) + hex_add_zero(
            h1_len, byte = True)

    # 得到总的流
    Public = publich1 + publich2 + publich3 + publich4 + publicMain
    return Public


def output_private( data = { 'n': 0, 'e': 0, 'd': 0, 'p': 0, 'q': 0 } ):
    tag = "\x02"
    ver = "\x00"
    tagh = "\x30"

    exponent1 = data[ 'd' ] % (data[ 'p' ] - 1)
    exponent2 = data[ 'd' ] % (data[ 'q' ] - 1)
    coefficient = (data[ 'q' ] - 1) % data[ 'p' ]

    nc = hex_add_zero(data[ 'n' ])
    ec = hex_add_zero(data[ 'e' ])
    dc = hex_add_zero(data[ 'd' ])
    pc = hex_add_zero(data[ 'p' ])
    qc = hex_add_zero(data[ 'q' ])

    ep1c = hex_add_zero(exponent1)
    ep2c = hex_add_zero(exponent2)
    coec = hex_add_zero(coefficient)

    n = hex_add_zero(data[ 'n' ], byte = True)
    e = hex_add_zero(data[ 'e' ], byte = True)
    d = hex_add_zero(data[ 'd' ], byte = True)
    p = hex_add_zero(data[ 'p' ], byte = True)
    q = hex_add_zero(data[ 'q' ], byte = True)

    ep1 = hex_add_zero(exponent1, byte = True)
    ep2 = hex_add_zero(exponent2, byte = True)
    coe = hex_add_zero(coefficient, byte = True)

    n_len = len(nc) // 2
    e_len = len(ec) // 2
    d_len = len(dc) // 2
    p_len = len(pc) // 2
    q_len = len(qc) // 2

    ep1_len = len(ep1c) // 2
    ep2_len = len(ep2c) // 2
    coe_len = len(coec) // 2

    nc, n, n_len = add_zero([ nc, n, n_len ])
    dc, d, d_len = add_zero([ dc, d, d_len ])
    qc, q, q_len = add_zero([ qc, q, q_len ])
    pc, p, p_len = add_zero([ pc, p, p_len ])
    ep1c, ep1, ep1_len = add_zero([ ep1c, ep1, ep1_len ])
    ep2c, ep2, ep2_len = add_zero([ ep2c, ep2, ep2_len ])
    coec, coe, coe_len = add_zero([ coec, coe, coe_len ])

    # 求n部分
    if (n_len < 0x80):
        privateN = bytes((tag + chr(int("0x%02x" % n_len, 16))).encode("latin1"))
    else:
        privateN = bytes(
            (tag + chr(int("0x8%d" % ((len(hex(n_len)[ 2: ]) + 1) // 2), 16))).encode("latin1")) + hex_add_zero(n_len,
                                                                                                                byte = True)
    privateN += n

    # 求e部分
    if (e_len < 0x80):
        privateE = bytes((tag + chr(int("0x%02x" % e_len, 16))).encode("latin1"))
    else:
        privateE = bytes(
            (tag + chr(int("0x8%d" % ((len(hex(e_len)[ 2: ]) + 1) // 2), 16))).encode("latin1")) + hex_add_zero(e_len,
                                                                                                                byte = True)
    privateE += e

    # 求d部分
    if (d_len < 0x80):
        privateD = bytes((tag + chr(int("0x%02x" % d_len, 16))).encode("latin1"))
    else:
        privateD = bytes(
            (tag + chr(int("0x8%d" % ((len(hex(d_len)[ 2: ]) + 1) // 2), 16))).encode("latin1")) + hex_add_zero(d_len,
                                                                                                                byte = True)
    privateD += d

    # 求p部分
    if (p_len < 0x80):
        privateP = bytes((tag + chr(int("0x%02x" % p_len, 16))).encode("latin1"))
    else:
        privateP = bytes(
            (tag + chr(int("0x8%d" % ((len(hex(p_len)[ 2: ]) + 1) // 2), 16))).encode("latin1")) + hex_add_zero(p_len,
                                                                                                                byte = True)
    privateP += p

    # 求q部分
    if (q_len < 0x80):
        privateQ = bytes((tag + chr(int("0x%02x" % q_len, 16))).encode("latin1"))
    else:
        privateQ = bytes(
            (tag + chr(int("0x8%d" % ((len(hex(q_len)[ 2: ]) + 1) // 2), 16))).encode("latin1")) + hex_add_zero(q_len,
                                                                                                                byte = True)
    privateQ += q

    # 求ep1部分
    if (ep1_len < 0x80):
        privateEP1 = bytes((tag + chr(int("0x%02x" % ep1_len, 16))).encode("latin1"))
    else:
        privateEP1 = bytes(
            (tag + chr(int("0x8%d" % ((len(hex(ep1_len)[ 2: ]) + 1) // 2), 16))).encode("latin1")) + hex_add_zero(
            ep1_len, byte = True)
    privateEP1 += ep1

    # 求ep2部分
    if (ep2_len < 0x80):
        privateEP2 = bytes((tag + chr(int("0x%02x" % ep2_len, 16))).encode("latin1"))
    else:
        privateEP2 = bytes(
            (tag + chr(int("0x8%d" % ((len(hex(ep2_len)[ 2: ]) + 1) // 2), 16))).encode("latin1")) + hex_add_zero(
            ep2_len, byte = True)
    privateEP2 += ep2

    # 求coe部分
    if (coe_len < 0x80):
        privateCOE = bytes((tag + chr(int("0x%02x" % coe_len, 16))).encode("latin1"))
    else:
        privateCOE = bytes(
            (tag + chr(int("0x8%d" % ((len(hex(coe_len)[ 2: ]) + 1) // 2), 16))).encode("latin1")) + hex_add_zero(
            coe_len, byte = True)
    privateCOE += coe

    # 求版本头
    version = bytes((tag + "\x01" + ver).encode("latin1"))

    # 求文件头部分
    privateMain = len(version) + len(privateN) + len(privateE) + len(privateD) + len(privateP) + len(privateQ) + len(
        privateEP1) + len(privateEP2) + len(privateCOE)

    if (privateMain < 0x80):
        privateheader = bytes((tagh + chr(int("0x%02x" % privateMain, 16))).encode("latin1"))
    else:
        privateheader = bytes(
            (tagh + chr(int("0x8%d" % ((len(hex(privateMain)[ 2: ]) + 1) // 2), 16))).encode("latin1")) + hex_add_zero(
            privateMain, byte = True)

    Private = privateheader + version + privateN + privateE + privateD + privateP + privateQ + privateEP1 + privateEP2 + privateCOE
    return Private


def input_public( inf = "", public = "", b64de = True ):
    start = b"-----BEGIN PUBLIC KEY-----"  # pem公钥文件头
    end = b"-----END PUBLIC KEY-----"  # pem公钥文件尾
    const = "06092a864886f70d0101010500"  # 固定值
    tag = 0x02
    tagh = 0x30
    tagh2 = 0x03

    publicdata = bytes( )

    if (inf != ""):
        try:
            file = open(inf, "rb")
            read = file.readlines( )
            if (start in read[ 0 ] and end in read[ -1 ]):  # 文件格式必须正确
                read.pop(0)
                read.pop( )
                for line in read:
                    if (line[ -2 ] == 0x0d and line[ -1 ] == 0x0a):
                        publicdata += line[ :-2 ]  # 读base64转码的主要内容
                    else:
                        publicdata += line[ :-1 ]
            else:
                return 0  # 格式错误
        except Exception:
            return -1  # 操作错误
    if (public != ""):
        publicdata = public

    if (b64de):  # pem一般来说都是用base64将内容转码过的，需要解码
        publicdata = D_b64.deb64(publicdata)
    public_len = len(publicdata)

    headers = [ 0, public_len, public_len, public_len ]
    publich = [ public_len, public_len ]
    Public = [ ]

    for byte in range(public_len):

        if (len(headers) > 0):
            if (byte == headers[ 0 ]):
                if (len(headers) == 3):  # 若是头2，则是特殊情况
                    tmp = ""
                    for each in range(15):
                        tmp += "%02x" % int(hex(publicdata[ each + headers[ 0 ] ])[ 2: ], 16)
                    if (tmp == "300d" + const):
                        next = byte + 15
                        headers.pop(0)
                        headers[ 0 ] = next
                        continue
                    else:
                        return 0  # 格式错误

                if (publicdata[ headers[ 0 ] ] == tagh or publicdata[ headers[ 0 ] ] == tagh2):
                    if (len(headers) == 2 and publicdata[ headers[ 0 ] ] == tagh):
                        return 0  # 格式错误
                    len_1 = publicdata[ headers[ 0 ] + 1 ]
                    len_2 = 0
                    len_3 = 0
                    if (len_1 > 0x80):
                        len_2 = len_1 - 0x80
                        tmp = ""
                        for each in range(len_2):
                            tmp += "%02x" % int(hex(publicdata[ 2 + each + byte ])[ 2: ], 16)
                        len_3 = int(tmp, 16)
                    else:
                        len_3 = len_1
                    if (len_3 == public_len - (byte + 2 + len_2)):
                        headers.pop(0)
                        next = byte + 2 + len_2
                        if (len(headers) == 1):  # \x00
                            next += 1
                        elif (len(headers) == 0):
                            publich[ 0 ] = next
                            continue
                        headers[ 0 ] = next
                    else:
                        return 0  # 格式错误
                else:
                    return 0  # 格式错误
        else:
            if (byte == publich[ 0 ] and publicdata[ publich[ 0 ] ] == tag):
                len_1 = publicdata[ publich[ 0 ] + 1 ]
                len_2 = 0
                len_3 = 0
                if (len_1 > 0x80):
                    len_2 = len_1 - 0x80
                    tmp = ""
                    for each in range(len_2):
                        tmp += "%02x" % int(hex(publicdata[ 2 + each + byte ])[ 2: ], 16)
                    len_3 = int(tmp, 16)
                else:
                    len_3 = len_1
                tmp = ""
                for by in range(len_3):
                    tmp += "%02x" % int(hex(publicdata[ 2 + by + byte + len_2 ])[ 2: ], 16)
                Public.append(int(tmp, 16))

                publich.pop(0)

                if (len(publich) == 0):
                    break
                next = byte + 2 + len_2 + len_3
                publich[ 0 ] = next

            elif (publicdata[ publich[ 0 ] ] != tag):
                return 0  # 格式错误

    return Public


def input_private( inf = "", private = "", b64de = True ):
    start = b"-----BEGIN RSA PRIVATE KEY-----"  # pem密钥文件头
    end = b"-----END RSA PRIVATE KEY-----"  # pem密钥文件尾
    tag = 0x02

    privatedata = bytes( )

    if (inf != ""):
        try:
            file = open(inf, "rb")
            read = file.readlines( )
            if (start in read[ 0 ] and end in read[ -1 ]):  # 文件格式必须正确
                read.pop(0)
                read.pop( )
                for line in read:
                    if (line[ -2 ] == 0x0d and line[ -1 ] == 0x0a):
                        privatedata += line[ :-2 ]  # 读base64转码的主要内容
                    else:
                        privatedata += line[ :-1 ]
            else:
                return 0  # 格式错误
        except Exception:
            return -1  # 操作错误
    if (private != ""):
        privatedata = private

    if (b64de):  # pem一般来说都是用base64将内容转码过的，需要解码
        privatedata = D_b64.deb64(privatedata)

    private_len = len(privatedata)

    headers = [ 0, private_len ]
    privateh = [ private_len, private_len, private_len, private_len, private_len, private_len, private_len,
                 private_len ]
    Private = [ ]

    for byte in range(private_len):

        if (len(headers) > 0):
            if (byte == headers[ 0 ]):
                if (len(headers) == 2):  # 抓文件头
                    if (privatedata[ headers[ 0 ] ] == 0x30):
                        len_1 = privatedata[ headers[ 0 ] + 1 ]
                        len_2 = 0
                        len_3 = 0
                        if (len_1 > 0x80):
                            len_2 = len_1 - 0x80
                            tmp = ""
                            for each in range(len_2):
                                tmp += "%02x" % int(hex(privatedata[ 2 + each + byte ])[ 2: ], 16)
                            len_3 = int(tmp, 16)
                        else:
                            len_3 = len_1
                        if (len_3 == private_len - (byte + 2 + len_2)):
                            headers.pop(0)
                            next = byte + 2 + len_2
                            headers[ 0 ] = next
                        else:
                            return 0  # 格式错误
                    else:
                        return 0  # 格式错误

                elif (len(headers) == 1):  # 抓版本
                    if (privatedata[ headers[ 0 ] ] == tag):
                        len_1 = privatedata[ headers[ 0 ] + 1 ]
                        len_2 = 0
                        len_3 = 0
                        if (len_1 > 0x80):
                            len_2 = len_1 - 0x80
                            tmp = ""
                            for each in range(len_2):
                                tmp += "%02x" % int(hex(privatedata[ 2 + each + byte ])[ 2: ], 16)
                            len_3 = int(tmp, 16)
                        else:
                            len_3 = len_1
                        tmp = ""
                        for by in range(len_3):
                            tmp += "%02x" % int(hex(privatedata[ 2 + by + byte + len_2 ])[ 2: ], 16)
                        next = byte + 2 + len_2 + len_3
                        Version = int(tmp, 16)
                        Private.append(Version)
                        headers.pop(0)
                        privateh[ 0 ] = next
                    else:
                        return 0  # 格式错误
        else:
            if (byte == privateh[ 0 ] and privatedata[ privateh[ 0 ] ] == tag):
                len_1 = privatedata[ privateh[ 0 ] + 1 ]
                len_2 = 0
                len_3 = 0
                if (len_1 > 0x80):
                    len_2 = len_1 - 0x80
                    tmp = ""
                    for each in range(len_2):
                        tmp += "%02x" % int(hex(privatedata[ 2 + each + byte ])[ 2: ], 16)
                    len_3 = int(tmp, 16)
                else:
                    len_3 = len_1
                tmp = ""
                for by in range(len_3):
                    tmp += "%02x" % int(hex(privatedata[ 2 + by + byte + len_2 ])[ 2: ], 16)
                Private.append(int(tmp, 16))

                privateh.pop(0)

                if (len(privateh) == 0):
                    break
                next = byte + 2 + len_2 + len_3
                privateh[ 0 ] = next

            elif (privatedata[ privateh[ 0 ] ] != tag):
                return 0  # 格式错误

    return Private


# RSA加密
def encrypt_stream( M, N, E, more = True, pad = "." ):
    stream = D_b64.enb64(M, enbytes = False)  # 将需要加密的流先进行base64转码
    mesg = ""  # 预设数字明文
    pas = ""  # 预设密文
    stream = stream.replace("=", "")  # 将base64补位"="去除
    for each in stream:
        mesg += "%02d" % (D_b64.base64_reverse_dict[ each ] + 10)  # 以每个base64字符为1单位获取base64编码逆表的对应值+10
    length = len(mesg)  # 计算数字明文的总长度
    line = len(str(N)) - 1  # 计算公钥的总长 - 1，也就是每段最多能加密的长度
    if (more):  # 判断是否进行分段加密
        if (length > line):  # 若需要加密的数字明文长度 > 单段能够加密的总长度则
            while (len(mesg) > line):  # 循环进行分段加密
                pas += str(modq(int(mesg[ :line ]), E, N)) + pad  # 每段得出的密文使用相应的分隔符
                mesg = mesg[ line: ]
        pas += str(modq(int(mesg), E, N))  # 将剩余段的数字明文进行加密
    else:
        if (length <= line):  # 若不适用分段加密，当需要加密的数字明文长度 <= 单段能够加密的总长度则
            pas = str(modq(int(mesg), E, N))  # 可以加密
        else:
            return -1  # 长度过长，无法加密
    return pas  # 返回密文数字


# RSA解密
def decrypt( C, N, D, more = True, pad = "." ):
    try:
        pas = C.decode( )  # 预处理将密文进行二进制流解码
    except AttributeError:
        pas = C
    mesg = ""  # 预设明文
    length = len(pas)  # 计算密文总长
    line = len(str(N)) - 1  # 计算给出的公钥最多能支持的每段长度
    if (more):  # 若使用分段解密
        part = pas.split(pad)  # 根据段与段间的分隔符划分成多段
        if (len(part) > 1):  # 若段的个数 > 1则
            for each in part:
                mesg += str(modq(int(each), D, N))  # 逐段进行解密
        else:
            mesg = str(modq(int(pas), D, N))  # 否则只需解密1段
    else:
        if (length <= line):  # 若不使用分段解密且当密文长度 <= 公钥最多能支持的每段长度时能够正常解密
            mesg = str(modq(int(pas), D, N))
        else:
            return -1  # 长度过长，无法解密
    return mesg  # 返回明文数字


# 还原函数(得到base64)
def i2upb( data ):
    mesg = ""  # 预设还原值
    if (len(data) % 2):  # 若长度不为2的倍数则输出错误
        return -1  # 长度错误
    else:
        for each in range(len(data) // 2):  # 这里是以每2个数字为1组
            mesg += D_b64.base64_dict[
                int(data[ each * 2:(each + 1) * 2 ]) - 10 ]  # 将取到的数字先 - 10 然后使用base64编码逆表还原成对应base64编码
    return mesg  # 返回还原值(base64)


if __name__ == '__main__':
    pass
