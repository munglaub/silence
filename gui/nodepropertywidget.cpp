#include "nodepropertywidget.h"
#include "controller.h"

NodePropertyWidget::NodePropertyWidget(const QString &title, QWidget *parent, Qt::WindowFlags flags)
	: QDockWidget(title, parent, flags)
{
	setAllowedAreas(Qt::AllDockWidgetAreas);
	setFloating(true);
	layout = new QVBoxLayout;

	tabwidget = new QTabWidget(this);
	layout->addWidget(tabwidget);
	tabwidget->addTab(createNodeInfoTab(), tr("Nodeinfos"));
	tabwidget->addTab(createLabelTab(), tr("Labels"));
	tabwidget->addTab(createMetaInfoTab(), tr("Metainfos"));

	frame = new QFrame;
	frame->setLayout(layout);
	setWidget(frame);
}

NodePropertyWidget::~NodePropertyWidget()
{
}

QWidget* NodePropertyWidget::createNodeInfoTab()
{
	QFormLayout *infolayout = new QFormLayout;
	nodeName = new QLineEdit;
	infolayout->addRow(tr("Node name:"), nodeName);
	
	syntax = new QComboBox;
	syntax->addItem(tr("None"));
	syntax->addItem(tr("Bash"));
	syntax->addItem(tr("Batch"));
	syntax->addItem(tr("CMake"));
	syntax->addItem(tr("C++"));
	syntax->addItem(tr("C#"));
	syntax->addItem(tr("CSS"));
	syntax->addItem(tr("D"));
	syntax->addItem(tr("Diff"));
	syntax->addItem(tr("HTML"));
	syntax->addItem(tr("IDL"));
	syntax->addItem(tr("Java"));
	syntax->addItem(tr("JavaScript"));
	syntax->addItem(tr("Lua"));
	syntax->addItem(tr("Makefile"));
	syntax->addItem(tr("Perl"));
	syntax->addItem(tr("POV"));
	syntax->addItem(tr("Python"));
	syntax->addItem(tr("Ruby"));
	syntax->addItem(tr("SQL"));
	syntax->addItem(tr("TeX"));
	syntax->addItem(tr("VHDL"));
	infolayout->addRow(tr("Syntax:"), syntax);
	
	creationdate = new QLabel("");
	infolayout->addRow(tr("Creationdate:"), creationdate);

	modificationdate = new QLabel("");
	infolayout->addRow(tr("Modificationdate:"), modificationdate);

	applyNodeInfo = new QPushButton(tr("Apply"));
	infolayout->addRow("", applyNodeInfo);
	connect(applyNodeInfo, SIGNAL(clicked()), this, SLOT(saveNodeInfo()));

	QFrame *infoframe = new QFrame;
	infoframe->setLayout(infolayout);
	return infoframe;
}

QWidget* NodePropertyWidget::createLabelTab()
{

	labellayout = new QGridLayout;
	newLabel = new QLineEdit;
	labellayout->addWidget(newLabel, 0, 0);
	btnAddLabel = new QPushButton(tr("Add"));
	connect(btnAddLabel, SIGNAL(clicked()), this, SLOT(addLabel()));
	labellayout->addWidget(btnAddLabel, 0, 1);
	availlabels = new QListWidget;
	availlabels->setSelectionMode(QAbstractItemView::MultiSelection);
	availlabels->addItems(*Controller::create()->getDataStore()->getLabels());
	labellayout->addWidget(availlabels, 1, 0, 1, 2);

	applyLabels = new QPushButton(tr("Apply"));
	connect(applyLabels, SIGNAL(clicked()), this, SLOT(saveLabels()));
	labellayout->addWidget(applyLabels, 2, 1);

	QFrame *labelframe = new QFrame;
	labelframe->setLayout(labellayout);
	return labelframe;
}

QWidget* NodePropertyWidget::createMetaInfoTab()
{
	return new QLabel("bar");
}

void NodePropertyWidget::setNode(Node* node)
{
	// nodeinfos
	this->node = node;
	nodeName->setText(node->getCaption());
	syntax->setEnabled(false);
	if (node->getContent() != 0)
		if (node->getContent()->getMimeType() == "text/plain")
			syntax->setEnabled(true);

	creationdate->setText(node->getCreationDate().toString(Qt::SystemLocaleShortDate));
	modificationdate->setText(node->getModificationDate().toString(Qt::SystemLocaleShortDate));
	
	// labels
	availlabels->clear();
	QStringList *allLabels = Controller::create()->getDataStore()->getLabels();
	for (int i=0; i<allLabels->size(); ++i)
	{
		availlabels->addItem(allLabels->at(i));
		if (node->getLabels()->contains(allLabels->at(i)))
			availlabels->item(availlabels->count() - 1)->setSelected(true);
	}

	// metainfos
}


void NodePropertyWidget::saveNodeInfo()
{
	node->setCaption(nodeName->text());
	if (syntax->isEnabled())
		node->getContent()->addMetaInfo("Syntax", syntax->currentText());
}

void NodePropertyWidget::saveLabels()
{
	node->getLabels()->clear();
	for (int i=0; i<availlabels->selectedItems().size(); ++i)
	{
		QString label = availlabels->selectedItems().at(i)->text();
		//if (!node->getLabels().contains(label))
			node->addLabel(label);
	}
}

void NodePropertyWidget::addLabel()
{
	if (newLabel->text().isEmpty())
		return;
	availlabels->addItem(newLabel->text());
	availlabels->item(availlabels->count() - 1)->setSelected(true);
	QStringList *labels = Controller::create()->getDataStore()->getLabels();
	if (!labels->contains(newLabel->text()))
		labels->append(newLabel->text());
}


