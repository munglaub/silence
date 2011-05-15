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

#ifndef LABEL_H
#define LABEL_H

#include <QList>
#include <QString>
#include <QStringList>

/*!\class Label
 * \brief The basis of the hierarchical labels.
 *
 * This class presents the structure of the hierarchical labels. It contains of functions to access its children and its parent. The most importent member is the text. It contains the value of the label that will be displayed to the user. 
 * The class is not used in the Node class because the nodes just contain a list of QStrings. The hierarchical labels are suposed to help the user to assign labels to a node. Thats their only assignment.
 *
 * \author Manuel Unglaub
 */

class Label
{
	public:
		/*! A constructor.
		 *
		 * Constructs a Label with parent = 0 and text = "".
		 */
		Label();

		/*! A constructor.
		 *
		 * Constructs a Label with parent = 0 and text initialized with the
		 * text parameter.
		 * \param text Setting the text of the Label to text.
		 */
		Label(QString text);

		/*! The destructor.
		 *
		 * Destroys the Label and all its children.
		 */
		~Label();

		/*!
		 * Get the index of this Label in its parents childlist.
		 * \return The index of this Label. If it has no parent it will return 0.
		 */
		int getIndex() const;

		/*!
		 * Get the text of this Label.
		 * \return The text of this Label.
		 */
		QString getText();

		/*!
		 * Set the text of this Label.
		 * \param text Set the member text to the parameter text.
		 */
		void setText(QString text);

		/*!
		 * Get the parent of this Label.
		 * \return The parent of this Label. If there is no parent it will return 0.
		 */
		Label* getParent();

		/*!
		 * Get the child of this Label at the specified index.
		 * \param index The index of the child. It must be between 0 and the childCount().
		 * \return The child at the specified index. If the index is not valid it will return 0.
		 */
		Label* getChild(int index);

		/*!
		 * Add a child to the Label at a specified index.
		 * \param index The index where the child will be inserted in the list of children in this Label. If the index is 0 it will be prepended to the list. If it is childCount() it will be appended. The child will only be inserted if the index is greater or equal to 0 and less or equal to childCount().
		 * \param child The child that will be inserted in the list of children of this Label.
		 * \return True if the child was successful inserted.
		 */
		bool addChild(int index, Label *child);

		/*!
		 * Creates a specified number of children at a specified position.
		 * \param position The index where the children will be inserted in the list of children in this Label. If the index is 0 they will be prepended to the list. If it is childCount() they will be appended. The children will only be created if the index is greater or equal to 0 and less or equal to childCount().
		 * \param count The number of children that will be created.
		 * \return True if all children are successful created.
		 */
		bool addChildren(int position, int count);

		/*!
		 * Deletes the specified number of children at the specified position.
		 * \param position The index of the first child that will be removed. The position must be greater or equal to 0 and less or equal to childCount() - count.
		 * \param count The number of children that will be removed.
		 * \return True if all children are successful removed.
		 */
		bool removeChildren(int position, int count);

		/*!
		 * Get a child of this Label and remove it from the list of children.
		 * \param position The position of the label in the list of children. It must be greater or equal to 0 and less then getChildCount().
		 * \return The label at position or 0 if the position is out of bounds.
		 */
		Label* takeChild(int position);

		/*!
		 * Append a child to this Label.
		 * \param child The child that will be appended to the list of children of this Label.
		 */
		void appendChild(Label *child);

		/*!
		 * Get the number of children of this Label.
		 * \return The number of children of this Label.
		 */
		int childCount();

		/*!
		 * Get a QStringList of this Label and all its sublabels. The list contains the member text of all these Labels.
		 * \return A QStringList of this Label and al its sublabels.
		 */
		QStringList toStringList();

		/*!
		 * Find out if this Label or one of its sublabels members text contains the specified text.
		 * \param labelText The exact text to look for.
		 * \return True if this Label or its sublabels contain a member text with the value of the parameter labelText.
		 */
		bool contains(QString labelText);

		/*!
		 * Find out if this Label or on of its sublabels has the specified id.
		 * \param id The id to look for.
		 * \return True if this Label or its sublabels have the specified id.
		 * \sa contains(), getId()
		 */
		bool contains(int id);

		/*!
		 * Get the id of this Label. The id is a automatic generated uniqe identifier for a Label.
		 * \return The id of this Label.
		 */
		int getId();
	
	protected:
		/*!
		 * Set the parent of this Label.
		 * \param parent The parent of this Label will be set to this parameter.
		 */
		void setParent(Label *parent);

	private:
		static int highestid;
		int id;
		QString text;
		Label* parent;
		QList<Label*> children;
		
		void init(Label *parent, QString text);
};

#endif // LABEL_H

