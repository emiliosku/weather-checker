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

    bool addLocation(const Locations location);
    QVector<Locations> getAllLocations();
    Locations getLocationById(int id);
    bool updateLocation(int id, Locations location);
    bool deleteLocation(int id);

signals:
};

#endif // LOCATIONSDB_H
