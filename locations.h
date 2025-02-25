#ifndef LOCATIONS_H
#define LOCATIONS_H

#include <QObject>
#include <QGeoCoordinate>

class Locations {
private:

    QString m_city;
    QString m_state;
    QString m_country;
    float m_latitude;
    float m_longitude;
    QGeoCoordinate m_coordinates;

public:
    /**
     * @brief Locations Default constructor
     */
    Locations() = default;

    /**
     * @brief Locations Custom constructor.
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
     * @brief Locations Custom constructor.
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
              const float latitude,
              const float longitude);
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
    float getCityLatitude();

    /**
     * @brief getCityLongitude
     * @return
     */
    float getCityLongitude();

    /**
     * @brief getCityCoordinates
     * @return
     */
    QGeoCoordinate getCityCoordinates();

    /**
     * @brief reset Resets all the location fields.
     */
    void reset();
};

#endif // LOCATIONS_H
