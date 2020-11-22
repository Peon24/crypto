#ifndef LOG_H
#define LOG_H

#include <QDialog>
#include <QMovie>

namespace Ui {
class log;
}

class Log : public QDialog
{
    Q_OBJECT

public:

    QMovie *movie;

    void startMovie();
    void stopMovie();

    explicit Log(QWidget *parent = nullptr);
    ~Log();

private:
    Ui::log *ui;
};

#endif // LOG_H
