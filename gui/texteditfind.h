#ifndef TEXTEDITFIND_H
#define TEXTEDITFIND_H

#include <QHBoxLayout>
#include <QLineEdit>
#include <Qsci/qsciscintilla.h>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>


class TextEditFind : public QWidget
{
	Q_OBJECT

	public:
		TextEditFind(QsciScintilla *editor, QWidget *parent = 0);
		~TextEditFind();	
	
	public slots:
		void show();

	private slots:
		void findFirst();

	private:
		QsciScintilla *editor;

		QHBoxLayout *layout;
		QLineEdit *findEdit;
		QPushButton *findBtn,
					*hideBtn;
		
};

#endif // TEXTEDITFIND_H

