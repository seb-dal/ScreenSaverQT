#include "dialbutton.h"
#include "dialbutton_ui.h"

#include "utils/appConst.h"
#include "utils/util.h"
#include "utils/utilMacro.h"

DialButton::DialButton(QString title, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DialButton)
{
    ui->setupUi(this);
    ui->Title->setText(title);
}

DialButton::~DialButton() { deleteIfReq(ui); }

void DialButton::value(int v) { emit valueChange(v); }

void DialButton::textUpdate(int v)
{
    ui->content->setText(QString("%1%").arg(static_cast<int>(v / 256.f * 100)));
}

void DialButton::resizeEvent(QResizeEvent*)
{
    float ratio = util::computeRatio(this);
    util::setFontSize(ui->Title, appConst::sizeTitleText * ratio);

    ratio = util::computeRatio(ui->bt);
    util::setFontSize(ui->content, appConst::sizeDialText * ratio);
}
