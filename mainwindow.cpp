#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Inicializar el reproductor de video y el control de audio
    Player = new QMediaPlayer(this);
    QAudioOutput* audioOutput = new QAudioOutput(this);
    Player->setAudioOutput(audioOutput);

    // Asignar iconos a los botones
    ui->pushButton_pausar->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButton_adelantar->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_retroceder->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButton_mute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    // Establecer el rango del slider de volumen
    ui->verticalSlider->setMinimum(0);
    ui->verticalSlider->setMaximum(100);
    audioOutput->setVolume(ui->verticalSlider->value() / 100.0);  // Configura el volumen inicial



    connect(Player, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    connect(Player, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);

    ui->horizontalSlider->setRange(0, Player->duration() / 1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::durationChanged(qint64 duration)
{
    mDuration = duration / 1000;
    ui->horizontalSlider->setMaximum(mDuration);
}

void MainWindow::positionChanged(qint64 duration)
{
    if (!ui->horizontalSlider->isSliderDown())
    {
        ui->horizontalSlider->setValue(duration / 1000);
    }
    updateDuration(duration / 1000);
}

void MainWindow::updateDuration(qint64 Duration)
{
    if ( Duration || mDuration)
    {
        if (Duration || mDuration)
        {
            QTime CurrentTime((Duration / 3600) % 60, (Duration / 60) % 60, Duration % 60, (Duration * 1000) % 1000);
            QTime TotalTime((mDuration / 3600) % 60, (mDuration / 60) % 60, mDuration % 60, (mDuration * 1000) % 1000);
            QString Format = "";
            if (mDuration > 3600) Format = "hh:mm:ss";
            else Format = "mm:ss";

            ui->label_time->setText(CurrentTime.toString(Format));

    }

}
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
    QAudioOutput* audioOutput = static_cast<QAudioOutput*>(Player->audioOutput());
    if (IS_Muted == false) {
        IS_Muted = true;  // Asignar valor verdadero (silenciar)
        ui->pushButton_mute->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted)); // Cambiar icono a silenciado
        audioOutput->setMuted(true);  // Silenciar el audio
    } else {
        IS_Muted = false;  // Asignar valor falso (activar sonido)
        ui->pushButton_mute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));  // Cambiar icono a sonido activado
        audioOutput->setMuted(false);  // Activar sonido
    }
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    QAudioOutput* audioOutput = static_cast<QAudioOutput*>(Player->audioOutput());
    audioOutput->setVolume(value / 100.0); // Ajustar el volumen
}

void MainWindow::on_pushButton_stop_clicked()
{
    Player->stop(); // Detener reproducción
}

void MainWindow::on_pushButton_adelantar_clicked()
{
    Player->setPosition(Player->position() + 10000); // Adelanta 10 segundos
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Seleccionar archivo de video"),
        "",
        tr("Archivos MP4 (*.mp4)")
        );

    // Crea un nuevo widget de video
    QVideoWidget* video = new QVideoWidget();

    // Ajusta la geometría del widget de video dentro de groupBox_Video
    video->setGeometry(
        5, 5,
        ui->groupBox_Video->width() - 10,
        ui->groupBox_Video->height() - 10
        );

    // Establece el widget de video como hijo de groupBox_Video
    video->setParent(ui->groupBox_Video);

    // Configura el reproductor de video
    Player->setVideoOutput(video);
    Player->setSource(QUrl::fromLocalFile(fileName));  // Usa setSource en lugar de setMedia

    // Muestra el widget de video
    video->setVisible(true);
    video->show();
}


