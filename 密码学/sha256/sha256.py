import re, functools


class SHA_256(object):
    def __init__( self ):

        # 初始化哈希初值
        self.Hash_init = [
            0x6a09e667, 0xbb67ae85,
            0x3c6ef372, 0xa54ff53a,
            0x510e527f, 0x9b05688c,
            0x1f83d9ab, 0x5be0cd19
        ]

        # 初始化哈希常量
        self.Hash_const = [
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
            0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
            0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
            0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
        ]

    # 右旋转
    def rightrotate_( self, s, length ):
        return s[ -length: ] + s[ :-length ]

    # 右移位
    def rightshift_( self, s, length ):
        return "0" * length + s[ :-length ]

    # hash加
    def hash_add( self, x, y ):
        return (x + y) & 0xffffffff

    # 扩充内容
    def prepare_( self, data ):
        try:
            data = data.encode( )
        except AttributeError:
            data = data
        data_bin_steam = "".join(bin(each)[ 2: ].zfill(8) for each in data)
        data_bin_len = len(data_bin_steam)
        return data_bin_steam + "1" + "0" * ((960 if data_bin_len > 448 else 448) - (data_bin_len % 512) - 1) + bin(
            data_bin_len)[ 2: ].zfill(64)

    # hash256
    def main_( self, data ):
        data_blocks = [ data[ index:(index + 1) * 512 ] for index in range(len(data) // 512) ]
        data_hash_main = self.Hash_init.copy( )

        # 对每个块进行摘要
        for block in data_blocks:

            # 求W[0~15]
            W = re.findall('\d{32}', block[ :32 * 16 ])

            # 求W[16~63]
            for i in range(16, 64):
                o0 = int(self.rightrotate_(W[ i - 15 ], 7), 2) ^ \
                     int(self.rightrotate_(W[ i - 15 ], 18), 2) ^ \
                     int(self.rightshift_(W[ i - 15 ], 3), 2)

                o1 = int(self.rightrotate_(W[ i - 2 ], 17), 2) ^ \
                     int(self.rightrotate_(W[ i - 2 ], 19), 2) ^ \
                     int(self.rightshift_(W[ i - 2 ], 10), 2)
                W.append(bin(functools.reduce(self.hash_add, [ int(W[ i - 16 ], 2), o0, int(W[ i - 7 ], 2), o1 ]))[2: ].zfill(32))

            data_hash = data_hash_main.copy( )

            # 进行64轮摘要
            for i in range(64):
                s0 = int(self.rightrotate_(bin(data_hash[ 0 ])[ 2: ].zfill(32), 2), 2) ^ \
                     int(self.rightrotate_(bin(data_hash[ 0 ])[ 2: ].zfill(32), 13), 2) ^ \
                     int(self.rightrotate_(bin(data_hash[ 0 ])[ 2: ].zfill(32), 22), 2)

                maj = (data_hash[ 0 ] & data_hash[ 1 ]) ^ \
                      (data_hash[ 0 ] & data_hash[ 2 ]) ^ \
                      (data_hash[ 1 ] & data_hash[ 2 ])

                s1 = int(self.rightrotate_(bin(data_hash[ 4 ])[ 2: ].zfill(32), 6), 2) ^ \
                     int(self.rightrotate_(bin(data_hash[ 4 ])[ 2: ].zfill(32), 11), 2) ^ \
                     int(self.rightrotate_(bin(data_hash[ 4 ])[ 2: ].zfill(32), 25), 2)

                ch = (data_hash[ 4 ] & data_hash[ 5 ]) ^ ((~data_hash[ 4 ]) & data_hash[ 6 ])

                t1 = functools.reduce(self.hash_add,[ data_hash[ 7 ], s1, ch, self.Hash_const[ i ] + int(W[ i ], 2)])
                t2 = functools.reduce(self.hash_add, [ s0, maj ])

                data_hash=[ self.hash_add(data_hash[i - 1] ,t1*(not i%4 )) for i in range(1,8)]
                data_hash.insert(0, self.hash_add(t1,t2))

                #print("<%d>[ "%i+" , ".join(hex(each) for each in data_hash)+"]")

            data_hash_main = [ self.hash_add(data_hash[ i ],data_hash_main[ i ]) for i in range(8) ]
        return "".join(hex(each)[ 2: ] for each in data_hash_main)


def show_decbox( box , length):
    for row in range(len(box) // length):
        print("[ " + " , ".join("0x" + hex(each)[ 2: ].zfill(8) for each in [box[row*length + i] for i in range(length)]) + " ]")
    print("\n")


if __name__ == '__main__':
    sha256=SHA_256()

    print("*" * 52 + "[ SHA256 ]" + "*" * 52)
    print("哈希初值 => ")
    show_decbox(sha256.Hash_init,2)
    print("哈希常量 => ")
    show_decbox(sha256.Hash_const, 8)
    print("*" * 52 + "[ SHA256 ]" + "*" * 52)

    while True:
        try:
            c = sha256.main_(data = sha256.prepare_(data = input("请输入需要进行SHA256的值：")))
            print("[ SHA256  =》]")
            print(c)
        except KeyboardInterrupt:
            print("Bye!")
            exit(0)
