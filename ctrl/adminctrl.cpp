#include "ctrl/adminctrl.h"

AdminCtrl::AdminCtrl(AdminView* v, AdminModel* m, Ctrl* parent) : Ctrl(v, m, parent){
    //Collego i SIGNAL della View Ai SLOT del Controller
    connectViewCtrlSignalsSlots();
    /*
    è essenziale che prima si creino la razzeTable e la classiTable e solo poi la recordTable
    Questo perchè in caso contrario si verificano dei problemi sulle QComboBox della
    view che vengono registrati doppiamente.
    */
    getView()->createRazzeTable({"RAZZE",""});
    //Creao Prima Row Pulsante Add
    getView()->createAddRowRazzeTable(0);
    //Dopo la razzeTable con i dati presi da Model
    uint id= 0;
    for (const QString& r : *getModel()->getRazzeList()) {
        getView()->addItemRazzeTable(id++, r);
    }

    getView()->createClassiTable({"CLASSI",""});
    getView()->createAddRowClassiTable(0);
    id= 0;
    for (const QString& r : *getModel()->getClassiList()) {
        getView()->addItemClassiTable(id++, r);
    }

///TODO aggiungere spaziatura

    //Creao la Record Table
    getView()->createRecordTable({ "Razza", "Classe", "Allineamento", "Livello", ""});
    //Creo Prima Row Pulsante Add
    getView()->createAddRowRecordTable(0, *getModel()->getRazzeList(),
                                       *getModel()->getClassiList(), *getModel()->getAllineamentiList());
    //Popolo La RecordTable con i Record presi da Model
    id= 0;
    for (Record* r : getModel()->getRecordList()) {
        getView()->addItemRecordTable(id++, *r, *getModel()->getRazzeList(),
                                      *getModel()->getClassiList(), *getModel()->getAllineamentiList());
    }
}

AdminView* AdminCtrl::getView() const {
    return static_cast<AdminView*>(view);
}

AdminModel* AdminCtrl::getModel() const {
    return static_cast<AdminModel*>(model);
}

void AdminCtrl::connectViewCtrlSignalsSlots() const{

    //connessioni per la RecordTable
    connect(view, SIGNAL(recordTableRemoved(uint)), this, SLOT(onRecordTableRemoved(uint)));
    connect(view, SIGNAL(recordTableAdded(QString, QString, QString, uint)), this, SLOT(onRecordTableAdded(QString, QString, QString, uint)));
    connect(view, SIGNAL(recordTableRazzaMod(uint, QString)), this, SLOT(onRecordTableRazzaMod(uint, QString)));
    connect(view, SIGNAL(recordTableClasseMod(uint, QString)), this, SLOT(onRecordTableClasseMod(uint, QString)));
    connect(view, SIGNAL(recordTableAllineamentoMod(uint, QString)), this, SLOT(onRecordTableAllineamentoMod(uint, QString)));
    connect(view, SIGNAL(recordTableLivelloMod(uint, uint)), this, SLOT(onRecordTableLivelloMod(uint, uint)));

    //connessioni per la ModelTable
    connect(view, SIGNAL(razzeTableAdded(QString)), this, SLOT(onRazzeTableAdded(QString)));
    connect(view, SIGNAL(razzeTableRemoved(uint)), this, SLOT(onRazzeTableRemoved(uint)));
    connect(view, SIGNAL(razzeTableMaterialeMod(uint, QString)), this, SLOT(onRazzeTableRazzaMod(uint, QString)));

    connect(view, SIGNAL(classiTableAdded(QString)), this, SLOT(onClassiTableAdded(QString)));
    connect(view, SIGNAL(classiTableRemoved(uint)), this, SLOT(onClassiTableRemoved(uint)));
    connect(view, SIGNAL(classiTableMaterialeMod(uint, QString)), this, SLOT(onClassiTableClasseMod(uint, QString)));

    //connessioni per i pulsanti di interazione
    connect(view, SIGNAL(newBPressed()), this, SLOT(onNewBPressed()));
    connect(view, SIGNAL(saveBPressed()), this, SLOT(onSaveBPressed()));
    connect(view, SIGNAL(saveAsBPressed()), this, SLOT(onSaveAsBPressed()));
    connect(view, SIGNAL(homeBPressed()), this, SLOT(onHomeBPressed()));

    connect(view, SIGNAL(pieChartBPressed(bool)), this, SLOT(onPieChartBPressed(bool)));
    connect(view, SIGNAL(scatterChartBPressed()),this,SLOT(onScatterChartBPressed()));
    connect(view, SIGNAL(barChartBPressed()), this, SLOT(onBarChartBPressed()));
}

void AdminCtrl::onViewClosed() const {delete this;}

void AdminCtrl::onRecordTableRemoved(uint row){
    getModel()->removeRecord(row);
}

void AdminCtrl::onRecordTableAdded(const QString& r, const QString& c, const QString& a, uint l){
    Record* re= new Record(r, c, a, l);
    getModel()->addRecord(re);
    getView()->addItemRecordTable(getModel()->getRecordListSize()-1, *re,
                                  *getModel()->getRazzeList(), *getModel()->getClassiList(), *getModel()->getAllineamentiList());
}

void AdminCtrl::onRecordTableRazzaMod(uint row, const QString& r){
    getModel()->getRecord(row)->setRazza(r);
}

void AdminCtrl::onRecordTableClasseMod(uint row, const QString& c){
    getModel()->getRecord(row)->setClasse(c);
}

void AdminCtrl::onRecordTableAllineamentoMod(uint row, const QString& a){
    getModel()->getRecord(row)->setAllineamento(a);
}

void AdminCtrl::onRecordTableLivelloMod(uint row, uint l){
    getModel()->getRecord(row)->setLivello(l);
}

void AdminCtrl::onRazzeTableAdded(const QString &r){
    for(const QString& rAdd : *getModel()->getRazzeList()){
        if(rAdd == r){
            getView()->showCriticalDialog("Inserimento Fallito","Inserimento non concesso\nassicurarsi che il nome sia univoco");
            return;
        }
    }
    getModel()->addRazza(r);
    getView()->addItemRazzeTable(getModel()->getRazzeList()->size()-1, r);
}
void AdminCtrl::onClassiTableAdded(const QString &c){
    for(const QString& cAdd : *getModel()->getRazzeList()){
        if(cAdd == c){
            getView()->showCriticalDialog("Inserimento Fallito","Inserimento non concesso\nassicurarsi che il nome sia univoco");
            return;
        }
    }
    getModel()->addClasse(c);
    getView()->addItemClassiTable(getModel()->getClassiList()->size()-1, c);
}

void AdminCtrl::onRazzeTableRazzaMod(uint row, const QString &r){
    //Counter per controllare che il duplicato esista e non sia se stesso.
    uint counter= 0;
    for(const QString& rAdd : *getModel()->getRazzeList()){
        if(rAdd == r && counter != row){
            //Duplicato trovato , modifico modello e materiale nella view con appeso '_'
            getModel()->setRazza(row, r);
            getView()->modifyItemRazzeTable(row, r + "_");
            return;
        }//Se esiste un duplicato ed è se stesso
        else if(rAdd == r && counter == row)
            return;
        counter++;
    }
    //Duplicato non trovato, modifico il modello, la view è già corretta, emetto un segnale
    //per aggiornare anche i QComboBox della View nella recordTable
    getModel()->setRazza(row, r);
    emit getView()->razzeTableRazzaModChecked(row, r);
}
void AdminCtrl::onClassiTableClasseMod(uint row, const QString &c){
    //Counter per controllare che il duplicato esista e non sia se stesso.
    uint counter= 0;
    for(const QString& cAdd : *getModel()->getClassiList()){
        if(cAdd == c && counter != row){
            //Duplicato trovato , modifico modello e materiale nella view con appeso '_'
            getModel()->setClasse(row, c);
            getView()->modifyItemClassiTable(row, c + "_");
            return;
        }//Se esiste un duplicato ed è se stesso
        else if(cAdd == c && counter == row)
            return;
        counter++;
    }
    //Duplicato non trovato, modifico il modello, la view è già corretta, emetto un segnale
    //per aggiornare anche i QComboBox della View nella recordTable
    getModel()->setClasse(row, c);
    emit getView()->classiTableClasseModChecked(row, c);
}

void AdminCtrl::onRazzeTableRemoved(uint row){
    QString r= getModel()->getRazza(row);
    for(Record* re : getModel()->getRecordList()){
        if(re->getRazza() == r){
            getView()->showCriticalDialog("Impossibile Rimuovere",
                                          "Rimozione non concessa\nAssicurarsi che la razza non sia usata nella lista di Record");
            return;
        }
    }
    getView()->removeItemRazzeTable(row);
    getModel()->removeRazza(row);
}
void AdminCtrl::onClassiTableRemoved(uint row){
    QString c= getModel()->getClasse(row);
    for(Record* r : getModel()->getRecordList()){
        if(r->getClasse() == c){
            getView()->showCriticalDialog("Impossibile Rimuovere",
                                          "Rimozione non concessa\nAssicurarsi che la razza non sia usata nella lista di Record");
            return;
        }
    }
    getView()->removeItemClassiTable(row);
    getModel()->removeClasse(row);
}

void AdminCtrl::onNewBPressed(){
    if(!view->showQuestionDialog(3,"Nuovo Dungeon", "Vuoi aprire un nuovo Dungeon?")) return;
    View* parentView= (view->parent())? static_cast<View*>(view->parent()) : nullptr;
    Ctrl* parentCtrl= (parent())? static_cast<Ctrl*>(parent()) : nullptr;

    AdminView* adminView= new AdminView(view->size(), parentView);
    adminView->setViewTitle(tr("Nuovo"));
    adminView->setWindowSize(view->size());
    AdminCtrl* adminCtrl= new AdminCtrl(adminView, new AdminModel(), parentCtrl);
    adminCtrl->showView();
    view->hide();
    delete this;
}

void AdminCtrl::onSaveBPressed() const{
    //se il file non esiste, salva con nome
    if(getModel()->getFilePath().isEmpty() || getModel()->getFilePath().isNull()){
        onSaveAsBPressed();
        return;
    }
    //imposto il titolo alla schermata
    QStringList pieces= getModel()->getFilePath().split("/");
    QString last= pieces.value(pieces.length()-1);
    view->setViewTitle(last);
    //effettua il salvataggio e in base all'esito mostro un messaggio
    bool esito= JsonFilePicker::saveAdminModel(getModel()->toQJsonDocument(), getModel()->getFilePath());
    if(!esito) view->showCriticalDialog("Errore Salvataggio grave", "Salvataggio NON riuscito");
    else view->showInformationDialog("Perfetto!", "Salvataggio Riuscito");
}

void AdminCtrl::onSaveAsBPressed() const{
    //richiesta per il nome del file
    QString jsonFilter= "Json Files (*.json)";
    QString titolo= QString::fromStdString("Salva file con nome");
    QString fname= QFileDialog::getSaveFileName(view, titolo, QDir::homePath(), jsonFilter);
    //verifica che il nome sia valido
    if(fname.isEmpty() || fname.isNull()){
        view->showCriticalDialog("Errore Salvataggio", "Salvataggio NON riuscito\nInserire un nome file valido");
        return;
    }
    if (!fname.endsWith(".json"))
        fname+= tr(".json");
    //set nome del file al modello di dati
    getModel()->setFilePath(fname);
    //salvataggio automatico
    onSaveBPressed();
}

void AdminCtrl::onHomeBPressed(){
    if(!view->showQuestionDialog(3, "Back Home", "Vuoi tornare alla Home?")) return;
    if(view->parent()) static_cast<View*>(view->parent())->show();
    view->hide();
    delete this;
}

void AdminCtrl::onPieChartBPressed(bool occ) const{
    if(getModel()->getRecordList().size() == 0){
        view->showWarningDialog("Attenzione", "Inserire dei dati prima");
        return;
    }
    //Inizializzazione polimorfa del PieChartView
    PieChartView* pcView;
    pcView= (occ)? new PieChartOView(QSize(800, 700), view) :
                      new PieChartView(QSize(800, 700), view);
    PieChartModel* pcModel= new PieChartModel(getModel());
    PieChartCtrl* pcCtrl= new PieChartCtrl(pcView, pcModel, const_cast<AdminCtrl*>(this));
    pcCtrl->showView();
}

void AdminCtrl::onScatterChartBPressed() const{
    if(getModel()->getRecordList().size() == 0){
        view->showWarningDialog("Attenzione", "Inserire dei dati prima");
        return;
    }
    ScatterChartView* scView= new ScatterChartView(QSize(800, 700), view);
    ScatterChartModel* scModel= new ScatterChartModel(getModel());
    ScatterChartCtrl* scCtrl = new ScatterChartCtrl(scView, scModel, const_cast<AdminCtrl*>(this));
    scCtrl->showView();
}

void AdminCtrl::onBarChartBPressed() const{
    if(getModel()->getRecordList().size() == 0){
        view->showWarningDialog("Attenzione", "Inserire dei dati prima");
        return;
    }
    BarChartView* bcView= new BarChartView(QSize(800, 700), view);
    BarChartModel* bcModel= new BarChartModel(getModel());
    BarChartCtrl* bcCtrl = new BarChartCtrl(bcView, bcModel, const_cast<AdminCtrl*>(this));
    bcCtrl->showView();
}
