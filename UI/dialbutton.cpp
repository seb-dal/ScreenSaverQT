#include "dialbutton.h"
#include "dialbutton_ui.h"

DialButton::DialButton(QString title, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DialButton)
{
    ui->setupUi(this);
    ui->Title->setText(title);

    QObject::connect(ui->bt, &QDial::valueChanged, this, &DialButton::value);
}

DialButton::~DialButton()
{
    delete ui;
}

void DialButton::value(int v)
{
    emit valueChange(v);
}

void DialButton::resizeEvent(QResizeEvent*)
{
    QSize s = this->size();
    int size = qMin(s.height(), s.width());
    float ratio = size / 200.f;

    QFont f(ui->Title->font());
    f.setPixelSize(16 * ratio);
    ui->Title->setFont(f);

    QFont f2(ui->content->font());
    f2.setPixelSize(32 * ratio);
    ui->content->setFont(f2);
}
