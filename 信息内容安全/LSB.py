from random import randint
from re import findall
from os import path
from time import time


#  ************** BMP 生成部分START **************

# 获取颜色
def get_color( color: tuple = (0, 0, 0) ):
    return "".join(chr(x) for x in color)[ ::-1 ]


# 获取长度
def get_hex( i: int = "", byte: int = 1 ):
    return "".join(
        chr(int(x, 16)) for x in findall("\w{2}", hex(i)[ 2: ].zfill(byte * 2))[ ::-1 ]
    )


# 生成bmp图像字节流
def BMP( width: int = 256, height: int = 256, color: tuple = (-1, -1, -1) ):
    # 初始化一些24位BMP的固有信息
    BMP_image = {
        "head": "\x42\x4D",
        "OffBits": get_hex(i = 54, byte = 4),
        "bSize": get_hex(i = 40, byte = 4),
        "width": get_hex(i = width, byte = 4),
        "height": get_hex(i = height, byte = 4),
        "Planes": get_hex(i = 1, byte = 2),
        "BigCount": get_hex(i = 24, byte = 2),
        "Compression": get_hex(i = 0, byte = 4),
        "XpelsPerMete": get_hex(i = 0, byte = 4),
        "YpelsPerMete": get_hex(i = 0, byte = 4),
        "ClrUsed": get_hex(i = 0, byte = 4),
        "ClrImportant": get_hex(i = 0, byte = 4),
    }

    # 各个像素的rbg，从左往右，从下往上
    Color_part = ""
    for row in range(height):
        for col in range(width):
            Color_part += get_color(
                color = (
                    randint(0, 255) if color[ 0 ] == -1 else color[ 0 ],
                    randint(0, 255) if color[ 1 ] == -1 else color[ 1 ],
                    randint(0, 255) if color[ 2 ] == -1 else color[ 2 ],
                )
            )

    BMP_image[ "SizeImage" ] = get_hex(i = len(Color_part), byte = 4)
    BMP_image[ "Size" ] = get_hex(i = len(Color_part) + 54, byte = 4)

    # 组装各个部分
    image = (
            BMP_image[ "head" ]
            + BMP_image[ "Size" ]
            + get_hex(i = 0, byte = 2 + 2)
            + BMP_image[ "OffBits" ]
            + BMP_image[ "bSize" ]
            + BMP_image[ "width" ]
            + BMP_image[ "height" ]
            + BMP_image[ "Planes" ]
            + BMP_image[ "BigCount" ]
            + BMP_image[ "Compression" ]
            + BMP_image[ "SizeImage" ]
            + BMP_image[ "XpelsPerMete" ]
            + BMP_image[ "YpelsPerMete" ]
            + BMP_image[ "ClrUsed" ]
            + BMP_image[ "ClrImportant" ]
            + Color_part
    )

    return image.encode("latin1")


#  ************** BMP 生成部分END **************


#  ************** LSB 隐写部分START **************

def LSB_encrypt( data: bytes = b"", bmp_file: str = "" ):
    # BMP图片是否存在
    if not path.exists(bmp_file):
        raise Exception("File not found!!!")
    # 读取BMP图片内容
    with open(bmp_file, "rb") as f:
        bmp_content = f.read( )

    # 分别获取需隐写信息的bin值以及长度、图片像素值内容以及长度
    # 若需隐写信息的bin值长度 > 图片像素内容的长度（隐写信息的总bits > 图片像素的总bytes）则无法隐写
    data_bits, bmp_bytes = (
        "".join(bin(byte)[ 2: ].zfill(8) for byte in data),
        bmp_content[ 54: ],
    )
    data_length, bmp_length = len(data_bits), len(bmp_bytes)
    if bmp_length < data_length:
        raise Exception("Too long!!!")

    # 进行LSB隐写
    result_bytes = ""
    for i in range(data_length):
        result_bytes += chr(
            bmp_bytes[ i ]
            ^ (
                    sum(each == '1' for each in bin(bmp_bytes[ i ])[ 2: ]) % 2
                    != int(data_bits[ i ])
            )
        )

    return bmp_content[ :54 ] + result_bytes.encode("latin1") + bmp_bytes[ data_length: ]


#  ************** LSB 隐写部分END **************


#  ************** LSB 拆解部分START **************

def LSB_decrypt( bmp_file: str = "" ):
    if not path.exists(bmp_file):
        raise Exception("File not found!!!")

    with open(bmp_file, "rb") as f:
        bmp_content = f.read( )

    bmp_bytes = bmp_content[ 54: ]
    bmp_length = len(bmp_bytes)

    # 进行LSB拆解
    result_bits = ""
    for i in range(bmp_length):
        result_bits += str(
            sum(each == '1' for each in bin(bmp_bytes[ i ])[ 2: ]) % 2
        )

    return "".join(chr(int(x, 2)) for x in findall("\d{8}", result_bits)).encode(
        "latin1"
    )


#  ************** LSB 拆解部分START **************


def main( ):
    # LSB隐写所用的载体BMP图片
    bmp_file = "A.bmp"

    # 经过LSB隐写生成的BMP图片
    bmp_file_encrypt = "B.bmp"

    # BMP图片宽度
    bmp_width = 320
    # BMP图片高度
    bmp_height = 320
    # BMP图片各个像素的颜色值（RGB）若填 -1 则任一像素中该位置的颜色随机
    color = (255, 255, 0)

    print("\n载体BMP图片创建中·····")
    create_file_start = time( )
    LSB_before = BMP(width = bmp_width, height = bmp_height, color = color)
    with open(file = bmp_file, mode = "wb") as bmp_A:
        bmp_A.write(LSB_before)

    print("\n创建完毕( %.6fs )·····\n" % (time( ) - create_file_start))

    while True:
        try:
            text = input("请输入需要LBS隐写的信息：")

            print("\n开始进行LSB隐写·····")
            LSB_encrypt_start = time( )
            LSB_out = LSB_encrypt(data = text.encode( ), bmp_file = bmp_file)
            print("\n隐写完毕( %.6fs )·····\n" % (time( ) - LSB_encrypt_start))

            print("\n开始生成LSB隐写后的BMP图片·····")
            LSB_out_start = time( )
            with open(file = bmp_file_encrypt, mode = "wb") as bmp_B:
                bmp_B.write(LSB_out)
            print("\n经过LSB隐写的BMP图片生成完毕( %.6fs )·····\n" % (time( ) - LSB_out_start))

            print("\n开始拆解经过LSB隐写生成的BMP图片·····")
            LSB_decrypt_start = time( )
            LSB_decrypt_content = LSB_decrypt(bmp_file = bmp_file_encrypt)
            print("\n拆解完毕( %.6fs )·····\n" % (time( ) - LSB_decrypt_start))

            print("LSB隐写信息：" + text)
            print("LSB隐写前的载体BMP图片内容：" + LSB_before.decode("latin1"))
            print("LSB隐写后的载体BMP图片内容：" + LSB_out.decode("latin1"))
            print("LSB拆解后得到的隐写信息：", LSB_decrypt_content.decode( ))

            print( )

        except KeyboardInterrupt:
            break
        except Exception as e:
            print("Error => ", e)


if __name__ == "__main__":
    main( )
