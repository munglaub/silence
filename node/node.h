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

#include "node/abstractnodecontent.h"
#include "node/nodeid.h"
#include <QString>
#include <QStringList>
#include <QDateTime>


class Node : public QObject
{
	Q_OBJECT

	public:
		// Konstruktoren & Destruktoren
		Node(Node *parent = 0); 
		~Node();

		int getIndex() const;
		Node* getParent() const;
		NodeId getId() const;
		void setId(NodeId id);

		// children
//		void addChild(Node *child);
//		bool addChild(Node *child, int position);
		bool addChildren(int position, int count);
		Node* getChild(int index) const;
		int getChildCount() const;
		bool removeChildren(int position, int count);
		

		// caption
		QString getCaption() const;
		bool setCaption(QString caption);
		
		// content
		AbstractNodeContent* getContent() const;
		void setContent(AbstractNodeContent *content);

		// dates
		QDateTime getCreationDate() const;
		void setCreationDate(QDateTime date);
		QDateTime getModificationDate() const;
		void setModificationDate(QDateTime date);

		int columnCount() const;

		// labels
		QStringList* getLabels();
		void addLabel(QString label);
		void addLabels(QStringList labels);
		
	private slots:
		void change();
	
	signals:
		void changed(Node *node);

	private:
		NodeId id;
		QString caption;
		AbstractNodeContent *content;
		QDateTime creationDate;
		QDateTime modificationDate;
		QStringList labels;
/*
		icon
		QString mimeType;
*/		
		Node *parent;
		QList<Node*> children;
};

#endif // NODE_H
