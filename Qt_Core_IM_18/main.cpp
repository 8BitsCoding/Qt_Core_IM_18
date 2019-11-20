#include <QtCore/QCoreApplication>

#include <qiodevice.h>
#include <qdebug.h>
#include <qfile.h>
#include <qstring.h>
#include <qbytearray.h>
#include <qdir.h>
#include <qtextstream.h>

bool write(QString path, QByteArray data) {
	QFile file(path);

	if (!file.open(QIODevice::WriteOnly)) {
		qWarning() << file.errorString();
		return false;
	}

	qint64 bytes = file.write(data);
	file.close();

	if (bytes) return true;

	return false;
}

bool createfile(QString path) {
	QByteArray data;

	for (int i = 0; i < 5; i++) {
		data.append(QString::number(i));
		data.append("Hello World!\r\n");
	}

	return write(path, data);
}

void readFile(QString path) {
	QFile file(path);

	if (!file.exists()) {
		qWarning() << "File not found";
		return;
	}

	if (!file.open(QIODevice::ReadOnly)) {
		qWarning() << file.errorString();
		return;
	}

	qInfo() << "**** Reading file *****";
	qInfo() << file.readAll();		// 파일이 클 경우 위험하다.
	qInfo() << "**** Done *****";

	file.close();
}

void readlines(QString path) {
	QFile file(path);

	if (!file.exists()) {
		qWarning() << "File not found";
		return;
	}

	if (!file.open(QIODevice::ReadOnly)) {
		qWarning() << file.errorString();
		return;
	}

	qInfo() << "**** Reading file *****";
	while (!file.atEnd()) {
		QString line(file.readLine());
		qInfo() << "Read: " << line.trimmed();
	}
	qInfo() << "**** Done *****";

	file.close();
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QString path = QDir::currentPath() + QDir::separator() + "test.txt";
	qInfo() << "Path : " << path;

	if (createfile(path)) {
		readlines(path);
	}

	return a.exec();
}
