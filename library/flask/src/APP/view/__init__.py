# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/6/10 下午5:07    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : __init__.py.py         
# @Software: PyCharm
# @Discript:
# ============================================
from .first import first_view
from .second import second_view
from .temp import temp_view


def init_view(app):
    app.register_blueprint(first_view)
    app.register_blueprint(second_view)
    app.register_blueprint(temp_view)
