#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardItemModel>

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

    //conexion de señales y slots (actualiza posición video)
    connect(Player, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    connect(Player, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);

    ui->progressBar->setRange(0, Player->duration() / 1000);

    //Inicalizar y configurar el TreeView
    setupTreeView();

    // Crear acciones para el menú
    QAction *actionOpen = new QAction("Abrir carpeta", this);
    QAction *actionAddFile = new QAction("Agregar archivo", this);

    // Conectar las acciones a sus respectivos slots
    connect(actionOpen, &QAction::triggered, this, &MainWindow::on_actionOpen_triggered);
    connect(actionAddFile, &QAction::triggered, this, &MainWindow::on_actionAddFile_triggered);

    // Crear un menú "Archivo" si no existe
    QMenu *fileMenu = menuBar()->findChild<QMenu *>("menuArchivo");
    if (!fileMenu) {
        fileMenu = menuBar()->addMenu("Archivo");
    }

    // Agregar las acciones al menú
    fileMenu->addAction(actionOpen);
    fileMenu->addAction(actionAddFile);

    // Añade esta línea junto con las otras conexiones
    connect(Player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::onMediaStatusChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Biblioteca
void MainWindow::setupTreeView()
{
    // Crear y configurar el modelo (permite gestionen elementos)
    model = new DragDropModel(this);
    model->setHorizontalHeaderLabels(QStringList() << "Biblioteca Musica");

    //Muestra los elementos añadidos
    ui->treeView->setModel(model);

    // Configurar el TreeView
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers); // NO Editar texto
    ui->treeView->setSelectionMode(QAbstractItemView::SingleSelection); // Un Solo Elemento a la Vez
    ui->treeView->setSelectionBehavior(QAbstractItemView::SelectRows);  // Se Seleccione la Fila Correspondiente (Comportamiento)
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu); // Menu Contextual

    // Agregar estas nuevas líneas aquí:
    ui->treeView->setDragEnabled(true); // Deslizar Canción
    ui->treeView->setAcceptDrops(true); // Soltar al Deslizar Canción
    ui->treeView->setDropIndicatorShown(true); // Indicador Caiga Canción
    ui->treeView->setDragDropMode(QAbstractItemView::InternalMove); //

    // Mantén las conexiones existentes
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::on_treeView_clicked); //Click
    connect(ui->treeView, &QTreeView::customContextMenuRequested, //Menú Conceptual
            this, &MainWindow::showTreeViewContextMenu);
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    if (index.isValid()) {    // Verifica elemento click - Recupera elemento (ruta) - Se estabece y reproduce
        currentSongIndex = index.row();  // Actualizar el índice actual
        QStandardItem *item = model->itemFromIndex(index);
        QString filePath = item->data(Qt::UserRole).toString();
        Player->setSource(QUrl::fromLocalFile(filePath));
        Player->play();
    }
}
void MainWindow::showTreeViewContextMenu(const QPoint &pos)
{
    QModelIndex index = ui->treeView->indexAt(pos); // Posición donde hizo click de (menú) - Valido crea (eliminar)
    if (index.isValid()) {
        QMenu contextMenu(this);
        QAction *removeAction = contextMenu.addAction("Eliminar"); // Conecta la eliminación al slot(canción)
        connect(removeAction, &QAction::triggered, this, &MainWindow::removeSelectedVideo);
        contextMenu.exec(ui->treeView->viewport()->mapToGlobal(pos)); // Muestra el menú conceptual
    }
}

void MainWindow::removeSelectedVideo()
{
    QModelIndex index = ui->treeView->currentIndex(); // Obtiene el indicador seleccionado - valido? = T (Lo elimina)
    if (index.isValid()) {
        model->removeRow(index.row());
    }
}

void MainWindow::on_actionOpen_triggered() //Abrir Carpeta Con Videos
{
    QString folderPath = QFileDialog::getExistingDirectory( //Permite al usuario seleccionar la carpeta
        this,
        tr("Seleccionar carpeta con videos"),
        "",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );

    if (!folderPath.isEmpty()) { // Folder vacio?

        // Restablecer el modelo existente
        model->clear();
        model->setHorizontalHeaderLabels(QStringList() << "Biblioteca Musica");

        QDir directory(folderPath); //Interaccion en el sistema de archivos de esa carpeta
        QStringList filters;
        filters << "*.mp4" << "*.mp3" << "*.avi" << "*.mkv"; //Filtros para Tipos de archivos
        QFileInfoList files = directory.entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot); //Se obtiene carpeta que coinciden
                                                                                                    //con este filtro

        foreach(const QFileInfo &fileInfo, files) { //Para Cada Archivo Se Crea Un Nuevo QStandardItem con el nombre del archivo
            QStandardItem *item = new QStandardItem(fileInfo.fileName());
            item->setData(fileInfo.filePath(), Qt::UserRole);
            model->appendRow(item);
        }

        //Selecciona el primer archivo (automatico)
        if (!files.isEmpty()) {
            currentSongIndex = 0;  // Inicializar el índice

            QVideoWidget* video = new QVideoWidget();
            video->setGeometry(
                5, 5,
                ui->groupBox_Video->width() - 10,
                ui->groupBox_Video->height() - 10
                );
            video->setParent(ui->groupBox_Video);

            Player->setVideoOutput(video);
            Player->setSource(QUrl::fromLocalFile(files.first().filePath()));
            Player->play();  // Comenzar reproducción

            video->setVisible(true);
            video->show();
        }
    }
}
void MainWindow::on_actionAddFile_triggered() //Agregar Archivos a la Biblioteca
{
    QStringList fileNames = QFileDialog::getOpenFileNames(
        this,
        tr("Seleccionar archivos de video"),
        "",
        tr("Archivos multimedia (*.mp4 *.mp3 *.avi *.mkv)")
        );

    foreach(const QString &fileName, fileNames) { //Itera sobre cada objeto (Informacion, nombre, ruta)
        QFileInfo fileInfo(fileName);
        QStandardItem *item = new QStandardItem(fileInfo.fileName());
        item->setData(fileName, Qt::UserRole);
        model->appendRow(item);
    }

    if (!fileNames.isEmpty()) { //Verificacion de archivos
        QVideoWidget* video = new QVideoWidget();
        video->setGeometry(
            5, 5,
            ui->groupBox_Video->width() - 10,
            ui->groupBox_Video->height() - 10
            );
        video->setParent(ui->groupBox_Video);

        Player->setVideoOutput(video);
        Player->setSource(QUrl::fromLocalFile(fileNames.first()));

        video->setVisible(true);
        video->show();
    }
}

void MainWindow::playNextSong()//Siguiente cancion
{
    qDebug() << "Intentando reproducir siguiente canción"; //Ayuda a rastrear el flujo de ejecucion y el estado de la variable
    qDebug() << "Índice actual:" << currentSongIndex;

    // Si no hay canciones en la lista (comprueba si hay canciones dispobibles)
    if (model->rowCount() == 0) {
        qDebug() << "No hay canciones en la lista";
        return;
    }

    // Incrementar el índice PARA APUNTAR A LA SIGUIENTE CANCION
    currentSongIndex++;
    if (currentSongIndex >= model->rowCount()) {
        currentSongIndex = 0;  // Volver al principio si llegamos al final
    }

    QModelIndex nextIndex = model->index(currentSongIndex, 0); //Comprovar y validar siguiente cancion
    if (nextIndex.isValid()) {
        QString filePath = model->itemFromIndex(nextIndex)->data(Qt::UserRole).toString();
        qDebug() << "Reproduciendo:" << filePath;

        // Actualizar la selección visual en el TreeView REFLEJAR EN LA BIBLIOTECA
        ui->treeView->setCurrentIndex(nextIndex);

        Player->setSource(QUrl::fromLocalFile(filePath));
        Player->play();
    }
}

void MainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status) //Manejo De Cambios En EL Estado Del Medio
{
    qDebug() << "Estado del reproductor cambiado:" << status;  // Indicar el estado del reproductor de medios

    if (status == QMediaPlayer::EndOfMedia) { // llego al final del estado que se esta reproduciendo
        qDebug() << "Final de la canción detectado";  // Si detecta que la funcion llega a su final DEPURA
        playNextSong();
    }
}
//hasta aqui xd


void MainWindow::durationChanged(qint64 duration)
{
    mDuration = duration / 1000;
    ui->progressBar->setMaximum(mDuration);
}

void MainWindow::positionChanged(qint64 duration)
{
    if (!ui->progressBar->isSliderDown())
    {
        ui->progressBar->setValue(duration / 1000);
    }
    updateDuration(duration / 1000);
}

void MainWindow::updateDuration(qint64 Duration)
{
    QTime CurrentTime((Duration / 3600) % 60, (Duration / 60) % 60, Duration % 60);
    QTime TotalTime((mDuration / 3600) % 60, (mDuration / 60) % 60, mDuration % 60);

    QString Format = (mDuration > 3600) ? "hh:mm:ss" : "mm:ss";
    ui->label_time->setText(CurrentTime.toString(Format) + " / " + TotalTime.toString(Format));
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
