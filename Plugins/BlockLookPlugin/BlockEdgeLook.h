#ifndef BLOCKEDGELOOK_H
#define BLOCKEDGELOOK_H

#include <interfaces/EdgeLook.h>

class BlockEdgeLook : public Elve::EdgeLook
{
public:
    BlockEdgeLook(const Elve::NodeLook& from, Elve::Index outi, const Elve::NodeLook& to, Elve::Index ini);
    void addToPath(QPainterPath& path) override;
    QPen pen() const override;
};

#endif // BLOCKEDGELOOK_H
