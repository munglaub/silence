#ifndef TEXTEDITFIND_H
#define TEXTEDITFIND_H

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <Qsci/qsciscintilla.h>
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
		void findNext();
		void findPrevious();

	private:
		QsciScintilla *editor;

		QHBoxLayout *layout;
		QLineEdit *findEdit;
		QPushButton *nextBtn,
					*prevBtn,
					*hideBtn;
		QCheckBox 	*caseCbx,
					*wordCbx;

	void find(bool forward);
};

#endif // TEXTEDITFIND_H

