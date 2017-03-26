#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <poppler/qt5/poppler-qt5.h>
#include <QtGui>
#include <QQuickView>
#include <QQmlContext>
#include <QUrl>
#include <string.h>
#include <QQmlComponent>

using namespace std;

class pdf_preview : public QObject {

    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)

public:

    QImage image;
    string test = "Hello World!";
    void setImage(){
        QString filename = "usb_layout.pdf";
        Poppler::Document* document = Poppler::Document::load(filename);
        Poppler::Page* pdfPage = document->page(0);  // Document starts at page 0
        QImage image = pdfPage->renderToImage(72.0, 72.0, -1, -1, -1, -1);
    }
};

int main(int argc, char *argv[]) {

    QGuiApplication app(argc, argv);

    /*QQuickView view;

    pdf_preview data;
    view.engine()->rootContext()->setContextProperty("pdfpreviewdata", &data);

    view.setSource(QUrl::fromLocalFile("main.qml"));
    view.show();*/


    /*QQmlEngine engine;
    QQmlContext *context = new QQmlContext(engine.rootContext());

    pdf_preview data;
    context->setContextProperty("pdfpreviewdata", &data);

    QQmlComponent component(&engine, "main.qml");
    QObject *object = component.create(context);*/

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
