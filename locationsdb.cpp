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
        )
    )";

    if (!query.exec(createTable)) {
        qCritical() << "Failed to create table:" << query.lastError().text();
    }
}

bool LocationsDB::addLocation(const Locations location) {
    bool success{true};
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
    return success;
}

QVector<Locations> LocationsDB::getAllLocations() {
    QVector<Locations> locations;
    QSqlQuery query("SELECT * FROM locations");

    while (query.next()) {
        Locations loc{query.value("city").toString(),
                      query.value("state").toString(),
                      query.value("country").toString(),
                      query.value("latitude").toDouble(),
                      query.value("longitude").toDouble()};
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
        loc(query.value("city").toString(),
            query.value("state").toString(),
            query.value("country").toString(),
            query.value("latitude").toDouble(),
            query.value("longitude").toDouble());
    }
    return loc;
}

bool LocationsDB::updateLocation(int id, Locations location) {
    Q_UNUSED(location);
    return true;
}

bool LocationsDB::deleteLocation(int id) {
    Q_UNUSED(id);
    return true;
}
