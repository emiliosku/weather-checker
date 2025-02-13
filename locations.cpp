#include "locations.h"

Locations::Locations(const QString &city,
                     const QString &state,
                     const QString &country,
                     const QString &latitude,
                     const QString &longitude)
    : m_city{city},
      m_state{state},
      m_country{country},
      m_latitude{latitude},
      m_longitude{longitude} {
    m_coordinates.setLatitude(m_latitude.toFloat());
    m_coordinates.setLongitude(m_longitude.toFloat());
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

QString Locations::getCityLatitude() {
    return m_latitude;
}

QString Locations::getCityLongitude() {
    return m_longitude;
}

QGeoCoordinate Locations::getCityCoordinates() {
    return m_coordinates;
}
