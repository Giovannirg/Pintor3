#ifndef PINTOR3_H
#define PINTOR3_H

#include <QMainWindow>
#include <QImage>

#if defined(QT_PRINTSUPPORT_LIB)
#  include <QtPrintSupport/qtprintsupportglobal.h>

#  if QT_CONFIG(printer)
#    include <QPrinter>
#  endif
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class Pintor3; }

//[0] Classes <<Taken from Image viewer example>>
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
//[/0]

QT_END_NAMESPACE

class Pintor3 : public QMainWindow
{
    Q_OBJECT

public:
    Pintor3(QWidget *parent = nullptr);
    ~Pintor3();
    bool loadFile(const QString &);//

private slots: //[1]for Menu Actions <<taken from Imageviewer>>
    void open();
    void saveAs();
    void print();
    void copy();
    void paste();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void about();
    //[/1]
private:
    //[2]for Menu Actions <<taken from Imageviewer>>
    void createActions();
    void createMenus();
    void updateActions();
    bool saveFile(const QString &fileName);
    void setImage(const QImage &newImage);
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);


    QImage image;
    QLabel *textLabel; //Related to the TextLabel
    QScrollArea *scrollArea;
    double scaleFactor = 1;

#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printer;
#endif
     //[2]

    Ui::Pintor3 *ui;
};
#endif // PINTOR3_H
