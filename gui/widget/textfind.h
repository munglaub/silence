/*
 * Silence
 *
 * Copyright (C) 2009 Manuel Unglaub, Yves Adler
 *
 * This file is part of Silence.
 *
 * Silence is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version GPLv2 only of the License.
 *
 * Silence is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Silence.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TEXTFIND_H
#define TEXTFIND_H

#include <QCheckBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include <QAction>


class TextFind : public QWidget
{
	Q_OBJECT

	public:
		TextFind(QWidget *parent = 0);
		~TextFind();	

		bool getCaseSensitivity();
		bool getWholeWord();
		QString getSearchString();
		QString getReplaceString();

		QPushButton* getPrevBtn();
		QPushButton* getNextBtn();
		QLineEdit* getFindEdit();

		QPushButton* getReplaceBtn();
		QPushButton* getReplaceAllBtn();

		void setFound(bool found);

	
	public slots:
		void show();
		void showMore();

	private slots:
		void findTextChange(const QString &text);

	private:
		bool showAll;
		QGridLayout *layout;
		QHBoxLayout *optionLayout;
		QFrame *optionPanel;
		QLineEdit *findEdit,
				*replaceEdit;
		QPushButton *nextBtn,
					*prevBtn,
					*hideBtn,
					*moreBtn,
					*replaceBtn,
					*replaceAllBtn;
		QCheckBox 	*caseCbx,
					*wordCbx;
		QAction *abortAction;

};

#endif // TEXTFIND_H

