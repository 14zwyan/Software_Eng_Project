#ifndef QUESTIONGETTER_H
#define QUESTIONGETTER_H

#include<QObject>
#include<QtNetwork/QNetworkAccessManager>
#include<QtNetwork/QNetworkRequest>
#include<QtNetwork/QNetworkReply>

#include<string>
#include<vector>
#include<utility>


#include"QuestionGetter.h"


class Question
{
public :
    void set_question(std::string question )  { question_=question; }
    void add(   std::pair<std::string , bool> elem)
    {
        answer_.push_back(elem);
    }

    std::string  question()  { return question_; }
    std::vector< std::pair<std::string, bool> > answer()  { return answer_;}

    void ClearAnswer()  {  answer_.clear(); }

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
    std::string  question()  { return question_.question(); }
    std::vector< std::pair<std::string, bool> > answer()  { return question_.answer();}

   void ClearAnswer()  { question_.ClearAnswer(); }

private:
    QNetworkAccessManager  *m_pManager;
    Question question_;

private slots:
    void GetQuestion();


};

#endif // QUESTIONGETTER_H
