#ifndef ADMINVIEW_H
#define ADMINVIEW_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QGroupBox>
#include <QLineEdit>
#include <QTableWidget>
#include <QScrollArea>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDateEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QComboBox>
#include "view/view.h"
#include "model/adminmodel.h"

/**
 * @brief The AdminView class
 * Classe derivata da View
 * View specializzata nella Parte Admin della applicazione, ossia la parte di amministrazione dei dati da elaborare
 */
class AdminView : public View{
    Q_OBJECT
private:
    QGridLayout* mainLayout;
    QTableWidget* recordTable;
    QTableWidget* razzeTable;
    QTableWidget* classiTable;

    QPushButton* homeB;
    QPushButton* newB;
    QPushButton* saveB;
    QPushButton* saveAsB;
    QPushButton* pieChartRB;
    QPushButton* pieChartCB;
    QPushButton* scatterChartB;
    QPushButton* barChartB;

    /**
     * @brief connectViewSignals Metodo virtuale
     * Questo Metodo serve a connettere i SIGNAL degli elementi grafici della AdminView ai SIGNAL della
     * AdminView i quali dovranno comunicare con il Controller AdminCtrl
     */
    void connectViewSignals() const override;

protected:
    /**
     * @brief closeEvent Overriding del metodo closeEvent implementato da QWidget
     * Tramite questo Overriding si cerca di modificare l'evento di chiusura della window con la X.
     * In particolare questo metodo chiede una conferma al utente prima di chiudere.
     * Viene poi emesso un segnale al controller per avvisarlo della chiusura della finestra.
     * @param event Evento di chiusura della scermata window
     */
    void closeEvent(QCloseEvent*) override;

public:
    /**
     * @brief AdminView
     * Costruttore della Admin View
     * @param s windowSize, grandezza della finestra della View
     */
    explicit AdminView(const QSize& = QSize(), View* = nullptr);

    /**
     * @brief setViewTitle Metodo che setta il titolo alla view, aggiunge al titolo il prefisso "Personaggi"
     * @param title titolo della view
     */
    void setViewTitle(const QString&) override;

    /**
     * @brief createRecordTable Crea la QTableWidget su cui poi mostrare i dati.
     * @param headers Etichette da mostrare
     */
    void createRecordTable(const QStringList&) const;
    /**
     * @brief createRazzeTable Crea la QTableWidget su cui mostrare i dati
     * @param headers Etichette da mostrare
     */
    void createRazzeTable(const QStringList&) const;
    /**
     * @brief createClassiTable Crea la QTableWidget su cui mostrare i dati
     * @param headers Etichette da mostrare
     */
    void createClassiTable(const QStringList&) const;

    /**
     * @brief createAddRowRecordTable Crea una riga specifica di add, alla riga row,
     * in cui aggiunge uno spazio nuovo su cui si potrà inserire i dettagli di un nuovo record.
     * Associa al pulsante '+' creato, anche una connessione per Segnale la quale Aggiornerà anche il Model.
     * @param row riga a cui aggiungere la riga di add
     */
    void createAddRowRecordTable(uint, const QStringList&,const QStringList&,const QStringList&);
    /**
     * @brief createAddRowRazzeTable Metodo che si occupa di creare la riga di inserimento delle razze,
     * in questa riga si potranno inserire i dettagli di una nuova razza
     * @param row riga a cui creare
     */
    void createAddRowRazzeTable(uint);
    /**
     * @brief createAddRowClassiTable Metodo che si occupa di creare la riga di inserimento delle classi,
     * in questa riga si potranno inserire i dettagli di una nuova classe
     * @param row riga a cui creare
     */
    void createAddRowClassiTable(uint);

    /**
     * @brief addItemRecordTable Metodo che aggiunge una nuova riga alla recordTable, la riga rappresenta
     * un Record come dato.
     * Mostra ciascun dato con per ciascuno un input QT adeguato, e alla fine della riga l'ultima colonna
     * aggiunge un pulsante che serve ad eliminare la riga.
     * All'inizio si occupa di richiamare createAddRecordTable una riga più in basso, appunto per spostare la
     * riga di inserimento di un nuovo record.
     * successivamente mostra per ogni caso, per ogni colonna un QWidget adeguato.
     * Ad ogni QWidget ci assoccia anche delle connessioni lambda che seviranno a intercettare eventi di modifica
     * del dato e tramite dei segnali della View verranno reindirizzati al Controller insieme al nuovo dato e alla riga in questione.
     * Ci sono altri segnali associati cioè quello assocciato al ultimo pulsante Delete, che si occupa tramite
     * una connessione lambda di eliminare la riga in questione ed i suoi QWidget e le connessioni associate.
     * Ci sono poi altre connessioni iniziali solo per la prima colonna di RazzeW e ClassiW (Add/Remove/Modify) le quali
     * intercettano i cambiamenti che avvengono nella tabella di razzeTable e classiTable e adeguano il QComboBox modificando di conseguenza
     * le opzioni scheglibili.
     *
     * Attenzione data alle connessioni lambda le quali essendo tra oggetti nello heap
     * e con funzioni anonime possono generare facilmente Undefined Behavior se mal gestite.
     * In questo caso ci si assicura che che gli oggetti da cui partono segnali o a cui arrivano slot
     * vengano distrutti (tramite il meccanismo di parentela) e le connessioni vengano disconnesse.
     * @param row Riga in cui fare la aggiuntaa
     * @param r Record da aggiungere
     * @param razzeList lista di razze tra cui scegliere per la cella di selezione Razza
     * @param classiList lista di classi tra cui scegliere per la cella di selezione Classe
     * @param allineamentiList lista di allineamenti tra cui scegliere per la cella di selezione Allineamento
     */
    void addItemRecordTable(uint, const Record&, const QStringList&, const QStringList&, const QStringList&);
    /**
     * @brief addItemRazzeTable Metodo che aggiunge ad una QTableWidget,
     * in particolare alla razzeTable, aggiunge un Modello di dato specifico cioè un QString preso dal Model.
     * Questa aggiunta avviene ad una riga precisa della tabella row.
     * Si occupa anche di associare un pulsante ad ogni Riga.
     * Si occupa anche di associare nelle connessioni di signali ai pulsanti e alla modifica dei campi
     * @param row
     * @param m
     */
    void addItemRazzeTable(uint, const QString&);
    /**
     * @brief addItemClassiTable Metodo che aggiunge ad una QTableWidget,
     * in particolare alla classiTable, aggiunge un Modello di dato specifico cioè un QString preso dal Model.
     * Questa aggiunta avviene ad una riga precisa della tabella row.
     * Si occupa anche di associare un pulsante ad ogni Riga.
     * Si occupa anche di associare nelle connessioni di signali ai pulsanti e alla modifica dei campi
     * @param row
     * @param m
     */
    void addItemClassiTable(uint, const QString&);

    /**
     * @brief modifyItemRazzeTable Metodo che modifica una specifica Razza della razzeTable
     * Infine viene emesso un segnale per aggiornare anche i QComboBox con la modifica da fare alla razza
     * @param row
     * @param m
     */
    void modifyItemRazzeTable(uint, const QString&);
    /**
     * @brief modifyItemClassiTable Metodo che modifica una specifica Razza della materialTable
     * Infine viene emesso un segnale per aggiornare anche i QComboBox con la modifica da fare alla classe
     * @param row
     * @param m
     */
    void modifyItemClassiTable(uint, const QString&);

    /**
     * @brief removeItemRazzeTable Metodo che elimina un item della record table
     * Viene emmesso un segnale per aggiornare i QComboBox per la razza della recordTable
     * @param row riga della Razza da rimuovere
     */
    void removeItemRazzeTable(uint);
    /**
     * @brief removeItemClassiTable Metodo che elimina un item della record table
     * Viene emmesso un segnale per aggiornare i QComboBox per la classe della recordTable
     * @param row riga della Classe da rimuovere
     */
    void removeItemClassiTable(uint);

signals:
    //SIGNAL catturatti da un Controller, servono per aggiornare il Model con la modifica della recordTable
    void recordTableRemoved(uint);
    void recordTableAdded(QString, QString, QString, uint);
    void recordTableRazzaMod(uint, QString);
    void recordTableClasseMod(uint, QString);
    void recordTableAllineamentoMod(uint, QString);
    void recordTableLivelloMod(uint, uint);

    //SIGNAL catturati da un Controller, servono per aggiornare il Model con la modifica di razzeTable
    void razzeTableAdded(QString);
    void razzeTableMaterialeMod(uint,QString);
    void razzeTableRemoved(uint);

    //SIGNAL catturati da un Controller, servono per aggiornare il Model con la modifica di classiTable
    void classiTableAdded(QString);
    void classiTableMaterialeMod(uint,QString);
    void classiTableRemoved(uint);

    //SIGNAL catturati dalla View, servono per aggiornare i QComboBox con la modifica del campo dato Razza della recordTable
    void razzeTableAddedChecked(QString);
    void razzeTableMaterialeModChecked(uint,QString);
    void razzeTableRemovedChecked(uint);

    //SIGNAL catturati dalla View, servono per aggiornare i QComboBox con la modifica del campo dato Classe della recordTable
    void classiTableAddedChecked(QString);
    void classiTableMaterialeModChecked(uint,QString);
    void classiTableRemovedChecked(uint);

    //SIGNAL catturati da un Controller, servono per eseguire delle azioni
    void newBPressed();
    void saveBPressed();
    void saveAsBPressed();
    void homeBPressed();
    void pieChartBPressed(bool) const;
    void scatterChartBPressed();
    void barChartBPressed() const;

public slots:

};

#endif // ADMINVIEW_H
