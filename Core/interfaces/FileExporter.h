#ifndef FILEEXPORTER_H
#define FILEEXPORTER_H

#include <QGenericPlugin>
#include "Plugin.h"
#include <EGraph.h>

#define ExporterPlugin_iid "ch.epfl.lap.elfe.LayoutPlugin"

class FileExporter : public QObject, public Plugin
{
    Q_OBJECT
public:
    FileExporter();
    virtual void exportGraph(const QString& filename, const SharedEGraph& eg) = 0;
    virtual QString formatName() = 0;
    virtual QString fileFilter() = 0;
    virtual std::string cliName() = 0;
};

Q_DECLARE_INTERFACE(FileExporter,ExporterPlugin_iid)

#define ELVE_EXPORTER(Exporter,full_name,filter,cli_name)\
 public:\
    inline QString formatName() override {return (full_name);}\
    inline QString fileFilter() override {return filter;}\
    inline std::string cliName() override {return (cli_name);}

#endif // FILEEXPORTER_H
