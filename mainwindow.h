#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include <QTreeView>
#include <QStandardItemModel>

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
    void durationChanged(qint64 duration);
    void positionChanged(qint64 duration);
    void on_pushButton_pausar_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_pushButton_retroceder_clicked();
    void on_pushButton_mute_clicked();
    void on_verticalSlider_valueChanged(int value);
    void on_pushButton_stop_clicked();
    void on_pushButton_adelantar_clicked();

    void on_actionOpen_triggered();
    void on_actionAddFile_triggered();

    //Biblioteca
    void on_treeView_clicked(const QModelIndex &index); // Nuevo slot para manejar clicks
    //Implemetaciones
    void showTreeViewContextMenu(const QPoint &pos);
    void removeSelectedVideo();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *Player;
    QVideoWidget *Video; // Este widget debería ser inicializado y usado en la implementación
    qint64 mDuration;
    bool IS_Pause = true;
    bool IS_Muted = false;
    //Biblioteca
    QStandardItemModel *model; // Modelo para el TreeView
    void setupTreeView(); // Función para configurar el TreeView
    //Hasta aqui
    void updateDuration(qint64 Duration);
};

#endif // MAINWINDOW_H
