#include "adminmodel.h"

QStringList const* AdminModel::allineamentiList= new QStringList({"legale,buono","legale,neutrale","legale,malvagio",
                                                           "neutrale,buono","neutrale,neutrale","neutrale,malvagio",
                                                           "caotico,buono","caotico,neutrale","caotico,malvagio"});

AdminModel::AdminModel(QJsonDocument* data, QString* path){
    razzeList= JsonFilePicker::getRazzeList(data);
    classiList= JsonFilePicker::getClassiList(data);
    recordList= JsonFilePicker::getRecords(data);
    filepath= path;
}
AdminModel::AdminModel(){
    razzeList= new QStringList();
    classiList= new QStringList();
    filepath= new QString();
}
AdminModel::AdminModel(const AdminModel& m){
    filepath= new QString(*m.filepath);
    razzeList= new QStringList(*m.razzeList);
    classiList= new QStringList(*m.classiList);
    for(const auto& r : m.recordList)
        recordList.push_back(new Record(*r));
}
AdminModel::~AdminModel(){
    delete filepath;
    delete razzeList;
    delete classiList;
    for(auto r : recordList)
        delete r;
}

QStringList* AdminModel::getRazzeList() const{ return razzeList;}
QStringList* AdminModel::getClassiList() const{ return classiList;}
QStringList const* AdminModel::getAllineamentiList() const{ return allineamentiList;}
QList<Record*> AdminModel::getRecordList() const{return recordList;}

void AdminModel::removeRecord(uint row){
    QList<Record*>::iterator it= recordList.begin();
    std::advance(it, row);
    recordList.erase(it);
}

Record* AdminModel::getRecord(uint row) const{
    QList<Record*>::const_iterator it= recordList.begin();
    std::advance(it, row);
    return *it;
}

const QString &AdminModel::getRazza(uint row) const{
    return razzeList->at(row);
}
const QString &AdminModel::getClasse(uint row) const{
    return classiList->at(row);
}
const QString &AdminModel::getAllineamento(uint row) const{
    return allineamentiList->at(row);
}

const QJsonDocument &AdminModel::toQJsonDocument() const{
    QJsonDocument* modelJson= new QJsonDocument();
    QJsonObject mainObj;
    QJsonArray recordsArray;
    for(Record* r : recordList){
        QJsonObject recObj;
        recObj.insert(QString::fromStdString("razza"),r->getRazza());
        recObj.insert(QString::fromStdString("classe"),r->getClasse());
        recObj.insert(QString::fromStdString("allineamento"),r->getAllineamento());
        recObj.insert(QString::fromStdString("livello"),QJsonValue((int)r->getLivello()));
        recordsArray.push_back(recObj);
    }
    mainObj.insert(QString::fromStdString("razze"),QJsonArray::fromStringList(*razzeList));
    mainObj.insert(QString::fromStdString("classi"),QJsonArray::fromStringList(*classiList));
    mainObj.insert(QString::fromStdString("records"),recordsArray);
    modelJson->setObject(mainObj);

    return *modelJson;
}

void AdminModel::setFilePath(const QString& fname){*filepath= fname;}

void AdminModel::addRecord(Record* r){recordList.push_back(r);}

uint AdminModel::getRecordListSize() const{return recordList.size();}

void AdminModel::addRazza(const QString &r){razzeList->push_back(r);}
void AdminModel::addClasse(const QString &c){classiList->push_back(c);}

void AdminModel::setRazza(uint row, const QString& r){razzeList->replace(row, r);}
void AdminModel::setClasse(uint row, const QString& c){classiList->replace(row, c);}

void AdminModel::removeRazza(uint row){razzeList->removeAt(row);}
void AdminModel::removeClasse(uint row){classiList->removeAt(row);}

const QString& AdminModel::getFilePath() const{return *filepath;}
