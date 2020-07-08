# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/6/10 下午6:07    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : models.py         
# @Software: PyCharm
# @Discript:
# ============================================
import flask_sqlalchemy
from manage import app

models = flask_sqlalchemy.SQLAlchemy(app)


class User(models.Model):
    id = models.Column(models.Integer, primary_key=True)
    username = models.Column(models.String(16))
