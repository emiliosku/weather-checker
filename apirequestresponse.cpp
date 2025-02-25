#include "apirequestresponse.h"

APIRequestResponse::APIRequestResponse(QObject *parent)
    : QObject{parent},
    m_networkManager{new QNetworkAccessManager(this)} {
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &APIRequestResponse::onRequestFinished);
}

APIRequestResponse::~APIRequestResponse() {
    delete m_networkManager;
}

void APIRequestResponse::sendGetRequest(const QString &url) {
    QNetworkRequest request{QUrl(url)};
    m_networkManager->get(request);
}

void APIRequestResponse::sendPostRequest(const QString &url, const QJsonObject &payload)
{
    QNetworkRequest request{QUrl(url)};

    QJsonDocument doc(payload);
    QByteArray data = doc.toJson();

    m_networkManager->post(request, data);
}

void APIRequestResponse::onRequestFinished(QNetworkReply *reply)
{
    QJsonObject jsonResponse = parseResponse(reply);
    emit requestCompleted(jsonResponse);
    reply->deleteLater();
}

QJsonObject APIRequestResponse::parseResponse(QNetworkReply *reply)
{
    QJsonObject jsonResponse;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();

        QJsonParseError jsonError{QJsonParseError::NoError};
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData, &jsonError);

        if (jsonDoc.isNull()) {
            qDebug() << "JSON Parse Error:" << jsonError.errorString();
            jsonResponse["error"] = "Invalid JSON received: " + jsonError.errorString();
        }
        else if (jsonDoc.isObject()) {
            jsonResponse = jsonDoc.object();
        }
        else if (jsonDoc.isArray()) {
            jsonResponse.insert("data", jsonDoc.array());
        }
        else {
            jsonResponse["error"] = "Invalid JSON format received";
        }
    } else {
        jsonResponse["error"] = reply->errorString();
        jsonResponse["status_code"] = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    }

    return jsonResponse;
}
