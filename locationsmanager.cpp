#include "locationsmanager.h"

LocationsManager::LocationsManager(QObject *parent)
    : QObject{parent},
    m_apiClient{},
    m_location{},
    m_database{}{

}

void LocationsManager::sendLocationMetadataRequestFromApi(const QString &location) {
    emit waitingForLocationUpdate();
    // Connect requestCompleted signal from API to this class handle.
    QObject::connect(
        &m_apiClient, &APIRequestResponse::requestCompleted,
        this, &LocationsManager::handleLocationMetadataResponseFromApi,
        Qt::AutoConnection
        );
    m_apiClient.sendGetRequest(getLocationQuery(location));
}

bool LocationsManager::getIsLocationAlreadyInDatabase(Locations &location) {
    return m_database.cityExists(location);
}

bool LocationsManager::addCurrentLocationToDatabase() {
    const bool success = m_database.addLocation(m_location);
    if (success) {
        emit databaseUpdated();
    }
    return success;
}

bool LocationsManager::deleteCurrentLocationFromDatabase() {
    const bool success = m_database.deleteLocation(m_location);
    if (success) {
        emit databaseUpdated();
    }
    return success;
}

QVector<Locations> LocationsManager::getAllLocationsFromDatabase() {
    return m_database.getAllLocations();
}

Locations LocationsManager::getLocationFromDatabase(int locationId) {
    return m_database.getLocationById(locationId);
}

void LocationsManager::setCurrentLocationFromDatabase(int locationId) {
    m_location = m_database.getLocationById(locationId);
    emit locationUpdated(m_location);
}

QString LocationsManager::getLocationQuery(const QString &locationName) {
    return QString("https://nominatim.openstreetmap.org/search?q=%1&format=json&addressdetails=1").arg(locationName);
}

bool LocationsManager::handleLocationMetadataResponseFromApi(const QJsonObject &response) {
    bool success = true;
    // Disconnect requestCompleted signal from API from this class handle.
    QObject::disconnect(
        &m_apiClient, &APIRequestResponse::requestCompleted,
        this, &LocationsManager::handleLocationMetadataResponseFromApi
    );
    QJsonArray jsonArray = response.value("data").toArray();
    if (!jsonArray.isEmpty()) {
        QJsonObject firstResult = jsonArray.first().toObject();
        QJsonObject addressObject = firstResult.value("address").toObject();

        m_location = Locations(
            firstResult.value("name").toString(),
            addressObject.value("state").toString(),
            addressObject.value("country").toString(),
            firstResult.value("lat").toString(),
            firstResult.value("lon").toString()
        );
    }
    else {
        success = false;
        m_location.reset();
        qDebug() << "No results found.";
    }
    emit locationUpdated(m_location);

    return success;
}
