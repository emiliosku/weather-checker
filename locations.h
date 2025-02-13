#ifndef LOCATIONS_H
#define LOCATIONS_H

#include <QObject>
#include <QGeoCoordinate>

class Locations {
private:

    QString m_city;
    QString m_state;
    QString m_country;
    QString m_latitude;
    QString m_longitude;
    QGeoCoordinate m_coordinates;

public:
    /**
     * @brief Locations Private constructor.
     *
     * @param city City name.
     * @param state Province or state name.
     * @param country Country name.
     * @param latitude City latitude.
     * @param longitude City longitude.
     */
    Locations(const QString &city,
              const QString &state,
              const QString &country,
              const QString &latitude,
              const QString &longitude);
    /**
     * @brief getCityName
     * @return
     */
    QString getCityName();

    /**
     * @brief getStateName
     * @return
     */
    QString getStateName();

    /**
     * @brief getCountryName
     * @return
     */
    QString getCountryName();

    /**
     * @brief getCityLatitude
     * @return
     */
    QString getCityLatitude();

    /**
     * @brief getCityLongitude
     * @return
     */
    QString getCityLongitude();

    /**
     * @brief getCityCoordinates
     * @return
     */
    QGeoCoordinate getCityCoordinates();
};

#endif // LOCATIONS_H
