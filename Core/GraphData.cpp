#include "GraphData.h"
#include <QJsonObject>
#include <QJsonArray>

GraphData::GraphData(const NodeDatas& nodesData,QString filename)
    : mDatas(nodesData), mFilename(filename)
{

}

GraphData::GraphData(const QJsonObject& obj) {
    mFilename = obj.value("filename").toString("unnamed");
    size_t size = obj.value("node_count").toInt(0);
    mDatas.reserve(size);
    QJsonArray nodes = obj.value("nodes").toArray();
    for(const QJsonValue& j : nodes) {
        mDatas.emplace_back(
                    //(j.toObject().value("id").toInt(0)),
                    (j.toObject())
                    );
    }
}

GraphData::Builder::Builder() : mID(0)
{

}

NodeID GraphData::Builder::id(const NodeName& name) {
    auto it = mIDs.find(name);
    if(it == mIDs.end()) {
        NodeID i = mID++;
        mNames.emplace(i,name);
        mIDs.emplace(name,i);
        return i;
    } else {
        return it->second;
    }
}

NodeType GraphData::Builder::type(const NodeID& id) {
    auto it = mTypes.find(id);
    if(it == mTypes.end()) {
        return NODE;
    }
    return it->second;
}

NodeProperties GraphData::Builder::props(const NodeID &id) {
    auto it = mProperties.find(id);
    if(it == mProperties.end()) {
        return {};
    }
    return it->second;
}

Index GraphData::Builder::index(const NodeID& id) {
    auto it = mIndice.find(id);
    if(it == mIndice.end()) {
        return 0;
    }
    return it->second;
}

NodeIDs GraphData::Builder::dependencies(const NodeID& i) {
    auto it = mDependencies.find(i);
    if(it == mDependencies.end()) {
        return {};
    }
    return it->second;
}

void GraphData::Builder::setDependencies(const NodeName& name, const NodeIDs &dependencies) {
    mDependencies[id(name)] = dependencies;
}


void GraphData::Builder::setDependencies(const NodeName& name, const NodeNames &dependencies) {
    NodeIDs deps;
    for(const NodeName& n : dependencies) {
        deps.push_back(id(n));
    }
    mDependencies[id(name)] = deps;
}

void GraphData::Builder::setProperties(const NodeName& name, const NodeProperties& props) {
    mProperties[id(name)] = props;
}

QJsonObject& GraphData::Builder::properties(const NodeName& name) {
    auto it = mProperties.find(id(name));
    if(it == mProperties.end()) {
        auto p = mProperties.emplace(id(name),QJsonObject{});
        return p.first->second;
    }
    return it->second;
}

void GraphData::Builder::setType(const NodeName& name, const NodeType& type) {
    NodeID i = id(name);
    mTypes[i] = type;
    if(type == OUTPUT_CLUSTER || type == OUTPUT) {
        mOutputs.push_back(i);
    } else if (type == INPUT_CLUSTER || type == INPUT) {
        mInputs.push_back(i);
    }
}

void GraphData::Builder::setIoIndex(const NodeName& name, const Index& index) {
    mIndice[id(name)] = index;
}

const SharedData GraphData::Builder::build(const QString& filename) {
    NodeDatas dats;
    for(NodeID i = 0; i < mID; i++) {
        dats.emplace_back(i,mNames.at(i),dependencies(i),type(i),props(i),index(i));
    }
    return std::make_shared<GraphData>(dats,filename);
}

const NodeIDs& GraphData::Builder::outputs() const {
    return mOutputs;
}

const NodeIDs& GraphData::Builder::inputs() const {
    return mInputs;
}

const NodeName& GraphData::Builder::name(const NodeID& id) const {
    return mNames.at(id);
}

const NodeDatas& GraphData::nodeDatas() const {
    return mDatas;
}

const QString& GraphData::filename() const {
    return mFilename;
}

QJsonObject GraphData::json() const {
    QJsonObject obj;
    obj.insert("filename",mFilename);
    obj.insert("node_count",(int)mDatas.size());

    using pair_type = NodeDatas::value_type;
    QJsonArray nodes;
    for(const NodeData& d : mDatas) {
        nodes.append(d.json());
    }
    obj.insert("nodes",nodes);
    return obj;
}
