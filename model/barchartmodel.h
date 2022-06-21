#ifndef BARCHARTMODEL_H
#define BARCHARTMODEL_H

#include <QMap>
#include "model/model.h"
#include "model/adminmodel.h"

class BarChartModel : public Model{
private:
    //livello medio per classe
    QMap<QString, uint> livelliMedi;
public:
    /**
     * @brief BarChartModel Costruttore del BarChart che usa un Admin Model per
     * costruire un modello di dati che servirà al barChart
     * @param m Admin Model
     */
    explicit BarChartModel(AdminModel*);

    /**
     * @brief getLivelliMedi metodo getter
     * @return mappa che rappresenta per ogni classe il livello medio registrato nei record del modello
     */
    QMap<QString, uint> getLivelliMedi() const;
};

#endif // BARCHARTMODEL_H
