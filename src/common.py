import sys
from PySide2.QtWidgets import (QApplication)
from PySide2.QtCore import QObject, Property, QCoreApplication

def get_property(name):
    return qApp.property("_kernel").property('currentAction').property(name)

