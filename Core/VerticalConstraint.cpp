#include "VerticalConstraint.h"
#include "Point.h"

namespace Elve {

VerticalConstraint::VerticalConstraint(qreal height) : mHeight(height)
{

}


void VerticalConstraint::constrain(Point &mass) {

    float hardn = 0.2;
    QVector2D p = mass.pos();
    QVector2D speed = mass.speed();

    mass.setPos({p.x(),mHeight*hardn+p.y()*(1-hardn)});
    mass.setSpeed({speed.x(),0});
}

}
