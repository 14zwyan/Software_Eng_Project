#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtNetwork/QNetworkAccessManager>
#include<QtNetwork/QNetworkRequest>
#include<QtNetwork/QNetworkReply>
#include<QStringListModel>


#include"QuestionGetter.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    void get_law_next();
    void get_law_prev();

    void get_morality_next() ;
    void get_morality_prev();

    void get_mao_next();
    void get_mao_prev();

    void get_marx_next();
    void get_marx_prev();

    void get_history_next();
    void get_history_prev();

    Ui::MainWindow *ui;

    QuestionGetter  question_getter_;

    QStringListModel * listmodel_=nullptr;
    QStringList strlist_;

    QStringListModel *listmodel_morality_=nullptr;
    QStringList strlist_morality_;

    QStringListModel *listmodel_mao_=nullptr;
    QStringList strlist_mao_;

    QStringListModel *listmodel_marx_=nullptr;
    QStringList strlist_marx_;


    QStringListModel  *listmodel_history_=nullptr;
    QStringList strlist_history_;

    int fljc_count=0;
    int sxdd_count=0;
    int mzdsx_count=0;
    int mkszy_count=0;
    int zgjds_count=0;

private slots:
    //void slotrelpy();

    void on_buuton_law_next_clicked();
    void on_button_law_prev_clicked();
    void on_button_morality_next_clicked();
    void on_button_mao_next_clicked();
    void on_button_marx_next_clicked();
    void on_button_history_next_clicked();
    void on_button_morality_prev_clicked();
    void on_button_mao_prev_clicked();
    void on_button_marx_prev_clicked();
    void on_button_history_prev_clicked();
};

#endif // MAINWINDOW_H
