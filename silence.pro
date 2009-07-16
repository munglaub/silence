

TARGET = silence
TEMPLATE = app

SOURCES += 	main.cpp\
			gui/mainwindow.cpp\
			gui/filemenu.cpp\
			gui/helpmenu.cpp\
			gui/aboutdialog.cpp\
			gui/editmenu.cpp

HEADERS +=	gui/mainwindow.h\
			gui/filemenu.h\
			gui/helpmenu.h\
			gui/aboutdialog.h\
			gui/editmenu.h

LIBS	+=	-lqscintilla2


