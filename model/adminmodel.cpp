#include "adminmodel.h"

AdminModel::AdminModel(QJsonDocument *data, QString* path){
    razzeList = JSONFilePicker::getRazzeList(data);
    classiList = JSONFilePicker::getClassiList(data);
    allineamentiList = JSONFilePicker::getAllineamentiList(data);
    recordList = JSONFilePicker::getRecords(data);
    filepath = path;
}
AdminModel::AdminModel(){
    razzeList = new QStringList();
    classiList = new QStringList();
    allineamentiList = new QStringList();
    filepath = new QString();
}
AdminModel::AdminModel(const AdminModel &m){
    filepath = new QString(*m.filepath);
    razzeList = new QStringList(*m.razzeList);
    classiList = new QStringList(*m.classiList);
    allineamentiList = new QStringList(*m.allineamentiList);
    for(const auto& r : m.recordList)
        recordList.push_back(new Record(*r));
}
AdminModel::~AdminModel(){
    delete filepath;
    delete razzeList;
    delete classiList;
    delete allineamentiList;
    for(auto r : recordList)
        delete r;
}

QStringList* AdminModel::getRazzeList() const{ return razzeList;}
QStringList* AdminModel::getClassiList() const{ return classiList;}
QStringList* AdminModel::getAllineamentiList() const{ return allineamentiList;}
std::list<Record*> AdminModel::getRecordList() const{return recordList;}

void AdminModel::removeRecord(unsigned int row){
    std::list<Record*>::iterator it= recordList.begin();
    std::advance(it,row);
    recordList.erase(it);
}

Record* AdminModel::getRecord(unsigned int row) const{
    std::list<Record*>::const_iterator it= recordList.begin();
    std::advance(it,row);
    return *it;
}

const QString &AdminModel::getRazza(unsigned int row) const{
    return razzeList->at(row);
}
const QString &AdminModel::getClasse(unsigned int row) const{
    return classiList->at(row);
}
const QString &AdminModel::getAllineamento(unsigned int row) const{
    return allineamentiList->at(row);
}

const QJsonDocument &AdminModel::toQJSonDocument() const{
    QJsonDocument* modelJson = new QJsonDocument();
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
    mainObj.insert(QString::fromStdString("allineamenti"),QJsonArray::fromStringList(*allineamentiList));
    mainObj.insert(QString::fromStdString("records"),recordsArray);
    modelJson->setObject(mainObj);

    return *modelJson;
}

void AdminModel::setFilePath(const QString &fname){*filepath = fname;}

void AdminModel::addRecord(Record *r){recordList.push_back(r);}

unsigned int AdminModel::getRecordListSize() const{return recordList.size();}

void AdminModel::addRazza(const QString &r){razzeList->push_back(r);}
void AdminModel::addClasse(const QString &c){classiList->push_back(c);}
void AdminModel::addAllineamento(const QString &a){allineamentiList->push_back(a);}

void AdminModel::setRazza(unsigned int row, const QString &r){razzeList->replace(row,r);}
void AdminModel::setClasse(unsigned int row, const QString &c){classiList->replace(row,c);}
void AdminModel::setAllineamento(unsigned int row, const QString &a){allineamentiList->replace(row,a);}

void AdminModel::removeRazza(unsigned int row){razzeList->removeAt(row);}
void AdminModel::removeClasse(unsigned int row){classiList->removeAt(row);}
void AdminModel::removeAllineamento(unsigned int row){allineamentiList->removeAt(row);}

const QString& AdminModel::getFilePath() const{return *filepath;}
