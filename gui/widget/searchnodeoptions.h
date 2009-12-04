/*
 * Silence
 *
 * Copyright (C) 2009 Manuel Unglaub
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

#ifndef SEARCHNODEOPTIONS_H
#define SEARCHNODEOPTIONS_H

#include <QCheckBox>
#include <QComboBox>
#include <QDateEdit>
#include <QFrame>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>


class SearchNodeOptions : public QFrame
{
	Q_OBJECT

	public:
		SearchNodeOptions(QWidget * parent = 0, Qt::WindowFlags f = 0);
		~SearchNodeOptions();

	signals:
		void enabledFulltext(bool enabled);
		void enabledMimetype(bool enabled);
		void enabledCreationDate(bool enabled);
		void enabledModificationDate(bool enabled);

		void mimetypeSelected(QString mimetype);
		void changedCreatedFrom(QDate date);
		void changedCreatedTo(QDate date);
		void changedModifiedFrom(QDate date);
		void changedModifiedTo(QDate date);

	private slots:
		void toggleVisibility();
		void enableMimetype(bool enabled);
		void enableCreationDate(bool enabled);
		void enableModificationDate(bool enabled);
		void enableFulltext(bool enabled);
		void changedMimetype(QString mimetype);
		void changeCreatedFrom(QDate date);
		void changeCreatedTo(QDate date);
		void changeModifiedFrom(QDate date);
		void changeModifiedTo(QDate date);

	private:
	bool showOptions;
		QGridLayout *layout,
					*optboxlayout,
					*dateboxlayout;
		QFrame *datebox;
		QLabel *title;
		QPushButton *showBtn;

		QGroupBox *optionbox;
		QRadioButton	*captionBtn,
						*fulltextBtn;
		QCheckBox 	*cbMime,
					*cbCreated,
					*cbModified;
		QDateEdit 	*fromCreated,
					*toCreated,
					*fromModified,
					*toModified;
		QComboBox *mimeCombo;
		QLabel	*clbland,
				*mlbland;

		QWidget* createOptionbox();
};

#endif // SEARCHNODEOPTIONS_H


