from flask import Flask

import numpy as np
from tensorflow as
app = Flask(__name__)


@app.route('/')
def hello_world():
    return 'Hello World!'


@app.route('/xiao')
def xiao():
    return 'xiao'


@app.route('/xuan')
def xuan():
    return 'xuan'


if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True, port=1414)

