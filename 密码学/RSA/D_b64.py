'''
@Description: Base64
@Author: DQ
@LastEditors  : DQ
@Date: 2020-01-04 14:55:52
@LastEditTime : 2020-01-04 22:05:46
'''

# base64编码表
base64_dict = { 0: 'A', 1: 'B', 2: 'C', 3: 'D', 4: 'E', 5: 'F', 6: 'G', 7: 'H', 8: 'I', 9: 'J',
                10: 'K', 11: 'L', 12: 'M', 13: 'N', 14: 'O', 15: 'P', 16: 'Q', 17: 'R', 18: 'S',
                19: 'T', 20: 'U', 21: 'V', 22: 'W', 23: 'X', 24: 'Y', 25: 'Z', 26: 'a', 27: 'b',
                28: 'c', 29: 'd', 30: 'e', 31: 'f', 32: 'g', 33: 'h', 34: 'i', 35: 'j', 36: 'k',
                37: 'l', 38: 'm', 39: 'n', 40: 'o', 41: 'p', 42: 'q', 43: 'r', 44: 's', 45: 't',
                46: 'u', 47: 'v', 48: 'w', 49: 'x', 50: 'y', 51: 'z', 52: '0', 53: '1', 54: '2',
                55: '3', 56: '4', 57: '5', 58: '6', 59: '7', 60: '8', 61: '9', 62: '+', 63: '/' }

# base64编码逆表
base64_reverse_dict = { 'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4, 'F': 5, 'G': 6, 'H': 7, 'I': 8, 'J': 9,
                        'K': 10, 'L': 11, 'M': 12, 'N': 13, 'O': 14, 'P': 15, 'Q': 16, 'R': 17, 'S': 18,
                        'T': 19, 'U': 20, 'V': 21, 'W': 22, 'X': 23, 'Y': 24, 'Z': 25, 'a': 26, 'b': 27,
                        'c': 28, 'd': 29, 'e': 30, 'f': 31, 'g': 32, 'h': 33, 'i': 34, 'j': 35, 'k': 36,
                        'l': 37, 'm': 38, 'n': 39, 'o': 40, 'p': 41, 'q': 42, 'r': 43, 's': 44, 't': 45,
                        'u': 46, 'v': 47, 'w': 48, 'x': 49, 'y': 50, 'z': 51, '0': 52, '1': 53, '2': 54,
                        '3': 55, '4': 56, '5': 57, '6': 58, '7': 59, '8': 60, '9': 61, '+': 62, '/': 63 }


# base64转码
def enb64( source, enbytes = True ):
    try:
        data = source.encode( )  # 预处理将传入值转为2进制流
    except AttributeError:
        data = source
    length = len(data)  # 获取需转码的值的总长度
    end = length % 3  # 获取补位数
    out = ""  # 预设输出变量
    equal = ""  # 预设输出补位
    if (end != 0):  # 若补位数不为0则计算需要进行的补位各个量
        tmp = ""
        for _ in range(3 - end):
            tmp += "\x00"
            equal += "="
        data += bytes(tmp.encode( ))  # 进行补位(\x00)
        length += 3 - end  # 刷新补位后的总长度
    for part in range(length // 3):  # 以每3个字节为1组进行操作
        bins = ""
        for byte in range(3):
            bins += "%08d" % int(bin(data[ part * 3 + byte ])[ 2: ])  # 将每3个字节分解成 3 * 8 共 24 个bit

        for byte in range(4):
            out += base64_dict[ int(bins[ byte * 6:(byte + 1) * 6 ], 2) ]  # 从上边24个bit中每6个bit的数值索引base64编码
    if (end != 0):  # 若补位数不为0则在结果后边补上对应数量的"="
        out = (out[ :(-1) * (3 - end) ] + equal)
    if (enbytes):  # 判断是否需要将结果转为2进制流
        out = out.encode( )
    return out  # 输出结果


# base64解码
def deb64( source, debytes = True ):
    try:
        data = source.decode( )  # 预处理将传入值进行2进制流解码
    except AttributeError:
        data = source
    length = len(data)  # 计算总长
    equaln = length % 4  # 若长度不正确自动补"="
    for _ in range(equaln):  # 补"="
        data += "="
    end = data.count("=")  # 计算"="的数量
    out = bytes( )  # 预设输出变量
    data = data.replace("=", "A")  # 将补位符"="转换成"A"(000000)以好做解码处理
    for part in range(length // 4):  # 以每4个字符1组进行解码
        bins = ""
        for each in range(4):
            bins += "%06d" % int(
                bin(base64_reverse_dict[ data[ part * 4 + each ] ])[ 2: ])  # 将组中每个字符经过base64编码逆表得到的数值重组回24bit

        for each in range(3):
            out += bytes(chr(int(bins[ each * 8:(each + 1) * 8 ], 2)).encode("latin1"))  # 将得到的24bit重组回 3 * 8 模式的3个字节
    if (end != 0):  # 若存在补位则将后边补位的"\x00"去除
        out = out[ :(-1) * end ]
    if (not debytes):  # 判断是否将二进制流结果解码
        out = out.decode( )
    return out  # 输出结果

if __name__ == '__main__':
    f=open("wewe.txt","rb")
    o=deb64(f.read())
    w=open("wewe.bmp","wb")
    w.write(o)
    f.close()
    w.close()
