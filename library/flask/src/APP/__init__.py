# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/6/10 下午5:12    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : __init__.py.py         
# @Software: PyCharm
# @Discript:
# ============================================
from .view import init_view
from flask import Flask
from flask_sqlalchemy import SQLAlchemy

def create_app():
    app = Flask(__name__)

    init_view(app)
    return app
