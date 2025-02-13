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

    QSqlDatabase m_locationsDatabase;

    void initialiseDatabase();

public:
    explicit LocationsDB(QObject *parent = nullptr);
    ~LocationsDB();

    bool addLocation(Locations &location);
    QVector<Locations> getAllLocations();
    Locations getLocationById(int id);
    bool deleteLocation(Locations &location);
    bool cityExists(Locations &location);
    int getLocationId(Locations &location);

};

#endif // LOCATIONSDB_H
