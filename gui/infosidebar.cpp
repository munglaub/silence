#include "gui/infosidebar.h"
#include <QGridLayout>
#include <QLabel>
#include <QWidget>


InfoSidebar::InfoSidebar(const QString &title, QWidget *parent, Qt::WindowFlags flags)
	: QDockWidget(title, parent, flags)
{
	setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	layout = new QGridLayout();

	int row = 0;
	
	icon = new QLabel(tr("Icon"));
	icon->setFont(QFont("Times", 34, QFont::Bold));
	layout->addWidget(icon, row, 0, 1, 2, Qt::AlignCenter);
	++row;

	caption = new QLabel(tr(""));
	caption->setFont(QFont("Times", 10, QFont::Bold));
	layout->addWidget(caption, row, 0, 1, 2, Qt::AlignCenter);
	++row;

	created = new QLabel(tr("Created:"));
	created->setFont(QFont("Times", 10, QFont::Bold));
	layout->addWidget(created, row, 0);
	createdDate = new QLabel(tr("21.03.2008"));
	layout->addWidget(createdDate, row, 1);
	++row;

	lastedit = new QLabel(tr("Last edit:"));
	lastedit->setFont(QFont("Times", 10, QFont::Bold));
	layout->addWidget(lastedit, row, 0);
	lasteditDate = new QLabel(tr("17.04.2008"));
	layout->addWidget(lasteditDate, row, 1);
	++row;

	type = new QLabel(tr("Type:"));
	type->setFont(QFont("Times", 10, QFont::Bold));
	layout->addWidget(type, row, 0);
	typeName = new QLabel(tr(""));
	layout->addWidget(typeName, row, 1);
	++row;

	labels = new QLabel(tr("Labels:"));
	labels->setFont(QFont("Times", 10, QFont::Bold));
	layout->addWidget(labels, row, 0);
	labelsData = new QLabel(tr("Private, Important"));
	layout->addWidget(labelsData, row, 1);
	

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

	// set node infos
	caption->setText(node->getCaption());
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

	// set content infos
	if (node->getContent())
	{
		typeName->setText(node->getContent()->getMimeType());
		type->setHidden(false);
		typeName->setHidden(false);
	} else {
		type->setHidden(true);
		typeName->setHidden(true);
	}
}


