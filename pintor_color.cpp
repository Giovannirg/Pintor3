#include <QComboBox>
#include <QSlider>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>

#include "pintor_color.h"

/* 8 bit color depth */
#define PIXEL_VAL_MIN   0U
#define PIXEL_VAL_MAX   255U



QHBoxLayout* pintorColor::createColorHBox(QString name, QLabel *p_label, QSlider *p_slider, QLineEdit *p_lineEdit)
{
    p_label = new QLabel(tr(name.toLatin1().data()));

    p_slider = new QSlider(Qt::Horizontal);
    p_slider->setRange(PIXEL_VAL_MIN, PIXEL_VAL_MAX);
    p_slider->setValue(PIXEL_VAL_MAX);

    p_lineEdit = new QLineEdit();
    p_lineEdit->setMaximumWidth(30);
    p_lineEdit->setText(tr(QString::number(p_slider->value()).toLatin1().data()));

    QHBoxLayout *retLayout = new QHBoxLayout;
    retLayout->addWidget(p_label);
    retLayout->addWidget(p_slider);
    retLayout->addWidget(p_lineEdit);

    return retLayout;
}

pintorColor::pintorColor(QWidget *parent)
    : QDialog(parent) /* Pass on the parent parameter to the base class constructor. */
{
    /* Do not disable access to windows underneath this one */
    this->setModal(false);

    /* RGB ---------------------------------- */
    QRadioButton *buttonRGB = new QRadioButton(tr("RGB"));
    QHBoxLayout *radioRgbLayout = new QHBoxLayout;
    radioRgbLayout->addWidget(buttonRGB);
    radioRgbLayout->addStretch();

    QHBoxLayout *redLayout = createColorHBox("R", labelRed, sliderRed, editRed);
    QHBoxLayout *greenLayout = createColorHBox("G", labelGreen, sliderGreen, editGreen);
    QHBoxLayout *blueLayout = createColorHBox("B", labelBlue, sliderBlue, editBlue);

    QVBoxLayout *rgbLayout = new QVBoxLayout;
    rgbLayout->addLayout(redLayout);
    rgbLayout->addLayout(greenLayout);
    rgbLayout->addLayout(blueLayout);
    /* ---------------------------------- */

    /* YUV ---------------------------------- */
    QRadioButton *buttonYUV = new QRadioButton(tr("YUV"));
    QHBoxLayout *radioYuvLayout = new QHBoxLayout;
    radioYuvLayout->addWidget(buttonYUV);
    radioRgbLayout->addStretch();

    QHBoxLayout *lumaLayout = createColorHBox("Y", labelLuma, sliderLuma, editLuma);
    QHBoxLayout *chromaBlueLayout = createColorHBox("U", labelBlueProjection, sliderBlueProjection, editBlueProjection);
    QHBoxLayout *chromaRedLayout = createColorHBox("V", labelRedProjection, sliderRedProjection, editRedProjection);

    QVBoxLayout *yuvLayout = new QVBoxLayout;
    yuvLayout->addLayout(lumaLayout);
    yuvLayout->addLayout(chromaBlueLayout);
    yuvLayout->addLayout(chromaRedLayout);
    /* ---------------------------------- */

    /* ---------------------------------- */
    /* Ampersands indicate shortcuts */
    buttonPreview = new QPushButton(tr("&Preview"), this);
    buttonClose = new QPushButton(tr("&Close"), this);
    buttonApply = new QPushButton(tr("&Apply"), this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(buttonPreview);
    buttonLayout->addStretch();
    buttonLayout->addWidget(buttonClose);
    buttonLayout->addWidget(buttonApply);
    /* ---------------------------------- */

    /* ---------------------------------- */
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(radioRgbLayout);
    mainLayout->addLayout(rgbLayout);
    mainLayout->addLayout(radioYuvLayout);
    mainLayout->addLayout(yuvLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    /* ---------------------------------- */

}
