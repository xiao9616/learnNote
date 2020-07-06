from PyQt5.QtWidgets import QApplication,QWidget,QMainWindow
import sys
import untitled

if __name__ == '__main__':
    # app=QApplication(sys.argv)
#     # w=QWidget()
#     # w.resize(400,200)
#     #
#     # w.move(300,300)
#     # w.setWindowTitle("nihao")
#     # w.show()
#     # sys.exit(app.exec())
    app=QApplication(sys.argv)
    mainWindow=QMainWindow()
    ui=untitled.Ui_MainWindow()
    ui.setupUi(mainWindow)
    mainWindow.show()
    sys.exit(app.exec())
