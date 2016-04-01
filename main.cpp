// main.cpp

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QTextCodec>
#include <QQuickView>

int main(int argc, char **argv){
    QApplication app(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

    QQmlApplicationEngine engine("main.qml");
    
    return app.exec();
}
