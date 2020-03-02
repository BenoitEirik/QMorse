#ifndef COMMORSE_H
#define COMMORSE_H

#include <QObject>
#include <QString>
#include <string>
#include "QMorse.h"

using namespace std;

class comMorse : public QObject
{
	Q_OBJECT
public:
	explicit comMorse(QObject *parent = nullptr);
	void setTreeMorse(treeNode* tree);

signals:

public slots:
	QString codingStringMorse(QString data);
	QString dcodingStringMorse(QString data);

private:
	QString code;
	QString dcode;
	treeNode* treeMorse;

};

#endif // COMMORSE_H
