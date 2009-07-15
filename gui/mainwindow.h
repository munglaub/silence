#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <Qsci/qsciscintilla.h>

class MainWindow : public QMainWindow
{

	public:
		MainWindow(QWidget *parent = 0);
		~MainWindow();
	private:
		QsciScintilla *textEdit;
};

#endif // MAINWINDOW_H


