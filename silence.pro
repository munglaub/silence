

TARGET = silence
TEMPLATE = app

SOURCES += 	main.cpp\
			controller.cpp\
			data/datastore.cpp\
			node/node.cpp\
			node/nodeid.cpp\
			node/label.cpp\
			node/treemodel.cpp\
			node/filtermodel.cpp\
			node/listproxymodel.cpp\
			node/textnodecontent.cpp\
			node/richtextnodecontent.cpp\
			gui/mainwindow.cpp\
			gui/nodemenu.cpp\
			gui/silencemenu.cpp\
			gui/helpmenu.cpp\
			gui/aboutdialog.cpp\
			gui/editmenu.cpp\
			gui/viewmenu.cpp\
			gui/treeview.cpp\
			gui/textedit.cpp\
			gui/richtextedit.cpp\
			gui/infosidebar.cpp\
			gui/searchnodesidebar.cpp\
			gui/statusbar.cpp\
			gui/newnodedialog.cpp\
			gui/contentview.cpp\
			gui/welcomeview.cpp\
			gui/nodepropertywidget.cpp\
			gui/textfind.cpp\
			gui/labelwidget.cpp\
			gui/labelmanagementdialog.cpp

HEADERS +=	controller.h\
			data/datastore.h\
			node/node.h\
			node/nodeid.h\
			node/label.h\
			node/treemodel.h\
			node/listproxymodel.h\
			node/filtermodel.h\
			node/abstractnodecontent.h\
			node/textnodecontent.h\
			node/richtextnodecontent.h\
			gui/mainwindow.h\
			gui/nodemenu.h\
			gui/silencemenu.h\
			gui/helpmenu.h\
			gui/aboutdialog.h\
			gui/editmenu.h\
			gui/viewmenu.h\
			gui/treeview.h\
			gui/textedit.h\
			gui/richtextedit.h\
			gui/infosidebar.h\
			gui/searchnodesidebar.h\
			gui/statusbar.h\
			gui/newnodedialog.h\
			gui/contentview.h\
			gui/welcomeview.h\
			gui/nodepropertywidget.h\
			gui/textfind.h\
			gui/labelwidget.h\
			gui/labelmanagementdialog.h

QT		+= xml

LIBS	+=	-lqscintilla2

RESOURCES	=	silence.qrc

TRANSLATIONS	=	silence_de_DE.ts \
					silence_en_US.ts \
					silence_en_GB.ts 
