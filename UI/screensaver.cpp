#include "screensaver.h"
#include "screensaver_ui.h"

#include <string>

ScreenSaver::ScreenSaver(QWidget* parent)
    : QFrame(parent)
    , ui(new Ui::ScreenSaver)
{
    ui->setupUi(this);
}

ScreenSaver::~ScreenSaver()
{
    delete ui;
}
