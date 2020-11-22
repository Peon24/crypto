#include "log.h"
#include "ui_log.h"

Log::Log(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::log)
{
    ui->setupUi(this);
    movie = new QMovie(":/gifs/links-legs-kicking.gif");
}

Log::~Log()
{

    delete movie;
    delete ui;
}

void Log::startMovie(){
    this->show();

    ui->movie->setMovie(movie);
    movie->setSpeed(100);
    movie->setScaledSize(QSize(400, 400));
    movie->start();

}

void Log::stopMovie(){
    movie->stop();

    this->close();


}
