#include "comMorse.h"
#include <iostream>
#include <QtDebug>


using namespace std;

comMorse::comMorse(QObject *parent) : QObject(parent)
{

}

void comMorse::setTreeMorse(treeNode* tree)
{
	treeMorse = tree;
}

QString comMorse::codingStringMorse(QString data)
{
	// QString to string
	string dataToString;
	dataToString = data.toStdString();

	// TEST qDebug() << "Data send : " << dataToString.c_str() << endl;

	code = QString::fromStdString(codingString(dataToString, treeMorse));

	return code;
}

QString comMorse::dcodingStringMorse(QString data)
{
	// QString to string
	string dataToString = data.toStdString();

	// TEST qDebug() << "Data send : " << dataToString.c_str() << endl;

	dcode = QString::fromStdString(decodingString(dataToString, treeMorse));

	return dcode;
}
