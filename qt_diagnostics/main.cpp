#include <QApplication>
#include "MainWindow.hpp"

#include "ui/model/CanMessage.hpp"
#include "ui/model/DiagnosticEvent.hpp"
#include "qt_types/FaultTypeQt.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qRegisterMetaType<CanMessage>("CanMessage");
    qRegisterMetaType<DiagnosticEvent>("DiagnosticEvent");
    qRegisterMetaType<FaultType>("FaultType");
    
    MainWindow window;
    window.show();

    return app.exec();
}