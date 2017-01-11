#include "NodeItem.h"
#include <QBrush>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QString>
#include <QIcon>
#include <QImageReader>
#include <unordered_map>


#define SIZE 4

using namespace std;

NodeItem::NodeItem(const NodeData& data, QGraphicsItem *parent) : QGraphicsPixmapItem(parent), mDraged(false), mData(data)
{
    if(data.type() == CLUSTER) {
        setToolTip(QString("Name : %1\n"
                           "ID   : %2\n"
                           "nodeCount : %3").arg(mData.name().c_str()).arg(mData.id()).arg(data.dependencies().size()));
    } else {
        QJsonObject truthtable = mData.properties()["truthtable"].toObject();
        QString table;
        for(QJsonObject::const_iterator it = truthtable.constBegin();
                it != truthtable.constEnd();
                it++) {
            table += it.key() + " ";
            table += it.value().toString() + "\n";
        }
        setToolTip(QString("Name : %1\n"
                           "ID   : %2\n"
                           "truthtable : %3\n"
                           "ancestorsCount : %4").arg(mData.name().c_str()).arg(mData.id()).arg(table).arg(mData.dependencies().size()));
    }

    static unordered_map<NodeType,QString> pixmaps{
        {NodeType::CLUSTER,":/resources/cluster.svg"},
        {NodeType::NODE,":/resources/node.svg"},
        {NodeType::INPUT,":/resources/input.svg"},
        {NodeType::OUTPUT,":/resources/output.svg"},
        {NodeType::INPUT_CLUSTER,":/resources/input.svg"},
        {NodeType::OUTPUT_CLUSTER,":/resources/output.svg"}};

    setZValue(1);
    QIcon ico(pixmaps.at(data.type()));
    setPixmap(ico.pixmap(64,64));
    setOffset(-32,-32);
    setScale(0.25f);

    //setBrush(QBrush(QColor(240,240,240)));
    setAcceptedMouseButtons(Qt::MouseButton::AllButtons);
}

void NodeItem::onStateChange(const QVector2D& p, const QVector2D& speed)
{
    if(mDraged) {
        setState({pos().x(),pos().y()},{0,0});
    } else {
        setPos(p.x(),p.y());
    }
}


void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton) {
        mDraged = true;
        qDebug() << mData.name().c_str();
        event->accept();
    }
}

void NodeItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton) {
        mDraged = false;
        QPointF delta = event->scenePos() - event->lastScenePos();
        setState({event->scenePos().x(),event->scenePos().y()},
        {delta.x(),delta.y()});
        event->accept();
    }
}

void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(mDraged) {
        setState({event->scenePos().x(),event->scenePos().y()},{0,0});
        setPos(event->scenePos());
        event->accept();
    }
}
