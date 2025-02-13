#include "locationsdb.h"

LocationsDB::LocationsDB(QObject *parent)
    : QObject{parent} {
    m_locationsDatabase = QSqlDatabase::addDatabase("QSQLITE");
    m_locationsDatabase.setDatabaseName("locations.db");

    if (!m_locationsDatabase.open()) {
        qCritical() << "Error opening database:" << m_locationsDatabase.lastError().text();
    }
    else {
        initialiseDatabase();
    }
}

LocationsDB::~LocationsDB() {
    if (m_locationsDatabase.isOpen()) {
        m_locationsDatabase.close();
    }
}

void LocationsDB::initialiseDatabase() {
    QSqlQuery query;
    QString createTable = R"(
        CREATE TABLE IF NOT EXISTS locations (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            city TEXT NOT NULL,
            state TEXT NOT NULL,
            country TEXT NOT NULL,
            latitude REAL NOT NULL,
            longitude REAL NOT NULL
            UNIQUE(city, state, country)
        )
    )";

    if (!query.exec(createTable)) {
        qCritical() << "Failed to create table:" << query.lastError().text();
    }
}

bool LocationsDB::addLocation(Locations &location) {
    bool success{true};
    if (cityExists(location)) {
        qInfo() << "Location already saved on DB.";
    } else {
        QSqlQuery query;
        query.prepare("INSERT INTO locations (city, state, country, latitude, longitude) VALUES (?, ?, ?, ?, ?)");
        query.addBindValue(location.getCityName());
        query.addBindValue(location.getStateName());
        query.addBindValue(location.getCountryName());
        query.addBindValue(location.getCityCoordinates().latitude());
        query.addBindValue(location.getCityCoordinates().longitude());

        if (!query.exec()) {
            qCritical() << "Insert failed:" << query.lastError().text();
            success = false;
        }
    }
    return success;
}

QVector<Locations> LocationsDB::getAllLocations() {
    QVector<Locations> locations;
    QSqlQuery query("SELECT * FROM locations");

    while (query.next()) {
        Locations loc(query.value("city").toString(),
                      query.value("state").toString(),
                      query.value("country").toString(),
                      query.value("latitude").toDouble(),
                      query.value("longitude").toDouble());
        locations.append(loc);
    }
    return locations;
}

Locations LocationsDB::getLocationById(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM locations WHERE id = ?");
    query.addBindValue(id);

    Locations loc;
    if (query.exec() && query.next()) {
        loc = Locations(query.value("city").toString(),
                        query.value("state").toString(),
                        query.value("country").toString(),
                        query.value("latitude").toDouble(),
                        query.value("longitude").toDouble());
    }
    return loc;
}

bool LocationsDB::deleteLocation(Locations &location) {
    bool success{true};
    int id{getLocationId(location)};
    if (id > 0) {
        QSqlQuery query;
        query.prepare("DELETE FROM locations WHERE id = ?");
        query.addBindValue(id);

        if (!query.exec()) {
            qCritical() << "Delete failed:" << query.lastError().text();
            success = false;
        }
    }
    return success;
}

bool LocationsDB::cityExists(Locations &location) {
    bool exists{false};
    if (getLocationId(location) > 0) {
        exists = true;
    }
    return exists;
}
int LocationsDB::getLocationId(Locations &location) {
    int id{-1};
    QSqlQuery query;
    query.prepare("SELECT id FROM locations WHERE city = ? AND state = ? AND country = ?");
    query.addBindValue(location.getCityName());
    query.addBindValue(location.getStateName());
    query.addBindValue(location.getCountryName());

    if (query.exec() && query.next()) {
        id = query.value(0).toInt();  // Return found ID
    }
    return id;
}
