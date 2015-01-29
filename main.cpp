// main.cpp

#include <QApplication>
#include <QDesktopWidget>
#include <QTime>

#include "window.h"
#include "errorlog.h"
#define ERRORLOG 1


#if ERRORLOG == 1
void myMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& message)
 {
     switch (type) {
     case QtDebugMsg:
         ErrorLOG::getSingleton() << QTime::currentTime().toString() <<  " Debug: " << message << "In file: " << context.file << " In function: " << context.function << " In line: " << context.line << "\n";
         break;
     case QtWarningMsg:
         ErrorLOG::getSingleton() << QTime::currentTime().toString() << " Warning: " << message << "In file: " << context.file << " In function: " << context.function << " In line: " << context.line << "\n";
         break;
     case QtCriticalMsg:
         ErrorLOG::getSingleton() << QTime::currentTime().toString() << " Critical: " << message << "In file: " << context.file << " In function: " << context.function << " In line: " << context.line << "\n";
         break;
     case QtFatalMsg:
         ErrorLOG::getSingleton() << QTime::currentTime().toString() << " Fatal: " << message << "In file: " << context.file << " In function: " << context.function << " In line: " << context.line << "\n";
         break;
     default: break;
     }
 }
#endif

int main(int argc, char *argv[])
{
    #if ERRORLOG == 1
        qInstallMessageHandler(myMessageOutput);
    #endif

    QApplication app(argc, argv);
    Window window;

    window.resize(window.sizeHint());
    int desktopArea = QApplication::desktop()->width() *
                     QApplication::desktop()->height();
    int widgetArea = window.width() * window.height();

    window.setWindowTitle("OpenGL with Qt");

    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        window.show();
    else
        window.showMaximized();
    return app.exec();
}

