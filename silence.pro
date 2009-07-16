

TARGET = silence
TEMPLATE = app

SOURCES += 	main.cpp\
			gui/mainwindow.cpp\
			gui/filemenu.cpp\
			gui/helpmenu.cpp\
			gui/aboutdialog.cpp

HEADERS +=	gui/mainwindow.h\
			gui/filemenu.h\
			gui/helpmenu.h\
			gui/aboutdialog.h

LIBS	+=	-lqscintilla2


