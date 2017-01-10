#include "NodeLook.h"

#include <QGraphicsSceneMouseEvent>

NodeLook::NodeLook(Node *n) : mNode(n), mDraged(false)
{

}

void NodeLook::onStateChange(const QVector2D& p, const QVector2D& speed)
{
    if(mDraged) {
        setState({pos().x(),pos().y()},{0,0});
    } else {
        setPos(p.x(),p.y());
    }
}

void NodeLook::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton) {
        mDraged = true;
        event->accept();
    }
}

void NodeLook::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton) {
        mDraged = false;
        QPointF delta = event->scenePos() - event->lastScenePos();
        setState({event->scenePos().x(),event->scenePos().y()},
        {delta.x(),delta.y()});
        event->accept();
    }
}

void NodeLook::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(mDraged) {
        setState({event->scenePos().x(),event->scenePos().y()},{0,0});
        setPos(event->scenePos());
        event->accept();
    }
}

QPointF NodeLook::inputPos(int index) {
    return pos();
}

QPointF NodeLook::outputPos(int index) {
    return pos();
}

QPointF NodeLook::inputPos(const NodeID& from) {
    int i = 0;
    for(Node* n : mNode->ancestors()) {
        if(n->id() == from) {
            return inputPos(i);
        }
        i++;
    }
    return inputPos(0);
}

QPointF NodeLook::outputPos(const NodeID& to) {
    int i = 0;
    for(Node* n : mNode->children()) {
        if(n->id() == to) {
            return outputPos(i);
        }
        i++;
    }
    return inputPos(0);
}

Node* NodeLook::node() {
    return mNode;
}
