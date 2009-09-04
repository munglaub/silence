#ifndef TEXTFIND_H
#define TEXTFIND_H

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>


class TextFind : public QWidget
{
	Q_OBJECT

	public:
		TextFind(QWidget *parent = 0);
		~TextFind();	

		bool getCaseSensitivity();
		bool getWholeWord();
		QString getSearchString();

		QPushButton* getPrevBtn();
		QPushButton* getNextBtn();
		QLineEdit* getFindEdit();

		void setFound(bool found);

	
	public slots:
		void show();

	private slots:
		void findTextChange(const QString &text);

	private:
		QHBoxLayout *layout;
		QLineEdit *findEdit;
		QPushButton *nextBtn,
					*prevBtn,
					*hideBtn;
		QCheckBox 	*caseCbx,
					*wordCbx;

};

#endif // TEXTFIND_H

