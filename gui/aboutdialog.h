#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

class AboutDialog : public QDialog
{
	public:
		AboutDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
		~AboutDialog();
};

#endif // ABOUTDIALOG_H
