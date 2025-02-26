#ifndef LOCATIONSDB_H
#define LOCATIONSDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "locations.h"


class LocationsDB : public QObject {
private:
    Q_OBJECT

    /**
     * @brief m_locationsDatabase Object used to handle the SQLite database.
     */
    QSqlDatabase m_locationsDatabase;

    /**
     * @brief initialiseDatabase Function that initialises the database.
     */
    void initialiseDatabase();

    /**
     * @brief reorderDatabase
     * @return
     */
    bool reorderDatabase();

public:
    // Class constructor and destructor
    explicit LocationsDB(QObject *parent = nullptr);
    ~LocationsDB();

    /**
     * @brief addLocation Adds a location to the database.
     * @param location The location to be added.
     * @return If added correctly true; otherwise, false.
     */
    bool addLocation(Locations &location);

    /**
     * @brief getAllLocations Retrieves all the locations within the database.
     * @return A list of all the locations on the database.
     */
    QVector<Locations> getAllLocations();

    /**
     * @brief getLocationById Gets a specific location through its database ID.
     * @param id The ID associated to a Location.
     * @return The location with the desired ID.
     */
    Locations getLocationById(int id);

    /**
     * @brief deleteLocation Deletes a specific location from the database.
     * @param location Location to delete from the database.
     * @return If deleted correctly true; otherwise, false.
     */
    bool deleteLocation(Locations &location);

    /**
     * @brief cityExists Checks whether a city is in the database or not.
     * @param location Location to check
     * @return If present in database true; otherwise, false.
     */
    bool cityExists(Locations &location);

    /**
     * @brief getLocationId Retrieve the Location ID by using the location itself.
     * @param location Location from which we want the ID.
     * @return The location ID.
     */
    int getLocationId(Locations &location);

};

#endif // LOCATIONSDB_H
