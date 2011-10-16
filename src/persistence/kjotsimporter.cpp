/*
 * Silence
 *
 * Copyright (C) 2011 Manuel Unglaub
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
 *
 * You should have received a copy of the GNU General Public License
 * along with Silence.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "src/persistence/kjotsimporter.h"

#include<iostream>
KjotsImporter::KjotsImporter(Node *node, QString fileName)
{
	this->rootNode = node;
	this->fileName = fileName;

	// needs to be saved
	this->importedNodes << rootNode;

	std::cout << "foo" << std::endl;
}

KjotsImporter::~KjotsImporter()
{
	// TODO: implement
}

QList<Node*> KjotsImporter::import(){

	//TODO: wrong!!
	return importedNodes;
}

