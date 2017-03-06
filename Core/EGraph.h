#ifndef EGRAPH_H
#define EGRAPH_H

#include "Graph.h"
#include <array>
#include "interfaces/LayoutPlugin.h"
#include "interfaces/LookFactoryPlugin.h"
#include "Selection.h"
#include <memory>

namespace Elve {

class EGraph;

typedef std::shared_ptr<EGraph> SharedEGraph;
typedef std::array<Selection,10> SelectionMasks;

class GraphWidget;
class EGraph : public std::enable_shared_from_this<EGraph>
{
public:
    EGraph(const SharedGraph& g, const NodePositions& positions = NodePositions());
    static SharedEGraph fromJSON(const QJsonObject& obj);

    static SharedEGraph fromGraph(const SharedGraph& g);

    static SharedEGraph fromFile(const QString& filename);
    void toFile(const QString& filename);

    SharedEGraph group(const NodeIDSet &names, const NodeName &groupName);
    SharedEGraph ungroup(const NodeIDSet &names) const;

    SelectionMasks& selections();
    Selection& selection(size_t i);
    Selection& currentSelection();

    QJsonObject json() const;
    const NodePositions &positions() const;
    const SharedGraph& graph() const;

    void setLayout(const SharedLayout& l);
    void setLook(const SharedLook& l);

    void setMask(int id);
    int mask() const;
    const SharedLayout& layout();
    const SharedLook& look();
    void applyLayout(const NodePositions& p = NodePositions());
    void setView(GraphWidget* view);
    GraphWidget* view();
    SharedEGraph clone(const SharedGraph& graph, const NodePositions& positions = {}) const;
    ~EGraph();
private:
    mutable bool mPosDirty;
    SharedGraph mGraph;
    mutable NodePositions mPositions; //Defining last saved node positions
    SharedLayout mLayout;
    SharedLook mLook;
    GraphWidget* mView;
    SelectionMasks mSelections;
    int mMaskId; ///Selection mask index
};

}

#endif // EGRAPH_H
