#ifndef FRAMELESS_H
#define FRAMELESS_H

#include "lib/include/fameta-counter"
#include <QtCore/QEvent>
#include <QtCore/QObject>
#include <QtCore/QPoint>
#include <QtCore/QRect>
#include <QtCore/Qt>
#include <QtGui/QHoverEvent>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QRubberBand>
#include <QtWidgets/QWidget>

constexpr fameta::counter<__COUNTER__, 0> C;

/*
* Base de Code by "iman4k" : https://stackoverflow.com/questions/5752408/qt-resize-borderless-widget
*/
class FrameLess : public QObject {
    Q_OBJECT

public:
    enum Edge {
        None = 0,
        Left = auto_int_pow2(C),
        Top = auto_int_pow2(C),
        Right = auto_int_pow2(C),
        Bottom = auto_int_pow2(C),
        TopLeft = Top + Left,
        TopRight = Top + Right,
        BottomLeft = Bottom + Left,
        BottomRight = Bottom + Right,
    };
    Q_ENUM(Edge);
    Q_DECLARE_FLAGS(Edges, Edge);

    FrameLess(QWidget* target);
    ~FrameLess();

    void setBorderWidth(int w) { _borderWidth = w; }
    int borderWidth() const { return _borderWidth; }

protected:
    bool eventFilter(QObject* o, QEvent* e) override;
    void mouseHover(QHoverEvent*);
    void mouseLeave(QEvent*);
    void mousePress(QMouseEvent*);
    void mouseRealese(QMouseEvent*);
    void mouseMove(QMouseEvent*);
    void updateCursorShape(const QPoint&);
    void calculateCursorPosition(const QPoint&, const QRect&, Edges&);

private:
    QWidget* _target = nullptr;
    QRubberBand* _rubberband = nullptr;
    bool _cursorchanged;
    bool _leftButtonPressed;
    Edges _mousePress = Edge::None;
    Edges _mouseMove = Edge::None;
    int _borderWidth;

    QPoint _dragPos;
    bool _dragStart = false;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(FrameLess::Edges);
#endif // FRAMELESS_H
