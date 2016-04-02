// main.cpp

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QTextCodec>
#include <QQuickView>

#include "ScoreDrawing.h"

int main(int argc, char **argv){
    QApplication app(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

	qmlRegisterType<ScoreDrawing>("ScoreDrawing", 1, 0, "ScoreDrawing");
	QQmlApplicationEngine engine("main.qml");
    
    return app.exec();
}
