#ifndef MASS_H
#define MASS_H

#include <QVector2D>
#include <QObject>
#include <set>
#include "Force.h"
#include "Movable.h"
#include "Constraint.h"

class Spring;

class Mass
{
public:
    Mass(qreal mass, Movable* m = nullptr);
    bool moved() const;
    const QVector2D& pos() const;
    const QVector2D& speed() const;
    const qreal& mass() const;
    void setPos(const QVector2D& pos);
    void setSpeed(const QVector2D& speed);
    void addMovable(Movable* m);
    void removeMovable(Movable* m);
    void addForce(Force* force);
    void addConstraint(Constraint* c);
    void resetForce();
    void computeForce();
    void tick(float dt, bool update = true);
    void* containerData() const;
    void setContainerData(void* data) const;
private:
    QVector2D mPos;
    QVector2D mSpeed;
    QVector2D mForce;
    std::set<Force*> mForces;
    std::set<Movable*> mMovables;
    std::set<Constraint*> mConstraints;
    qreal mM;
    mutable void* mContainerData;
};

#endif // MASS_H
