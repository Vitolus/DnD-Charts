#ifndef ADMINCTRL_H
#define ADMINCTRL_H

#include "ctrl/piechartctrl.h"
#include "ctrl/barchartctrl.h"
#include "ctrl/scatterchartctrl.h"
#include "view/adminview.h"
#include "view/piechartoview.h"

/**
 * @brief The AdminCtrl class
 * AdminCtrl classe derivata da Ctrl ossia un Controller specializzato della schermata Admin della applicazione
 */
class AdminCtrl : public Ctrl{
    Q_OBJECT
private:
    /**
     * @brief connectViewCtrlSignalsSlots Metodo overloading
     * Questo Metodo serve a connettere i SIGNAL della AdminView ai Slot del AdminCtrl
     */
    void connectViewCtrlSignalsSlots() const;

public:
    /**
     * @brief AdminCtrl
     * @param v View collegata al Controller
     * @param m Model collegato al Controller
     */
    AdminCtrl(AdminView*, AdminModel* = new AdminModel(), Ctrl* = nullptr);

    /**
     * @brief getView Ritorna La View castata almeno al tipo corrente AdminView
     * @return
     */
    AdminView* getView() const override;

    /**
     * @brief getModel Ritorna il Model castato almeno al tipo corrente ModelView
     * @return
     */
    AdminModel* getModel() const override;

signals:

public slots:
     /**
      * @brief onViewClosed SLOT eseguito alla ricezione di SEGNALI di chiusura della View
      * Distrugge il controller, che di seguito distrugge la view e il model
      */
     void onViewClosed() const override;
     /**
      * @brief onRecordTableRemoved SLOT eseguito alla ricezione di SEGNALI dalla view per la rimozione
      * di un record dalla record table, questo slot modifica il modello aggiornandolo con il record da rimuovere
      * @param row indice del record da rimuovere dalla recordList
      */
     void onRecordTableRemoved(uint row);

     /**
      * @brief onRecordTableAdded SLOT eseguito alla ricezione di SEGNALI dalla view per l'aggiunta di un record
      * viene quindi modificato il modello aggiungendo un record alla recordList
      * @param r razza
      * @param c classe
      * @param d allineamento
      * @param l livello
      */
     void onRecordTableAdded(const QString&, const QString&, const QString&, uint);

     /**
      * @brief onRecordTableRazzaMod SLOT eseguito alla ricezione di SEGNALI dalla view
      * per la modifica della razza di uno specifico Record
      * @param row indice del record da modificare dalla recordList
      * @param r Razza
      */
     void onRecordTableRazzaMod(uint, const QString&);

     /**
      * @brief onRecordTableClasseMod SLOT eseguito alla ricezione di SEGNALI dalla view
      * per la modifica della classe di uno specifico Record
      * @param row indice del record da modificare della recordList
      * @param c Classe
      */
     void onRecordTableClasseMod(uint, const QString&);

     /**
      * @brief onRecordTableAllineamentoMod SLOT eseguito alla ricezione di SEGNALI dalla view
      * per la modifica dell'allineamento di uno specifico record
      * @param row indice del record da modificare
      * @param a Allineamento
      */
     void onRecordTableAllineamentoMod(uint, const QString&);

     /**
      * @brief onRecordTableLivelloMod SLOT eseguito alla ricezione di SEGNALI dalla view per la
      * modifica del livello di uno specifico Record
      * @param row indice del record da modificare nella recordList
      * @param da Data
      */
     void onRecordTableLivelloMod(uint, uint);

     /**
      * @brief onRazzeTableAdded SLOT eseguito alla ricezione di SEGNALI dalla view per la
      * aggiunta di una razza alla razzeList
      * @param r Razza
      */
     void onRazzeTableAdded(const QString&);
     /**
      * @brief onClasstTableAdded SLOT eseguito alla ricezione di SEGNALI dalla view per la
      * aggiunta di una classe alla classiList
      * @param c Classe
      */
     void onClassiTableAdded(const QString&);

     /**
      * @brief onRazzeTableRazzaMod SLOT eseguito alla ricezione di SEGNALI dalla view
      * per la modifica di una razza specifica della razzeList
      * Verifica che la razza non esista già effettivamente nel modello per non creare duplicati.
      * Se trova una razza già esistente la modifica con il carattere '_' appeso alla fine.
      * Successivamente si manda un segnale della VIEW per aggioranre i QComboBox
      * @param row indice della Razza da modificare dalla razzeList
      * @param r Razza
      */
     void onRazzeTableRazzaMod(uint, const QString& r);
     /**
      * @brief onClassiTableClasseMod SLOT eseguito alla ricezione di SEGNALI dalla view
      * per la modifica di una classe specifica della classiList
      * Verifica che la classe non esista già effettivamente nel modello per non creare duplicati.
      * Se trova una classe già esistente la modifica con il carattere '_' appeso alla fine.
      * Successivamente si manda un segnale della VIEW per aggioranre i QComboBox
      * @param row indice della Classe da modificare dalla classiList
      * @param c Classe
      */
     void onClassiTableClasseMod(uint, const QString& c);

     /**
      * @brief onRazzeTableRemoved SLOT eseguito alla ricezione di SEGNALI dalla view
      * per la rimozione di una specifica razza dalla razzeList
      * La razza può essere rimossa solamente se non è presente in uno dei
      * record della recordList, per mantenere l'integrità dei dati.
      * @param row indice del record da rimuovereturno
      // @param check questo parametro rapresenta se la rimozione del materiale è già stata verificata
      */
     void onRazzeTableRemoved(uint);
     /**
      * @brief onClassiTableRemoved SLOT eseguito alla ricezione di SEGNALI dalla view
      * per la rimozione di una specifica classe dalla classiList
      * La classe può essere rimossa solamente se non è presente in uno dei
      * record della recordList, per mantenere l'integrità dei dati.
      * @param row indice del record da rimuovereturno
      */
     void onClassiTableRemoved(uint);

     /**
      * @brief onNewBPressed SLOT eseguito alla ricezione di SEGNALI dalla view
      * Azione da eseguire per aprire un nuovo progetto
      */
     void onNewBPressed();

     /**
      * @brief onSaveBPressed SLOT eseguito alla ricezione di SEGNALI dalla view
      * azione eseguite per salvare il progetto
      */
     void onSaveBPressed()const;

     /**
      * @brief onSaveAsBPressed SLOT eseguito alla ricezione di SEGNALI dalla view
      * azione eseguita per salvare il progetto con un nome diverso
      */
     void onSaveAsBPressed()const;

     /**
      * @brief onHomeBPressed SLOT eseguito alla ricezione di SEGNALI dalla view
      * azione eseguita per tornare alla home
      */
     void onHomeBPressed();

     /**
      * @brief onPieChartBPressed SLOT eseguito alla ricezione di SEGNALI dall view
      * che chiede come azione eseguita l'apertura di un PieChart
      * viene usato il modello attuale nel Ctrl
      * @param occ
      */
     void onPieChartBPressed(bool)const;

     /**
      * @brief onScatterChartBPressed SLOT eseguito alla ricezione di SEGNALI dalla view
      * che chiede come azione eseguita l'apertura di uno ScatterChart
      * viene usato il modello attuale nel Ctrl
      */
     void onScatterChartBPressed()const;

     /**
      * @brief onBarChartBPressed SLOT eseguito alla ricezione di SEGNALI dalla view
      * che chiede come azione eseguita l'apertura di un BarChart
      * viene usato il modello attuale nel Ctrl
      */
     void onBarChartBPressed() const;
};

#endif // ADMINCTRL_H
