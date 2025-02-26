#ifndef LOCATIONSMANAGER_H
#define LOCATIONSMANAGER_H

#include <QObject>
#include <QDebug>

#include "locations.h"
#include "apirequestresponse.h"
#include "locationsdb.h"


class LocationsManager : public QObject {
private:
    Q_OBJECT

    /**
     * @brief m_apiClient Object to handle API requests and responses.
     */
    APIRequestResponse m_apiClient;

    /**
     * @brief m_location Stores the current location.
     */
    Locations m_location;

    /**
     * @brief m_database Object to handle database access.
     */
    LocationsDB m_database;


public:
    /**
     * @brief LocationsManager Constructor for the LocationsManager class.
     * @param parent The parent QObject (if any).
     */
    explicit LocationsManager(QObject *parent = nullptr);

    /**
     * @brief sendLocationMetadataRequestFromApi Sends a GET API request to get a location coordinates and other metadata.
     * @param location Location to get information from.
     */
    void sendLocationMetadataRequestFromApi(const QString &location);

    /**
     * @brief getIsLocationAlreadyInDatabase Check whether a location is already storedon the database.
     * @param location Location object containing all metadata.
     * @return If location is on the database, true; otherwise, false.
     */
    bool getIsLocationAlreadyInDatabase(Locations &location);

    /**
     * @brief addCurrentLocationToDatabase Adds the currently selected location to the database.
     * @return If operation successful, true; otherwise, false.
     */
    bool addCurrentLocationToDatabase();

    /**
     * @brief deleteCurrentLocationFromDatabase Deletes the currently selected location from the database.
     * @return If operation successful, true; otherwise, false.
     */
    bool deleteCurrentLocationFromDatabase();

    /**
     * @brief getAllLocationsFromDatabase Get all locations from the database.
     * @return All the locations from the database.
     */
    QVector<Locations> getAllLocationsFromDatabase();

    /**
     * @brief getLocationFromDatabase Gets the location for the requested database ID.
     * @param locationId The ID of the location position on the database.
     * @return The location object corresponding to the database ID.
     */
    Locations getLocationFromDatabase(int locationId);

    /**
     * @brief setCurrentLocationFromDatabase Sets the current location from the database ID.
     * @param locationId The ID of the location position on the database.
     */
    void setCurrentLocationFromDatabase(int locationId);

public slots:
    /**
     * @brief handleLocationMetadataResponseFromApi Parse the raw information received from the API.
     * @param response The raw location metadata from the API.
     * @return If the parsing was correct, true; otherwise, false.
     */
    bool handleLocationMetadataResponseFromApi(const QJsonObject &response);

private:

    /**
     * @brief getLocationQuery Get the Nominatim API url modified with the location to query.
     * @param locationName Location to get information from.
     * @return The URL to the Nominatim API.
     */
    QString getLocationQuery(const QString &locationName);

signals:
    /**
     * @brief waitingForLocationUpdate Emitted when an API request has been sent.
     */
    void waitingForLocationUpdate();

    /**
     * @brief locationUpdated Emitted when the current location has changed.
     * @param location Location object containing all metadata.
     */
    void locationUpdated(Locations &location);

    /**
     * @brief databaseUpdated Emitted when there's been a change on the database.
     */
    void databaseUpdated();
};

#endif // LOCATIONSMANAGER_H
