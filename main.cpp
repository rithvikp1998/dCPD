#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <poppler/qt5/poppler-qt5.h>
#include <QtGui>
#include <QQuickView>
#include <QQmlContext>
#include <QUrl>
#include <iostream>
#include <QQmlComponent>
#include <QQuickImageProvider>

using namespace std;

class pdf_preview : public QQuickImageProvider {

public:
    pdf_preview()
        : QQuickImageProvider(QQuickImageProvider::Image)
    {
    }

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize)
    {

        Poppler::Document* document = Poppler::Document::load("/tmp/test.pdf");
        if (!document || document->isLocked() || document == 0 )
        {
            cout << "ERROR" << endl;
        }

        Poppler::Page* pdfPage = document->page(0);
        if (pdfPage == 0)
        {
            cout << "ERROR" << endl;
        }

        QImage image = pdfPage->renderToImage(72.0,72.0,0,0,pdfPage->pageSize().width(),pdfPage->pageSize().height());
        if (image.isNull())
        {
            cout << "ERROR" << endl;
        }

        return image;

        //delete document and image after use
    }
};

int main(int argc, char *argv[]) {

    QGuiApplication app(argc, argv);

    QQuickView view;
    view.engine()->addImageProvider(QLatin1String("preview"), new pdf_preview);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}
