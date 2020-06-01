#include "pintor3.h"
#include "ui_pintor3.h"


#include <QApplication>
#include <QClipboard>
#include <QColorSpace>
#include <QDir>
#include <QFileDialog>
#include <QImageReader>
#include <QImageWriter>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QMimeData>
#include <QPainter>
#include <QScreen>
#include <QScrollArea>
#include <QScrollBar>
#include <QStandardPaths>
#include <QStatusBar>

/*#if defined(QT_PRINTSUPPORT_LIB)
#  include <QtPrintSupport/qtprintsupportglobal.h>

#  if QT_CONFIG(printdialog)
#    include <QPrintDialog>
#  endif
#endif*/

Pintor3::Pintor3(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Pintor3)
{
//[0]
        resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);


    ui->setupUi(this);
}


Pintor3::~Pintor3()
{
    delete ui;
}
//[1] Loads a File
bool Pintor3::loadFile(const QString &fileName)
{
    /* Define a image reader; second arg omitted, can be used
     * to find out the image type */
    QImageReader reader(fileName);
    /* If JPEG is portrait, enables viewer transformations to
     * portrait mode */
    reader.setAutoTransform(true);
    /* Read the image from the path and return an image object */
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

    setImage(newImage);

    setWindowFilePath(fileName);

    setFileName(fileName);

    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
    statusBar()->showMessage(message);
    return true;
}
//[/1]

void Pintor3::setFileName(const QString &fileName)
{

    imageName = fileName;

    return;
}

QString Pintor3::getFileName()
{

    return imageName;
}

//[2] set an Image inside the App canvas
void Pintor3::setImage(const QImage &newImage)
{
    image = newImage;
    if (image.colorSpace().isValid())
        image.convertToColorSpace(QColorSpace::SRgb);
    ui->label->setPixmap(QPixmap::fromImage(image));
  //  QPixmap pixmap = QPixmap::fromImage(image).scaled(image.size()*scaleFactor, Qt::KeepAspectRatio, Qt::SmoothTransformation);


    scaleFactor = 1.0;

  //  ui->label->setPixmap(pixmap);
   // this->scaleImage(scaleFactor);

   // scrollArea->setVisible(true);
    //printAct->setEnabled(true);
   // fitToWindowAct->setEnabled(true);
   // updateActions(); wird autiomatisch gemacht?

 //  if (!fitToWindowAct->isChecked())
      //  ui->label->adjustSize();
}
//[/2]




bool Pintor3::saveFile(const QString &fileName)
{
    QImageWriter writer(fileName);

    if (!writer.write(image)) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot write %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName)), writer.errorString());
        return false;
    }
    const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName));
    statusBar()->showMessage(message);
    QMessageBox::information(this, QGuiApplication::applicationDisplayName(), message);
    return true;
}

//[4] Initializes the supported image types
static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    for (const QByteArray &mimeTypeName : supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}
//[/4]





//[6] Saves an image file
void Pintor3::saveAs()
{
    QFileDialog dialog(this, tr("Save File As"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);

    while (dialog.exec() == QDialog::Accepted && !saveFile(dialog.selectedFiles().first())) {}
}
//[/6]

// [7] Prints a image
void Pintor3::print()

{
    Q_ASSERT(label->pixmap());
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printdialog)
//! [6] //! [7]
    QPrintDialog dialog(&printer, this);
//! [7] //! [8]
    if (dialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = label->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(label->pixmap()->rect());
        painter.drawPixmap(0, 0, *label->pixmap());
    }
#endif
}
//[/7]

//[8] Clipboard: Copy

void Pintor3::copy()
{
#ifndef QT_NO_CLIPBOARD
    QGuiApplication::clipboard()->setImage(image);
#endif // !QT_NO_CLIPBOARD
}

#ifndef QT_NO_CLIPBOARD
static QImage clipboardImage()
{
    if (const QMimeData *mimeData = QGuiApplication::clipboard()->mimeData()) {
        if (mimeData->hasImage()) {
            const QImage image = qvariant_cast<QImage>(mimeData->imageData());
            if (!image.isNull())
                return image;
        }
    }
    return QImage();
}
#endif // !QT_NO_CLIPBOARD
//[/8]


//[9] Clipboard: Paste
void Pintor3::paste()
{
#ifndef QT_NO_CLIPBOARD
    const QImage newImage = clipboardImage();
    if (newImage.isNull()) {
        statusBar()->showMessage(tr("No image in clipboard"));
    } else {
        setImage(newImage);
        setWindowFilePath(QString());
        const QString message = tr("Obtained image from clipboard, %1x%2, Depth: %3")
            .arg(newImage.width()).arg(newImage.height()).arg(newImage.depth());
        statusBar()->showMessage(message);
    }
#endif // !QT_NO_CLIPBOARD
}

//[10] Clipboard: Cut

//[/10]

//[11] Zoom In
void Pintor3::zoomIn()

{
  scaleImage(scaleFactor * 1.25);
}
//[/11]

//[12] Zoom out
void Pintor3::zoomOut()
{
    scaleImage(scaleFactor * 0.80);
}
//[12]

//[13] Actual Size
void Pintor3::normalSize()

{
  //  ui->label->adjustSize();
    scaleFactor = 1.0;
   // scaleImage(1.0);


}
//[/13]

//[14] Fit to window
void Pintor3::on_action_Fit_to_Window_triggered()

{
  // bool fitToWindow = on_action_Fit_to_Window_triggered();
 //   scrollArea->setWidgetResizable(label);
  //  if (!fitToWindow)
       // normalSize();
    //updateActions();
    double scaleW = static_cast<double>(ui->scrollArea->width()) /image.width();
    double scaleH = static_cast<double>(ui->scrollArea->height()) /image.height();

    scaleImage(scaleFactor*qMin(scaleH,scaleW)*0.98);

}
// [/14]


// [15] About => (duplicated to creat a about QT??)
void Pintor3::about()

{
    QMessageBox::about(this, tr("About Image Viewer"),
            tr("<p>The <b>Image Viewer</b> example shows how to combine QLabel "
               "and QScrollArea to display an image. QLabel is typically used "
               "for displaying a text, but it can also display an image. "
               "QScrollArea provides a scrolling view around another widget. "
               "If the child widget exceeds the size of the frame, QScrollArea "
               "automatically provides scroll bars. </p><p>The example "
               "demonstrates how QLabel's ability to scale its contents "
               "(QLabel::scaledContents), and QScrollArea's ability to "
               "automatically resize its contents "
               "(QScrollArea::widgetResizable), can be used to implement "
               "zooming and scaling features. </p><p>In addition the example "
               "shows how to use QPainter to print an image.</p>"));
}
// [15]


void Pintor3::scaleImage(double factor)
{

    QPixmap pixmap = QPixmap::fromImage(image).scaled(image.size()*scaleFactor, Qt::KeepAspectRatio, Qt::SmoothTransformation);

   ui->label->setPixmap(pixmap);
   this->scaleFactor = factor;
   Q_ASSERT(ui->label->pixmap());
    scaleFactor *= factor;
    ui->label->resize(scaleFactor * ui->label->pixmap()->size());

 //   adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
   // adjustScrollBar(scrollArea->verticalScrollBar(), factor);
 /*
  //  zoomInAct->setEnabled(scaleFactor < 3.0);
  //  zoomOutAct->setEnabled(scaleFactor > 0.333);*/
}

/*void Pintor3::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}*/


void Pintor3::action_exit()
{
    QApplication::quit();
}

void Pintor3::on_action_exit_triggered()
{
    QApplication::quit();
}

void Pintor3::on_action_Open_triggered()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

void Pintor3::on_action_Save_triggered()
{
    QString fileName = getFileName();

    QImageWriter writer(fileName);

    if (!writer.write(image)) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot write %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName)), writer.errorString());
        return;
    }
    const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName));
    statusBar()->showMessage(message);
    QMessageBox::information(this, QGuiApplication::applicationDisplayName(), message);

    return;


}

void Pintor3::on_action_Save_As_triggered()
{
    /* Hold the default picture location for the OS.
     * If empty, then use the last used picture location */
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QString directory = picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last();

    QFileInfo pictureInfo(imageName);
    QString pictureSuffix = pictureInfo.completeSuffix();
    QString pictureSuffixFileBrowserPre = pictureSuffix.prepend("Images (*.");
    QString pictureSuffixFileBrowserAp = pictureSuffix.append(");;");

    /* The filesystem object representing the saved file */
    QFile file;

    /* Open a file dialog in the chosen directory and save file name in same format */
    const QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save File As"),
                                                    directory,
                                                    tr(pictureSuffixFileBrowserAp.toLocal8Bit().data()));


    /* If no filename given, then save using original image name */
    if (fileName.isEmpty())
    {
        saveFile(imageName);

    }
    else
    {
        saveFile(fileName);
    }

    return;
}

void Pintor3::on_action_Copy_triggered()
{

    copy();
}

void Pintor3::on_action_Paste_triggered()
{
    paste();
}

void Pintor3::on_action_Cut_triggered()
{

}

void Pintor3::on_action_Zoom_In_triggered()
{
    scaleImage(scaleFactor * 1.25);
}

void Pintor3::on_action_Zoom_Out_triggered()
{
    scaleImage(scaleFactor * 0.80);


}

void Pintor3::on_action_Actual_Size_triggered()
{
   // ui->label->adjustSize();
    //scaleFactor = 1.0;

    //normalSize();
   scaleImage(1.0);
}

void Pintor3::on_action_About_Pintor_triggered()
{
    QMessageBox::about(this, tr("About Image Viewer"),


                       tr("<p>The <b>Pintor APP</b> For Modul M3: Ausgewählte Kapitel der Softwareentwicklung example shows how to combine QLabel "
                                      "and QScrollArea to display an image. QLabel is typically used "
                                      "for displaying a text, but it can also display an image. "
                                      "QScrollArea provides a scrolling view around another widget. "
                                      "If the child widget exceeds the size of the frame, QScrollArea "
                                      "automatically provides scroll bars. </p><p>The example "
                                      "demonstrates how QLabel's ability to scale its contents "
                                      "(QLabel::scaledContents), and QScrollArea's ability to "
                                      "automatically resize its contents "
                                      "(QScrollArea::widgetResizable), can be used to implement "
                                      "zooming and scaling features. </p><p>In addition the example "
                                      "shows how to use QPainter to print an image.</p>"));
}

void Pintor3::on_action_About_Qt_triggered()
{
    QMessageBox::aboutQt(this, tr("About Image Viewer"));
}



//[16] Menu Actions?? necessary or to control from the UI -> Resevuoir
/* void Pintor3::createActions()

{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAct = fileMenu->addAction(tr("&Open..."), this, &Pintor3::open);
    openAct->setShortcut(QKeySequence::Open);
//Already declared in GUI??
    saveAs = fileMenu->addAction(tr("&Save As..."), this, &Pintor3::saveAs);
    saveAsAct->setEnabled(false);

    printAct = fileMenu->addAction(tr("&Print..."), this, &Pintor3::print);
    printAct->setShortcut(QKeySequence::Print);
    printAct->setEnabled(false);

  //  fileMenu->addSeparator();

    QAction *exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcut(tr("Ctrl+Q"));

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

    copyAct = editMenu->addAction(tr("&Copy"), this, &Pintor3::copy);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setEnabled(false);

    QAction *pasteAct = editMenu->addAction(tr("&Paste"), this, &Pintor3::paste);
    pasteAct->setShortcut(QKeySequence::Paste);

    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));

    zoomInAct = viewMenu->addAction(tr("Zoom &In (25%)"), this, &Pintor3:zoomIn);
    zoomInAct->setShortcut(QKeySequence::ZoomIn);
    zoomInAct->setEnabled(false);

    zoomOutAct = viewMenu->addAction(tr("Zoom &Out (25%)"), this, &Pintor3::zoomOut);
    zoomOutAct->setShortcut(QKeySequence::ZoomOut);
    zoomOutAct->setEnabled(false);

    normalSizeAct = viewMenu->addAction(tr("&Normal Size"), this, &Pintor3::normalSize);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setEnabled(false);

   // viewMenu->addSeparator();

    fitToWindowAct = viewMenu->addAction(tr("&Fit to Window"), this, &Pintor3::fitToWindow);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    helpMenu->addAction(tr("&About"), this, &Pintor3::about);
    helpMenu->addAction(tr("About &Qt"), &QApplication::aboutQt);
}
//! [16]
*/
// [17]
/*void Pintor3::updateActions()
//! [21] //! [22]
{
    saveAsAct->setEnabled(!image.isNull());
    copyAct->setEnabled(!image.isNull());
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}
//! [17]
*/


