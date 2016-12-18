#include<iostream>
#include<string>


#include "MainWindow.h"
#include "ui_MainWindow.h"

#include<QtNetwork/QtNetwork>
#include<QtNetwork/QNetworkAccessManager>
#include<QtNetwork/QNetworkRequest>
#include<QtNetwork/QNetworkReply>
#include<QVector>

#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonParseError>
#include<QJsonObject>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//   access_manager_=new QNetworkAccessManager();
//   network_request_=new QNetworkRequest();
//   network_request_->setUrl(QUrl("http://app.aitouda.com/api/io/question?id=1&type=mkszy"));
//   network_reply_=access_manager_->get(*network_request_);
//   connect( network_reply_, SIGNAL( readyRead() ) ,this, SLOT( slotrelpy() ) );
}


void MainWindow::slotrelpy()
{
    std::cout<<"in"<<std::endl;
    QByteArray array=network_reply_->readAll();
    QJsonParseError json_errorn;
    QJsonDocument doc=QJsonDocument::fromJson( array, &json_errorn);

    if( json_errorn.error !=  QJsonParseError::NoError)
    {
        std::cout<<"error"<<std::endl;
        return ;
    }
    if( doc.isObject() )
    {
        std::cout<<"is object"<<std::endl;
        QJsonObject obj=doc.object();
        //std::cout<<obj.contains("data")<<std::endl;
        QJsonValue qdata_value=obj.take("data");

        QJsonObject qdata_object=qdata_value.toObject();
        QJsonValue  question_value=qdata_object.value("question");
        QString q_question=question_value.toString();
        std::cout<<q_question.toStdString()<<std::endl;
//       QJsonArray data=obj["data"].toArray();
//       int n_size=data.size();

//       for( int i=0; i != n_size ; ++i)
//       {
//         QJsonObject object=data.at(i).toObject();
//           QString qstring=object["question"].toString();
//            std::string result=qstring.toStdString();
//           std::cout<<"In here" <<result<<std::endl;
//     }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}



