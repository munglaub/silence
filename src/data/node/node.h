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

#ifndef NODE_H
#define NODE_H

#include "src/data/node/abstractnodecontent.h"
#include "src/data/node/nodeid.h"
#include <QDateTime>
#include <QString>
#include <QStringList>


/*!\class Node
 * \brief The basis of the data structure.
 *
 * A node contains of caption, creation date, modification date, labels and content. It has a parent and can have child nodes. That means the basic structure is a tree.
 *
 * \author Manuel Unglaub
 */
class Node : public QObject
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs a node which is a child of parent.
		 * \param parent The parent of this Node.
		 */
		Node(Node *parent = 0); 

		/*! The destructor.
		 *
		 * Destroys the object including its children.
		 */
		~Node();

		/*!
		 * Get the position of this node in its parents list of children.
		 * \return The position index of this node.
		 */
		int getIndex() const;

		/*!
		 * Get the parent of this node.
		 * \return The parent of this node or 0 if it does not have one.
		 */
		Node* getParent() const;

		/*!
		 * Get a list containing this node and all nodes below it.
		 * \return A list of this node and all nodes below it.
		 */
		QList<Node*> toNodeList();

		/*!
		 * Get the id of this node.
		 * \return The NodeId of this node.
		 * \sa setId()
		 */
		NodeId getId();

		/*!
		 * Set the id of this node.
		 * \param id The NodeId which will be assigned to this node.
		 * \sa getId()
		 */
		void setId(NodeId *id);

		/*!
		 * Find out if a specific node is within the nodes below this node.
		 * \param node The node to look for.
		 * \return True if the node is within the nodes below this node, false if not.
		 */
		bool contains(Node* node);

		/*!
		 * Add a number of children at a specific position.
		 * \param position The position where the children will be created. It must be greater or equal 0 and less or equal to getChildCount().
		 * \param count The number of children that will be created.
		 * \return True if it was successfull.
		 * \sa getChild(), takeChild(), removeChildren(), addChild()
		 */
		bool addChildren(int position, int count);

		/*!
		 * Get a specific child of this node.
		 * \param index The index of the requested child. It must be greater or equal to 0 and less then getChildCount().
		 * \return The node at position index in the list of childs or 0 if the index is out of bounds.
		 * \sa addChildren(), takeChild(), removeChildren(), addChild()
		 */
		Node* getChild(int index) const;

		/*!
		 * Get the number of children of this node.
		 * \return The number of children of this node.
		 */
		int getChildCount() const;

		/*!
		 * Remove children from this node.
		 * \param position The position of the children which will be removed. The position must be greater or equal to 0 and less then position + getChildCount() - count.
		 * \param count The number of children which will be removed.
		 * \return True if the children are removed successfull.
		 * \sa getChild(), takeChild(), addChildren(), addChild()
		 */
		bool removeChildren(int position, int count);

		/*!
		 * Get a child of this node and remove it from the nodes list of children.
		 * \param position The position of the node in the list of children. It must be greater or equal to 0 and less then getChildCount().
		 * \return The node position or 0 if the position is out of bounds.
		 * \sa getChild(), addChildren(), removeChildren(), addChild()
		 */
		Node* takeChild(int position);

		/*!
		 * Add a node as child to this node at a specific position.
		 * \param child The node which will be added to the childs of this node.
		 * \param position The posittion of the node in the list of children. It must be greater or equal then 0 and less or equal to getChildCount().
		 * \return True if it was successfull.
		 * \sa getChild(), takeChild(), removeChildren(), addChildren()
		 */
		bool addChild(Node* child, int position);
		
		/*!
		 * Get the caption of this node.
		 * \return The caption of this node.
		 * \sa setCaption()
		 */
		QString getCaption() const;

		/*!
		 * Set the caption of this node. This will also change the modification date of this node and emit the changed() signal.
		 * \param caption The new caption of this node.
		 * \return True if it was successfull.
		 * \sa getCaption()
		 */
		bool setCaption(QString caption);

		/*!
		 * Get the content of this node.
		 * \return The content of this node.
		 * \sa setContent()
		 */
		AbstractNodeContent* getContent() const;

		/*!
		 * Set the content of this node. This will also change the modification date of this node and emit the changed() signal. Whenever the changed() signal of the content is emited the modification date will be updated and the changed() signal of this node will be emited.
		 * \param content The new content of this node.
		 * \sa getContent()
		 */
		void setContent(AbstractNodeContent *content);

		/*!
		 * Get the date this node was created.
		 * \return The creation date of this node.
		 * \sa setCreationDate()
		 */
		QDateTime getCreationDate() const;

		/*!
		 * Set the creation date of this node. Should be used to initialize the node after loading it from the persistence layer.
		 * \param date The creation date of this node.
		 * \sa getCreationDate()
		 */
		void setCreationDate(QDateTime date);

		/*!
		 * Get the modification date of this node.
		 * \return The date of the last modification of this node.
		 * \sa setModificationDate()
		 */
		QDateTime getModificationDate() const;

		/*!
		 * Set the modification date of this node. Should be used to initialize the node after loading it form the persistence layer.
		 * \param date The modification date of this node.
		 * \sa getModificationDate()
		 */
		void setModificationDate(QDateTime date);

		/*!
		 * Get all labels assigned to this node.
		 * \return A pointer to the QStringList with the labes of this node.
		 * \sa addLabel(), addLabels(), removeLabel()
		 */
		QStringList* getLabels();

		/*!
		 * Add a label to this node. This will also change the modification date of this node and emit the changed() signal.
		 * \param label This label will be added to this node.
		 * \sa getLabels(), addLabels(), removeLabel()
		 */
		void addLabel(QString label);

		/*!
		 * Add labels to this node. This will also change the modification date of this node and emit the changed() signal.
		 * \param labels The list of labels which will be added to this node.
		 * \sa addLabel(), getLabels(), removeLabel()
		 */
		void addLabels(QStringList labels);

		/*!
		 * Remove a label from this node. If the removal of the label was successfull the modification date of the node will be changed and the changed() signal will be emitted.
		 * \param label The label which will be removed from this node.
		 * \return True if the label was removed.
		 * \sa addLabel(), addLabels(), getLabels()
		 */
		bool removeLabel(QString label);

		/*!
		 * Transform the node to a QString.
		 *
		 * \return The node as a QString.
		 */
		QString toString();
		
	signals:
		/*!
		 * Signal is emitted when the caption, labels or the content changes.
		 * \param node A pointer to this node.
		 */
		void changed(Node *node);

	protected:
		/*!
		 * Set a new parent for this node.
		 * \param parent The parent of this node.
		 * \sa getParent()
		 */
		void setParent(Node* parent);

	private slots:
		void change();

	private:
		NodeId *id;
		QString caption;
		AbstractNodeContent *content;
		QDateTime creationDate;
		QDateTime modificationDate;
		QStringList labels;
		
		Node *parent;
		QList<Node*> children;
};

#endif // NODE_H


