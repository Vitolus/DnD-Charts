#include "scatterchartmodel.h"

ScatterChartModel::ScatterChartModel(AdminModel* m){
    //inizializzo allineamentiOcc a 0
    QMap<QString,QMap<QString, uint>> allineamentiOcc;
    for(const QString& classe : *m->getClassiList()){
        for(const QString& allineamento : *m->getAllineamentiList()){
            allineamentiOcc.insert(classe, QMap<QString, uint>{{allineamento, 0}});
        }
    }
    //aggiorna i dati in allineamentiOcc
    for(const QString& classe : *m->getClassiList()){
        for(Record* r : m->getRecordList()){
            if(r->getClasse() == classe){
                allineamentiOcc[classe][r->getAllineamento()]+= 1;//modo brutto ma necessario
            }
        }
    }
    //inseriso le coordinate dell'allineamento per ogni classe
    for(QMap<QString,QMap<QString, uint>>::const_iterator it= allineamentiOcc.cbegin(); it != allineamentiOcc.cend(); it++){
        uint legge= 0, bonta= 0;
        QMap<QString, uint> all= it.value();
        for (QMap<QString, uint>::const_iterator ait= all.cbegin(); ait != all.cend(); ait++){
            if(ait.key().contains("legale")) legge+= ait.value();
            else if(ait.key().contains("caotico")) legge-= ait.value();

            if(ait.key().contains("buono")) bonta+= ait.value();
            else if(ait.key().contains("malvagio")) bonta-= ait.value();
        }
        allinementiMedi.insert(it.key(),{legge, bonta});
    }
}

QMap<QString,std::pair<uint, uint>> ScatterChartModel::getAllineamentiMedi() const{return allinementiMedi;}
