#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author  : nacker 648959@qq.com
# @Time    : 2019-08-17 01:57
# @Site    : 
# @File    : 29_vipvideo.py
# @Software: PyCharm

# imageio
# numpy
# Pillow
# beautifulsoup4

import tkinter
import tkinter as tk
from tkinter import ttk
import tkinter.messagebox as msgbox
import webbrowser
import re
import json
# import os
# import types
# import requests
# import time

from tkinter.filedialog import askdirectory
from urllib import request, parse
# from bs4 import BeautifulSoup

class APP:
    def __init__(self, width=500, height=350):
        self.w = width
        self.h = height
        self.title = '二哥版VIP视频破解器'
        self.root = tk.Tk(className=self.title)
        # self.root.iconbitmap('logo.ico')
        self.url = tk.StringVar()
        self.v = tk.IntVar()
        self.v.set(1)

        self.channel = ""

        # Frame空间
        frame_0 = tk.Frame(self.root)
        frame_1 = tk.Frame(self.root)
        frame_2 = tk.Frame(self.root)
        frame_3 = tk.Frame(self.root)

        # Menu菜单
        menu = tk.Menu(self.root)
        self.root.config(menu=menu)
        filemenu = tk.Menu(menu, tearoff=0)
        moviemenu = tk.Menu(menu, tearoff=0)
        menu.add_cascade(label='菜单', menu=filemenu)
        menu.add_cascade(label='友情链接', menu=moviemenu)
        filemenu.add_command(label='退出', command=self.root.quit)

        # 各个网站链接
        moviemenu.add_command(label='网易公开课', command=lambda: webbrowser.open('http://open.163.com/'))
        moviemenu.add_command(label='腾讯视频', command=lambda: webbrowser.open('http://v.qq.com/'))
        moviemenu.add_command(label='搜狐视频', command=lambda: webbrowser.open('http://tv.sohu.com/'))
        moviemenu.add_command(label='芒果TV', command=lambda: webbrowser.open('http://www.mgtv.com/'))
        moviemenu.add_command(label='爱奇艺', command=lambda: webbrowser.open('http://www.iqiyi.com/'))
        moviemenu.add_command(label='PPTV', command=lambda: webbrowser.open('http://www.bilibili.com/'))
        moviemenu.add_command(label='优酷', command=lambda: webbrowser.open('http://www.youku.com/'))
        moviemenu.add_command(label='乐视', command=lambda: webbrowser.open('http://www.le.com/'))
        moviemenu.add_command(label='土豆', command=lambda: webbrowser.open('http://www.tudou.com/'))
        moviemenu.add_command(label='A站', command=lambda: webbrowser.open('http://www.acfun.tv/'))
        moviemenu.add_command(label='B站', command=lambda: webbrowser.open('http://www.bilibili.com/'))

        # 控件内容设置
        group = tk.Label(frame_0, text='请选择一个视频播放通道：', padx=10, pady=10)

        # 创建下拉菜单
        '''
        下拉菜单
        '''
        def go(*args):  # 处理事件，*args表示可变参数
            #     print(comboxlist.get())  # #获取选中的值方法1
            #     print(self.url.get())  # #获取选中的值方法2
            self.channel = comboxlist.get()
        comvalue = tkinter.StringVar()  # 窗体自带的文本，新建一个值
        comboxlist = ttk.Combobox(frame_0, width=20,textvariable=comvalue, state='readonly')  # 初始化
        comboxlist["values"] = ("线路1",
                                "线路2",
                                "线路3"
                                )
        comboxlist.current(0)  # 选择第一个
        comboxlist.bind("<<ComboboxSelected>>", go)  # 绑定事件,(下拉列表框被选中时，绑定go()函数)
        # comboxlist.pack()


        label1 = tk.Label(frame_1, text="请输入视频链接：")
        entry = tk.Entry(frame_1, textvariable=self.url, highlightcolor='Fuchsia', highlightthickness=1, width=35)
        label2 = tk.Label(frame_1, text=" ")
        # 播放
        play = tk.Button(frame_2, text="播放", font=('楷体', 12), fg='red', width=20, height=1, command=self.video_play)
        # 下载
        download = tk.Button(frame_2, text = "下载", font = ('楷体',12), fg = 'red', width = 20, height = 1, command = self.download_video)
        # 提示
        label_warning = tk.Label(frame_3, fg='blue', font=('楷体', 12), text='\n建议：将Chrome内核浏览器设置为默认浏览器\n作者:帶頭二哥 QQ:648959')

        # 控件布局
        frame_0.pack()
        frame_1.pack()
        frame_2.pack()
        frame_3.pack()

        # 表格布局
        # frame_0
        group.grid(row=0, column=0)
        comboxlist.grid(row=0, column=1)

        # frame_1
        label1.grid(row=0, column=0)
        entry.grid(row=0, column=1)
        label2.grid(row=0, column=2)

        # frame_2
        play.grid(row=1, column=0, ipadx=10, ipady=10)
        download.grid(row=1, column=1,ipadx=10, ipady=10)

        # frame_3
        label_warning.grid(row=2, column=0)

    """
    函数说明:jsonp解析
    """
    def loads_jsonp(self, _jsonp):
        try:
            _json = json.loads(re.match(".*?({.*}).*", _jsonp, re.S).group(1))
            return _json
        except:
            raise ValueError('Invalid Input')

    """
    函数说明:视频播放
    """
    def video_play(self):
        # 视频解析网站地址
        # port_1 = 'https://www.ikukk.com/?url='
        port_1 = 'http://jx.598110.com/?url='
        port_2 = 'http://www.jiexi-jiexi.com/?url='
        port_3 = 'https://jx.618g.com/?url='
        # port_3 = 'https://jx.xianmuyu.com?url='


        if len(self.channel) == 0:
            msgbox.showerror(title='错误', message='请选择播放通道!')
            return

        # 正则表达是判定是否为合法链接
        if re.match(r'^https?:/{2}\w.+$', self.url.get()):
            # 视频链接获取
            ip = self.url.get()
            # 视频链接加密
            ip = parse.quote_plus(ip)

            if self.channel == "线路1":
                # 浏览器打开
                webbrowser.open(port_1 + self.url.get())
            elif self.channel == "线路2":
                webbrowser.open(port_2 + self.url.get())
            else:
                webbrowser.open(port_3 + self.url.get())

        else:
            msgbox.showerror(title='错误', message='视频链接地址无效，请重新输入！')

    """
    函数说明:下载视频
    """
    def download_video(self):
        msgbox.showerror(title='开发中...', message='开发中...')


    def center(self):
        ws = self.root.winfo_screenwidth()
        hs = self.root.winfo_screenheight()
        x = int((ws / 2) - (self.w / 2))
        y = int((hs / 2) - (self.h / 2))
        self.root.geometry('{}x{}+{}+{}'.format(self.w, self.h, x, y))

    def loop(self):
        self.root.resizable(False, False)  # 禁止修改窗口大小
        self.center()  # 窗口居中
        self.root.mainloop()

if __name__ == '__main__':
    app = APP()  # 实例化APP对象
    app.loop()  # loop等待用户事件
