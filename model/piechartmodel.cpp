#include "piechartmodel.h"

PieChartModel::PieChartModel(AdminModel *mAdmin){
    for(const QString& razza : *mAdmin->getRazzeList()){
        unsigned int occ = 0;
        for(Record* r : mAdmin->getRecordList()){
            if(r->getRazza() == razza)
                occ++;
        }
        razzeOcc.insert({razza, occ});
    }

    for(const QString& classe : *mAdmin->getClassiList()){
        unsigned int occ = 0;
        for(Record* r : mAdmin->getRecordList()){
            if(r->getClasse() == classe)
                occ++;
        }
        classiOcc.insert({classe, occ});
    }
}

std::map<QString, unsigned int> PieChartModel::getRazzeOccurrences() const{return razzeOcc;}
std::map<QString, unsigned int> PieChartModel::getClassiOccurrences() const{return classiOcc;}
