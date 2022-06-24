#ifndef BARCHARTMODEL_H
#define BARCHARTMODEL_H

#include <QMap>
#include "model/model.h"
#include "model/adminmodel.h"

class BarChartModel : public Model{
private:
    //livello medio per classe
    QMap<QString, uint> livelliMedi;
    QStringList listaClassi;
    uint livelloMax;
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
    /**
     * @brief getClassiList metodo getter
     * @return lista di tutte le classi
     */
    const QStringList& getClassiList() const;
    /**
     * @brief getLivelloMax metodo getter
     * @return livello massimo all'interno del modello
     */
};

#endif // BARCHARTMODEL_H
