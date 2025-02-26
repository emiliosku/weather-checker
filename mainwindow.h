#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "locationsmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
private:
    Q_OBJECT

    /**
     * @brief m_view
     */
    Ui::MainWindow *m_view;

    /**
     * @brief m_locationsManager
     */
    LocationsManager m_locationsManager;

public:
    // Class constructor and destructor
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief getLocationFieldText
     * @return
     */
    QString getLocationFieldText() const;

private:
    /**
     * @brief joinCityAddress
     * @param location
     * @return
     */
    QString joinCityAddress(Locations &location) const;

private slots:
    /**
     * @brief on_pb_sendLocationQuery_clicked
     */
    void on_pb_sendLocationQuery_clicked();

    /**
     * @brief setLabelText
     * @param location
     */
    void setLabelText(Locations &location);

    /**
     * @brief setLocationDatabaseButtonsVisibility
     * @param location
     */
    void setLocationDatabaseButtonsVisibility(Locations &location);

    /**
     * @brief updateDatabaseLocationsList
     */
    void updateDatabaseLocationsList();

    /**
     * @brief clearSearchItems
     */
    void clearSearchItems();

    /**
     * @brief on_pb_addToDb_clicked
     */
    void on_pb_addToDb_clicked();

    /**
     * @brief on_pb_removeFromDb_clicked
     */
    void on_pb_removeFromDb_clicked();

    /**
     * @brief on_l_database_doubleClicked
     * @param index
     */
    void on_l_database_doubleClicked(const QModelIndex &index);
};
#endif // MAINWINDOW_H
