#include<iostream>


#include"QuestionGetter.h"

#include "MainWindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    std::cout<<"haha"<<std::endl;


    //question_getter.test();

//  QNetworkAccessManager *netManager =new QNetworkAccessManager();
//   //MyNetManager manager(netManager);

// //   manager.get(QUrl("http://blog.csdn.net/u010002704"));


    return a.exec();
}
