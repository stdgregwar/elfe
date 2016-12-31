#include "PluginManager.h"
#include <QDir>
#include <QMessageBox>
#include <QDebug>

PluginManager::PluginManager()
{
    //loadPlugins(".");
}

const Loaders &PluginManager::loaders() const
{
    return mLoaders;
}

const Layouts& PluginManager::layouts() const {
    return mLayouts;
}

const Exporters& PluginManager::exporters() const {
    return mExporters;
}

template <class T>
void _load(const QString& path, const QString& type, QList<T*>& toFill) {
    QDir dir(path);
    qDebug() << "Searching for" << type << "plugins in" << dir.absoluteFilePath(path);
    for(const QFileInfo& info : dir.entryInfoList(QDir::Files)) {
        qDebug() << "Trying to load" << info.baseName();
        if(info.suffix() == "so" || info.suffix() == "dll" || info.suffix() == "dylib") {
            QPluginLoader* qpl = new QPluginLoader(info.filePath());
            if(!qpl->load()) {
                QMessageBox("Warning","Could not load " + info.baseName() + " : \n" + qpl->errorString(),QMessageBox::Warning,0,0,0).exec();
                qDebug() << qpl->errorString() << endl;
            } else {
                QObject* obj = qpl->instance();
                T* interface = qobject_cast<T*>(obj);
                if(interface) {
                    if(dir.exists(info.baseName()+".ini")) {
                        qDebug() << "found config file for plugin" << info.baseName();
                        //TODO link config file path with plugin
                    }
                    toFill.push_back(interface);
                } else {
                    QMessageBox("Warning","Could not load " + info.baseName() + " : \n Plugin is not a " + type,QMessageBox::Warning,0,0,0).exec();
                }
            }
            delete qpl;
        }
    }
}

SharedLayout PluginManager::getLayout(const QString& name) const
{
    for(LayoutPlugin* l : mLayouts) {
        if(l->name() == name) {
            return l->create();
        }
    }
    throw std::runtime_error("couldn't find " + name.toStdString() + " layout");
    return nullptr; //TODO
}

SharedLayout PluginManager::defaultLayout() const
{
    return getLayout("Simple-Force");
}

void PluginManager::load(const QString& path)
{
    //For loaders
    _load(path+"/loaders","Graph Loader",mLoaders);
    //For layouts
    _load(path+"/layouts","Layout",mLayouts);
    //For exporters
    _load(path+"/exporters","Exporter",mExporters);
}
