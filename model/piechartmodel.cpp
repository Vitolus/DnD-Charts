#include "piechartmodel.h"

PieChartModel::PieChartModel(AdminModel* m){
    for(const QString& razza : *m->getRazzeList()){
        uint occ= 0;
        for(Record* r : m->getRecordList()){
            if(r->getRazza() == razza) occ++;
        }
        razzeOcc.insert(razza, occ);
    }
}

QMap<QString, uint> PieChartModel::getRazzeOccurrences() const{return razzeOcc;}
