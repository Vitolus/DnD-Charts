#ifndef HOMEVIEW_H
#define HOMEVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QCloseEvent>
#include <QGroupBox>
#include "view/view.h"

/**
 * @brief The HomeView class
 * Classe derivata di View, è una View specializzata per la parte Home della applicazinoe
 */
class HomeView : public View{
    Q_OBJECT
private:
    QPushButton* newButton;
    QPushButton* openButton;
    /**
     * @brief createButtonsLayout
     * Questo Metodo si occupa di realizare e predisporre il layout con i pulsanti della Home
     * @return Layout contenente i pulsanti del menu Home
     */
    QLayout* createButtonsLayout();
    /**
     * @brief createDescriptionLayout
     * Metodo che si occupa di realizzare e predisporre il layout con la parte descrittiva delLa Home
     * @param description descrizione da inserire all'interno del layout
     * @param imgPath path della immagine da includere nel layout
     * @return layout contenente la parte della descrizione della applicazione
     */
    QLayout* createDescriptionLayout(const QString&);
    /**
     * @brief connectViewSignals Metodo virtuale
     * Questo Metodo serve a connettere i SIGNAL degli elementi grafici della Homeview,
     * i quali dovranno comunicare con il Controller HomeCtrl
     */
    void connectViewSignals() const override;

protected:
    /**
     * @brief closeEvent Overriding del metodo closeEvent implementato da QWidget
     * Chiede una conferma al utente prima di chiudere.
     * Viene poi emesso un segnale per avvisare il controller della chiusura
     * @param event Evento di chiusura della scermata window
     */
    void closeEvent(QCloseEvent*) override;
public:
    /**
     * @brief HomeView
     * Il Costruttore si occupa di Creare la View e creare i due layout laterali della app e mostrarli.
     * @param s Grandezza della finistra, la windowSize
     */
    explicit HomeView(const QSize& = QSize(),View* = nullptr);

signals:
    void newDungeon();
    void openDungeon();

public slots:

};

#endif // HOMEVIEW_H
