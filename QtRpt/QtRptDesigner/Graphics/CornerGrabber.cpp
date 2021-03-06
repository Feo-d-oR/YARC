#include "CornerGrabber.h"
#include <QApplication>
#include <QDebug>

CornerGrabber::CornerGrabber(QGraphicsItem *parent,  int corner) :
    QGraphicsItem(parent),
    mouseDownX(0),
    mouseDownY(0),
    _outterborderColor(Qt::black),
    _outterborderPen(),
    _width(6),
    _height(6),
    _corner(corner),
    _mouseButtonState(kMouseReleased)
{
    setParentItem(parent);

    _outterborderPen.setWidth(2);
    _outterborderPen.setColor(_outterborderColor);

   this->setAcceptHoverEvents(true);
}

void CornerGrabber::setMouseState(int s) {
    _mouseButtonState = s;
}

int CornerGrabber::getMouseState() {
    return _mouseButtonState;
}

int CornerGrabber::getCorner() {
    return _corner;
}

// we have to implement the mouse events to keep the linker happy,
// but just set accepted to false since are not actually handling them
void CornerGrabber::mouseMoveEvent(QGraphicsSceneDragDropEvent *event) {
    event->setAccepted(false);
}

void CornerGrabber::mousePressEvent(QGraphicsSceneDragDropEvent *event) {
    event->setAccepted(false);
}

void CornerGrabber::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ) {
    event->setAccepted(true);
}

void CornerGrabber::mousePressEvent ( QGraphicsSceneMouseEvent * event ) {
    event->setAccepted(false);
}

void CornerGrabber::mouseMoveEvent ( QGraphicsSceneMouseEvent * event ) {
    event->setAccepted(false);
}

// change the color on hover events to indicate to the use the object has
// been captured by the mouse
void CornerGrabber::hoverLeaveEvent ( QGraphicsSceneHoverEvent * ) {
    _outterborderColor = Qt::black;

    // reset the cursor
    this->setCursorToResize(false);
    this->update(0,0,_width,_height);
}

void CornerGrabber::hoverEnterEvent ( QGraphicsSceneHoverEvent * ) {
    _outterborderColor = Qt::red;

    // change the cursor to the diagonal sizer
    this->setCursorToResize(true);
    this->update(0,0,_width,_height);
}

QRectF CornerGrabber::boundingRect() const {
    return QRectF(0,0,_width,_height);
}

QPointF CornerGrabber::getCenterPoint() {
    return QPointF(pos().x() + _width/2,pos().y() + _height/2);

//    if ( _corner == 0 )
//        return QPointF(pos().x() + _width/2,pos().y() + _height/2);
//    else  if ( _corner == 1 )
//        return QPointF(pos().x() - _width/2,pos().y() + _height/2);
//    else  if ( _corner == 2 )
//        return QPointF(pos().x() - _width/2,pos().y() - _height/2);
//    else  if ( _corner == 3 )
//        return QPointF(pos().x() + _width/2,pos().y() - _height/2);

}

void CornerGrabber::paint (QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    // fill the box with solid color, use sharp corners

    _outterborderPen.setCapStyle(Qt::SquareCap);
    _outterborderPen.setStyle(Qt::SolidLine);
    painter->setPen(_outterborderPen);

    QPointF topLeft (0, 0);
    QPointF bottomRight ( _width, _height);

    QRectF rect (topLeft, bottomRight);

    QBrush brush (Qt::SolidPattern);
    brush.setColor (_outterborderColor);
    painter->fillRect(rect,brush);
}

void CornerGrabber::setCursorToResize(bool on) {
    if (on) {
        switch(_corner) {
        case 0:
        case 2:
            QApplication::setOverrideCursor(Qt::SizeFDiagCursor);
            break;
        case 1:
        case 3:
            QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
            break;
        case 4:  //bottom center
        case 5:  //top center
            QApplication::setOverrideCursor(Qt::SizeVerCursor);
            break;
        case 6:  //left center
        case 7:  //rigth center
            QApplication::setOverrideCursor(Qt::SizeHorCursor);
            break;
        }
    } else {
        QApplication::restoreOverrideCursor();
    }
}
