import asyncio, threading, multiprocessing, queue, math
import requests, re, os
import aiohttp
from urllib.parse import *


# 判断进程是否满了
def is_full_p():
    return Now_exist_P >= Max_exist_P


# 判断正在解析的URL数量是否满了
def is_full_url():
    return P_url_count.value > Max_exist_P * Max_urls


# 主函数
def mainset(
    Table_: list = [],
    Type_: int = 1,
    Max_exist_P_: int = 5,
    Max_urls_: int = 5,
    thread_num_: int = 10,
    timeout_: float = 3.0,
    Base_dir_: str = "Nearl_",
    Request_struct_: dict = {},
    URLS_len_: int = 1000,
):
    global Main_P_Pool, Table, CPU_count, Max_exist_P, Now_exist_P, Max_urls, P_result_queue, P_url_queue, P_url_count, Action_url, P_pool, Base_dir, URLs, Request_struct, URLS_len, Finish
    # 一顿操作
    # ****
    # ****

    # 去重
    URLs = set(Table_)

    # 装入URL
    Table = queue.Queue()
    for _ in URLs:
        Table.put(_)

    # 选择的爬的类型
    Type = Type_

    # 返回CPU核数
    CPU_count = multiprocessing.cpu_count()

    # 最多存在的进程数
    Max_exist_P = Max_exist_P_ if Max_exist_P_ > 0 else CPU_count

    # 每个进程最多解析的URL数量
    Max_urls = Max_urls_

    # 当前存在的进程数
    Now_exist_P = 0

    # 进程中共享装分析结果的队列
    P_result_queue = multiprocessing.Queue()

    # 进程中共享装URL的队列
    P_url_queue = multiprocessing.Queue()

    # 进程中共享装当前正在解析的URL的数量
    P_url_count = multiprocessing.Value("i", 0)

    # 投入解析的URL总数
    Action_url = 0

    # 伪进程池
    P_pool = []

    # 基础路径
    Base_dir = Base_dir_

    # 请求结构
    Request_struct = Request_struct_

    # 爬的最大URL值
    URLS_len = URLS_len_

    # 判断是否满足结束条件
    Finish = False

    # 主进程需要做的的大致流程：

    # 1、主进程对进程进行动态分配，
    # 2、开启1~20个线程将URL池get到进程的共享queue内，
    # 3、开启线程A来更新URL

    eval(
        "Open_process_%d(thread_num = %d, timeout =%f )"
        % (Type_, thread_num_, timeout_)
    )


# 更新URL池
def Table_update(timeout=3.0):
    global Table, P_result_queue, URLS_len, Finish, URLs
    while True:
        try:
            result = P_result_queue.get(block=True, timeout=timeout)
            for url in result:
                print("GET NEW URL => %s" % url)
                if url not in URLs and URLS_len != 0:
                    URLs.add(url)
                    Table.put_nowait(url)
                    URLS_len = URLS_len - 1
        except:
            Finish = True
            exit(0)


# 将URL池get到进程的共享queue内
def Give_urls():
    global P_url_queue, Action_url
    while True:
        if not is_full_url():
            try:
                this_url = Table.get(block=True, timeout=None)
                if this_url:
                    Action_url = Action_url + 1
                    print(
                        "THREAD [%s] GET URL => %s"
                        % (threading.currentThread().name, this_url)
                    )
                    P_url_queue.put_nowait(this_url)
            except:
                pass


# *******************************
#              方法1
# *******************************


def Open_process_1(thread_num: int = 20, timeout: float = 3):
    global Now_exist_P, P_url_queue, P_result_queue, P_url_count, P_pool, Request_struct
    print("Run [Open_proccess_1]")

    _thread_table_update = threading.Thread(
        target=Table_update, kwargs={"timeout": timeout}
    )
    _thread_table_update.setDaemon(daemonic=True)
    _thread_table_update.start()

    _threads_urls = set(
        threading.Thread(target=Give_urls, name=str(_)) for _ in range(thread_num)
    )

    for _ in _threads_urls:
        _.setDaemon(daemonic=True)
        _.start()

    while True:
        try:
            Now_exist_P = sum(
                each.is_alive() or bool(P_pool.remove(each)) for each in P_pool
            )
            if not is_full_p() and not is_full_url():
                if Now_exist_P <= P_url_count.value:
                    new_process = multiprocessing.Process(
                        target=p_get,
                        kwargs={
                            "Queue_url": P_url_queue,
                            "Queue_result": P_result_queue,
                            "Url_count": P_url_count,
                            "Max_urls": Max_urls,
                            "Base_dir": Base_dir,
                            "Request_dict": Request_struct,
                        },
                    )
                    P_pool.append(new_process)
                    new_process.start()
                    Now_exist_P = Now_exist_P + 1
        except KeyboardInterrupt:
            break

        if Finish:
            exit(0)


# *******************************


# *******************************
#              方法2
# *******************************


def Open_process_2(thread_num: int = 20, timeout: float = 3):
    global P_result_queue, P_url_count, P_url_queue, P_pool, Request_struct
    print("Run [Open_proccess_2]")

    P_result_queue = multiprocessing.Manager().Queue()
    P_url_count = multiprocessing.Manager().Value("i", 0)
    P_url_queue = multiprocessing.Manager().Queue()

    Main_Pool_P = multiprocessing.Pool(Max_exist_P)
    P_pool = [
        Main_Pool_P.apply_async(
            func=p_get_pool,
            kwds={
                "Queue_url": P_url_queue,
                "Queue_result": P_result_queue,
                "Url_count": P_url_count,
                "Max_urls": Max_urls,
                "Base_dir": Base_dir,
                "Request_dict": Request_struct,
            },
        )
        for i in range(Max_exist_P)
    ]
    Main_Pool_P.close()

    _thread_table_update = threading.Thread(
        target=Table_update, kwargs={"timeout": timeout}
    )
    _thread_table_update.setDaemon(daemonic=True)
    _thread_table_update.start()

    _threads_urls = set(
        threading.Thread(target=Give_urls, name=str(_)) for _ in range(thread_num)
    )
    for _ in _threads_urls:
        _.setDaemon(daemonic=True)
        _.start()

    while not Finish:
        try:
            pass
        except KeyboardInterrupt:
            exit(0)
    exit(0)


# *******************************


# *******************************
#              方法3
# *******************************


def Open_process_3(thread_num: int = 20, timeout: float = 3):
    global Now_exist_P, P_url_queue, P_result_queue, P_url_count, P_pool, Request_struct
    print("Run [Open_proccess_3]")

    _thread_table_update = threading.Thread(
        target=Table_update, kwargs={"timeout": timeout}
    )
    _thread_table_update.setDaemon(daemonic=True)
    _thread_table_update.start()

    _threads_urls = set(
        threading.Thread(target=Give_urls, name=str(_)) for _ in range(thread_num)
    )

    for _ in _threads_urls:
        _.setDaemon(daemonic=True)
        _.start()

    while True:
        try:
            Now_exist_P = sum(
                each.is_alive() or bool(P_pool.remove(each)) for each in P_pool
            )
            if not is_full_p() and not is_full_url():
                if Now_exist_P <= math.ceil(P_url_count.value / Max_urls):
                    new_process = multiprocessing.Process(
                        target=p_get,
                        kwargs={
                            "Queue_url": P_url_queue,
                            "Queue_result": P_result_queue,
                            "Url_count": P_url_count,
                            "Max_urls": Max_urls,
                            "Base_dir": Base_dir,
                            "Request_dict": Request_struct,
                        },
                    )
                    P_pool.append(new_process)
                    new_process.start()
                    Now_exist_P = Now_exist_P + 1
        except KeyboardInterrupt:
            break

        if Finish:
            exit(0)


# *******************************


# *******************************
#         方法2对应的进程
# *******************************
def p_get_pool(Queue_url, Queue_result, Url_count, Max_urls, Base_dir, Request_dict):
    global current_urls, end_result

    Session = requests.session()

    end_result = set()
    current_urls = 0
    thread_queue = queue.Queue()

    tend = threading.Thread(target=t_end, kwargs={"Queue": thread_queue})
    tend.setDaemon(daemonic=True)
    tend.start()

    while True:
        try:

            # 若该进程的新URL结果集合大小大于0，则将该进程解析到的新URL回复给URL池
            if len(end_result) > 0:
                Queue_result.put_nowait(end_result)
                end_result = set()

            # 该进程从进程共享队列中竞争获取需要解析的URL
            if current_urls < Max_urls and not Queue_url.empty():
                try:
                    url = Queue_url.get_nowait()
                    if url:
                        print(
                            "PROCESS [%s] GET URL => %s"
                            % (multiprocessing.current_process().name, url)
                        )
                        current_urls = current_urls + 1
                        Url_count.value = Url_count.value + 1

                        thread_ = threading.Thread(
                            target=t_start,
                            kwargs={
                                "url": url,
                                "Queue": thread_queue,
                                "url_count": Url_count,
                                "base_dir": Base_dir,
                                "Session": Session,
                                "Request_dict": Request_dict,
                            },
                        )
                        thread_.setDaemon(daemonic=True)
                        thread_.start()
                except Exception:
                    pass
        except Exception as e:
            print("[ERROR]", e)


# *******************************


# *******************************
#              方法1、3
# *******************************
def p_get(Queue_url, Queue_result, Url_count, Max_urls, Base_dir, Request_dict):
    global current_urls, end_result

    Session = requests.session()

    end_result = set()
    current_urls = 0
    thread_queue = queue.Queue()

    tend = threading.Thread(target=t_end, kwargs={"Queue": thread_queue})
    tend.setDaemon(daemonic=True)
    tend.start()

    while True:
        try:

            # 若该进程的新URL结果集合大小大于0，则将该进程解析到的新URL回复给URL池
            if len(end_result) > 0:
                Queue_result.put_nowait(end_result)
                end_result = set()

            # 该进程从进程共享队列中竞争获取需要解析的URL
            if current_urls < Max_urls and not Queue_url.empty():
                try:
                    url = Queue_url.get_nowait()
                    if url:
                        print(
                            "PROCESS [%s] GET URL => %s"
                            % (multiprocessing.current_process().name, url)
                        )
                        current_urls = current_urls + 1
                        Url_count.value = Url_count.value + 1

                        thread_ = threading.Thread(
                            target=t_start,
                            kwargs={
                                "url": url,
                                "Queue": thread_queue,
                                "url_count": Url_count,
                                "base_dir": Base_dir,
                                "Session": Session,
                                "Request_dict": Request_dict,
                            },
                        )
                        thread_.setDaemon(daemonic=True)
                        thread_.start()
                except Exception:
                    pass
            elif current_urls == 0:

                # 当前所有线程执行完后后自动关闭进程
                break
        except Exception as e:
            print("[ERROR]", e)
    pass


# *******************************


# 进程中处理结果的线程（线程A）
def t_end(Queue):
    global end_result
    while True:
        try:

            # 获取得到的新URL，并将其放入该进程的新URL结果集合中
            result = Queue.get(block=True)
            for url in result:
                end_result.add(url)
        except:
            pass


# 简单的实现协程解析的线程（线程2...?）
def t_start(url, Queue, url_count, base_dir, Session, Request_dict):
    global current_urls

    # 开始调度主协程
    loop = asyncio.new_event_loop( )
    try:
        asyncio.set_event_loop(loop)
        result = loop.run_until_complete(
            xc_main(
                url=url, base_dir=base_dir, Session=Session, Request_dict=Request_dict
            )
        )
        Queue.put_nowait(result)
        loop.run_until_complete(asyncio.sleep(0.25))
    except:
        pass
    finally:
        loop.close()

    # 此时该URL已经完成解析
    current_urls = current_urls - 1
    url_count.value = url_count.value - 1


# 主协程
async def xc_main(url, base_dir, Session, Request_dict):
    # 发送相关http请求
    get_ = Session.request(
        method=Request_dict["Method"],
        url=url,
        headers=Request_dict["Headers"],
        cookies=Request_dict["Cookie"],
        params=Request_dict["Params"],
        data=Request_dict["Data"],
    )

    # 若网页呈跳转则将跳转地址收入URL池中
    if 300 <= get_.status_code < 400:
        return [re.search("location:.*?['\"](.+)['\"]", get_.headers)[1]]

    # print(get_.text)

    # 获取 <a > 标签
    a = set(re.findall(pattern="<a.+?href\s*=\s*[\"'](.+?)[\"']", string=get_.text))

    # 获取 <script > 标签
    script = set(
        re.findall(pattern="<script.+?src\s*=\s*[\"'](.+?)[\"']", string=get_.text)
    )

    # 获取 <link > 标签
    css = set(
        re.findall(pattern="<link.+?href\s*=\s*[\"'](.+?)[\"']", string=get_.text)
    )

    # 获取 <img > 标签
    img = set(re.findall(pattern="<img.+?src\s*=\s*[\"'](.+?)[\"']", string=get_.text))

    # 将URL的主域名、网页文件名抽离
    url_parse = urlparse(url=url)

    base_url = os.path.dirname(url.split("?", maxsplit=1)[0])

    # 在本地目录上还原网络目录
    path_ = base_dir + url_parse[2]
    dir_ = os.path.dirname(path_)

    if not os.path.exists(path_) or os.path.getsize(path_) == 0:
        if get_.status_code == requests.codes.ok:
            if not os.path.exists(dir_):
                try:
                    os.makedirs(dir_)
                    with open(path_, "wb") as page_out:
                        page_out.write(get_.content)
                except OSError:
                    pass

    async with aiohttp.ClientSession() as session_:
        try:

        # 将协程预载安排入日程表
            xc_a = asyncio.ensure_future(xc_text_url(get_text_a=a, base_url=base_url))

            xc_script = asyncio.ensure_future(
                xc_text_script(
                    get_text_script=script,
                    base_url=base_url,
                    base_dir=base_dir,
                    session=session_,
                )
            )

            xc_css = asyncio.ensure_future(
                xc_text_css(
                    get_text_css=css,
                    base_url=base_url,
                    base_dir=base_dir,
                    session=session_,
                )
            )
            xc_img = asyncio.ensure_future(
                xc_text_img(
                    get_text_img=img,
                    base_url=base_url,
                    base_dir=base_dir,
                    session=session_,
                )
            )

            # 协程获取A标签上的新URL
            await asyncio.wait_for(xc_a,timeout = None)

            # 协程2获取SCRIPT文件并抓取
            await asyncio.wait_for(xc_script, timeout = None)

            # 协程3获取CSS文件并抓取
            await asyncio.wait_for(xc_css, timeout = None)

            # 协程4获取图片连接并抓取
            await asyncio.wait_for(xc_img, timeout = None)

            result = xc_a.result( )

        except:
            result = set()

    return result


# 解析协程1（解析URL）
async def xc_text_url(get_text_a, base_url):
    # 解析得到的新URL，并去重
    href = set(
        each
        if re.match("http.?://", each)
        else base_url + "/" * (each[0] != "/") + each
        for each in get_text_a
    )

    return href


# 解析协程2（解析脚本）
async def xc_text_script(get_text_script, base_url, base_dir, session):

    # 解析得到脚本文件网页路径，并去重
    # 抓取该路径的文件内容，并将其下载至本地
    src = set(
        each
        if re.match("http.?://", each)
        else base_url + "/" * (each[0] != "/") + each
        for each in get_text_script
    )

    for link in src:
        path_ = base_dir + urlparse(url=link)[2]
        dir_ = os.path.dirname(path_)

        if not os.path.exists(path_) or os.path.getsize(path_) == 0:

            try:
                request = session.get
                js = await request(url=link, timeout=1)

                assert js.status == 200, "Cant fetch"

                content = await js.content.read()

                if not os.path.exists(dir_):
                    os.makedirs(dir_)

                with open(path_, "wb") as js_out:
                    js_out.write(content)

            except:
                continue


# 解析协程3（解析CSS）
async def xc_text_css(get_text_css, base_url, base_dir, session):

    # 解析得到CSS文件网页路径，并去重
    # 抓取该路径的文件内容，并将其下载至本地
    css = set(
        each
        if re.match("http.?://", each)
        else base_url + "/" * (each[0] != "/") + each
        for each in get_text_css
    )

    for link in css:

        path_ = base_dir + urlparse(url=link)[2]
        dir_ = os.path.dirname(path_)

        if not os.path.exists(path_) or os.path.getsize(path_) == 0:

            try:
                request = session.get
                css = await request(url=link, timeout=1)
                assert css.status == 200, "Cant fetch"
                content = await css.content.read()

                if not os.path.exists(dir_):
                    os.makedirs(dir_)

                with open(path_, "wb") as css_out:
                    css_out.write(content)

            except:
                continue


# 解析协程4（解析图片）
async def xc_text_img(get_text_img, base_url, base_dir, session):

    # 解析得到图片文件网页路径，并去重
    # 抓取该路径的文件内容，并将其下载至本地
    src = set(
        each
        if re.match("http.?://", each)
        else base_url + "/" * (each[0] != "/") + each
        for each in get_text_img
    )

    for link in src:

        path_ = base_dir + urlparse(url=link)[2]
        dir_ = os.path.dirname(path_)

        if not os.path.exists(path_) or os.path.getsize(path_) == 0:

            try:
                request = session.get
                img = await request(url=link, timeout=1)
                assert img.status == 200, "Cant fetch"
                content = await img.content.read()

                if not os.path.exists(dir_):
                    os.makedirs(dir_)

                with open(path_, "wb") as img_out:
                    img_out.write(content)

            except:
                continue


if __name__ == "__main__":
    Request_struct = {
        "Method": "GET",
        "Params": {},
        "Data": {},
        "Headers": {
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:73.0) Gecko/20100101 Firefox/73.0",
            "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
            "Accept-Language": "zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2",
            "Accept-Encoding": "gzip, deflate",
            "DNT": "1",
            "Connection": "close",
            "Upgrade-Insecure-Requests": "1",
        },
        "Cookie": {
            "BAIDUID": "C64D632476D9890507A65F853454E062:FG=1",
            "BIDUPSID": "C64D632476D9890507A65F853454E062",
            "PSTM": "1583369547",
            "delPer": "0",
            "BD_CK_SAM": "1",
            "PSINO": "7",
            "H_PS_PSSID": "30968_1446_21117_30823_26350_22157",
            "BD_UPN": "13314752",
            "H_PS_645EC": "615e8an0reh2KwGF9HGEz4zHX7h58YSaWyeGWZSlO3dK1USJybkqgfECKAI",
            "BDORZ": "B490B5EBF6F3CD402E515D22BCDA1598",
        },
    }

    mainset(
        # 需要爬的页面
        Table_=["https://***.***.***/linux/linux-comm-whoami.html"],
        # 调度方法类型
        Type_=3,
        # 最大进程数
        Max_exist_P_=5,
        # 分配给每个进程的最大URL数
        Max_urls_=5,
        # 从URL池中将URL发放给进程共享队列的线程数
        thread_num_=3,
        # 爬取超时时间（秒）
        timeout_=30.0,
        # 在本地的爬取目录
        Base_dir_="Nearl_3",
        # 各种参数以及头信息
        Request_struct_=Request_struct,
        # 最大爬取URL数，若为-1则无限
        URLS_len_=-1,
    )
