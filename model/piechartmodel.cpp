#include "piechartmodel.h"

PieChartModel::PieChartModel(AdminModel* m){
    for(const QString& razza : *m->getRazzeList()){
        uint occ= 0;
        for(Record* r : m->getRecordList()){
            if(r->getRazza() == razza) occ++;
        }
        razzeOcc.insert(razza, occ);
    }

    for(const QString& classe : *m->getClassiList()){
        uint occ= 0;
        for(Record* r : m->getRecordList()){
            if(r->getClasse() == classe) occ++;
        }
        classiOcc.insert(classe, occ);
    }
}

QMap<QString, uint> PieChartModel::getRazzeOccurrences() const{return razzeOcc;}
QMap<QString, uint> PieChartModel::getClassiOccurrences() const{return classiOcc;}
