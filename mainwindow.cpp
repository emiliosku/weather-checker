#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    m_view(new Ui::MainWindow),
    m_locationsManager{} {
    m_view->setupUi(this);

    // Set buttons as invisible at the beginning.
    m_view->pb_addToDb->setVisible(false);
    m_view->pb_removeFromDb->setVisible(false);

    QObject::connect(
        &m_locationsManager, &LocationsManager::locationUpdated,
        this, &MainWindow::setLabelText, Qt::AutoConnection
    );
    QObject::connect(
        &m_locationsManager, &LocationsManager::locationUpdated,
        this, &MainWindow::setLocationDatabaseButtonsVisibility,
        Qt::AutoConnection
    );

    // // Loading screen signaling.
    // QObject::connect(
    //     &m_locationsManager, &LocationsManager::waitingForLocationUpdate,
    //     &m_loadingScreenView, &LoadingScreen::show,
    //     Qt::AutoConnection
    // );
    // QObject::connect(
    //     &m_locationsManager, &LocationsManager::locationUpdated,
    //     &m_loadingScreenView, &LoadingScreen::hide,
    //     Qt::AutoConnection
    // );

}

MainWindow::~MainWindow()
{
    delete m_view;
}

QString MainWindow::getLocationFieldText() const {
    return QString(m_view->le_locationText->text());
}


void MainWindow::on_pb_sendLocationQuery_clicked() {
    m_locationsManager.sendLocationMetadataRequestFromApi(getLocationFieldText());
}

void MainWindow::setLabelText(Locations &location) {
    m_view->lbl_queryOutput->setText(
        QString(location.getCityName() + ", " +
                location.getStateName() + ", " +
                location.getCountryName()
        )
    );
}

void MainWindow::setLocationDatabaseButtonsVisibility(Locations &location) {
    if (m_locationsManager.getIsLocationAlreadyInDatabase(location)) {
        m_view->pb_addToDb->setVisible(false);
        m_view->pb_removeFromDb->setVisible(true);
    }
    else {
        m_view->pb_addToDb->setVisible(true);
        m_view->pb_removeFromDb->setVisible(false);
    }
}

void MainWindow::on_pb_addToDb_clicked() {
    m_locationsManager.addCurrentLocationToDatabase();
}


void MainWindow::on_pb_removeFromDb_clicked(){
    m_locationsManager.deleteCurrentLocationFromDatabase();
}

