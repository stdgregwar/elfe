#ifndef GRAPHDATA_H
#define GRAPHDATA_H

#include "NodeData.h"

namespace Elve {

class GraphData;
typedef std::shared_ptr<GraphData> SharedData;

class Graph;
class GraphData
{
    friend class Graph;
public:
    class Builder{
    public:
        Builder();
        void setDependencies(const NodeName& name, const NodeNames& dependencies);
        void setDependencies(const NodeName &name, const Dependencies &dependencies);
        void setProperties(const NodeName& name, const NodeProperties& props);
        void setNodeInputNames(const NodeName& name, const Names& names);
        void setNodeOutputNames(const NodeName& name, const Names& names);

        QJsonObject& properties(const NodeName& name);
        void setType(const NodeName& name, const NodeType& type);
        void setIoIndex(const NodeName& name, const Index& index);
        const SharedData build(const QString &filename);

        NodeID id(const NodeName& name);
        NodeType type(const NodeID& id);
        NodeProperties props(const NodeID& id);
        Index index(const NodeID& id);
        Dependencies dependencies(const NodeID& id);
        Names nodeInputNames(const NodeID& id);
        Names nodeOutputNames(const NodeID& id);
        int nodeInputCount(const NodeID& id);
        int nodeOutputCount(const NodeID& id);

        const NodeIDs& outputs() const;
        const NodeIDs& inputs() const;
        const NodeName& name(const NodeID& id) const;
    private:

        NodeID mID;
        std::unordered_map<NodeID,Dependencies> mDependencies;
        std::unordered_map<NodeID,NodeProperties> mProperties;
        std::unordered_map<NodeID,Names> mNodeInputsNames;
        std::unordered_map<NodeID,Names> mNodeOutputsNames;
        std::unordered_map<NodeID,int> mNodeInputCount;
        std::unordered_map<NodeID,int> mNodeOutputCount;
        std::unordered_map<NodeID,Index> mIndice;
        std::unordered_map<NodeID,NodeType> mTypes;
        std::unordered_map<NodeName,NodeID> mIDs;
        std::unordered_map<NodeID,NodeName> mNames;
        NodeIDs mOutputs;
        NodeIDs mInputs;
    };

    GraphData(const NodeDatas& nodesData = {}, QString filename = "graph");
    GraphData(const QJsonObject& obj);
    const NodeDatas& nodeDatas() const;
    const QString& filename() const;
    QJsonObject json() const;
private:
    QString mFilename;
    NodeDatas mDatas;
};

}

#endif // GRAPHDATA_H
