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

#ifndef NODEPROPERTYWIDGET_H
#define NODEPROPERTYWIDGET_H

#include "data/node/node.h"
#include "gui/widget/labelwidget.h"
#include "gui/widget/syntaxbox.h"
#include <QDockWidget>
#include <QFormLayout>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>


class NodePropertyWidget : public QDockWidget
{
	Q_OBJECT
	
	public:
		NodePropertyWidget(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);
		~NodePropertyWidget();

		void setNode(Node *node);
		void updateLabels();

	private slots:
		void saveNodeInfo();
		void saveLabels();

	private:
		Node *node;
		QVBoxLayout *layout;
		QFrame *frame;
		QTabWidget *tabwidget;

		// nodeinfotab
		QFormLayout *infolayout;
		QFrame *infoframe;
		QLineEdit *nodeName;
		QLabel *creationdate;
		QLabel *modificationdate;
		QPushButton *applyNodeInfo;
		SyntaxBox *syntaxbox;

		// labeltab
		QGridLayout *labellayout;
		QFrame *labelframe;
		LabelWidget *labelwidget;
		QPushButton *applyLabels;

		QWidget* createNodeInfoTab();
		QWidget* createLabelTab();
	
};

#endif // NODEPROPERTYWIDGET_H

