# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/6/10 下午5:07    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : first.py         
# @Software: PyCharm
# @Discript:
# ============================================
from flask import Blueprint

first_view = Blueprint("first", __name__)


@first_view.route("/first")
def first():
    return "first"
