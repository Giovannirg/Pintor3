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

    void saveAs();
    void print();
    void copy();
    void paste();
    void zoomIn();
    void zoomOut();
    void normalSize();
   // void fitToWindow();
    void about();
    void action_exit();
    //[/1]
    void on_action_Fit_to_Window_triggered();

    void on_action_exit_triggered();



    void on_action_Save_triggered();

    void on_action_Save_As_triggered();

    void on_action_Copy_triggered();

    void on_action_Paste_triggered();

    void on_action_Cut_triggered();

    void on_action_Zoom_In_triggered();

    void on_action_Zoom_Out_triggered();

    void on_action_Actual_Size_triggered();

    void on_action_About_Pintor_triggered();

    void on_action_About_Qt_triggered();

    void on_action_Open_triggered();

private:
    //[2]for Menu Actions <<taken from Imageviewer>>
  //  void createActions();
    void createMenus();
    //void updateActions();
    bool saveFile(const QString &fileName);
    void setImage(const QImage &newImage);
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    void setFileName(const QString &fileName);


    QString getFileName();

    QImage image;
    QString imageName;
    QLabel *label; //Related to the TextLabel/mageLabel
    QScrollArea *scrollArea;
    double scaleFactor = 1.0;

#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printer;
#endif
     //[2]

    Ui::Pintor3 *ui;
};
#endif // PINTOR3_H
