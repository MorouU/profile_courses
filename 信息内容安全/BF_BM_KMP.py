"""
*/* *****************************

    @Description: Three methods for 'string matching'
    @Author: DQ
    @LastEditors  : DQ
    @Date: 2020-03-23 19:09:38
    @LastEditTime : 2020-03-24 03:31:51

*/* ******************************
"""


def get_table( s: str ):
    """
     */* *****************************

        @Thanks for Longlone
        @Able to generate partial matching table

    */* ******************************

    :param s: string
    :return: list
    """
    result = [ ]
    for i in range(1, len(s) + 1):
        if (i == 1):
            result.append(0)
            continue
        ss = s[ :i ]
        ss_len = len(ss)
        one, two = set((ss[ :i ] for i in range(ss_len))), set((ss[ i: ] for i in range(ss_len)))
        tmp = one & two
        result.append(len(max(tmp)) if (tmp) else 0)
    return result


def BF( text: str, pattern: str ):
    print("\t".join(str(i + 1) for i in range(len(text))))
    print("\t".join(each for each in text))
    index = 0
    results=[]
    while index <= len(text) - len(pattern):
        cmp = text[ index:index + len(pattern) ]
        result = [ "", "", "" ]
        for i in range(len(cmp)):
            if (pattern[ i ] != cmp[ i ]):
                result[ 1 ] = pattern[ i ]
                result[ 2 ] = pattern[ i + 1: ]
                break
            result[ 0 ] += pattern[ i ]
        print("\t" * index + "\033[32m" + "\t".join(list(result[ 0 ])) + "\t" * (len(result[ 0 ]) > 0)
              + "\033[31m" + "\t".join(list(result[ 1 ])) + "\t" * (len(result[ 1 ]) > 0)
              + "\033[0m" + "\t".join(list(result[ 2 ])) + "\033[0m")

        if (result[0] == text[ index:index + len(pattern) ]):
            results.append(index)
            index += 1
            continue

        index += 1

    return results


def KMP( text: str, pattern: str ):
    #table = get_table(pattern)

    
    table = [ 0 ]
    table.extend(len(max(
    [ same * (same in [ pattern[ :i + 1 ][ ::-1 ][ :k + 1 ][ ::-1 ] for k in range(len(pattern[ :i ])) ]) for same in
      [ pattern[ :i + 2 ][ :j + 1 ] for j in range(len(pattern[ :i ])) ]
      ]))for i in range(len(pattern)) if i > 0)

    print("Partial Matching Table:\n" + "\t".join(each for each in pattern)
          + "\n" + "\t".join(str(value) for value in table) + "\n")

    print("\t".join(str(i + 1) for i in range(len(text))))
    print("\t".join(each for each in text))
    results = [ ]

    index = 0
    while  index <= len(text) - len(pattern):
        cmp = text[ index:index + len(pattern) ]
        result = [ "", "", "" ]
        for i in range(len(cmp)):
            if (pattern[ i ] != cmp[ i ]):
                result[ 1 ] = pattern[ i ]
                result[ 2 ] = pattern[ i + 1: ]
                break
            result[ 0 ] += pattern[ i ]
        print("\t" * index + "\033[32m" + "\t".join(list(result[ 0 ])) + "\t" * (len(result[ 0 ]) > 0)
              + "\033[31m" + "\t".join(list(result[ 1 ])) + "\t" * (len(result[ 1 ]) > 0)
              + "\033[0m" + "\t".join(list(result[ 2 ])) + "\033[0m")

        if (result[0] == text[ index:index + len(pattern) ]):
            results.append(index)
            index +=1
            continue

        index = index + 1 if len(result[ 0 ]) == 0 else index + len(result[ 0 ]) - table[ len(result[ 0 ]) - 1 ]

    return results

def BM( text: str, pattern: str ):
    print("\t".join(str(i + 1) for i in range(len(text))))
    print("\t".join(each for each in text))
    index = 0
    results=[]
    pattern_r = pattern[ ::-1 ]
    while index <= len(text) - len(pattern):
        cmp_r = text[ index:index + len(pattern) ][ ::-1 ]
        result = [ "", "", "" ]
        for i in range(len(cmp_r)):
            if (pattern_r[ i ] != cmp_r[ i ]):
                result[ 1 ] = pattern_r[ i ]
                result[ 2 ] = pattern_r[ i + 1: ]
                break
            result[ 0 ] += pattern_r[ i ]
        print("\t" * index + "\033[0m" + "\t".join(list(result[ 2 ][ ::-1 ])) + "\t" * (len(result[ 2 ]) > 0)
              + "\033[31m" + "\t".join(list(result[ 1 ][ ::-1 ])) + "\t" * (len(result[ 1 ]) > 0)
              + "\033[32m" + "\t".join(list(result[ 0 ][ ::-1 ])) + "\033[0m")

        if (result[0][::-1] == text[ index:index + len(pattern) ]):
            results.append(index)
            index += 1
            continue

        if (len(result[ 1 ]) > 0):
            if (cmp_r[ len(result[ 0 ]) ] in pattern_r[ ::-1 ][ :-(len(result[ 0 ]) + 1) ]):
                index += (len(cmp_r) - (len(result[ 0 ]) + 1)) - (
                        pattern_r[ ::-1 ][ :-(len(result[ 0 ]) + 1) ].rfind(cmp_r[ len(result[ 0 ]) ]) + 0)
            else:
                index += len(pattern) - len(result[ 0 ])

    return results


if __name__ == '__main__':


    while True:
        try:
            method = input("=> method: ")
            t = input("=> text: ")
            p = input("=> pattern: ")
            print( )
            if (len(p) > len(t)): raise Exception("Errorlength")
            result = eval(method + f"(t,p)")
            if (len(result) > 0):
                print(
                    "\n \033[34m[+] \033[32m'{P}' \033[31min \033[36m'{T}'\033[0m\n".format(
                        P = p,
                        T = t
                    ))
                for each in result:
                    print(
                        " \033[34m[+] \033[32m<[ {index} ]> \033[0m".format(
                            index=each
                        ))
            else:
                print(
                    "\n \033[33m[-] \033[32m'{P}' \033[31mnot in \033[36m'{T}'\033[0m\n".format(
                        P = p,
                        T = t
                    ))
            print()
        except KeyboardInterrupt:
            print("bye!")
            exit(0)
        except Exception as e:
            print(e)
            pass
