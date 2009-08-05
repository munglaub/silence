

TARGET = silence
TEMPLATE = app

SOURCES += 	main.cpp\
			data/datastore.cpp\
			node/node.cpp\
			node/nodeid.cpp\
			node/treemodel.cpp\
			gui/mainwindow.cpp\
			gui/filemenu.cpp\
			gui/helpmenu.cpp\
			gui/aboutdialog.cpp\
			gui/editmenu.cpp\
			gui/viewmenu.cpp\
			gui/treeview.cpp\
			gui/textedit.cpp\
			gui/infosidebar.cpp\
			gui/statusbar.cpp\
			gui/newnodedialog.cpp\
			gui/searchnodedialog.cpp

HEADERS +=	data/datastore.h\
			node/node.h\
			node/nodeid.h\
			node/treemodel.h\
			gui/mainwindow.h\
			gui/filemenu.h\
			gui/helpmenu.h\
			gui/aboutdialog.h\
			gui/editmenu.h\
			gui/viewmenu.h\
			gui/treeview.h\
			gui/textedit.h\
			gui/infosidebar.h\
			gui/statusbar.h\
			gui/newnodedialog.h\
			gui/searchnodedialog.h

LIBS	+=	-lqscintilla2


