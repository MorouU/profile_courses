'''
@Description: AES128
@Author: DQ
@LastEditors  : DQ
@Date: 2020-03-14 21:16:22
@LastEditTime : 2020-03-15 01:52:14
'''

import b64, re, functools


class AES_128(object):

    def __init__( self ):

        # 声明正S盒
        self.S_box = [
            [ 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76 ],
            [ 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0 ],
            [ 0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15 ],
            [ 0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75 ],
            [ 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84 ],
            [ 0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf ],
            [ 0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8 ],
            [ 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2 ],
            [ 0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73 ],
            [ 0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb ],
            [ 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79 ],
            [ 0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08 ],
            [ 0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a ],
            [ 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e ],
            [ 0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf ],
            [ 0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 ]
        ]

        # 声明S盒的逆
        self.S_box_r = [
            [ 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb ],
            [ 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb ],
            [ 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e ],
            [ 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25 ],
            [ 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92 ],
            [ 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84 ],
            [ 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06 ],
            [ 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b ],
            [ 0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73 ],
            [ 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e ],
            [ 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b ],
            [ 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4 ],
            [ 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f ],
            [ 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef ],
            [ 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61 ],
            [ 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d ]
        ]

        # 声明RC常量
        self.RC = [ 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36 ]

        # 声明列混淆矩阵常量
        self.BOX = [
            [ 0x02, 0x03, 0x01, 0x01 ],
            [ 0x01, 0x02, 0x03, 0x01 ],
            [ 0x01, 0x01, 0x02, 0x03 ],
            [ 0x03, 0x01, 0x01, 0x02 ]
        ]

        self.BOX_r = [
            [ 0x0e, 0x0b, 0x0d, 0x09 ],
            [ 0x09, 0x0e, 0x0b, 0x0d ],
            [ 0x0d, 0x09, 0x0e, 0x0b ],
            [ 0x0b, 0x0d, 0x09, 0x0e ]
        ]

        # 声明主要变量
        self.KEY, self.KEY_EXTEND = [ ], [ ]

    # 矩阵行列倒置
    def re_rc( self, box ):
        return [ [ row[ i ] for row in box ] for i in range(len(box[ 0 ])) ]

    # 矩阵内容16进制字符转10进制数字
    def str2dec( self, box ):
        for i in range(len(box)):
            for j in range(len(box[ i ])):
                box[ i ][ j ] = int(box[ i ][ j ], 16)
        return box

    # 列混淆元计算
    def fun2( self, i ):
        i <<= 1
        if (i & 0x100 != 0):
            i = (i & 0xff) ^ 0x1b
        return i

    # 获取扩展密钥矩阵
    def get_extend( self, key, rc, count = 10 ):
        W = [ ]
        W_each_len = len(key)
        for col in self.re_rc(key):
            W.append("".join(hex(each)[ 2: ] for each in col).zfill(W_each_len * 2))

        for i in range(W_each_len, (count + 1) * W_each_len):
            if (i % W_each_len):
                W.append(hex(int(W[ i - W_each_len ], 16) ^ int(W[ i - 1 ], 16))[ 2: ].zfill(W_each_len * 2))
            else:
                W_tmp = "".join(hex(self.S_box[ int(each[ 0 ], 16) ][ int(each[ 1 ], 16) ])[ 2: ].zfill(2) for each in
                                re.findall(r'\w{1,2}', W[ i - 1 ][ 2: ] + W[ i - 1 ][ :2 ]))
                W.append(hex(
                    int(str(hex(int(W_tmp[ :2 ], 16) ^ rc[ i // W_each_len ]))[ 2: ].zfill(2) + W_tmp[ 2: ], 16) ^ int(
                        W[ i - W_each_len ],
                        16))[ 2: ].zfill(
                    W_each_len * 2))

        return [ [ W[ W_each_len * i + j ] for j in range(W_each_len) ] for i in range(len(W) // W_each_len) ]

    # 加密
    def aes_encode( self, content, key, rc, box, count = 10 ):
        key_re = self.re_rc(key)  # 密钥矩阵倒置
        content_re = self.re_rc(content)  # 明文矩阵倒置
        key_extend = self.get_extend(key, rc, count)  # 获取密钥扩展矩阵集
        aes_en = [ [ ] for i in range(len(key_re)) ]  # 预设加密结果矩阵
        aes_len = len(key_re)  # 计算矩阵边长

        # 首次轮密钥加
        for i in range(aes_len):
            for j in range(aes_len):
                aes_en[ i ].append(hex(key_re[ i ][ j ] ^ content_re[ i ][ j ])[ 2: ].zfill(2))

        # 进行共10轮操作
        for this_round in range(count):

            # 字节替代
            for i in range(aes_len):
                for j in range(aes_len):
                    aes_en[ i ][ j ] = hex(
                        self.S_box[ int(aes_en[ i ][ j ][ 0 ], 16) ][ int(aes_en[ i ][ j ][ 1 ], 16) ])[ 2: ].zfill(2)

            # 行位移
            aes_en = self.re_rc(aes_en)
            for i in range(1, aes_len):
                for j in range(i):
                    aes_en[ i ].append(aes_en[ i ].pop(0))
            aes_en = self.re_rc(aes_en)

            # 若不为最后一次加密则进行列混淆
            if (this_round != 9):
                for i in range(aes_len):
                    tmp_list = [ ]
                    for j in range(aes_len):
                        tmp_ = [ ]
                        for k in range(aes_len):
                            a = int(aes_en[ i ][ k ], 16)
                            b = bin(box[ j ][ k ])[ 2: ][ ::-1 ]
                            w = eval("^".join([ line for line in "^".join(
                                [ "self.fun2(" * (bit - 1) + "a" * (bit > 0) + ")" * (bit - 1) for bit in
                                  [ pos * bool(int(b[ pos - 1 ])) for pos in range(1, len(b) + 1) ] ]).split('^') if
                                                bool(line) ]))
                            tmp_.append(w)
                        tmp_list.append(hex(functools.reduce(lambda x, y: x ^ y, tmp_))[ 2: ].zfill(2))
                    aes_en[ i ] = tmp_list

            # 轮密钥加
            for i in range(aes_len):
                tmp_list = re.findall(r'\w{1,2}', key_extend[ this_round + 1 ][ i ])
                for j in range(aes_len):
                    aes_en[ i ][ j ] = hex(int(aes_en[ i ][ j ], 16) ^ int(tmp_list[ j ], 16))[ 2: ].zfill(2)

        return self.re_rc(aes_en)

    # 解密
    def aes_decode( self, passwd, key, rc, box, count = 10 ):
        passwd_re = self.re_rc(passwd)  # 密文矩阵倒置
        key_extend = self.get_extend(key, rc, count)  # 获取密钥扩展矩阵集
        aes_de = [ [ ] for i in range(len(key)) ]  # 预设解密结果矩阵
        aes_len = len(key)  # 计算矩阵边长

        # 首次轮密钥加
        for i in range(aes_len):
            for j in range(aes_len):
                aes_de[ i ].append(
                    hex(int(key_extend[ count ][ i ][ j * 2:(j + 1) * 2 ], 16) ^ passwd_re[ i ][ j ])[ 2: ].zfill(
                        2))

        # 进行共10轮操作
        for this_round in range(count):

            # 进行逆向行位移
            aes_de = self.re_rc(aes_de)
            for i in range(1, aes_len):
                for j in range(i):
                    aes_de[ i ].insert(0, aes_de[ i ].pop( ))
            aes_de = self.re_rc(aes_de)

            # 进行逆向字节替代
            for i in range(aes_len):
                for j in range(aes_len):
                    aes_de[ i ][ j ] = hex(
                        self.S_box_r[ int(aes_de[ i ][ j ][ 0 ], 16) ][ int(aes_de[ i ][ j ][ 1 ], 16) ])[ 2: ].zfill(2)

            # 进行路密钥加
            for i in range(aes_len):
                tmp_list = re.findall(r'\w{1,2}', key_extend[ count - this_round - 1 ][ i ])
                for j in range(aes_len):
                    aes_de[ i ][ j ] = hex(int(aes_de[ i ][ j ], 16) ^ int(tmp_list[ j ], 16))[ 2: ].zfill(2)

            # 进行逆向列混淆
            if (this_round != 9):
                for i in range(aes_len):
                    tmp_list = [ ]
                    for j in range(aes_len):
                        tmp_ = [ ]
                        for k in range(aes_len):
                            a = int(aes_de[ i ][ k ], 16)
                            b = bin(box[ j ][ k ])[ 2: ][ ::-1 ]
                            w = eval("^".join([ line for line in "^".join(
                                [ "self.fun2(" * (bit - 1) + "a" * (bit > 0) + ")" * (bit - 1) for bit in
                                  [ pos * bool(int(b[ pos - 1 ])) for pos in range(1, len(b) + 1) ] ]).split('^') if
                                                bool(line) ]))
                            tmp_.append(w)
                        tmp_list.append(hex(functools.reduce(lambda x, y: x ^ y, tmp_))[ 2: ].zfill(2))
                    aes_de[ i ] = tmp_list

        return self.re_rc(aes_de)

    def init( self, key, count = 10 ):
        self.KEY = key
        self.KEY_EXTEND = self.get_extend(key = key, rc = self.RC, count = count)


def str2box( s, r = 4, l = 4, byte = 2 ):
    box = [ [ ] for i in range(r) ]
    for i in range(r):
        for j in range(l):
            box[ i ].append(int(s[ (i * r + j) * byte:((i * r + j) + 1) * byte ], 16))
    return box


def box2str( box ):
    result = ""
    for row in range(len(box)):
        for each in box[ row ]:
            result += each
    return result


def aes128_encode( content, aes, bit = 32, pad = '\n' ):
    s_hex_base64 = "".join([ "%2x" % ord(each) for each in b64.enb64(source = content, enbytes = False) ])
    s_hex_base64_plus = s_hex_base64 + "0" * (len(s_hex_base64) % bit) if len(
        s_hex_base64) > bit else s_hex_base64 + "0" * (bit - len(s_hex_base64))
    return pad.join(box2str(aes.aes_encode(
        content = aes.re_rc(str2box(s = s_hex_base64_plus[ index * bit:(index + 1) * bit ], r = 4, l = 4, byte = 2)),
        key = aes.KEY, rc = aes.RC, box = aes.BOX)) for index in range(len(s_hex_base64_plus) // bit))


def aes128_decode( passwd, aes, bit = 32, pad = '\n' ):
    result = "".join(box2str(
        aes.re_rc(aes.aes_decode(passwd = str2box(s = line, r = 4, l = 4, byte = 2), key = aes.KEY, rc = aes.RC,
                                 box = aes.BOX_r))) for line in passwd.split(pad))
    return b64.deb64(
        "".join(chr(int(result[ i * 2:(i + 1) * 2 ], 16)) for i in range(len(result) // 2)).replace("\x00", ""),
        debytes = False)


def show_decbox( box ):
    for row in range(len(box)):
        print("[ " + " , ".join("0x" + hex(each)[ 2: ].zfill(2) for each in box[ row ]) + " ]")
    print("\n")


def show_key_extend_box( box ):
    for row in range(len(box)):
        print("*" * 24 + "[ _ROUND_<%02d> ]" % row + "*" * 24)
        for i in range(len(box[ row ])):
            print("[ " + " , ".join(
                "0x" + box[ row ][ j ][ i * 2:(i + 1) * 2 ].zfill(2) for j in range(len(box[ row ][ i ]) // 2)) + " ]")
    print("*" * 24 + "[ _END_ROUND_ ]" + "*" * 24 + "\n\n")


def hex2str( s ):
    return "".join(chr(int(each, 16)) for each in re.findall(r'\w{1,2}', s)).encode('latin1')


if __name__ == '__main__':

    # 密钥矩阵
    key = [
        [ 0x12, 0x34, 0x56, 0x78 ],
        [ 0x78, 0x65, 0x43, 0x21 ],
        [ 0x23, 0x33, 0x33, 0x33 ],
        [ 0x33, 0x33, 0x33, 0x32 ]
    ]

    aes = AES_128( )
    aes.init(key = key, count = 10)
    pad = "\n"

    print("*" * 52 + "[ AES128 ]" + "*" * 52)
    print("密钥矩阵 => ")
    show_decbox(aes.KEY)
    print("密钥扩展矩阵 => ")
    show_key_extend_box(aes.KEY_EXTEND)
    print("*" * 52 + "[ AES128 ]" + "*" * 52)

    while True:
        try:
            c = aes128_encode(content = input("请输入需要加密的信息："), aes = aes, bit = 32, pad = pad)
            print("[ 密文  =》]")
            print(c)
            print("[ 密文流  =》]")
            print(hex2str(c.replace(pad, "")))
            s = aes128_decode(passwd = c, aes = aes, bit = 32, pad = pad)
            print("[ 明文  =》]")
            print(s)
        except KeyboardInterrupt:
            print("Bye!")
            exit(0)
