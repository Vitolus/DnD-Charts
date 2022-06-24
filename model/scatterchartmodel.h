#ifndef SCATTERCHARTMODEL_H
#define SCATTERCHARTMODEL_H

#include <QMap>
#include <math.h>
#include "model/model.h"
#include "model/adminmodel.h"

class ScatterChartModel : public Model{
private:
    //allineamento medio per classe
    QMap<QString,std::pair<uint, uint>> allinementiMedi;
public:
    /**
     * @brief ScatterChartModel Costruttore del scatterChart che usa un Admin Model per
     * costruire un modello di dati che servirà allo scatterChart
     * @param m Admin Model
     */
    explicit ScatterChartModel(AdminModel*);

    /**
     * @brief getAllineamentiMedi metodo getter
     * @return mappa che rappresenta per ogni classe l'allineamento medio registrato nei record del modello, rappresentato con coordinate tra 1 e -1
     */
    QMap<QString,std::pair<uint, uint>> getAllineamentiMedi() const;
};

#endif // SCATTERCHARTMODEL_H
