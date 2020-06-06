#ifndef PINTORCOLOR_H
#define PINTORCOLOR_H

#include <QDialog>

/* Forward declaration of classes used
 * Tells the compiler that a class
 * exists, without providing the
 * class definition */
class QPushButton;
class QComboBox;

class pintorColor : public QDialog
{
    /* Necessary for all classes that define signals or slots. */
    Q_OBJECT

signals:
    /* Which signals are emitted when a user presses a button for example */

/* Expands into a construct that the C++ compiler can digest. (Same as signals) */
private slots:


public:
    pintorColor(QWidget *parent = NULL);

private:
    /* Forward declaration of classes used.
     * Pointers, so that we don't access them in the header
     * file, so the compiler doesn't need the full class definitions.
     */
    QPushButton *buttonClose;
    QPushButton *buttonApply;
    QPushButton *buttonPreview;

    QComboBox *colorModels;


};

#endif // PINTORCOLOR_H
