
HEADERS = 	src/main.cpp \
			src/commandline/cmdmain.h \
			src/commandline/nodefilter.h \
			src/utils/listutils.h \
			src/persistence/abstractdatastore.h \
			src/persistence/xmldatastore.h \
			src/gui/dialog/newlinkdialog.h \
			src/gui/dialog/newnodedialog.h \
			src/gui/dialog/aboutdialog.h \
			src/gui/dialog/labelmanagementdialog.h \
			src/gui/dialog/newtabledialog.h \
			src/gui/menu/editmenu.h \
			src/gui/menu/viewmenu.h \
			src/gui/menu/nodemenu.h \
			src/gui/menu/silencemenu.h \
			src/gui/menu/helpmenu.h \
			src/gui/widget/searchnodeoptions.h \
			src/gui/widget/labellist.h \
			src/gui/widget/labelwidget.h \
			src/gui/widget/textfind.h \
			src/gui/widget/inputwidget.h \
			src/gui/widget/syntaxbox.h \
			src/gui/widget/rtfedit.h \
			src/gui/mainwindow.h \
			src/gui/view/welcomeview.h \
			src/gui/view/richtextedit.h \
			src/gui/view/contentview.h \
			src/gui/view/textedit.h \
			src/gui/statusbar.h \
			src/gui/sidebar/treeview.h \
			src/gui/sidebar/infosidebar.h \
			src/gui/sidebar/searchnodesidebar.h \
			src/gui/sidebar/nodepropertywidget.h \
			src/data/label.h \
			src/data/aboutdata.h \
			src/data/node/abstractnodecontent.h \
			src/data/node/textnodecontent.h \
			src/data/node/richtextnodecontent.h \
			src/data/node/nodeid.h \
			src/data/node/node.h \
			src/data/model/simpletreemodel.h \
			src/data/model/treemodel.h \
			src/data/model/filtermodel.h \
			src/data/model/listproxymodel.h \
			src/data/model/labelmodel.h \
			src/controller.h \


SOURCES =	src/commandline/cmdmain.cpp \
			src/commandline/nodefilter.cpp \
			src/controller.cpp \
			src/utils/listutils.cpp \
			src/persistence/xmldatastore.cpp \
			src/gui/dialog/newnodedialog.cpp \
			src/gui/dialog/newtabledialog.cpp \
			src/gui/dialog/aboutdialog.cpp \
			src/gui/dialog/newlinkdialog.cpp \
			src/gui/dialog/labelmanagementdialog.cpp \
			src/gui/menu/viewmenu.cpp \
			src/gui/menu/helpmenu.cpp \
			src/gui/menu/nodemenu.cpp \
			src/gui/menu/silencemenu.cpp \
			src/gui/menu/editmenu.cpp \
			src/gui/widget/rtfedit.cpp \
			src/gui/widget/inputwidget.cpp \
			src/gui/widget/labelwidget.cpp \
			src/gui/widget/labellist.cpp \
			src/gui/widget/syntaxbox.cpp \
			src/gui/widget/searchnodeoptions.cpp \
			src/gui/widget/textfind.cpp \
			src/gui/view/textedit.cpp \
			src/gui/view/contentview.cpp \
			src/gui/view/richtextedit.cpp \
			src/gui/view/welcomeview.cpp \
			src/gui/mainwindow.cpp \
			src/gui/statusbar.cpp \
			src/gui/sidebar/infosidebar.cpp \
			src/gui/sidebar/searchnodesidebar.cpp \
			src/gui/sidebar/nodepropertywidget.cpp \
			src/gui/sidebar/treeview.cpp \
			src/data/node/textnodecontent.cpp \
			src/data/node/nodeid.cpp \
			src/data/node/node.cpp \
			src/data/node/richtextnodecontent.cpp \
			src/data/model/labelmodel.cpp \
			src/data/model/simpletreemodel.cpp \
			src/data/model/filtermodel.cpp \
			src/data/model/listproxymodel.cpp \
			src/data/model/treemodel.cpp \
			src/data/label.cpp \
			src/data/aboutdata.cpp \


TRANSLATIONS =	silence_de_DE.ts\
				silence_en_GB.ts\
				silence_en_US.ts


