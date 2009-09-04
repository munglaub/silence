#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

class AboutDialog : public QDialog
{
	public:
		AboutDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
		~AboutDialog();

	private:
                QGridLayout *subLayout,
                            *layout;
                QLabel      *logo,
                            *version,
                            *authors;
		QPushButton *quit;
};

#endif // ABOUTDIALOG_H
