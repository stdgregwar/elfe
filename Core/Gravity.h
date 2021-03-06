#ifndef GRAVITY_H
#define GRAVITY_H

#include "Force.h"
#include "Point.h"
#include "QuadTree.h"

namespace Elve {

class Gravity : public Force
{
public:
    Gravity(qreal k);
    virtual QVector2D force(const Point &m) const override;
    QVector2D plainOldGravity(const Point& m) const;
    QVector2D quadGravity(const Point& m) const;
    void setQuadTreeBounds(const QRectF bounds);
    void updateQuadTree();
    void addPoint(const Point* m);
    void clear();
    void debug(QPainter* p) const;
    void setK(qreal k);
private:
    std::set<const Point*> mGalaxy;
    QuadTree mQuadTree;
    qreal mK;
};

}

#endif // GRAVITY_H
