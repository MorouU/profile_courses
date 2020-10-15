import time, os, socket, uuid, D_b64, D_RSA

'''
@Description: Main
@Author: DQ
@LastEditors  : DQ
@Date: 2020-01-05 17:55:52
@LastEditTime : 2020-01-07 17:26:47
'''

rsa = D_RSA.RSA_value( )
version = ""
p = 0
q = 0
n = 0
m = 0
e = 0
d = 0
size = 2048
seed = int(time.time( ))


def getdateX( ):
    return "[ " + str(time.localtime( )[ 3 ]) + " 时 " + str(time.localtime( )[ 4 ]) + " 分 " + str(
        time.localtime( )[ 5 ]) + " 秒 ]"


def get_mac_address( ):
    mac = uuid.UUID(int = uuid.getnode( )).hex[ -12: ]
    return ":".join([ mac[ e:e + 2 ] for e in range(0, 11, 2) ])


def get_computer_hostname( ):
    return socket.getfqdn(socket.gethostname( ))


def get_computer_host( ):
    return socket.gethostbyname(get_computer_hostname( ))


def csh_rsa( ):
    global p, q, n, m, e, d, size, seed
    os.system("cls")
    print("\n======================" + "[ 初始化RSA的各项值 ]" + "======================\n")
    print(getdateX( ) + "请选择你要进行的操作：\n")
    print(" [ 1 ] -> 手动初始化")
    print(" [ 2 ] -> 自动初始化")
    print(" [ 3 ] -> 返回")
    action1 = input(" =>：")

    if (action1 == '1'):
        print("\n======================" + "[ 手动初始化 ]" + "======================\n")

        try:
            p = int(input(" [ * ] -> 请输入P值："))
            q = int(input(" [ * ] -> 请输入Q值："))
            e = int(input(" [ * ] -> 请输入E值："))
            d = int(input(" [ * ] -> 请输入D值："))
            n = p * q
            m = (p - 1) * (q - 1)

            print(" [ + ] -> 手动初始化成功！")
        except Exception:
            print(" [ - ] -> 手动初始化失败···")
    elif (action1 == "2"):
        print("\n======================" + "[ 自动初始化 ]" + "======================\n")

        try:
            sizet = input(" [ * ] -> 请输入生成的bit值（默认 %d ）：" % size)
            seedt = input(" [ * ] -> 请输入随机种子值（默认 %d ）：" % seed)
            if (sizet != ""):
                size = int(size)
            if (seedt != ""):
                seed = int(seed)

            p = rsa.p(size = size // 2, seed = seed)

            q = rsa.q(size = size // 2, seed = seed)

            n = p * q
            m = (p - 1) * (q - 1)
            e, d = rsa.e_d(m, seed = seed)

            print(" [ + ] -> 自动初始化成功！")
        except Exception:
            print(" [ - ] -> 自动初始化失败···")

    input("按回车键继续···")


def check_rsa( ):
    global p, q, n, m, e, d, size, seed
    os.system("cls")
    print("\n======================" + "[ 查看RSA的各项值 ]" + "======================\n")
    print(getdateX( ) + "请选择你要进行的操作：\n")
    print(" [ 1 ] -> 整体信息")
    print(" [ 2 ] -> 选择性查看")
    print(" [ 3 ] -> 返回")
    action1 = input(" =>：")

    if (action1 == '1'):
        print("\n======================" + "[ 整体信息 ]" + "======================\n")

        try:
            print("\n======================" + "[ P值 ]" + "======================\n")
            print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(p)[ 2: ]))
            print(" [ @ ] -> 数值：\n%d" % p)

            print("\n======================" + "[ Q值 ]" + "======================\n")
            print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(q)[ 2: ]))
            print(" [ @ ] -> 数值：\n%d" % q)

            print("\n======================" + "[ N值 ]" + "======================\n")
            print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(n)[ 2: ]))
            print(" [ @ ] -> 数值：\n%d" % n)

            print("\n======================" + "[ M值(p-1)*(q-1) ]" + "======================\n")
            print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(m)[ 2: ]))
            print(" [ @ ] -> 数值：\n%d" % m)

            print("\n======================" + "[ E值 ]" + "======================\n")
            print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(e)[ 2: ]))
            print(" [ @ ] -> 数值：\n%d" % e)

            print("\n======================" + "[ D值 ]" + "======================\n")
            print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(d)[ 2: ]))
            print(" [ @ ] -> 数值：\n%d" % d)

            print("\n======================" + "[ 随机种子值 ]" + "======================\n")
            print(" [ @ ] -> 随机种子：\n%d" % seed)

            print(" [ + ] -> 整体信息完成！")
        except Exception:
            print(" [ - ] -> 整体信息失败···")


    elif (action1 == "2"):
        print("\n======================" + "[ 选择性查看 ]" + "======================\n")

        try:
            while True:
                print(getdateX( ) + "请选择你要进行的操作：\n")
                print(" [ 1 ] -> 查看P值")
                print(" [ 2 ] -> 查看Q值")
                print(" [ 3 ] -> 查看N值")
                print(" [ 4 ] -> 查看M(p-1)*(q-1)值")
                print(" [ 5 ] -> 查看E值")
                print(" [ 6 ] -> 查看D值")
                print(" [ 7 ] -> 查看随机种子值")
                print(" [ 8 ] -> 退出查看")

                action2 = input(" =>: ")

                if (action2 == '1'):
                    print("\n======================" + "[ P值 ]" + "======================\n")
                    print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(p)[ 2: ]))
                    print(" [ @ ] -> 数值：\n%d" % p)
                if (action2 == '2'):
                    print("\n======================" + "[ Q值 ]" + "======================\n")
                    print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(q)[ 2: ]))
                    print(" [ @ ] -> 数值：\n%d" % q)

                if (action2 == '3'):
                    print("\n======================" + "[ N值 ]" + "======================\n")
                    print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(n)[ 2: ]))
                    print(" [ @ ] -> 数值：\n%d" % n)

                if (action2 == '4'):
                    print("\n======================" + "[ M值(p-1)*(q-1) ]" + "======================\n")
                    print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(p)[ m: ]))
                    print(" [ @ ] -> 数值：\n%d" % m)

                if (action2 == '5'):
                    print("\n======================" + "[ E值 ]" + "======================\n")
                    print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(e)[ 2: ]))
                    print(" [ @ ] -> 数值：\n%d" % e)

                if (action2 == '6'):
                    print("\n======================" + "[ D值 ]" + "======================\n")
                    print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(d)[ 2: ]))
                    print(" [ @ ] -> 数值：\n%d" % d)

                if (action2 == '7'):
                    print("\n======================" + "[ 随机种子值 ]" + "======================\n")
                    print(" [ @ ] -> 随机种子：\n%d" % seed)
                if (action2 == '8'):
                    break

            print(" [ + ] -> 选择性完成！")
        except Exception:
            print(" [ - ] -> 选择性查看失败···")

    input("按回车键继续···")


def encrypt_rsa( ):
    global p, q, n, m, e, d, size, seed
    os.system("cls")
    print("\n======================" + "[ 进行加密 ]" + "======================\n")
    print(getdateX( ) + "请选择你要进行的操作：\n")
    print(" [ 1 ] -> 加密信息")
    print(" [ 2 ] -> 加密文件")
    print(" [ 3 ] -> 返回")
    action1 = input(" =>：")

    if (action1 == '1'):
        print("\n======================" + "[ 加密信息 ]" + "======================\n")

        try:
            message = input(" [ * ] -> 请输入一段信息：\n")

            t = input(" [ ? ] -> 是否使用分段加密（Y/n)：")

            if (t == '' or t == 'y' or t == 'Y'):
                pad = input(" [ ? ] -> 请输入分段加密分隔符（需要非数字即可，默认 \\n )：")
                if (pad == ''):
                    pad = '\x0a'

                result = D_RSA.encrypt_stream(message.encode( ), n, e, more = True, pad = pad)
            else:
                result = D_RSA.encrypt_stream(message.encode( ), n, e, more = False)

            print(" [ + ] -> 加密信息成功！")

            t = input(" [ ? ] -> 是否将密文输出至屏幕（Y/n)：")
            if (t == '' or t == 'y' or t == 'Y'):
                print(" [ @ ] -> 密文：\n%s" % result)

            t = input(" [ ? ] -> 是否将密文输出至文件（y/N)：")
            if (t == 'y' or t == 'Y'):
                try:
                    filename = input(" [ * ] -> 请输入文件名称：")
                    with open(filename, "w") as file:
                        file.write(result)

                    print(" [ + ] -> 已成功将密文输出至 %s 文件中！" % filename)

                except Exception:
                    print(" [ - ] -> 输出至文件失败···")

        except Exception:
            print(" [ - ] -> 加密信息失败···")

    elif (action1 == '2'):
        print("\n======================" + "[ 加密文件 ]" + "======================\n")
        try:
            message = ""
            error = False
            while True:
                try:
                    filename = input(" [ * ] -> 请输入需要加密的文件名：\n")
                    file = open(filename, "rb")
                    message = file.read( )
                    file.close( )
                    print(" [ + ] -> 已成功获取文件信息！")
                    break
                except Exception:
                    print(" [ - ] -> 打开文件失败···")
                    t = input(" [ ? ] -> 是否继续（Y/n)：")
                    if (t != 'y' and t != 'Y'):
                        error = True
                        break
                except KeyboardInterrupt:
                    break
            if (error):
                input("按回车键继续···")
                return

            t = input(" [ ? ] -> 是否使用分段加密（Y/n)：")

            if (t == '' or t == 'y' or t == 'Y'):
                pad = input(" [ ? ] -> 请输入分段加密分隔符（需要非数字即可，默认 \\n )：")
                if (pad == ''):
                    pad = '\x0a'

                result = D_RSA.encrypt_stream(message, n, e, more = True, pad = pad)
            else:
                result = D_RSA.encrypt_stream(message, n, e, more = False)

            print(" [ + ] -> 加密文件成功！")

            t = input(" [ ? ] -> 是否将密文输出至屏幕（Y/n)：")
            if (t == '' or t == 'y' or t == 'Y'):
                print(" [ @ ] -> 密文：\n%s" % result)

            t = input(" [ ? ] -> 是否将密文输出至文件（y/N)：")
            if (t == 'y' or t == 'Y'):
                try:
                    filename = input(" [ * ] -> 请输入文件名称：")
                    with open(filename, "w") as file:
                        file.write(result)

                    print(" [ + ] -> 已成功将密文输出至 %s 文件中！" % filename)

                except Exception:
                    print(" [ - ] -> 输出至文件失败···")

        except Exception:
            print(" [ - ] -> 加密文件失败···")
    input("按回车键继续···")


def decrypt_rsa( ):
    global p, q, n, m, e, d, size, seed
    os.system("cls")
    print("\n======================" + "[ 进行解密 ]" + "======================\n")
    print(getdateX( ) + "请选择你要进行的操作：\n")
    print(" [ 1 ] -> 解密信息")
    print(" [ 2 ] -> 解密文件")
    print(" [ 3 ] -> 返回")
    action1 = input(" =>：")

    if (action1 == '1'):
        print("\n======================" + "[ 解密信息 ]" + "======================\n")

        try:
            message = input(" [ * ] -> 请输入一段密文：\n")

            t = input(" [ ? ] -> 是否使用分段解密（Y/n)：")

            if (t == '' or t == 'y' or t == 'Y'):
                pad = input(" [ ? ] -> 请输入分段加密分隔符（需要非数字即可，默认 \\n )：")
                if (pad == ''):
                    pad = '\x0a'

                result = D_RSA.decrypt(message.encode( ), n, d, more = True, pad = pad)
            else:
                result = D_RSA.decrypt(message.encode( ), n, d, more = False)

            print(" [ + ] -> 解密信息成功！")

            t = input(" [ ? ] -> 是否将信息再次解密成可视字符（Y/n)：")
            if (t == '' or t == 'y' or t == 'Y'):
                result = D_b64.deb64(D_RSA.i2upb(result))
                try:
                    result = result.decode( )
                except Exception:
                    pass

            t = input(" [ ? ] -> 是否将明文输出至屏幕（Y/n)：")
            if (t == '' or t == 'y' or t == 'Y'):
                print(" [ @ ] -> 明文：\n%s" % result)

            t = input(" [ ? ] -> 是否将明文输出至文件（y/N)：")
            if (t == 'y' or t == 'Y'):
                try:
                    filename = input(" [ * ] -> 请输入文件名称：")
                    with open(filename, "w") as file:
                        file.write(result)

                    print(" [ + ] -> 已成功将明文输出至 %s 文件中！" % filename)

                except Exception:
                    print(" [ - ] -> 输出至文件失败···")

        except Exception:
            print(" [ - ] -> 解密信息失败···")

    elif (action1 == '2'):
        print("\n======================" + "[ 解密文件 ]" + "======================\n")
        try:
            message = ""
            error = False
            while True:
                try:
                    filename = input(" [ * ] -> 请输入密文文件的文件名：\n")
                    file = open(filename, "rb")
                    message = file.read( )
                    file.close( )
                    print(" [ + ] -> 已成功获取文件信息！")
                    break
                except Exception:
                    print(" [ - ] -> 打开文件失败···")
                    t = input(" [ ? ] -> 是否继续（Y/n)：")
                    if (t != 'y' and t != 'Y'):
                        error = True
                        break
                except KeyboardInterrupt:
                    break
            if (error):
                input("按回车键继续···")
                return

            t = input(" [ ? ] -> 是否使用分段解密（Y/n)：")

            if (t == '' or t == 'y' or t == 'Y'):
                pad = input(" [ ? ] -> 请输入分段加密分隔符（需要非数字即可，默认 \\n )：")
                if (pad == ''):
                    pad = '\x0a'

                result = D_RSA.decrypt(message, n, d, more = True, pad = pad)
            else:
                result = D_RSA.decrypt(message, n, d, more = False)

            print(" [ + ] -> 解密文件成功！")
            t = input(" [ ? ] -> 是否将信息再次解密成可视字符（Y/n)：")
            if (t == '' or t == 'y' or t == 'Y'):
                result = D_b64.deb64(D_RSA.i2upb(result))

                try:
                    result = result.decode( )
                except Exception:
                    pass

            t = input(" [ ? ] -> 是否将明文输出至屏幕（Y/n)：")
            if (t == '' or t == 'y' or t == 'Y'):
                print(" [ @ ] -> 明文：\n%s" % result)

            t = input(" [ ? ] -> 是否将明文输出至文件（y/N)：")
            if (t == 'y' or t == 'Y'):
                try:
                    result=result.encode()
                except Exception:
                    pass
                try:
                    filename = input(" [ * ] -> 请输入文件名称：")
                    with open(filename, "wb") as file:
                        file.write(result)

                    print(" [ + ] -> 已成功将明文输出至 %s 文件中！" % filename)

                except Exception:
                    print(" [ - ] -> 输出至文件失败···")

        except Exception:
            print(" [ - ] -> 解密文件失败···")
    input("按回车键继续···")


def input_pem( ):
    global p, q, n, m, e, d, size, seed
    os.system("cls")
    print("\n======================" + "[ 导入PEM文件（目前支持PKCS#1 RSA算法标准） ]" + "======================\n")
    print(getdateX( ) + "请选择你要进行的操作：\n")
    print(" [ 1 ] -> 导入公钥PEM")
    print(" [ 2 ] -> 导入私钥PEM")
    print(" [ 3 ] -> 返回")
    action1 = input(" =>：")

    if (action1 == '1'):
        print("\n======================" + "[ 导入公钥PEM ]" + "======================\n")
        try:
            t = input(" [ ? ] -> 是否从文件内读取（Y/n)：")

            if (t == '' or t == 'y' or t == 'Y'):
                filename = input(" [ * ] -> 请输入公钥文件的文件名：\n")
                Public = D_RSA.input_public(inf = filename)
            else:
                message = input(" [ * ] -> 请输入公钥（base64值）：\n")
                Public = D_RSA.input_public(public = message)

            if (len(Public) == 2):
                print(" [ + ] -> 成功读取公钥值！")

                n = Public[ 0 ]
                e = Public[ 1 ]

                print("\n======================" + "[ N值 ]" + "======================\n")
                print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(n)[ 2: ]))
                print(" [ @ ] -> 数值：\n%d" % n)

                print("\n======================" + "[ E值 ]" + "======================\n")
                print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(e)[ 2: ]))
                print(" [ @ ] -> 数值：\n%d" % e)


            else:
                print(" [ - ] -> 公钥格式不正确···")
        except Exception:
            print(" [ - ] -> 导入公钥PEM失败···")
    elif (action1 == '2'):
        print("\n======================" + "[ 导入私钥PEM ]" + "======================\n")
        try:
            t = input(" [ ? ] -> 是否从文件内读取（Y/n)：")

            if (t == '' or t == 'y' or t == 'Y'):
                filename = input(" [ * ] -> 请输入私钥文件的文件名：\n")
                Private = D_RSA.input_private(inf = filename)
            else:
                message = input(" [ * ] -> 请输入公钥（base64值）：\n")
                Private = D_RSA.input_private(private = message)

            if (len(Private) == 9):
                print(" [ + ] -> 成功读取私钥值！")

                print("\n======================" + "[ 私钥版本@%s ]" % str(Private[ 0 ]) + "======================\n")

                n = Private[ 1 ]
                e = Private[ 2 ]
                d = Private[ 3 ]
                p = Private[ 4 ]
                q = Private[ 5 ]
                exp1 = Private[ 6 ]
                exp2 = Private[ 7 ]
                coe = Private[ 8 ]
                m = p * q

                print("\n======================" + "[ N值 ]" + "======================\n")
                print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(n)[ 2: ]))
                print(" [ @ ] -> 数值：\n%d" % n)

                print("\n======================" + "[ E值 ]" + "======================\n")
                print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(e)[ 2: ]))
                print(" [ @ ] -> 数值：\n%d" % e)

                print("\n======================" + "[ D值 ]" + "======================\n")
                print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(d)[ 2: ]))
                print(" [ @ ] -> 数值：\n%d" % d)

                print("\n======================" + "[ P值 ]" + "======================\n")
                print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(p)[ 2: ]))
                print(" [ @ ] -> 数值：\n%d" % p)

                print("\n======================" + "[ Q值 ]" + "======================\n")
                print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(q)[ 2: ]))
                print(" [ @ ] -> 数值：\n%d" % q)

                print("\n======================" + "[ EXP1值 d%(p-1) ]" + "======================\n")
                print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(exp1)[ 2: ]))
                print(" [ @ ] -> 数值：\n%d" % exp1)

                print("\n======================" + "[ EXP2值 d%(q-1) ]" + "======================\n")
                print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(exp2)[ 2: ]))
                print(" [ @ ] -> 数值：\n%d" % exp2)

                print("\n======================" + "[ COE值 (q-1)%p ]" + "======================\n")
                print(" [ @ ] -> 位数：\n%d bit(s)" % len(bin(coe)[ 2: ]))
                print(" [ @ ] -> 数值：\n%d" % coe)



            else:
                print(" [ - ] -> 私钥格式不正确···")
        except Exception:
            print(" [ - ] -> 导入私钥PEM失败···")

    input("按回车键继续···")


def output_pem( ):
    global p, q, n, m, e, d, size, seed
    os.system("cls")
    print("\n======================" + "[ 导出PEM文件（目前支持PKCS#1 RSA算法标准） ]" + "======================\n")
    print(getdateX( ) + "请选择你要进行的操作：\n")
    print(" [ 1 ] -> 导出公钥PEM")
    print(" [ 2 ] -> 导出私钥PEM")
    print(" [ 3 ] -> 返回")
    action1 = input(" =>：")

    if (action1 == '1'):
        print("\n======================" + "[ 导出公钥PEM ]" + "======================\n")
        try:
            if (n == 0 or e == 0):
                print(" [ - ] -> 无法生成私钥值！")
                raise Exception

            data = D_RSA.output_public(data = { 'n': n, 'e': e })
            print(" [ + ] -> 已成功生成公钥值！")

            start = "-----BEGIN PUBLIC KEY-----\n"
            end = "-----END PUBLIC KEY-----\n"

            message = D_b64.enb64(data, enbytes = False)

            public = ""
            while (len(message) > 64):
                public += message[ :64 ] + "\n"
                message = message[ 64: ]
            public += message + "\n"

            public = start + public + end

            t = input(" [ ? ] -> 是否导出至文件中（Y/n)：")

            if (t == '' or t == 'y' or t == 'Y'):
                filename = input(" [ * ] -> 请输入导出的公钥文件名：\n")
                try:
                    file = open(filename, "w")
                    file.write(public)
                    print(" [ + ] -> 已成功将公钥输出至 %s 文件中！" % filename)
                    file.close( )
                except Exception:
                    print(" [ - ] -> 写入文件失败···")
            else:
                print(public)

            print(" [ + ] -> 成功导出公钥值！")
        except Exception:
            print(" [ - ] -> 导出公钥PEM失败···")
    elif (action1 == '2'):
        print("\n======================" + "[ 导出私钥PEM ]" + "======================\n")
        try:
            if (n == 0 or e == 0 or d == 0 or p == 0 or q == 0):
                print(" [ - ] -> 无法生成私钥值！")
                raise Exception

            data = D_RSA.output_private(data = { 'n': n, 'e': e, 'd': d, 'p': p, 'q': q })
            print(" [ + ] -> 已成功生成私钥值！")

            start = "-----BEGIN RSA PRIVATE KEY-----\n"
            end = "-----END RSA PRIVATE KEY-----\n"

            message = D_b64.enb64(data, enbytes = False)

            private = ""
            while (len(message) > 64):
                private += message[ :64 ] + "\n"
                message = message[ 64: ]
            private += message + "\n"

            private = start + private + end

            t = input(" [ ? ] -> 是否导出至文件中（Y/n)：")

            if (t == '' or t == 'y' or t == 'Y'):
                filename = input(" [ * ] -> 请输入导出的私钥文件名：\n")
                try:
                    file = open(filename, "w")
                    file.write(private)
                    print(" [ + ] -> 已成功将私钥输出至 %s 文件中！" % filename)
                    file.close( )
                except Exception:
                    print(" [ - ] -> 写入文件失败···")
            else:
                print(private)

            print(" [ + ] -> 成功导出私钥值！")
        except Exception:
            print(" [ - ] -> 导出私钥PEM失败···")

    input("按回车键继续···")


def love( ):
    os.system("cls")
    os.system("color 0c")
    print('\n'.join([ ''.join([ ('LoveYou'[ (x - y) % 7 ] if ((x * 0.05) ** 2 + (y * 0.1) ** 2 - 1) ** 3 - (
            x * 0.05) ** 2 * (y * 0.1) ** 3 <= 0 else ' ') for x in range(-30, 30) ]) for y in
                      range(15, -15, -1) ]))
    return


def head( ):
    print("""                                                         
                        .....               o%@@%.       
                  .oXX%%@@@@%%%%Xo.       .%@#@@#%       
                X@#####@%%%@######@%X    X%@@o .%@X      
             o%@@%Xo...        .oX@@@%o .@@X.   .%@o     
           o@@%o                    X@@X%@o      o#%     
         .X%%o                       .%@#%.      o#%     
        .%@o                           X%@%.     .@%     
       .%@o                             o%@@.    o@%     
       X@X                               .%#%o  .%#X     
     .X%o                                  %#@  .%#@.    
     o@X.                                  .%#X  o@#%o   
     %@.                    .oX@@%.         .%@X  .X#%o  
    o@%                 .X%@@@@@@%.          o@@.   %@%  
    %@.              X%@###@%.                X@@.   @@. 
   o@%              o###@%X.                   X@%   %@. 
   X@o    ....o.    .%@@@@@@@%Xo               .%@X.o@@  
   %@..X%@#####%        ..oX%%@%.               o@#@#@X  
  .@% o#@%%@##@X              .                  X#@@o   
  X@o  ...X@@%o                       .o         .%@X    
  %@.   .%@@X.                       o@X          o@X    
  @%   .%#X                         o@@.          .%%X   
 .@X    .o                        oX@%o            .%@   
 o@X                           .X@##X               X#%  
 o@o                      .oX%@#@@X.                .%#..
 o@o               ..ooXX@##@@@%o     .o.o           X#%%
 o#%ooooooooXX%%%%@@##@@%%Xo.        X@%X@@X          %@@
 o##@@@#######@@@@%%%Xo..           .@@. X@@%.        X##
 o@##@XXoooXo..                     @%%Xoo@%@%        o@#
 .%@#@%.                           o#XoX%%@.X@.        %#
   .X%@@X.                         %#@%.o%@ .%%        X#
     .o@@X.                        %..%@%%@  o@%.      o@
       .oX%%X                     .@   X#X.    X@@o     X
          o%@@%Xo.                .@o%@##.       o%%o   .
            X%@##@X.               %##@XX          X@X   
               .o%@@@%Xoo.         .o@@.            .%@. 
                  .XX%#@@%%o         o%%   ..        .%%.
                      ..X@@X          XX XX%%.         %%
                        o@.           XX.@o.%%.        oX
                        X#            %oo%.  X@%         
                        X@            %%%X    .%%o       
                        X@            o@%o     .%@o      
                        %%             ..        o@%o    
                       .%X                        .X@@o  

""")


if __name__ == '__main__':

    os.system("color 09")
    os.system("title " + "{" + get_computer_host( ) + "}" + " 邪恶行为ing")
    os.system("mode con cols=140 lines=70")

    while True:
        try:
            os.system("cls")
            head( )
            print(getdateX( ) + "主机名称: < %s > " % get_computer_hostname( ))

            print(getdateX( ) + "IPv4地址: < %s > " % get_computer_host( ))

            print(getdateX( ) + "物理地址: < %s > " % get_mac_address( ))

            print("\n======================" + "[ 主菜单 ]" + "======================\n")

            print(getdateX( ) + "请选择你要进行的操作：\n")
            print(" [ 1 ] -> 初始化RSA的各项值")
            print(" [ 2 ] -> 查看RSA的各项值")
            print(" [ 3 ] -> 进行加密")
            print(" [ 4 ] -> 进行解密")
            print(" [ 5 ] -> 导入PEM文件（目前支持PKCS#1 RSA算法标准）")
            print(" [ 6 ] -> 导出PEM文件（目前支持PKCS#1 RSA算法标准）")
            print(" [ 7 ] -> 退出\n")

            action1 = input(" =>：")

            if (action1 == '1'):
                csh_rsa( )
            if (action1 == '2'):
                check_rsa( )
            if (action1 == '3'):
                encrypt_rsa( )
            if (action1 == '4'):
                decrypt_rsa( )
            if (action1 == '5'):
                input_pem( )
            if (action1 == '6'):
                output_pem( )

            if (action1 == '7'):
                love( )
                print("Bye!")
                break

        except KeyboardInterrupt:
            love( )
            print("Bye!")
            break
        except Exception:
            print("Error!")

    os.system("pause")
    exit(0)
