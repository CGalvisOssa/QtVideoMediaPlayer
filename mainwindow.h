#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QtCore>
#include <QtWidgets>
#include <QtGui>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_pausar_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_pushButton_retroceder_clicked();
    void on_pushButton_mute_clicked();
    void on_verticalSlider_valueChanged(int value);
    void on_pushButton_stop_clicked();
    void on_pushButton_adelantar_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *Player;
    QVideoWidget *Video; // Este widget debería ser inicializado y usado en la implementación
    qint64 mDuration;
    bool IS_Pause = true;
    bool IS_Muted = false;
};

#endif // MAINWINDOW_H
