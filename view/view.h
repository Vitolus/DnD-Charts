#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QSize>
#include <QMessageBox>
#include <QCloseEvent>

/**
 * @brief The View class
 * Classe che serve a rappresentare una View,
 */
class View : public QWidget{
    Q_OBJECT
private:
    /**
     * @brief connectViewSignals Interfaccia da implementare nelle classi derivate
     * Questo Metodo serve a dare l'interfaccia per le future implementazioni specifiche che connetteranno
     * i SIGNAL dei singoli elementi grafici (QPushButton, etc..) ai propri segnali della View.
     * I segnali della view saranno gli unici a comunicare con il Controller.
     */
    virtual void connectViewSignals() const= 0;

protected:
    /**
     * @brief closeEvent Overload di closeEvent ereditato da QWidget
     * tramite questa funzione si sceglie quali azioni eseguire alla view
     * quando si preme il pulsante X di chiusura.
     * in questo caso, non fa niente, viene accettato l'evento e la finestra viene chiusa
     * Viene poi emesso un segnale per avvisare il Controller della chiusura
     * @param event
     */
    void closeEvent(QCloseEvent*) override;

public:
    /**
     * @brief View Costruttore della view che si occupa di impostare la sua windowSize e ad applicarla
     * @param s Grandezza della finistra, la windowSize
     */
    explicit View(const QSize& = QSize(), View* = nullptr);

    /**
     * @brief ~View Reimplementazione del ristruttore,
     * per non creare conflitti con il meccanismo di distruzione di QT
     */
    virtual ~View() {
        setParent(nullptr);
    }

    /**
     * @brief applyWindowSize
     * Metodo che serve ad applicare la windowSize alla View e modificarne effettivamente la dimensione
     */
    void setWindowSize(const QSize&);

    /**
     * @brief showQuestionDialog Questo metodo mostra un popup a schermo
     * con stile di domanda e ne interpreta l'interazione.
     * @param paramNum numero di parametri tra cui si vuole scegliere, fondamentalmente
     * si sceglie se si vuole avere Cancel No Yes tra le opzioni.
     * 2 = No Yes
     * 3 = default = Cancel No Yes
     * @param title Titolo del popUp
     * @param info Messaggio Informativo da mostrare
     * @return valore booleano == true sse si è premuto su Yes
     */
    bool showQuestionDialog(uint, const QString&, const QString&);

    /**
     * @brief showWarningDialog Mostra un pop informativo che non interaziona in maniera fondamentale col utente.
     * Richiede solo la pressione di Ok.
     * STILE Avviso
     * @param title titolo del popup
     * @param mesInfo messaggio specifico da mostrare
     */
    void showWarningDialog(const QString&, const QString&);


    /**
     * @brief showInformationDialog Mostra un pop informativo che non interaziona in maniera fondamentale col utente.
     * Richiede solo la pressione di Ok.
     * Stile informativo
     * @param title titolo del popup
     * @param mesInfo messaggio specifico da mostrare
     */
    void showInformationDialog(const QString&, const QString &);


    /**
     * @brief showCriticalDialog Mostra un pop informativo che non interaziona in maniera fondamentale col utente.
     * Richiede solo la pressione di Ok.
     * Stile Critico
     * @param title titolo del popup
     * @param mesInfo messaggio specifico da mostrare
     */
    void showCriticalDialog(const QString&, const QString &);

    /**
     * @brief setViewTitle Metodo che setta il nome della Window, titolo della finestra
     * @param title titolo
     */
    virtual void setViewTitle(const QString&);

signals:
    //Segnale emesso al Controller per avvisarlo della chiusura della View
    void viewClosed() const;

public slots:

};

#endif // VIEW_H
