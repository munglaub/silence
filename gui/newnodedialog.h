#ifndef NEWNODEDIALOG_H
#define NEWNODEDIALOG_H

#include "node/abstractnodecontent.h"
#include <QComboBox>
#include <QDialog>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>


class NewNodeDialog : public QDialog
{
	Q_OBJECT

	public:
		NewNodeDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
		~NewNodeDialog();

		QString getCaption() const;
		AbstractNodeContent* getContent() const;
		QStringList getLabels() const;

	private slots:
		void indexChanged(int index);
		void addLabel();

	private:
		QVBoxLayout *baselayout;

		QFormLayout *namelayout;
		QLineEdit *nameedit;

		QGridLayout *typelayout;
		QLabel *lbltype;
		QComboBox *typebox;
		QLabel *lblhighlight;
		QComboBox *synbox;

		// labels
		QGroupBox *labelbox;
		QGridLayout *labellayout;
		QLineEdit *newLabel;
		QPushButton *btnAddLabel;
		QListWidget *availlabels;

		// butons
		QPushButton *cancel,
					*ok;
		QGridLayout *buttonlayout;
};

#endif // NEWNODEDIALOG_H


