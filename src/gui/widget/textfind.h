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
#include <klineedit.h>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include <QAction>


/*!\class TextFind
 * \brief A find and replace widget.
 *
 * The TextFind widget proviedes a GUI to search and replace text. The replace part is hiden per default and can be shown when needed. It provides the options choosen by the user and emittes signal when certain actions are triggered.
 *
 * This widget has no search or replace capabilities. It just provides a GUI.
 *
 * \authors Manuel Unglaub, Yves Adler
 */
class TextFind : public QWidget
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the TextFind which is a child of parent.
		 * \param parent The parent of this TextFind.
		 */
		TextFind(QWidget *parent = 0);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~TextFind();	

		/*!
		 * Find out if the match case option is selected.
		 * \return True if the match case option is selected.
		 */
		bool getCaseSensitivity();

		/*!
		 * Find out if the match whole word option is selected.
		 * \return True if the match whole word option is selected.
		 */
		bool getWholeWord();

		/*!
		 * Get the string entered in the search lineedit.
		 * \return The entered searchstring.
		 */
		QString getSearchString();

		/*!
		 * Get the string entered in the replace lineedit.
		 * \return The entered replacestring.
		 */
		QString getReplaceString();

		/*!
		 * This function will color the edit field of the TextFind to indicate if a searchstring was found.
		 * \param found Should indicate if a searchstring was found.
		 */
		void setFound(bool found);

	
	public slots:
		/*!
		 * Show the TextFind widget.
		 */
		void show();

		/*!
		 * Toggle the visibility of the replace parts.
		 */
		void showMore();

		/*!
		 * Show the full TextFind widget including the replace parts.
		 */
		void showFull();

	signals:
		/*!
		 * The find next action was triggered.
		 */
		void findNext();

		/*!
		 * The find previous action was triggered.
		 */
		void findPrev();

		/*!
		 * The replace action was triggered.
		 */
		void replace();

		/*!
		 * The replace all action was triggered.
		 */
		void replaceAll();

		/*!
		 * This signal is emitted when the searchstring is changed.
		 * \param searchString The changed searchString.
		 */
		void searchStringChanged(const QString& searchString);

	private slots:
		void findTextChange(const QString &text);
		void nextBtnClicked();
		void prevBtnClicked();
		void replaceBtnClicked();
		void replaceAllBtnClicked();

	private:
		bool showAll;
		QGridLayout *layout;
		QHBoxLayout *optionLayout;
		QFrame *optionPanel;
		KLineEdit *findEdit,
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

