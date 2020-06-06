#ifndef PINTORCOLOR_H
#define PINTORCOLOR_H

#include <QDialog>
#include <QComboBox>
#include <QDialogButtonBox>

class pintorColor : public QDialog
{
public:
    pintorColor();

protected:
    QDialogButtonBox buttonBox;
};

#endif // PINTORCOLOR_H
