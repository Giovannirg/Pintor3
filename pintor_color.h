#ifndef PINTORCOLOR_H
#define PINTORCOLOR_H

#include <QDialog>

/* Forward declaration of classes used
 * Tells the compiler that a class
 * exists, without providing the
 * class definition */
class QPushButton;
class QSlider;
class QComboBox;
class QLabel;
class QLineEdit;
class QHBoxLayout;
class QRadioButton;

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

    /* DRY-Principle for creating all the sliders for all
     * the possible color correction gammits */
    QHBoxLayout* createColorHBox(QString name, QLabel *p_label, QSlider *p_slider, QLineEdit *p_lineEdit);

    /* ---------------------------------- */
    /* Forward declaration of classes used.
     * Pointers, so that we don't access them in the header
     * file, so the compiler doesn't need the full class definitions.
     */
    QPushButton *buttonClose;
    QPushButton *buttonApply;
    QPushButton *buttonPreview;

    QRadioButton *buttonRGB;
    QRadioButton *buttonYUV;
    /* ---------------------------------- */

    /* ---------------------------------- */
    QLabel *labelRed;
    QLabel *labelGreen;
    QLabel *labelBlue;

    QLabel *labelLuma;
    QLabel *labelBlueProjection;
    QLabel *labelRedProjection;
    /* ---------------------------------- */

    /* ---------------------------------- */
    QSlider *sliderRed;
    QSlider *sliderGreen;
    QSlider *sliderBlue;

    QSlider *sliderLuma;
    QSlider *sliderBlueProjection;
    QSlider *sliderRedProjection;
    /* ---------------------------------- */

    /* ---------------------------------- */
    QLineEdit *editRed;
    QLineEdit *editGreen;
    QLineEdit *editBlue;

    QLineEdit *editLuma;
    QLineEdit *editBlueProjection;
    QLineEdit *editRedProjection;
    /* ---------------------------------- */



};

#endif // PINTORCOLOR_H
