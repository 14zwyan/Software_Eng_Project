#include "QuestionGetter.h"

#include<QUrl>
#include<QByteArray>
#include<QNetworkReply>
#include<QNetworkRequest>
#include<iostream>
#include<QJsonParseError>
#include<QJsonValue>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>


QuestionGetter::QuestionGetter(QNetworkAccessManager *parent):m_pManager(parent)
{

}

bool QuestionGetter::get(QUrl url)
{

    QNetworkRequest request;

    request.setUrl( url );

    QNetworkReply *reply=m_pManager->get( request );

    connect( reply, SIGNAL ( readyRead() ) ,this , SLOT(  GetQuestion())  ) ;
   // connect(reply,  SIGNAL( finished() ), this , SLOT( GetQuestion()) );
    return true;
}


void QuestionGetter::GetQuestion()
{
    ClearAnswer();
    QNetworkReply *reply= (QNetworkReply *) sender();

    QByteArray array=reply->readAll();

    QJsonParseError json_errorn;
    QJsonDocument doc=QJsonDocument::fromJson(array, &json_errorn);

    if(  json_errorn.error != QJsonParseError::NoError)
    {
        std::cout<<"Error"<<std::endl;
        return ;
    }
    if( doc.isObject() )
    {
        std::cout<<"is object"<<std::endl;
        QJsonObject obj=doc.object();

        QJsonValue data_value=obj.take( "data");

        QJsonObject data_object=data_value.toObject();

        QJsonValue id_value=data_object.take("id");
        int id=id_value.toInt();
        std::cout<<"Id:"<<id<<std::endl;

        QJsonValue question_value=data_object.take("question");
        QString q_question=question_value.toString();
        std::string question=q_question.toStdString();
        question_.set_question(question);
        std::cout<<"question:"<<question<<std::endl;

        QJsonValue type_value=data_object.take("type");
        int type=type_value.toVariant().toInt();
        std::cout<<"type:"<<type<<std::endl;

        QJsonValue answer_value=data_object.take("answer");
        //QJsonObject answer_object=answer_value.toObject();
        QJsonArray answer=answer_value.toArray();
        int n_size=answer.size();
        for( int i=0; i != n_size ; ++i)
        {
            QJsonObject object=answer.at(i).toObject();

            QJsonValue  text_value=object.value("text");
            QString q_text=text_value.toString();
            std::string text=q_text.toStdString();

            QJsonValue  isRight_value=object.value("is_right");
           int  is_right=isRight_value.toVariant().toInt();

            std::cout<<"text"<<text<<std::endl;
            std::cout<<"isright"<<is_right<<std::endl;
            if( is_right)
            {
                question_.add( std::make_pair(text, true ) );
            }
            else
            {
                question_.add( std::make_pair( text, false) );
            }
        }

        reply->deleteLater();
    }

}


void QuestionGetter::test()
{
    get(QUrl("http://app.aitouda.com/api/io/question?id=1&type=mkszy") );
}


 QuestionGetter::~QuestionGetter()
{

}
