#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QQuickImageProvider>
#include <poppler/qt5/poppler-qt5.h>
#include <cups/cups.h>
#include <QMessageLogger>

class QPdfPreview : public QQuickImageProvider
{
public:
    QPdfPreview() : QQuickImageProvider(QQuickImageProvider::Image) {}

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize)
    {

        Poppler::Document *document = Poppler::Document::load("/tmp/test.pdf");
        if (!document || document->isLocked())
            qCritical("File '%s' does not exist or is locked!", qUtf8Printable("/tmp/test.pdf"));

        Poppler::Page *pdfPage = document->page(0);
        if (pdfPage == nullptr)
            qCritical("File '%s' is empty?", qUtf8Printable("/tmp/test.pdf"));

        QImage image = pdfPage->renderToImage(72.0,72.0,0,0,pdfPage->pageSize().width(),pdfPage->pageSize().height());
        if (image.isNull())
            qCritical("Error!");

        return image;

        //addImageProvider handles the destruction of the object
    }
};


void qSetPrintersList(QStringList &printersList) {
    cups_dest_t *dests;
    int numDests = cupsGetDests(&dests);
    cups_dest_t *dest = cupsGetDest("name", nullptr, numDests, dests);
    for(dest = dests; dest != & dests[numDests]; dest++)
        if (dest->instance == nullptr)
            printersList.append(dest->name);

    cupsFreeDests(numDests, dests);
    return;
}

int main(int argc, char *argv[]) {

    QGuiApplication app(argc, argv);

    QStringList printersList;
    qSetPrintersList(printersList);

    QQuickView view;
    view.rootContext()->setContextProperty("printersListModel", QVariant::fromValue(printersList));
    view.engine()->addImageProvider(QLatin1String("preview"), new QPdfPreview);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}
