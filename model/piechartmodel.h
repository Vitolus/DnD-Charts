#ifndef PIECHARTMODEL_H
#define PIECHARTMODEL_H

#include <QMap>
#include "model/model.h"
#include "model/adminmodel.h"

/**
 * @brief The PieChartModel class Modello che serve a rappresentare i dati da mostrare nella
 * schermata PieChart (percentuale utilizzo)
 */
class PieChartModel : public Model{
private:
    QMap<QString, uint> razzeOcc;
    QMap<QString, uint> classiOcc;
public:
    /**
     * @brief PieChartModel Costruttore che a partire da un AdminModel viene usato per costruire
     * un PieChartModel, il sudetto modello elabora le info del AdminModel
     * per creareuna mappa RazzeOcc con: Per ogni razza il suo numero di utilizzi;
     * per creareuna mappa ClassiOcc con: Per ogni classe il suo numero di utilizzi
     * @param mAdmin
     */
    explicit PieChartModel(AdminModel*);

    /**
     * @brief getRazzeOccurrences Metodo getter
     * @return razzeOcc mappa con per ogni razza il numero di utilizzi
     */
    QMap<QString, uint> getRazzeOccurrences() const;
    /**
     * @brief getClassiOccurrences Metodo getter
     * @return classiOcc mappa con per ogni classe il numero di utilizzi
     */
    QMap<QString, uint> getClassiOccurrences() const;
};

#endif // PIECHARTMODEL_H
