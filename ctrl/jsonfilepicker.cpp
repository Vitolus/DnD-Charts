#include "jsonfilepicker.h"

QString JsonFilePicker::selectJsonFileDialog(){
    QFileDialog dialog;
    QString fileName;
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Json File (*.json)");
    if (dialog.exec()) fileName= dialog.selectedFiles().at(0);
    return fileName;
}

QJsonDocument* JsonFilePicker::getJsonFileData(const QString& path){
    if(path.isNull()) return new QJsonDocument();
    QString fileData;
    QFile file;
    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileData= file.readAll();
    file.close();
    //Controllo validità documento
    QJsonDocument* doc= new QJsonDocument(QJsonDocument::fromJson(fileData.toLocal8Bit()));
    QJsonObject dataObj= doc->object();
    if(!dataObj.contains("records") || !dataObj.contains("razze")
            || !dataObj.contains("classi")){
        delete doc;
        return new QJsonDocument();
    }
    return doc;
}

QStringList* JsonFilePicker::getRazzeList(QJsonDocument* data){
    QStringList* dataList= new QStringList;
    QJsonObject dataObj= data->object();
    QJsonArray dataArray= dataObj["razze"].toArray();
    for(const QJsonValue& value : dataArray){
        dataList->append(value.toString());
    }
    return dataList;
}
QStringList* JsonFilePicker::getClassiList(QJsonDocument* data){
    QStringList* dataList= new QStringList;
    QJsonObject dataObj= data->object();
    QJsonArray dataArray= dataObj["classi"].toArray();
    for(const QJsonValue& value : dataArray){
        dataList->append(value.toString());
    }
    return dataList;
}

QList<Record*> JsonFilePicker::getRecords(QJsonDocument* data){
    QList<Record*> ret;
    QJsonObject dataObj= data->object();
    QJsonArray records= dataObj["records"].toArray();
    for(const QJsonValue& record : records){
        Record* r= new Record(
                record.toObject().value("razza").toString(),
                record.toObject().value("classe").toString(),
                record.toObject().value("allineamento").toString(),
                record.toObject().value("livello").toInt());
        ret.push_back(r);
    }
    return ret;
}

bool JsonFilePicker::saveAdminModel(const QJsonDocument& doc, const QString& path){
    if(path.isNull() || path.isEmpty()) return false;
    QFile file(path);
    if(file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate)){
        file.write(doc.toJson());
        file.close();
        return true;
    }
    return false;
}


