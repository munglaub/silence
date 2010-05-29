/*
 * Silence
 *
 * Copyright (C) 2009, 2010 Manuel Unglaub <m.unglaub@gmail.com>
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


/*!\class SearchNodeOptions
 * \brief A widget for the SearchNodeSidebar.
 *
 * This widget provides a gui for the SearchNodeSidebar to restrict the search with various options. It consists of a row with a caption and a button to extend it and show its full functionallity.
 *
 * \author Manuel Unglaub
 */
class SearchNodeOptions : public QFrame
{
	Q_OBJECT

	public:
		/*!
		 * The constructor.
		 *
		 * Constructs a SearchNodeOptions widget which is a child of parent and has the provided window flags.
		 *
		 * \param parent The parent of this SearchNodeOptions.
		 * \param f The window flags of this SearchNodeOptions.
		 */
		SearchNodeOptions(QWidget *parent = 0, Qt::WindowFlags f = 0);

		/*!
		 * The destructor.
		 *
		 * Destroys the object.
		 */
		~SearchNodeOptions();

	signals:
		/*!
		 * This signal is emitted after the fulltext option changed.
		 *
		 * \param enabled If true the fulltext option is enabled.
		 */
		void enabledFulltext(bool enabled);

		/*!
		 * This signal is emitted after the mimetype option is de-/activated.
		 *
		 * \param enabled If true the mimetype option is activated.
		 */
		void enabledMimetype(bool enabled);

		/*!
		 * This signal is emitted after the creation date option is de-/activated.
		 *
		 * \param enabled If true the creation date option is activated.
		 */
		void enabledCreationDate(bool enabled);

		/*!
		 * This signal is emitted after the modification date option is de-/activated.
		 *
		 * \param enabled If true the modification date option is activated.
		 */
		void enabledModificationDate(bool enabled);

		/*!
		 * This signal is emitted after a mimetype is selected.
		 *
		 * \param mimetype The selected mimetype.
		 */
		void mimetypeSelected(QString mimetype);

		/*!
		 * This signal is emitted after the starting date of the creation date range is changed.
		 *
		 * \param date The new starting date of the creation date range.
		 */
		void changedCreatedFrom(QDate date);

		/*!
		 * This signal is emitted after the ending date of the creation date range is changed.
		 *
		 * \param date The new ending date of the creation date range.
		 */
		void changedCreatedTo(QDate date);

		/*!
		 * This signal is emitted after the starting date of the modification date range is changed.
		 *
		 * \param date The new starting date of the modification date range.
		 */
		void changedModifiedFrom(QDate date);

		/*!
		 * This signal is emitted after the ending date of the modification date range is changed.
		 *
		 * \param date The new ending date of the modification date range.
		 */
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


