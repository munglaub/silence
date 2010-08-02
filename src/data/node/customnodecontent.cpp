/*
 * Silence
 *
 * Copyright (C) 2010 Manuel Unglaub
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

#include "src/data/node/customnodecontent.h"

CustomNodeContent::CustomNodeContent()
{
//TODO: hier muss eine customnodetypedefinition uebergeben werden
	// TODO: implement
}

CustomNodeContent::~CustomNodeContent()
{
	// TODO: implement
}

AbstractContentView* CustomNodeContent::getWidget()
{
	// TODO: implement
	return 0;
}

QHash<QString, QString>* CustomNodeContent::getMetaInfos()
{
	// TODO: implement
	return 0;
}

void CustomNodeContent::addMetaInfo(QString key, QString value)
{
	// TODO: implement
}

QString CustomNodeContent::getMimeType()
{
//TODO: typ aus der customnodedefinition zurueckgeben
	// TODO: implement
	return "";
}

bool CustomNodeContent::contains(const QString& value)
{
	// TODO: implement
	return false;
}

QDomElement CustomNodeContent::getXmlData(QDomDocument &doc)
{
	// TODO: implement
	return QDomElement();
}

void CustomNodeContent::setXmlData(QDomElement &xmlNode)
{
	// TODO: implement
}

QPixmap CustomNodeContent::getPixmap()
{
	// TODO: implement
	return QPixmap();
}

QIcon CustomNodeContent::getIcon()
{
	// TODO: implement
	return QIcon();
}

QString CustomNodeContent::toString()
{
	// TODO: implement
	return "";
}


