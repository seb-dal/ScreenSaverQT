#include "qflowlayout.h"

#include <QWidget>

QFlowLayout::QFlowLayout(
    QWidget* parent, Qt::Orientations alignement, int margin, int hSpacing, int vSpacing)
    : QLayout(parent)
    , alignement(alignement)
    , m_hSpace(hSpacing)
    , m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}

QFlowLayout::QFlowLayout(Qt::Orientations alignement, int margin, int hSpacing, int vSpacing)
    : alignement(alignement)
    , m_hSpace(hSpacing)
    , m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}

QFlowLayout::~QFlowLayout()
{
    QLayoutItem* item;
    while ((item = takeAt(0)))
        delete item;
}

void QFlowLayout::addItem(QLayoutItem* item)
{
    itemList.append(item);
}

int QFlowLayout::horizontalSpacing() const
{
    if (m_hSpace >= 0) {
        return m_hSpace;
    } else {
        return smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
    }
}

int QFlowLayout::verticalSpacing() const
{
    if (m_vSpace >= 0) {
        return m_vSpace;
    } else {
        return smartSpacing(QStyle::PM_LayoutVerticalSpacing);
    }
}

int QFlowLayout::count() const
{
    return itemList.size();
}

QLayoutItem* QFlowLayout::itemAt(int index) const
{
    return itemList.value(index);
}

QLayoutItem* QFlowLayout::takeAt(int index)
{
    if (index >= 0 && index < itemList.size())
        return itemList.takeAt(index);
    return nullptr;
}

Qt::Orientations QFlowLayout::expandingDirections() const
{
    return {};
}

bool QFlowLayout::hasHeightForWidth() const
{
    return true;
}

int QFlowLayout::heightForWidth(int width) const
{
    int height = doLayout(QRect(0, 0, width, 0), true);
    return height;
}

void QFlowLayout::setGeometry(const QRect& rect)
{
    QLayout::setGeometry(rect);
    doLayout(rect, false);
}

QSize QFlowLayout::sizeHint() const
{
    return minimumSize();
}

QSize QFlowLayout::minimumSize() const
{
    QSize size;
    for (const QLayoutItem* item : qAsConst(itemList))
        size = size.expandedTo(item->minimumSize());

    const QMargins margins = contentsMargins();
    size += QSize(margins.left() + margins.right(), margins.top() + margins.bottom());
    return size;
}

/*int QFlowLayout::doLayout(const QRect &rect, bool testOnly) const
{
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
    int x = effectiveRect.x();
    int y = effectiveRect.y();
    int lineHeight = 0;
    int columnWidth = 0;
    for (QLayoutItem *item : qAsConst(itemList)) {
        const QWidget *wid = item->widget();

int spaceX = horizontalSpacing();
if (spaceX == -1)
    spaceX = wid->style()->layoutSpacing(QSizePolicy::PushButton,
                                         QSizePolicy::PushButton,
                                         Qt::Horizontal);

int spaceY = verticalSpacing();
if (spaceY == -1)
    spaceY = wid->style()->layoutSpacing(QSizePolicy::PushButton,
                                         QSizePolicy::PushButton,
                                         Qt::Vertical);

int next;
if (alignement == Qt::Horizontal) {
    int nextX = x + item->sizeHint().width() + spaceX;
    if (nextX - spaceX > effectiveRect.right() && lineHeight > 0) {
        x = effectiveRect.x();
        y = y + lineHeight + spaceY;
        nextX = x + item->sizeHint().width() + spaceX;
        lineHeight = 0;
    }
    next = nextX;
} else {
    int nextY = x + item->sizeHint().height() + spaceY;
    if (nextY - spaceY > effectiveRect.bottom() && columnWidth > 0) {
        y = effectiveRect.y();
        x = x + columnWidth + spaceX;
        nextY = y + item->sizeHint().height() + spaceY;
        lineHeight = 0;
    }
    next = nextY;
}



if (!testOnly)
    item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));

if (alignement == Qt::Horizontal) {
    x = next;
    lineHeight = qMax(lineHeight, item->sizeHint().height());
} else {
    y = next;
    columnWidth = qMax(columnWidth, item->sizeHint().width());
}
}
if (alignement == Qt::Horizontal) {
    return y + lineHeight - rect.y() + bottom;
} else {
    return x + columnWidth - rect.x() + right;
}
}*/

int QFlowLayout::doLayout(const QRect& rect, bool testOnly) const
{
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
    int x = effectiveRect.x();
    int y = effectiveRect.y();
    int lineHeight = 0;
    for (QLayoutItem* item : qAsConst(itemList)) {
        const QWidget* wid = item->widget();
        int spaceX = horizontalSpacing();
        if (spaceX == -1)
            spaceX = wid->style()->layoutSpacing(
                QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Horizontal);
        int spaceY = verticalSpacing();
        if (spaceY == -1)
            spaceY = wid->style()->layoutSpacing(
                QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Vertical);
        int nextX = x + item->sizeHint().width() + spaceX;
        if (nextX - spaceX > effectiveRect.right() && lineHeight > 0) {
            x = effectiveRect.x();
            y = y + lineHeight + spaceY;
            nextX = x + item->sizeHint().width() + spaceX;
            lineHeight = 0;
        }

        if (!testOnly)
            item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));

        x = nextX;
        lineHeight = qMax(lineHeight, item->sizeHint().height());
    }
    return y + lineHeight - rect.y() + bottom;
}

int QFlowLayout::smartSpacing(QStyle::PixelMetric pm) const
{
    QObject* parent = this->parent();
    if (!parent) {
        return -1;
    } else if (parent->isWidgetType()) {
        QWidget* pw = static_cast<QWidget*>(parent);
        return pw->style()->pixelMetric(pm, nullptr, pw);
    } else {
        return static_cast<QLayout*>(parent)->spacing();
    }
}
