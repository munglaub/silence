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

#ifndef ADDIMAGE_H
#define ADDIMAGE_H

#include <klineedit.h>
#include <knuminput.h>
#include <QCheckBox>
#include <QGridLayout>
#include <QPushButton>


/*!\class AddImage
 * \brief A widget to add images.
 *
 * This widget provides a gui to select an image form the file system and get an HTML image tag with height and width.
 *
 * \author Manuel Unglaub
 */
class AddImage : public QGridLayout
{
	Q_OBJECT

	public:
		/*!
		 * The constructor.
		 *
		 * Constructs the AddImage which is a child of parent.
		 *
		 * \param parent The parent of this AddImage.
		 */
		AddImage(QWidget *parent);

		/*!
		 * The destructor.
		 *
		 * Destroys the object.
		 */
		~AddImage();

	public slots:
		/*!
		 * Connect to this slot to destroy this object.
		 */
		void exit();

	signals:
		/*!
		 * This signal is emitted after the user successfully selected an image and clicked the ok button.
		 *
		 * \param html Containing the HTML image tag, possible with height and width.
		 */
		void addedImage(const QString &html);

	private slots:
		void addImage();
		void browse();

	private:
		KIntSpinBox *sbWidth,
					*sbHeight;
		QCheckBox	*cbWidth,
					*cbHeight;
		KLineEdit	*ledFile;
		QPushButton *btnBrowse,
					*btnOk,
					*btnCancel;
		QWidget *parent;
};


#endif // ADDIMAGE_H


