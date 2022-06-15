#ifndef ADMINMODEL_H
#define ADMINMODEL_H

#include "model/model.h"
#include <QJsonDocument>
#include <QString>
#include "ctrl/jsonfilepicker.h"
#include "model/record.h"

/**
 * @brief The AdminModel class Classe Che si occupa di rappresentare i dati che servono alla schermata Admin, in particolare
 * Elabora i Dati presi da un file JSON, e li memorizza dandogli un significato.
 */
class AdminModel : public Model{
private:
    QString* filepath;
    QStringList* razzeList;
    QStringList* classiList;
    QStringList* allineamentiList;
    std::list<Record*> recordList;
public:
    /**
     * @brief AdminModel Costruttore che viene usato per creare un modello a partire da un Documento Json
     * @param data dati in formato Json
     */
    explicit AdminModel(QJsonDocument*, QString*);
    /**
     * @brief AdminModel Costruttore che viene usato per creare un modello vuoto, senza dati
     */
    explicit AdminModel();

    /**
     * @brief AdminModel Costruttore di copia profondo
     * @param m modello da copiare
     */
    explicit AdminModel(const AdminModel&);

    /**
      * Costruttore virtuale ridefinito in quanto deve ocuparsi anche
      * di distruggere i campi in modo profondo
      */
    ~AdminModel() override;
    /**
     * @brief getRazzeList metodo getter
     * @return lista delle razze QStringList
     */
    QStringList* getRazzeList() const;
    QStringList* getClassiList() const;
    QStringList* getAllineamentiList() const;

    /**
     * @brief getRecordList metodo getter
     * @return lista di Record std::list
     */
    std::list<Record*> getRecordList() const;

    /**
     * @brief removeRecord Metodo che dato un intero rimuove dalla lista di Record l'elemento row-esimo
     * @param row indice dell'elemento da rimuovere
     */
    void removeRecord(unsigned int);

    /**
     * @brief addRecord Metodo che dato un ptr Record lo aggiunge alla lista di Record*
     * @param r Record* da aggiungere
     */
    void addRecord(Record*);

    /**
     * @brief getRecordListSize Metodo getter
     * @return gli elementi effettivi all'interno della lista, il numero di record
     */
    unsigned int getRecordListSize() const;

    /**
     * @brief addRazza Aggiunge alla QStringList razzeList una razza Qstring r
     * @param r razza da agigungere
     */
    void addRazza(const QString&);
    void addClasse(const QString&);
    void addAllineamento(const QString&);

    /**
     * @brief setRazza Metodo che modifica una razza eisstente nella razzeList e lo sostituisce con r
     * @param row indice della razza da sostituire
     * @param r razza con cui sostituire
     */
    void setRazza(unsigned int, const QString&);
    void setClasse(unsigned int, const QString&);
    void setAllineamento(unsigned int, const QString&);

    /**
     * @brief removeRazza Rimuove una razza dalla RazzeList alla riga==indice row
     * @param row indice della razza da rimuovere
     */
    void removeRazza(unsigned int);
    void removeClasse(unsigned int);
    void removeAllineamento(unsigned int);

    /**
     * @brief getRecord Metodo getter che restituisce un record specifico dalla record::list
     * @param row indice del Record dalla std::list da restituire
     * @return record da restituire
     */
    Record* getRecord(unsigned int) const;

    /**
     * @brief getRazza Metodo che ritorna una razza specifico dalla RazzeList
     * @param row riga della razza , indice della razza da ritornare
     * @return razza da ritornare
     */
    const QString& getRazza(unsigned int) const;
    const QString& getClasse(unsigned int) const;
    const QString& getAllineamento(unsigned int) const;

    /**
     * @brief getFilePath Ritorna la path del file, contente il suo percorso ed il nome del file
     * @return path
     */
    const QString& getFilePath() const;

    /**
     * @brief toQJSonDocument Metodo che trasforma l'AdminModel in un QJsonDocument,
     * viene tralasciata l'informazione della path
     * @return JSON document con i dati del modello
     */
    const QJsonDocument& toQJsonDocument() const;

    /**
     * @brief setFilePath Metodo che imposta la path del modello
     * @param fname
     */
    void setFilePath(const QString&);
};


#endif // ADMINMODEL_H
