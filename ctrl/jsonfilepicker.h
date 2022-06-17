#ifndef JsonFILEPICKER_H
#define JsonFILEPICKER_H

#include <QFile>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include "model/record.h"
#include "model/adminmodel.h"

class JsonFilePicker{
public:
    /**
     * Eliminazione dei costruttori di default per impedire creazione istanze della classe
     */
    explicit JsonFilePicker()= delete;
    explicit JsonFilePicker(const JsonFilePicker&)= delete;

    /**
     * @brief selectJsonFileDialog Mostra l'interfaccia grafica per la selezione di un File
     * Si può selezionare solo un file
     * @return Ritorna il percorso del file selezionato
     */
    static QString selectJsonFileDialog();

    /**
     * @brief getJsonFileData Dato il path di un file ne preleva i dati facendone la lettura, ed interpretandoli come
     * un Json, la elenaborazione va a buon fine solamente se la path è corretta e se il file è un Json valido.
     * @param path percorso dove si trova il file
     * @return Documento Json contenente i dati del Json,
     * se documento Json non valido o path non valida  return QString::isNull() == true
     */
    static QJsonDocument* getJsonFileData(const QString&);

    /**
     * @brief getRazzeList Metodo che Elabora i Dati Json e restituisce una lista con le Razze
     * @param data, Dati Json da elaborare
     * @return  QStringList, ogni elemento è una razza
     */
    static QStringList* getRazzeList(QJsonDocument*);
    /**
     * @brief getClassiList Metodo che Elabora i Dati Json e restituisce una lista con le Classi
     * @param data, Dati Json da elaborare
     * @return  QStringList, ogni elemento è una classe
     */
    static QStringList* getClassiList(QJsonDocument*);
    /**
     * @brief getAllineamentiList Metodo che Elabora i Dati Json e restituisce una lista con gli Allineamenti
     * @param data, Dati Json da elaborare
     * @return  QStringList, ogni elemento è un allineamento
     */
    static QStringList* getAllineamentiList(QJsonDocument*);

    /**
     * @brief getRecords Metodo che elebora i dati Json e resituisce un QJsonArray con i record delle stampe
     * @param data, Dati Json da elaborare
     * @return Records in formato QJsonArray
     */
    static QList<Record*> getRecords(QJsonDocument*);

    /**
     * @brief saveAdminModel metodo che dato un documento e una path lo salva nella
     * path specificata; il documento è in formato QJsonDocument e la path deve essere valida.
     * nel caso non sia valida il metodo ritorna false.
     * Solo nel caso in cui la scrittura vada a buon fine il metodo riorna true.
     * @param doc
     * @param path
     * @return
     */
    static bool saveAdminModel(const QJsonDocument&, const QString&);
};

#endif // JsonFILEPICKER_H
