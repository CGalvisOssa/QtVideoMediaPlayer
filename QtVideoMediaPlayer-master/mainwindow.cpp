#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Dando los estilos a cada uno de los botones del reproductor
    //Prueba de repositorio
    ui->setupUi(this);

    Player = new QMediaPlayer();

    // Asignar iconos a los botones
    ui->pushButton_pausar->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButton_adelantar->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_retroceder->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButton_mute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    // Establecer el rango del slider de volumen
    ui->verticalSlider_Volume->setMinimum(0);
    ui->verticalSlider_Volume->setMaximum(100);
    Player->setVolume(ui->verticalSlider_Volume->value());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_pausar_clicked()
{
    if (IS_Pause) {
        Player->play();
        IS_Pause = false;
        ui->pushButton_pausar->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    } else {
        Player->pause();
        IS_Pause = true;
        ui->pushButton_pausar->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    Player->setPosition(value); // Ajustar la posición del video
}

void MainWindow::on_pushButton_retroceder_clicked()
{
    Player->setPosition(Player->position() - 10000); // Retrocede 10 segundos
}

void MainWindow::on_pushButton_mute_clicked()
{
    if (IS_Muted == false) {
        IS_Muted = true;  // Asignar valor verdadero (silenciar)
        ui->pushButton_mute->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted)); // Cambiar icono a silenciado
        Player->setMuted(true);  // Silenciar el reproductor
    } else {
        IS_Muted = false;  // Asignar valor falso (activar sonido)
        ui->pushButton_mute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));  // Cambiar icono a sonido activado
        Player->setMuted(false);  // Activar sonido
    }
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    Player->setVolume(value); // Ajustar el volumen
}

void MainWindow::on_pushButton_stop_clicked()
{
    Player->stop(); // Detener reproducción
}

void MainWindow::on_pushButton_adelantar_clicked()
{
    Player->setPosition(Player->position() + 10000); // Adelanta 10 segundos
}

void MainWindow::on_treeView_collapsed(const QModelIndex &index)
{

}

