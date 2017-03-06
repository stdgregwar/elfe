#pragma once

#include <interfaces/LookFactoryPlugin.h>

class BlockLookPlugin : public Elve::LookFactoryPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ch.epfl.lap.baselook")
    Q_INTERFACES(Elve::LookFactoryPlugin)
public:
    ELVE_LOOK(BlockLookPlugin,"Block","block")
    Elve::NodeLook* node(const Elve::Node& n) override;
    Elve::EdgeLook* edge(const Elve::NodeLook& ancestor, const Elve::NodeLook& children) override;
    Elve::OrientationHint orientationHint() const override;
};
