#include "pintor_color.h"

pintorColor::pintorColor()
{
    /* Do not disable access to windows underneath this one */
    this->setModal(false);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QWidget colorMainWidget;
    colorMainWidget.setParent(this);

    QComboBox colorModels;
    colorModels.addItem("RGB");
    colorModels.addItem("YUV");


}
