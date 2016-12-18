#ifndef QUESTIONGETTER_H
#define QUESTIONGETTER_H

#include<QObject>
#include<QtNetwork/QNetworkAccessManager>
#include<QtNetwork/QNetworkRequest>
#include<QtNetwork/QNetworkReply>

#include<string>
#include<vector>
#include<utility>



class Question
{
public :
    void add(   std::pair<std::string , bool> elem)
    {
        answer_.push_back(elem);
    }

private:
    std::string question_;
    std::vector<std::pair<std::string , bool> >  answer_;

};




class QuestionGetter :public QObject
{
    Q_OBJECT

public:
    explicit  QuestionGetter(QNetworkAccessManager *pManager);

    ~QuestionGetter();

    bool get(QUrl url);

    void test();


private:
    QNetworkAccessManager  *m_pManager;
    Question question_;

private slots:
    void GetQuestion();


};

#endif // QUESTIONGETTER_H
