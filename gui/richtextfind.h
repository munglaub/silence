#ifndef RICHTEXTFIND_H
#define RICHTEXTFIND_H

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>


class RichTextFind : public QWidget
{
	Q_OBJECT

	public:
		RichTextFind(QTextEdit *editor, QWidget *parent = 0);
		~RichTextFind();	
	
	public slots:
		void hide();
		void show();

	private slots:
		void findit();
		void unhighlighte();

	private:
		QTextEdit *editor;

		QHBoxLayout *layout;
		QLineEdit *findEdit;
		QPushButton *findBtn,
					*hideFind;
		
		bool isFirstTime;

};

#endif // RICHTEXTFIND_H

