#include <QComboBox>
#include <QSlider>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

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

    /* ---------------------------------- */
    colorModels = new QComboBox;
    colorModels->addItem(tr("RGB"));
    colorModels->addItem(tr("YUV"));

    QHBoxLayout *colorModelsLayout = new QHBoxLayout;
    colorModelsLayout->addStretch();
    colorModelsLayout->addWidget(colorModels);
    colorModelsLayout->addStretch();
    /* ---------------------------------- */

    /* RGB ---------------------------------- */
    QHBoxLayout *redLayout = createColorHBox("R", labelRed, sliderRed, editRed);
    QHBoxLayout *greenLayout = createColorHBox("G", labelGreen, sliderGreen, editGreen);
    QHBoxLayout *blueLayout = createColorHBox("B", labelBlue, sliderBlue, editBlue);

    QVBoxLayout *rgbLayout = new QVBoxLayout;
    rgbLayout->addLayout(redLayout);
    rgbLayout->addLayout(greenLayout);
    rgbLayout->addLayout(blueLayout);
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
    mainLayout->addLayout(colorModelsLayout);
    mainLayout->addLayout(rgbLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    /* ---------------------------------- */

}
