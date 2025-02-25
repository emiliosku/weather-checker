#ifndef WEATHERMANAGER_H
#define WEATHERMANAGER_H

// Includes
#include <QDateTime>
#include <QDebug>

#include "locations.h"

class WeatherManager : public QObject {
private:
    Q_OBJECT

    // Private objects that will only be used within this class.

    /**
     * @brief m_currentTemperature Saves the current temperature retrieved from OpenMeteo.
     */
    float m_currentTemperature;

    /**
     * @brief m_currentTemperatureFeeling Saves the current temperature feeling retrieved from OpenMeteo.
     */
    float m_currentTemperatureFeeling;

    /**
     * @brief m_umbrella States if the umbrella is necessary or not for the day.
     */
    bool m_umbrella;



public:
    // Class constructor and destructor
    explicit WeatherManager(QObject *parent = nullptr);
    // ~WeatherManager();

    /**
     * @brief getCurrentTemperature
     * @return
     */
    float getCurrentTemperature() const;

    /**
     * @brief getCurrentTemperatureFeeling
     * @return
     */
    float getCurrentTemperatureFeeling() const;

    /**
     * @brief isUmbrellaNecessary
     * @return
     */
    bool isUmbrellaNecessary() const;


private:
    /**
     * @brief parseOpenMeteoResponse
     * @param apiReply
     * @return
     */
    bool parseOpenMeteoResponse(QJsonObject jsonResponse);

    /**
     * @brief setCurrentTemperature
     * @param currentTemp
     */
    void setCurrentTemperature(float currentTemp);

    /**
     * @brief setCurrentTemperatureFeeling
     * @param currentTempFeel
     */
    void setCurrentTemperatureFeeling(float currentTempFeel);

    /**
     * @brief setIsUmbrellaNecessary
     * @param isUmbrellaNecessary
     */
    void setIsUmbrellaNecessary(bool isUmbrellaNecessary);


public slots:
    // Public slots


signals:

};

#endif // WEATHERMANAGER_H
