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
     * @brief m_apiClient
     */
    APIRequestResponse m_apiClient;

    /**
     * @brief m_location
     */
    Locations m_location;

    /**
     * @brief m_database
     */
    LocationsDB m_database;


public:
    // Class constructor
    explicit LocationsManager(QObject *parent = nullptr);

    /**
     * @brief sendLocationMetadataRequestFromApi
     * @param location
     */
    void sendLocationMetadataRequestFromApi(const QString &location);

    /**
     * @brief getIsLocationAlreadyInDatabase
     * @param location
     * @return
     */
    bool getIsLocationAlreadyInDatabase(Locations &location);

    /**
     * @brief addCurrentLocationToDatabase
     * @return
     */
    bool addCurrentLocationToDatabase();

    /**
     * @brief deleteCurrentLocationFromDatabase
     * @return
     */
    bool deleteCurrentLocationFromDatabase();

public slots:
    /**
     * @brief handleLocationMetadataResponseFromApi
     * @param response
     * @return
     */
    bool handleLocationMetadataResponseFromApi(const QJsonObject &response);

private:

    /**
     * @brief getLocationQuery
     * @param locationName
     * @return
     */
    QString getLocationQuery(const QString &locationName);

    // Locations getLocationFromDatabase(int locationId);

    // QVector<Locations> getAllLocationsFromDatabase();

signals:
    /**
     * @brief waitingForLocationUpdate
     */
    void waitingForLocationUpdate();

    /**
     * @brief locationUpdated
     * @param location
     */
    void locationUpdated(Locations &location);
};

#endif // LOCATIONSMANAGER_H
