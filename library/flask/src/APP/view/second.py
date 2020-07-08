# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/6/10 下午5:08    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : second.py         
# @Software: PyCharm
# @Discript:
# ============================================
from flask import Blueprint

second_view= Blueprint("second", __name__)


@second_view.route("/second")
def second():
    return "second"
