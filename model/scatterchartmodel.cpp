#include "scatterchartmodel.h"

ScatterChartModel::ScatterChartModel(AdminModel* m){
    //inseriso le coordinate dell'allineamento per ogni classe
    for(const QString& classe : *m->getClassiList()){
        float legge= 0.0, bonta= 0.0;
        for(Record* r : m->getRecordList()){//assolutamente inefficiente
            if(r->getClasse() == classe){
                if(r->getAllineamento().contains("legale", Qt::CaseInsensitive)) legge++;
                else if(r->getAllineamento().contains("caotico", Qt::CaseInsensitive)) legge--;
                if(r->getAllineamento().contains("buono", Qt::CaseInsensitive)) bonta++;
                else if(r->getAllineamento().contains("malvagio", Qt::CaseInsensitive)) bonta--;
            }
        }
        allinementiMedi.insert(classe,{roundf(legge*100)/100, roundf(bonta*100)/100});
    }
}

QMap<QString,std::pair<uint, uint>> ScatterChartModel::getAllineamentiMedi() const{return allinementiMedi;}
