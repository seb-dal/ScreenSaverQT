#include "switchbutton.h"
#include "utils/util.h"
#include <QCoreApplication>

SwitchButton::SwitchButton(QWidget* parent)
    : QPushButton(parent)
{
    setCheckable(true);
    QObject::connect(this, &QPushButton::toggled, this, &SwitchButton::Translate);
}

SwitchButton::~SwitchButton()
{
}

void SwitchButton::Translate()
{
    if (this->isChecked()) {
        setText(QCoreApplication::translate("SwitchButton", "ON", nullptr));
    } else {
        setText(QCoreApplication::translate("SwitchButton", "OFF", nullptr));
    }
}
