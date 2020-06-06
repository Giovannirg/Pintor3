#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "pintor_color.h"

pintorColor::pintorColor(QWidget *parent)
    : QDialog(parent) /* Pass on the parent parameter to the base class constructor. */
{
    /* Do not disable access to windows underneath this one */
    this->setModal(false);

    colorModels = new QComboBox(this);
    colorModels->addItem("RGB");
    colorModels->addItem("YUV");

    /* Ampersands indicate shortcuts */
    buttonPreview = new QPushButton(tr("&Preview"), this);
    buttonClose = new QPushButton(tr("&Close"), this);
    buttonApply = new QPushButton(tr("&Apply"), this);

    QHBoxLayout *colorModelsLayout = new QHBoxLayout;
    colorModelsLayout->addStretch();
    colorModelsLayout->addWidget(colorModels);
    colorModelsLayout->addStretch();

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(buttonPreview);
    buttonLayout->addStretch();
    buttonLayout->addWidget(buttonClose);
    buttonLayout->addWidget(buttonApply);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(colorModelsLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    /*
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QWidget colorMainWidget;
    colorMainWidget.setParent(this);

    QComboBox colorModels;
    colorModels.addItem("RGB");
    colorModels.addItem("YUV");
    */

}
