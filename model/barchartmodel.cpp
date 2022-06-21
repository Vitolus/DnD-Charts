#include "barchartmodel.h"

BarChartModel::BarChartModel(AdminModel *m){
    for(const QString& classe : *m->getClassiList()){
        uint occ= 0, tot= 0;
        for(Record* r : m->getRecordList()){
            if(r->getClasse() == classe){
                occ++;
                tot+= r->getLivello();
            }
        }
        if(occ>0) livelliMedi.insert(classe, tot/occ);
        else livelliMedi.insert(classe, 0);
    }
}

QMap<QString, uint> BarChartModel::getLivelliMedi() const{return livelliMedi;}
