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

    // Update database list at start of the application.
    updateDatabaseLocationsList();

    // Update display name for the searched city.
    QObject::connect(
        &m_locationsManager, &LocationsManager::locationUpdated,
        this, &MainWindow::setLabelText, Qt::AutoConnection
    );

    // Update buttons visibility according to presence in database.
    QObject::connect(
        &m_locationsManager, &LocationsManager::locationUpdated,
        this, &MainWindow::setLocationDatabaseButtonsVisibility,
        Qt::AutoConnection
    );

    // Update database display list when an update is made.
    QObject::connect(
        &m_locationsManager, &LocationsManager::databaseUpdated,
        this, &MainWindow::updateDatabaseLocationsList,
        Qt::AutoConnection
    );
    QObject::connect(
        &m_locationsManager, &LocationsManager::databaseUpdated,
        this, &MainWindow::clearSearchItems,
        Qt::AutoConnection
    );

    // TODO: To be done when I switch to QML instead of QtDesigner.
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
    if (!location.getCityName().isEmpty()){
        m_view->lbl_queryOutput->setText(joinCityAddress(location));
    }
    else {
        m_view->lbl_queryOutput->setText("No results found for your query.");
    }
}

void MainWindow::setLocationDatabaseButtonsVisibility(Locations &location) {
    if (!location.getCityName().isEmpty()) {
        if (m_locationsManager.getIsLocationAlreadyInDatabase(location)) {
            m_view->pb_addToDb->setVisible(false);
            m_view->pb_removeFromDb->setVisible(true);
        }
        else {
            m_view->pb_addToDb->setVisible(true);
            m_view->pb_removeFromDb->setVisible(false);
        }
    }
    else {
        m_view->pb_addToDb->setVisible(false);
        m_view->pb_removeFromDb->setVisible(false);
    }
}

void MainWindow::updateDatabaseLocationsList() {
    QVector<Locations> allLocations = m_locationsManager.getAllLocationsFromDatabase();
    m_view->l_database->clear();
    for (Locations loc : std::as_const(allLocations)) {
        m_view->l_database->addItem(joinCityAddress(loc));
    }
}

void MainWindow::clearSearchItems() {
    m_view->pb_addToDb->setVisible(false);
    m_view->pb_removeFromDb->setVisible(false);
    m_view->le_locationText->clear();
    m_view->lbl_queryOutput->clear();
}

QString MainWindow::joinCityAddress(Locations &location) const {
    return QString(
        location.getCityName() + ", " +
        location.getStateName() + ", " +
        location.getCountryName()
    );
}

void MainWindow::on_pb_addToDb_clicked() {
    m_locationsManager.addCurrentLocationToDatabase();
}


void MainWindow::on_pb_removeFromDb_clicked(){
    m_locationsManager.deleteCurrentLocationFromDatabase();
}


void MainWindow::on_l_database_doubleClicked(const QModelIndex &index) {
    m_view->le_locationText->clear();
    m_locationsManager.setCurrentLocationFromDatabase(index.row() + 1);
}

