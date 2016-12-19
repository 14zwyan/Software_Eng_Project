#include<iostream>
#include<string>
#include<sstream>


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

#include<boost/lexical_cast.hpp>


using std::string;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) ,question_getter_( new QNetworkAccessManager() )
{
    ui->setupUi(this);

    ui->progressBar_law->setRange(0,732);
    ui->progressBar_morallity->setRange(0,700);
    ui->progressBar_mao->setRange(0,1407);
    ui->progressBar_marx->setRange(0,1333);

//    QNetworkAccessManager *net_manager=new QNetworkAccessManager();
//     question_getter_=QuestionGetter(net_manager);
//   access_manager_=new QNetworkAccessManager();
//   network_request_=new QNetworkRequest();
//   network_request_->setUrl(QUrl("http://app.aitouda.com/api/io/question?id=1&type=mkszy"));
//   network_reply_=access_manager_->get(*network_request_);
//   connect( network_reply_, SIGNAL( readyRead() ) ,this, SLOT( slotrelpy() ) );
}

string NumberToString(int num)
{
    std::stringstream ss;
    ss<<num;
    string result;
    ss>>result;
    return result;
}



/*
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
**/
MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::get_law_next()
{
  //  string url="http://app.aitouda.com/api/io/question?id=1&type=fljc";
    int id=++fljc_count;
    string s_id=NumberToString(id);
    ui->progressBar_law->setValue(id);
    std::cout<<"id flcjcount"<<s_id<<std::endl;
    string url="http://app.aitouda.com/api/io/question?id="+s_id+"&type=fljc";

    std::cout<<"url:"<<url<<std::endl;

    question_getter_.get( QUrl(  QString::fromStdString(url)  ) );




}
void MainWindow::get_law_prev()
{
    int id=--fljc_count;  //need to change
    string s_id=NumberToString(id);
    ui->progressBar_law->setValue(id);  // need to  change
    std::cout<<"id flcjcount"<<s_id<<std::endl;
    string url="http://app.aitouda.com/api/io/question?id="+s_id+"&type=fljc";  // need to change

    std::cout<<"url:"<<url<<std::endl;

    question_getter_.get( QUrl(  QString::fromStdString(url)  ) );
}
void MainWindow::on_buuton_law_next_clicked()
{
    get_law_next();
    string question=question_getter_.question();
    QString q_question=QString::fromStdString( question );
    ui->browser_law_question->setText( q_question);


    std::vector<std::pair< std::string , bool> > answer=question_getter_.answer();

    std::vector< std::pair< std::string, bool>>::iterator begin=answer.begin();
    std::vector<std::pair<  std::string, bool>>::iterator end=answer.end();

    //QStringList strlist;
    strlist_.clear();

    while ( begin != end)
    {
        if( (*begin).second==false  )
        {
        strlist_.append( QString::fromStdString( (*begin).first ));
        std::cout<<"Answer in while"<<(*begin).first<<std::endl;
        }
        else
        {
            string yes_answer=(*begin).first+"√";

            strlist_.append( QString::fromStdString( yes_answer ) );  //need to change
        }
       ++begin;
    }



        if( listmodel_ )
        {
            std::cout<<"in listmodel"<<std::endl;
            int row_count=listmodel_->rowCount();
          std::cout<<"row count"<<row_count<<std::endl;
            listmodel_->removeRows(0, row_count);
            listmodel_->setStringList( strlist_);
        }
        else
        {
            std::cout<<"not in listmodel"<<std::endl;
             listmodel_=new QStringListModel(strlist_);
             ui->listView_law_answer->setModel(listmodel_);
        }

}
void MainWindow::on_button_law_prev_clicked()
{
    get_law_prev();   // need to change
    string question=question_getter_.question();
    QString q_question=QString::fromStdString( question );
    ui->browser_law_question->setText( q_question);  // need to change



    std::vector<std::pair< std::string , bool> > answer=question_getter_.answer();

    std::vector< std::pair< std::string, bool>>::iterator begin=answer.begin();
    std::vector<std::pair<  std::string, bool>>::iterator end=answer.end();

    //QStringList strlist;
    strlist_.clear();  // need to change

    while ( begin != end)
    {
        if( (*begin).second==false  )
        {
        strlist_.append( QString::fromStdString( (*begin).first ));  //need to change
        std::cout<<"Answer in while"<<(*begin).first<<std::endl;
        }
        else
        {
            string yes_answer=(*begin).first+"√";

            strlist_.append( QString::fromStdString( yes_answer ) );  //need to change
        }
       ++begin;
    }



        if( listmodel_ )   // need to change
        {
            std::cout<<"in listmodel"<<std::endl;
            int row_count=listmodel_->rowCount();  // need to change
          std::cout<<"row count"<<row_count<<std::endl;
            listmodel_->removeRows(0, row_count);  // need to change
            listmodel_->setStringList( strlist_);    // need to change
        }
        else
        {
            std::cout<<"not in listmodel"<<std::endl;
             listmodel_=new QStringListModel(strlist_);  // need to change
             ui->listView_law_answer->setModel(listmodel_); // need to change
        }
}


void MainWindow::get_morality_next()
{
    int id=++sxdd_count;   //need to change
    string s_id=NumberToString(id);
    ui->progressBar_morallity->setValue(id);   //need to change
    std::cout<<"id flcjcount"<<s_id<<std::endl;
    string url="http://app.aitouda.com/api/io/question?id="+s_id+"&type=sxdd";  //need to change

    std::cout<<"url:"<<url<<std::endl;

    question_getter_.get( QUrl(  QString::fromStdString(url)  ) );
}
void MainWindow::get_morality_prev()
{
    int id=--sxdd_count;  //need to change
    string s_id=NumberToString(id);
    ui->progressBar_morallity->setValue(id);  // need to  change
    std::cout<<"id flcjcount"<<s_id<<std::endl;
    string url="http://app.aitouda.com/api/io/question?id="+s_id+"&type=sxdd";  // need to change

    std::cout<<"url:"<<url<<std::endl;

    question_getter_.get( QUrl(  QString::fromStdString(url)  ) );
}
void MainWindow::on_button_morality_next_clicked()
{

    get_morality_next();    //need to change
    string question=question_getter_.question();
    QString q_question=QString::fromStdString( question );
    ui->textBrowser_morality->setText( q_question);   //need to change


    std::vector<std::pair< std::string , bool> > answer=question_getter_.answer();

    std::vector< std::pair< std::string, bool>>::iterator begin=answer.begin();
    std::vector<std::pair<  std::string, bool>>::iterator end=answer.end();

    //QStringList strlist;
    strlist_morality_.clear();  //need to change

    while ( begin != end)
    {
        if( (*begin).second==false  )
        {
        strlist_morality_.append( QString::fromStdString( (*begin).first ));  //need to change
        std::cout<<"Answer in while"<<(*begin).first<<std::endl;
        }
        else
        {
            string yes_answer=(*begin).first+"√";

            strlist_morality_.append( QString::fromStdString( yes_answer ) );  //need to change
        }
       ++begin;
    }



        if( listmodel_morality_ )   // need to change
        {
            std::cout<<"in listmodel"<<std::endl;
            int row_count=listmodel_morality_->rowCount();  // need to change
          std::cout<<"row count"<<row_count<<std::endl;
            listmodel_morality_->removeRows(0, row_count);   // need to change
            listmodel_morality_->setStringList( strlist_morality_);  // need to change
        }
        else
        {
            std::cout<<"not in listmodel"<<std::endl;
             listmodel_morality_=new QStringListModel(strlist_morality_);  // need to change
             ui->listView_morality->setModel(listmodel_morality_);  // need to change
        }


}
void MainWindow::on_button_morality_prev_clicked()
{
    get_morality_prev();  // need to change
    string question=question_getter_.question();
    QString q_question=QString::fromStdString( question );
    ui->textBrowser_morality->setText( q_question);  // need to change



    std::vector<std::pair< std::string , bool> > answer=question_getter_.answer();

    std::vector< std::pair< std::string, bool>>::iterator begin=answer.begin();
    std::vector<std::pair<  std::string, bool>>::iterator end=answer.end();

    //QStringList strlist;
    strlist_morality_.clear();  // need to change

    while ( begin != end)
    {
        if( (*begin).second==false  )
        {
        strlist_morality_.append( QString::fromStdString( (*begin).first ));  //need to change
        std::cout<<"Answer in while"<<(*begin).first<<std::endl;
        }
        else
        {
            string yes_answer=(*begin).first+"√";

            strlist_morality_.append( QString::fromStdString( yes_answer ) );  //need to change
        }
       ++begin;
    }



        if( listmodel_morality_ )   // need to change
        {
            std::cout<<"in listmodel"<<std::endl;
            int row_count=listmodel_morality_->rowCount();  // need to change
          std::cout<<"row count"<<row_count<<std::endl;
            listmodel_morality_->removeRows(0, row_count);  // need to change
            listmodel_morality_->setStringList( strlist_morality_);    // need to change
        }
        else
        {
            std::cout<<"not in listmodel"<<std::endl;
             listmodel_morality_=new QStringListModel(strlist_morality_);  // need to change
             ui->listView_morality->setModel(listmodel_morality_); // need to change
        }
}



void MainWindow::get_mao_next()
{
    int id=++mzdsx_count;   //need to change
    string s_id=NumberToString(id);
    ui->progressBar_mao->setValue(id);   //need to change
    std::cout<<"id flcjcount"<<s_id<<std::endl;
    string url="http://app.aitouda.com/api/io/question?id="+s_id+"&type=mzdsx";  //need to change

    std::cout<<"url:"<<url<<std::endl;

    question_getter_.get( QUrl(  QString::fromStdString(url)  ) );
}
void MainWindow::get_mao_prev()
{
    int id=--mzdsx_count;  //need to change
    string s_id=NumberToString(id);
    ui->progressBar_mao->setValue(id);  // need to  change
    std::cout<<"id flcjcount"<<s_id<<std::endl;
    string url="http://app.aitouda.com/api/io/question?id="+s_id+"&type=mzdsx";  // need to change

    std::cout<<"url:"<<url<<std::endl;

    question_getter_.get( QUrl(  QString::fromStdString(url)  ) );
}
void MainWindow::on_button_mao_next_clicked()
{
    get_mao_next();    //need to change
    string question=question_getter_.question();
    QString q_question=QString::fromStdString( question );
    ui->textBrowser_mao->setText( q_question);   //need to change


    std::vector<std::pair< std::string , bool> > answer=question_getter_.answer();

    std::vector< std::pair< std::string, bool>>::iterator begin=answer.begin();
    std::vector<std::pair<  std::string, bool>>::iterator end=answer.end();

    //QStringList strlist;
    strlist_mao_.clear();  //need to change

    while ( begin != end)
    {
        if( (*begin).second==false  )
        {
        strlist_mao_.append( QString::fromStdString( (*begin).first ));  //need to change
        std::cout<<"Answer in while"<<(*begin).first<<std::endl;
        }
        else
        {
            string yes_answer=(*begin).first+"√";

            strlist_mao_.append( QString::fromStdString( yes_answer ) );  //need to change
        }
       ++begin;
    }



        if( listmodel_mao_ )   // need to change
        {
            std::cout<<"in listmodel"<<std::endl;
            int row_count=listmodel_mao_->rowCount();  // need to change
          std::cout<<"row count"<<row_count<<std::endl;
            listmodel_mao_->removeRows(0, row_count);   // need to change
            listmodel_mao_->setStringList( strlist_mao_);  // need to change
        }
        else
        {
            std::cout<<"not in listmodel"<<std::endl;
             listmodel_mao_=new QStringListModel(strlist_mao_);  // need to change
             ui->listView_mao->setModel(listmodel_mao_);  // need to change
        }

}
void MainWindow::on_button_mao_prev_clicked()
{
    get_mao_prev();  // need to change
    string question=question_getter_.question();
    QString q_question=QString::fromStdString( question );
    ui->textBrowser_mao->setText( q_question);  // need to change



    std::vector<std::pair< std::string , bool> > answer=question_getter_.answer();

    std::vector< std::pair< std::string, bool>>::iterator begin=answer.begin();
    std::vector<std::pair<  std::string, bool>>::iterator end=answer.end();

    //QStringList strlist;
    strlist_mao_.clear();  // need to change

    while ( begin != end)
    {
        if( (*begin).second==false  )
        {
        strlist_mao_.append( QString::fromStdString( (*begin).first ));  //need to change
        std::cout<<"Answer in while"<<(*begin).first<<std::endl;
        }
        else
        {
            string yes_answer=(*begin).first+"√";

            strlist_mao_.append( QString::fromStdString( yes_answer ) );  //need to change
        }
       ++begin;
    }



        if( listmodel_mao_ )   // need to change
        {
            std::cout<<"in listmodel"<<std::endl;
            int row_count=listmodel_mao_->rowCount();  // need to change
          std::cout<<"row count"<<row_count<<std::endl;
            listmodel_mao_->removeRows(0, row_count);  // need to change
            listmodel_mao_->setStringList( strlist_mao_);    // need to change
        }
        else
        {
            std::cout<<"not in listmodel"<<std::endl;
             listmodel_mao_=new QStringListModel(strlist_mao_);  // need to change
             ui->listView_mao->setModel(listmodel_mao_); // need to change
        }
}




void MainWindow::get_marx_next()
{
    int id=++mkszy_count;   //need to change
    string s_id=NumberToString(id);
    ui->progressBar_marx->setValue(id);   //need to change
    std::cout<<"id flcjcount"<<s_id<<std::endl;
    string url="http://app.aitouda.com/api/io/question?id="+s_id+"&type=mkszy";  //need to change

    std::cout<<"url:"<<url<<std::endl;

    question_getter_.get( QUrl(  QString::fromStdString(url)  ) );
}
void MainWindow::get_marx_prev()
{
    int id=--mkszy_count;  //need to change
    string s_id=NumberToString(id);
    ui->progressBar_marx->setValue(id);  // need to  change
    std::cout<<"id flcjcount"<<s_id<<std::endl;
    string url="http://app.aitouda.com/api/io/question?id="+s_id+"&type=mkszy";  // need to change

    std::cout<<"url:"<<url<<std::endl;

    question_getter_.get( QUrl(  QString::fromStdString(url)  ) );
}
void MainWindow::on_button_marx_next_clicked()
{
    get_marx_next();    //need to change
    string question=question_getter_.question();
    QString q_question=QString::fromStdString( question );
    ui->textBrowser_marx->setText( q_question);   //need to change


    std::vector<std::pair< std::string , bool> > answer=question_getter_.answer();

    std::vector< std::pair< std::string, bool>>::iterator begin=answer.begin();
    std::vector<std::pair<  std::string, bool>>::iterator end=answer.end();

    //QStringList strlist;
    strlist_marx_.clear();  //need to change

    while ( begin != end)
    {
        if( (*begin).second==false  )
        {
        strlist_marx_.append( QString::fromStdString( (*begin).first ));  //need to change
        std::cout<<"Answer in while"<<(*begin).first<<std::endl;
        }
        else
        {
            string yes_answer=(*begin).first+"√";

            strlist_marx_.append( QString::fromStdString( yes_answer ) );  //need to change
        }
       ++begin;
    }



        if( listmodel_marx_ )   // need to change
        {
            std::cout<<"in listmodel"<<std::endl;
            int row_count=listmodel_marx_->rowCount();  // need to change
          std::cout<<"row count"<<row_count<<std::endl;
            listmodel_marx_->removeRows(0, row_count);   // need to change
            listmodel_marx_->setStringList( strlist_marx_);  // need to change
        }
        else
        {
            std::cout<<"not in listmodel"<<std::endl;
             listmodel_marx_=new QStringListModel(strlist_marx_);  // need to change
             ui->listView_marx->setModel(listmodel_marx_);  // need to change
        }

}
void MainWindow::on_button_marx_prev_clicked()
{
    get_marx_prev();  // need to change
    string question=question_getter_.question();
    QString q_question=QString::fromStdString( question );
    ui->textBrowser_marx->setText( q_question);  // need to change



    std::vector<std::pair< std::string , bool> > answer=question_getter_.answer();

    std::vector< std::pair< std::string, bool>>::iterator begin=answer.begin();
    std::vector<std::pair<  std::string, bool>>::iterator end=answer.end();

    //QStringList strlist;
    strlist_marx_.clear();  // need to change

    while ( begin != end)
    {
        if( (*begin).second==false  )
        {
        strlist_marx_.append( QString::fromStdString( (*begin).first ));  //need to change
        std::cout<<"Answer in while"<<(*begin).first<<std::endl;
        }
        else
        {
            string yes_answer=(*begin).first+"√";

            strlist_marx_.append( QString::fromStdString( yes_answer ) );  //need to change
        }
       ++begin;
    }



        if( listmodel_marx_ )   // need to change
        {
            std::cout<<"in listmodel"<<std::endl;
            int row_count=listmodel_marx_->rowCount();  // need to change
          std::cout<<"row count"<<row_count<<std::endl;
            listmodel_marx_->removeRows(0, row_count);  // need to change
            listmodel_marx_->setStringList( strlist_marx_);    // need to change
        }
        else
        {
            std::cout<<"not in listmodel"<<std::endl;
             listmodel_marx_=new QStringListModel(strlist_marx_);  // need to change
             ui->listView_marx->setModel(listmodel_marx_); // need to change
        }
}




void MainWindow::get_history_next()
{
    int id=++zgjds_count;   //need to change
    string s_id=NumberToString(id);
    ui->progressBar_history->setValue(id);   //need to change
    std::cout<<"id flcjcount"<<s_id<<std::endl;
    string url="http://app.aitouda.com/api/io/question?id="+s_id+"&type=zgjds";  //need to change

    std::cout<<"url:"<<url<<std::endl;

    question_getter_.get( QUrl(  QString::fromStdString(url)  ) );
}
void MainWindow::get_history_prev()
{
    int id=--zgjds_count;  //need to change
    string s_id=NumberToString(id);
    ui->progressBar_history->setValue(id);  // need to  change
    std::cout<<"id flcjcount"<<s_id<<std::endl;
    string url="http://app.aitouda.com/api/io/question?id="+s_id+"&type=zgjds";  // need to change

    std::cout<<"url:"<<url<<std::endl;

    question_getter_.get( QUrl(  QString::fromStdString(url)  ) );
}
void MainWindow::on_button_history_next_clicked()
{
    get_history_next();    //need to change
    string question=question_getter_.question();
    QString q_question=QString::fromStdString( question );
    ui->textBrowser_history->setText( q_question);   //need to change


    std::vector<std::pair< std::string , bool> > answer=question_getter_.answer();

    std::vector< std::pair< std::string, bool>>::iterator begin=answer.begin();
    std::vector<std::pair<  std::string, bool>>::iterator end=answer.end();

    //QStringList strlist;
    strlist_history_.clear();  //need to change

    while ( begin != end)
    {
        if( (*begin).second==false  )
        {
        strlist_history_.append( QString::fromStdString( (*begin).first ));  //need to change
        std::cout<<"Answer in while"<<(*begin).first<<std::endl;
        }
        else
        {
            string yes_answer=(*begin).first+"√";

            strlist_history_.append( QString::fromStdString( yes_answer ) );  //need to change
        }
       ++begin;
    }



        if( listmodel_history_ )   // need to change
        {
            std::cout<<"in listmodel"<<std::endl;
            int row_count=listmodel_history_->rowCount();  // need to change
          std::cout<<"row count"<<row_count<<std::endl;
            listmodel_history_->removeRows(0, row_count);   // need to change
            listmodel_history_->setStringList( strlist_history_);  // need to change
        }
        else
        {
            std::cout<<"not in listmodel"<<std::endl;
             listmodel_history_=new QStringListModel(strlist_history_);  // need to change
             ui->listView_history->setModel(listmodel_history_);  // need to change
        }
}
void MainWindow::on_button_history_prev_clicked()
{
    get_history_prev();  // need to change
    string question=question_getter_.question();
    QString q_question=QString::fromStdString( question );
    ui->textBrowser_history->setText( q_question);  // need to change



    std::vector<std::pair< std::string , bool> > answer=question_getter_.answer();

    std::vector< std::pair< std::string, bool>>::iterator begin=answer.begin();
    std::vector<std::pair<  std::string, bool>>::iterator end=answer.end();

    //QStringList strlist;
    strlist_history_.clear();  // need to change

    while ( begin != end)
    {
        if( (*begin).second==false  )
        {
        strlist_history_.append( QString::fromStdString( (*begin).first ));  //need to change
        std::cout<<"Answer in while"<<(*begin).first<<std::endl;
        }
        else
        {
            string yes_answer=(*begin).first+"√";

            strlist_history_.append( QString::fromStdString( yes_answer ) );  //need to change
        }
       ++begin;
    }



        if( listmodel_history_ )   // need to change
        {
            std::cout<<"in listmodel"<<std::endl;
            int row_count=listmodel_history_->rowCount();  // need to change
          std::cout<<"row count"<<row_count<<std::endl;
            listmodel_history_->removeRows(0, row_count);  // need to change
            listmodel_history_->setStringList( strlist_history_);    // need to change
        }
        else
        {
            std::cout<<"not in listmodel"<<std::endl;
             listmodel_history_=new QStringListModel(strlist_history_);  // need to change
             ui->listView_history->setModel(listmodel_history_); // need to change
        }
}






