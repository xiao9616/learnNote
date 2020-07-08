# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/6/10 下午5:28    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : temp.py         
# @Software: PyCharm
# @Discript:
# ============================================
from flask import Blueprint, render_template

temp_view = Blueprint("temp_view", __name__)


@temp_view.route("/temp")
def temp():
    return render_template("index.html",msg="msg")
