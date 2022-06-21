#include "view/adminview.h"

AdminView::AdminView(const QSize& s,View* parent) :
    View(s, parent), mainLayout(new QGridLayout(this)), recordTable(new QTableWidget(this)),
    razzeTable(new QTableWidget(this)), classiTable(new QTableWidget(this)){
    // Grid layout with 3 buttons
    mainLayout->setSpacing(10);
    mainLayout->setMargin(10);
    newB= new QPushButton("New", this);
    mainLayout->addWidget(newB, 0, 0, 1, 1, Qt::AlignJustify);
    saveB= new QPushButton("Save", this);
    mainLayout->addWidget(saveB, 0, 1, 1, 1, Qt::AlignJustify);
    saveAsB= new QPushButton("Save As", this);
    mainLayout->addWidget(saveAsB, 0, 2, 1, 1, Qt::AlignJustify);
    homeB= new QPushButton("Home", this);
    mainLayout->addWidget(homeB,0, 4, 1, 1, Qt::AlignRight);

    //Pulsanti Grafici
    pieChartRB= new QPushButton("Razze scelte %", this);
    mainLayout->addWidget(pieChartRB, 2, 0, 1, 1, Qt::AlignCenter);
    pieChartCB= new QPushButton("Classi scelte %", this);
    mainLayout->addWidget(pieChartCB, 2, 1, 1, 1, Qt::AlignCenter);
    scatterChartB = new QPushButton("Allineamento classi", this);
    mainLayout->addWidget(scatterChartB, 2, 2, 1, 1, Qt::AlignCenter);
    barChartB= new QPushButton("Livello classi", this);
    mainLayout->addWidget(barChartB, 2, 3, 1, 1, Qt::AlignCenter);

    setLayout(mainLayout);
    connectViewSignals();
}

void AdminView::createRecordTable(const QStringList& headers) const{
    //Prints Table
    recordTable->setRowCount(0);
    recordTable->setColumnCount(5);
    recordTable->setHorizontalHeaderLabels(headers);
    recordTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    recordTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    recordTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
    recordTable->setColumnWidth(4, 25);
    mainLayout->addWidget(recordTable, 1, 0, 1, 3);
}
void AdminView::createRazzeTable(const QStringList& headers) const{
    //Razze Table
    razzeTable->setRowCount(0);
    razzeTable->setColumnCount(2);
    razzeTable->setHorizontalHeaderLabels(headers);
    razzeTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    razzeTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    razzeTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    razzeTable->setColumnWidth(1, 25);
    mainLayout->addWidget(razzeTable, 1, 3, 1, 2);
}
void AdminView::createClassiTable(const QStringList& headers) const{
    //Razze Table
    classiTable->setRowCount(0);
    classiTable->setColumnCount(2);
    classiTable->setHorizontalHeaderLabels(headers);
    classiTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    classiTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    classiTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    classiTable->setColumnWidth(1, 25);
    mainLayout->addWidget(classiTable, 1, 3, 1, 2);
}

void AdminView::createAddRowRecordTable(uint row, const QStringList& razzeList,
                                        const QStringList& classiList, const QStringList& allineamentiList){
    //Inserismo una nuova riga per fare spazio
    recordTable->insertRow(row);

    QComboBox* razzeW= new QComboBox(this);
    razzeW->addItems(razzeList);
    recordTable->setCellWidget(row, 0, razzeW);
    QComboBox* classiW= new QComboBox(this);
    classiW->addItems(classiList);
    recordTable->setCellWidget(row, 1, classiW);
    QComboBox* allineamentiW= new QComboBox(this);
    allineamentiW->addItems(allineamentiList);
    recordTable->setCellWidget(row, 2, allineamentiW);

    //Aggiornamento della lista di razze
    connect(this, &AdminView::razzeTableAddedChecked, razzeW, [razzeW](const QString& m){
        razzeW->addItem(m);
    });
    connect(this, &AdminView::razzeTableRemovedChecked, razzeW, [razzeW](uint i){
        razzeW->removeItem(i);
    });
    connect(this, &AdminView::razzeTableMaterialeModChecked, razzeW, [razzeW](uint i, const QString& m){
        //verifico se l'elemento attualmente selezionato è quello da modificare, andrà poi riselezionato
        bool iSelected= (razzeW->currentIndex() == (int)i);
        razzeW->removeItem(i);
        razzeW->insertItem(i,m);
        if(iSelected) razzeW->setCurrentIndex(i);
    });

    //Aggiornamento della lista di classi
    connect(this, &AdminView::classiTableAddedChecked, classiW, [classiW](const QString& m){
        classiW->addItem(m);
    });
    connect(this, &AdminView::classiTableRemovedChecked, classiW, [classiW](uint i){
        classiW->removeItem(i);
    });
    connect(this, &AdminView::classiTableMaterialeModChecked, classiW, [classiW](uint i, const QString& m){
        //verifico se l'elemento attualmente selezionato è quello da modificare, andrà poi riselezionato
        bool iSelected= (classiW->currentIndex() == (int)i);
        classiW->removeItem(i);
        classiW->insertItem(i,m);
        if(iSelected) classiW->setCurrentIndex(i);
    });

    //livello Widget
    QSpinBox* livelloW= new QSpinBox(this);
    livelloW->setRange(1,20);
    recordTable->setCellWidget(row,3,livelloW);

    //Add Button Widget
    QPushButton* addW= new QPushButton("+",this);
    recordTable->setCellWidget(row,4,addW);

    connect(addW, &QPushButton::clicked, this,
            [this, razzeW, classiW, allineamentiW, livelloW]() {
        if(razzeW->currentIndex() != -1 && classiW->currentIndex() != -1 &&
                allineamentiW->currentIndex() != -1)
            emit recordTableAdded(razzeW->currentText(), classiW->currentText(),
                                  allineamentiW->currentText(), livelloW->value());
        else showCriticalDialog("Inserimento non concesso","Inserire prima dei dati");
    });
}
void AdminView::createAddRowRazzeTable(uint row){
    //Inserismo una nuova riga per fare spazio
    razzeTable->insertRow(row);
    //Razze Widget Select Box
    QTextEdit* razzeW= new QTextEdit(this);
    razzeTable->setCellWidget(row, 0, razzeW);
    //ADD Button Widget
    QPushButton* addW= new QPushButton("+", this);
    razzeTable->setCellWidget(row, 1, addW);

    connect(addW, &QPushButton::clicked, [this, razzeW]() {
        if(razzeW->toPlainText().isNull() || razzeW->toPlainText().isEmpty())
            showCriticalDialog("Inserimento Non Concesso", "Inserire un nome valido");
        else emit razzeTableAdded(razzeW->toPlainText());
    });
}
void AdminView::createAddRowClassiTable(uint row){
    //Inserismo una nuova riga per fare spazio
    classiTable->insertRow(row);
    //Classi Widget Select Box
    QTextEdit* classiW= new QTextEdit(this);
    classiTable->setCellWidget(row, 0, classiW);
    //ADD Button Widget
    QPushButton* addW= new QPushButton("+", this);
    classiTable->setCellWidget(row, 1, addW);

    connect(addW, &QPushButton::clicked, [this, classiW]() {
        if(classiW->toPlainText().isNull() || classiW->toPlainText().isEmpty())
            showCriticalDialog("Inserimento Non Concesso", "Inserire un nome valido");
        else emit classiTableAdded(classiW->toPlainText());
    });
}

void AdminView::addItemRecordTable(uint row, const Record& r, const QStringList& razzeList,
                                   const QStringList& classiList, const QStringList& allineamentiList){
    //Creo La ADD Row più in basso
    createAddRowRecordTable(row+1, razzeList, classiList, allineamentiList);

    //razzeTable con la combo selectg box
    QComboBox* razzeW= new QComboBox(this);
    //Aggiungo la lista degli elementi tra cui scegliere
    razzeW->addItems(razzeList);
    //Seleziono l'elemento predefinito scelto
    int index= razzeW->findText(r.getRazza());
    if(index != -1) razzeW->setCurrentIndex(index);
    //Imposto il widget sulla cella
    recordTable->setCellWidget(row, 0, razzeW);

    //classiTable con la combo selectg box
    QComboBox* classiW= new QComboBox(this);
    classiW->addItems(classiList);
    index= classiW->findText(r.getClasse());
    if(index != -1) classiW->setCurrentIndex(index);
    recordTable->setCellWidget(row, 1, classiW);

    //allineamentoTable con la combo selectg box
    QComboBox* allineamentiW= new QComboBox(this);
    allineamentiW->addItems(allineamentiList);
    index= allineamentiW->findText(r.getAllineamento());
    if(index != -1) allineamentiW->setCurrentIndex(index);
    recordTable->setCellWidget(row, 2, allineamentiW);

    //Aggiornamento della lista di razze
    connect(this, &AdminView::razzeTableAddedChecked, razzeW, [razzeW](const QString& m){
        razzeW->addItem(m);
    });
    connect(this, &AdminView::razzeTableRemovedChecked, razzeW, [razzeW](uint i){
        razzeW->removeItem(i);
    });
    connect(this,&AdminView::razzeTableMaterialeModChecked, razzeW, [razzeW](uint i, const QString& m){
        //verifico se l'elemento attualmente selezionato è quello da modificare, sarà poi riselezionato
        bool iSelected= (razzeW->currentIndex() == (int)i);
        razzeW->removeItem(i);
        razzeW->insertItem(i, m);
        if(iSelected) razzeW->setCurrentIndex(i);
    });

    connect(razzeW, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [this, razzeW](){
        uint row= recordTable->indexAt(razzeW->pos()).row();
        emit recordTableRazzaMod(row, razzeW->currentText());
    });

    //Aggiornamento della lista di classi
    connect(this, &AdminView::classiTableAddedChecked, classiW, [classiW](const QString& m){
        classiW->addItem(m);
    });
    connect(this, &AdminView::classiTableRemovedChecked, classiW, [classiW](uint i){
        classiW->removeItem(i);
    });
    connect(this,&AdminView::classiTableMaterialeModChecked, classiW, [classiW](uint i, const QString& m){
        //verifico se l'elemento attualmente selezionato è quello da modificare, sarà poi riselezionato
        bool iSelected= (classiW->currentIndex() == (int)i);
        classiW->removeItem(i);
        classiW->insertItem(i, m);
        if(iSelected) classiW->setCurrentIndex(i);
    });

    connect(classiW, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [this, classiW](){
        uint row= recordTable->indexAt(classiW->pos()).row();
        emit recordTableClasseMod(row, classiW->currentText());
    });

    //livello Widget
    QSpinBox* livelloW= new QSpinBox(this);
    livelloW->setRange(1, 20);
    livelloW->setValue(r.getLivello());
    recordTable->setCellWidget(row, 3, livelloW);

    connect(livelloW, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [this, livelloW](int value){
        uint row= recordTable->indexAt(livelloW->pos()).row();
        emit recordTableLivelloMod(row,value);
        //livelloW->value() == value
    });

    //Delete Button Widget
    QPushButton* deleteW= new QPushButton("-", this);
    recordTable->setCellWidget(row, 4, deleteW);//Widget

    //Connessione al pulsante delete per eliminare la riga e aggiornare il modello di dati con l'eliminazione
    connect(deleteW, &QPushButton::clicked, this, [this, deleteW](){
        uint row = recordTable->indexAt(deleteW->pos()).row();
        emit recordTableRemoved(row);
        recordTable->removeRow(row);
    });
}
void AdminView::addItemRazzeTable(uint row ,const QString& m){
    //Creo La ADD Row più in basso
    createAddRowRazzeTable(row+1);

    //Materiale Widget Select Box
    QTextEdit* razzeW= new QTextEdit(this);
    razzeW->setText(m);
    razzeTable->setCellWidget(row, 0, razzeW);

    connect(razzeW, &QTextEdit::textChanged, [this, razzeW]() {
        uint row= razzeTable->indexAt(razzeW->pos()).row();
        emit razzeTableMaterialeMod(row, razzeW->toPlainText());
    });

    //Delete Button Widget
    QPushButton* deleteW= new QPushButton("-", this);
    //deleteW->setObjectName(QString::number(row));
    razzeTable->setCellWidget(row, 1, deleteW);//Widget

    connect(deleteW, &QPushButton::clicked, [this, deleteW]() {
        unsigned int row= razzeTable->indexAt(deleteW->pos()).row();
        emit razzeTableRemoved(row);
        //L'eliminazione effettiva avviene solamente al responso del controller
        //che richiama il metodo
        //this->removeItemMaterialTable();
    });
    emit razzeTableAddedChecked(m);
}
void AdminView::addItemClassiTable(uint row, const QString& m){
    //Creo La ADD Row più in basso
    createAddRowClassiTable(row+1);

    //Materiale Widget Select Box
    QTextEdit* classiW= new QTextEdit(this);
    classiW->setText(m);
    classiTable->setCellWidget(row, 0, classiW);

    connect(classiW, &QTextEdit::textChanged, [this, classiW]() {
        unsigned int row= classiTable->indexAt(classiW->pos()).row();
        emit classiTableMaterialeMod(row, classiW->toPlainText());
    });

    //Delete Button Widget
    QPushButton* deleteW= new QPushButton("-", this);
    //deleteW->setObjectName(QString::number(row));
    classiTable->setCellWidget(row, 1, deleteW);//Widget

    connect(deleteW, &QPushButton::clicked, [this, deleteW]() {
        unsigned int row= classiTable->indexAt(deleteW->pos()).row();
        emit classiTableRemoved(row);
        //L'eliminazione effettiva avviene solamente al responso del controller
        //che richiama il metodo
        //this->removeItemMaterialTable();
    });
    emit classiTableAddedChecked(m);
}

void AdminView::modifyItemRazzeTable(uint row, const QString& m){
    QTextEdit* textEdit= static_cast<QTextEdit*>(razzeTable->cellWidget(row, 0));
    textEdit->setText(m);
    emit razzeTableMaterialeModChecked(row, m);
}
void AdminView::modifyItemClassiTable(uint row, const QString &m){
    QTextEdit* textEdit= static_cast<QTextEdit*>(classiTable->cellWidget(row, 0));
    textEdit->setText(m);
    emit classiTableMaterialeModChecked(row, m);
}

void AdminView::removeItemRazzeTable(uint row){
    razzeTable->removeRow(row);
    emit razzeTableRemovedChecked(row);
}
void AdminView::removeItemClassiTable(uint row){
    classiTable->removeRow(row);
    emit classiTableRemovedChecked(row);
}

void AdminView::setViewTitle(const QString& title){
    setWindowTitle(title);
}

void AdminView::connectViewSignals() const{
    connect(newB, SIGNAL(clicked()), this, SIGNAL(newBPressed()));
    connect(saveB, SIGNAL(clicked()), this, SIGNAL(saveBPressed()));
    connect(saveAsB, SIGNAL(clicked()), this, SIGNAL(saveAsBPressed()));
    connect(homeB, SIGNAL(clicked()), this, SIGNAL(homeBPressed()));

    connect(pieChartRB, &QPushButton::clicked, this, [this](){emit pieChartBPressed(false);});
    connect(pieChartCB, &QPushButton::clicked, this, [this](){emit pieChartBPressed(true);});
    connect(scatterChartB, SIGNAL(clicked()), this, SIGNAL(scatterChartBPressed()));
    connect(barChartB, &QPushButton::clicked, this, [this](){emit barChartBPressed();});
}

void AdminView::closeEvent(QCloseEvent* event){
    //Elaboro chiusura solo se intenzionata da evento esterno
    if(!event->spontaneous()) return;

    if(!showQuestionDialog(3, "Exit", "Sei sicuro di voler uscire?\n"))
        //Ignoro l'evento di chiusura
        event->ignore();
    else{
        //Accetto l'evento di chiusura della Window
        event->accept();
        emit viewClosed();
    }
}





