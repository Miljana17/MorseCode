TARGET = pressedButton



  # Zameni sa imenom svog projekta

# Specify the template
TEMPLATE = app  # Ovo je aplikacija

# Include necessary Qt modules
QT += core gui widgets

# Specify source files
SOURCES += main.cpp \
           mainwindow.cpp

# Specify header files
HEADERS  += mainwindow.h

# Specify UI files
FORMS    += mainwindow.ui
LIBS += -lwiringPi
