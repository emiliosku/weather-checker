#include "locations.h"

Locations::Locations(const QString &city,
                     const QString &state,
                     const QString &country,
                     const QString &latitude,
                     const QString &longitude)
    : m_city{city},
      m_state{state},
      m_country{country},
      m_latitude{latitude.toFloat()},
      m_longitude{longitude.toFloat()} {
    m_coordinates.setLatitude(m_latitude);
    m_coordinates.setLongitude(m_longitude);
}

Locations::Locations(const QString &city,
                     const QString &state,
                     const QString &country,
                     const float latitude,
                     const float longitude)
    : m_city{city},
    m_state{state},
    m_country{country},
    m_latitude{latitude},
    m_longitude{longitude} {
    m_coordinates.setLatitude(m_latitude);
    m_coordinates.setLongitude(m_longitude);
}

QString Locations::getCityName() {
    return m_city;
}

QString Locations::getStateName() {
    return m_state;
}

QString Locations::getCountryName() {
    return m_country;
}

float Locations::getCityLatitude() {
    return m_latitude;
}

float Locations::getCityLongitude() {
    return m_longitude;
}

QGeoCoordinate Locations::getCityCoordinates() {
    return m_coordinates;
}

void Locations::reset() {
    m_city = "";
    m_state = "";
    m_country = "";
    m_latitude = 0.0;
    m_longitude = 0.0;
    m_coordinates = QGeoCoordinate(0.0,0.0);
}
