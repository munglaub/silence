#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QVBoxLayout>

class AboutDialog : public QDialog
{
	public:
		AboutDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
		~AboutDialog();
	private:
		QVBoxLayout *layout;

};

#endif // ABOUTDIALOG_H
