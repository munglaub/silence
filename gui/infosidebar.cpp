#include "gui/infosidebar.h"
#include <QGridLayout>
#include <QLabel>
#include <QWidget>


InfoSidebar::InfoSidebar(const QString &title, QWidget *parent, Qt::WindowFlags flags)
	: QDockWidget(title, parent, flags)
{
	setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	layout = new QGridLayout();
	
	icon = new QLabel(tr("Icon"));
	icon->setFont(QFont("Times", 34, QFont::Bold));
	layout->addWidget(icon, 0, 0, 1, 2, Qt::AlignCenter);

	created = new QLabel(tr("Created:"));
	created->setFont(QFont("Times", 10, QFont::Bold));
	layout->addWidget(created, 1, 0);
	createdDate = new QLabel(tr("21.03.2008"));
	layout->addWidget(createdDate, 1, 1);
	
	lastedit = new QLabel(tr("Last edit:"));
	lastedit->setFont(QFont("Times", 10, QFont::Bold));
	layout->addWidget(lastedit, 2, 0);
	lasteditDate = new QLabel(tr("17.04.2008"));
	layout->addWidget(lasteditDate, 2, 1);

/*
	QLabel *type = new QLabel(tr("Type:"));
	type->setFont(QFont("Times", 10, QFont::Bold));
	layout->addWidget(type, 3, 0);
	QLabel *typeName = new QLabel(tr("Text"));
	layout->addWidget(typeName, 3, 1);
*/

	labels = new QLabel(tr("Tags:"));
	labels->setFont(QFont("Times", 10, QFont::Bold));
	layout->addWidget(labels, 4, 0);
	labelsData = new QLabel(tr("Private, Important"));
	layout->addWidget(labelsData, 4, 1);

	frame = new QFrame;
	frame->resize(100, 175);
	frame->setLayout(layout);
	setWidget(frame);
}

InfoSidebar::~InfoSidebar()
{
	delete icon;
	delete created;
	delete createdDate;
	delete lastedit;
	delete lasteditDate;
	delete labels;
	delete labelsData;
	delete layout;
	delete frame;
}

void InfoSidebar::setData(Node *data)
{
	node = data;

	// daten aus node setzen
	createdDate->setText(node->getCreationDate().toString(Qt::SystemLocaleShortDate));
	lasteditDate->setText(node->getModificationDate().toString(Qt::SystemLocaleShortDate));

	QString labels;
	QStringListIterator iterator(node->getLabels());
	if (iterator.hasNext())
		labels = iterator.next();
	while (iterator.hasNext())
	{
		labels += ", ";
		labels += iterator.next();
	}

	labelsData->setText(labels);
}


