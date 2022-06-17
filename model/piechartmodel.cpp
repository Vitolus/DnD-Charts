#include "piechartmodel.h"

PieChartModel::PieChartModel(AdminModel *m){
    for(const QString& razza : *m->getRazzeList()){
        unsigned int occ= 0;
        for(Record* r : m->getRecordList()){
            if(r->getRazza() == razza) occ++;
        }
        razzeOcc.insert(razza, occ);
    }

    for(const QString& classe : *m->getClassiList()){
        unsigned int occ= 0;
        for(Record* r : m->getRecordList()){
            if(r->getClasse() == classe) occ++;
        }
        classiOcc.insert(classe, occ);
    }
}

QMap<QString, unsigned int> PieChartModel::getRazzeOccurrences() const{return razzeOcc;}
QMap<QString, unsigned int> PieChartModel::getClassiOccurrences() const{return classiOcc;}
