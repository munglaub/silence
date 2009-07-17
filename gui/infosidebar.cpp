#include "gui/infosidebar.h"
#include <QLabel>
#include <QGridLayout>
#include <QWidget>


InfoSidebar::InfoSidebar(const QString &title, QWidget *parent, Qt::WindowFlags flags)
	: QDockWidget(title, parent, flags)
{
	setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	QGridLayout *layout = new QGridLayout();
	
	QLabel *icon = new QLabel(tr("Icon"));
	icon->setFont(QFont("Times", 34, QFont::Bold));
	layout->addWidget(icon, 0, 0, 1, 2, Qt::AlignCenter);

	QLabel *created = new QLabel(tr("Created:"));
	created->setFont(QFont("Times", 10, QFont::Bold));
	layout->addWidget(created, 1, 0);
	QLabel *createdDate = new QLabel(tr("21.03.2008"));
	layout->addWidget(createdDate, 1, 1);
	
	QLabel *lastedit = new QLabel(tr("Last edit:"));
	lastedit->setFont(QFont("Times", 10, QFont::Bold));
	layout->addWidget(lastedit, 2, 0);
	QLabel *lasteditDate = new QLabel(tr("17.04.2008"));
	layout->addWidget(lasteditDate, 2, 1);

	QLabel *type = new QLabel(tr("Type:"));
	type->setFont(QFont("Times", 10, QFont::Bold));
	layout->addWidget(type, 3, 0);
	QLabel *typeName = new QLabel(tr("Text"));
	layout->addWidget(typeName, 3, 1);

	QLabel *tags = new QLabel(tr("Tags:"));
	tags->setFont(QFont("Times", 10, QFont::Bold));
	layout->addWidget(tags, 4, 0);
	QLabel *tagsData = new QLabel(tr("Private, Important"));
	layout->addWidget(tagsData, 4, 1);

	QWidget *widget = new QWidget();
	widget->setFixedHeight(175);
	widget->setLayout(layout);
	setWidget(widget);
}

InfoSidebar::~InfoSidebar()
{
}

