#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QQuickImageProvider>
#include <poppler/qt5/poppler-qt5.h>
#include <cups/cups.h>
#include <QMessageLogger>

class pdf_preview : public QQuickImageProvider {

public:
    pdf_preview()
        : QQuickImageProvider(QQuickImageProvider::Image)
    {
    }

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize)
    {

        Poppler::Document* document = Poppler::Document::load("/tmp/test.pdf");
        if (!document || document->isLocked())
        {
            qCritical("File '%s' does not exist or is locked!", qUtf8Printable("/tmp/test.pdf"));
        }

        Poppler::Page* pdfPage = document->page(0);
        if (pdfPage == nullptr)
        {
            qCritical("File '%s' is empty?", qUtf8Printable("/tmp/test.pdf"));
        }

        QImage image = pdfPage->renderToImage(72.0,72.0,0,0,pdfPage->pageSize().width(),pdfPage->pageSize().height());
        if (image.isNull())
        {
            qCritical("Error!");
        }

        return image;

        //delete document and image after use
    }
};

QStringList printers_list;

void set_printers_list(){
    cups_dest_t *dests;
    int num_dests = cupsGetDests(&dests);
    cups_dest_t *dest = cupsGetDest("name", nullptr, num_dests, dests);
    for(dest = dests; dest != & dests[num_dests]; dest++)
        if (dest->instance == nullptr)
            printers_list.append(dest->name);

    cupsFreeDests(num_dests, dests);
    return;
}

int main(int argc, char *argv[]) {

    QGuiApplication app(argc, argv);

    set_printers_list();

    QQuickView view;
    view.rootContext()->setContextProperty("printersListModel", QVariant::fromValue(printers_list));
    view.engine()->addImageProvider(QLatin1String("preview"), new pdf_preview);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}
