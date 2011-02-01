project( silence )
cmake_minimum_required( VERSION 2.6 )
set ( CMAKE_BUILD_TYPE Release )
add_definitions ( -Wall )
find_package ( Qt4 REQUIRED )
find_package ( KDE4 REQUIRED )
include_directories (
	${CMAKE_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	${KDE4_INCLUDES}
	)
set ( silence_HDRS
	src/controller.h
	src/constants.h
	src/data/node/nodeid.h
	src/data/node/abstractnodecontent.h
	src/data/node/abstractcontentchange.h
	src/data/node/textcontentchange.h
	src/data/node/rtfcontentchange.h
	src/data/node/customnodecontent.h
	src/data/node/customnodeitem.h
	src/data/node/customnodetypedefinition.h
	src/data/node/customcontentchange.h
	src/data/label.h
	src/data/aboutdata.h
	src/data/model/simpletreemodel.h
	src/gui/view/contentview.h
	src/gui/widget/syntaxbox.h
	src/commandline/cmdmain.h
	src/commandline/cmdlineoptions.h
	src/commandline/nodefilter.h
	src/utils/listutils.h
	src/persistence/xmldatastore.h
	src/data/node/node.h
	src/data/node/textnodecontent.h
	src/data/node/richtextnodecontent.h
	src/data/model/labelmodel.h
	src/data/model/treemodel.h
	src/data/model/listproxymodel.h
	src/data/model/filtermodel.h
	src/gui/mainwindow.h
	src/gui/sistatusbar.h
	src/gui/menu/viewmenu.h
	src/gui/menu/silencemenu.h
	src/gui/dialog/newnodedialog.h
	src/gui/dialog/newlinkdialog.h
	src/gui/dialog/labelmanagementdialog.h
	src/gui/dialog/exportsilencexmldialog.h
	src/gui/sidebar/treeview.h
	src/gui/sidebar/infosidebar.h
	src/gui/sidebar/searchnodesidebar.h
	src/gui/sidebar/nodepropertywidget.h
	src/gui/sidebar/navigationsidebar.h
	src/gui/view/abstractcontentview.h
	src/gui/view/textedit.h
	src/gui/view/welcomeview.h
	src/gui/view/richtextedit.h
	src/gui/view/customcontentview.h
	src/gui/widget/rtfedit.h
	src/gui/widget/textfind.h
	src/gui/widget/labelwidget.h
	src/gui/widget/inputwidget.h
	src/gui/widget/addimage.h
	src/gui/widget/addtable.h
	src/gui/widget/searchnodeoptions.h
	src/gui/widget/labellist.h
	src/gui/widget/notificationbox.h
	src/gui/widget/nodetypemanager.h
	src/gui/widget/nodetypebuilder.h
	src/gui/widget/nodetypespanel.h
	src/gui/widget/customnodeelement.h
	src/gui/widget/customdatawidget.h
	src/gui/widget/customstringdatawidget.h
	src/gui/widget/customtextdatawidget.h
	src/gui/widget/customintegerdatawidget.h
	src/gui/widget/customnumberdatawidget.h
	src/gui/widget/custombooleandatawidget.h
	src/gui/widget/customimagedatawidget.h
	)

set ( silence_SRCS
	src/main.cpp
	src/controller.cpp
	src/persistence/xmldatastore.cpp
	src/data/node/node.cpp
	src/data/node/nodeid.cpp
	src/data/node/textnodecontent.cpp
	src/data/node/richtextnodecontent.cpp
	src/data/node/textcontentchange.cpp
	src/data/node/rtfcontentchange.cpp
	src/data/node/customnodecontent.cpp
	src/data/node/customnodeitem.cpp
	src/data/node/customnodetypedefinition.cpp
	src/data/node/customcontentchange.cpp
	src/data/label.cpp
	src/data/aboutdata.cpp
	src/data/model/labelmodel.cpp
	src/data/model/treemodel.cpp
	src/data/model/simpletreemodel.cpp
	src/data/model/filtermodel.cpp
	src/data/model/listproxymodel.cpp
	src/gui/mainwindow.cpp
	src/gui/sistatusbar.cpp
	src/gui/menu/viewmenu.cpp
	src/gui/menu/silencemenu.cpp
	src/gui/dialog/newnodedialog.cpp
	src/gui/dialog/newlinkdialog.cpp
	src/gui/dialog/labelmanagementdialog.cpp
	src/gui/dialog/exportsilencexmldialog.cpp
	src/gui/sidebar/treeview.cpp
	src/gui/sidebar/infosidebar.cpp
	src/gui/sidebar/searchnodesidebar.cpp
	src/gui/sidebar/nodepropertywidget.cpp
	src/gui/sidebar/navigationsidebar.cpp
	src/gui/view/textedit.cpp
	src/gui/view/contentview.cpp
	src/gui/view/welcomeview.cpp
	src/gui/view/richtextedit.cpp
	src/gui/view/customcontentview.cpp
	src/gui/widget/rtfedit.cpp
	src/gui/widget/textfind.cpp
	src/gui/widget/labelwidget.cpp
	src/gui/widget/syntaxbox.cpp
	src/gui/widget/inputwidget.cpp
	src/gui/widget/addimage.cpp
	src/gui/widget/addtable.cpp
	src/gui/widget/searchnodeoptions.cpp
	src/gui/widget/labellist.cpp
	src/gui/widget/notificationbox.cpp
	src/gui/widget/nodetypemanager.cpp
	src/gui/widget/nodetypebuilder.cpp
	src/gui/widget/nodetypespanel.cpp
	src/gui/widget/customnodeelement.cpp
	src/gui/widget/customstringdatawidget.cpp
	src/gui/widget/customtextdatawidget.cpp
	src/gui/widget/customintegerdatawidget.cpp
	src/gui/widget/customnumberdatawidget.cpp
	src/gui/widget/custombooleandatawidget.cpp
	src/gui/widget/customimagedatawidget.cpp
	src/commandline/cmdmain.cpp
	src/commandline/cmdlineoptions.cpp
	src/commandline/nodefilter.cpp
	src/utils/listutils.cpp
	)

add_subdirectory( icons )
add_subdirectory( po )

set ( silence_RSCS
	silence.qrc
	)
QT4_ADD_RESOURCES(RSCS ${silence_RSCS})

set ( silence_MOCS
	src/persistence/abstractdatastore.h
	)
QT4_WRAP_CPP(MOCS ${silence_MOCS})

kde4_add_executable ( silence
	${silence_SRCS}
	${UIS}
	${RSCS}
	${TRS}
	${MOCS}
)
target_link_libraries ( silence
	${KDE4_KDEUI_LIBS}
	${KDE4_KIO_LIBS}
	${KDE4_KTEXTEDITOR_LIBS}
)

install(TARGETS silence  ${INSTALL_TARGETS_DEFAULT_ARGS} )
install(FILES Silence.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES src/silenceui.rc  DESTINATION ${DATA_INSTALL_DIR}/silence)





