#ifndef NEWNODEDIALOG_H
#define NEWNODEDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QComboBox>
#include "node/abstractnodecontent.h"
#include <QLabel>

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

	private:
		QVBoxLayout *baselayout;

		QFormLayout *namelayout;
		QLineEdit *nameedit;

		QGridLayout *typelayout;
		QLabel *lbltype;
		QComboBox *typebox;
		QLabel *lblhighlight;
		QComboBox *synbox;
};

#endif // NEWNODEDIALOG_H


