/*
Name: QtRptConnection
Version: 2.0.0
Web-site: http://www.qtrpt.tk
Programmer: Aleksey Osipov
E-mail: aliks-os@ukr.net
Web-site: http://www.aliks-os.tk

Copyright 2012-2016 Aleksey Osipov

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef RPTSQLCONNECTION_H
#define RPTSQLCONNECTION_H

#include <QString>

class RptSqlConnection
{
public:
    RptSqlConnection();
    explicit RptSqlConnection(QString dsName, QString dbType, QString dbName, QString dbHost, QString dbUser, QString dbPassword, int dbPort, QString dbConnectionName, QString sqlQuery, QString dbCoding, QString charsetCoding);

    void reset();

    RptSqlConnection &operator=(const RptSqlConnection & other);
    RptSqlConnection(const RptSqlConnection &) = default;

public:
    bool m_bIsActive;
    QString m_dsName;
    QString m_dbType;
    QString m_dbName;
    QString m_dbHost;
    QString m_dbUser;
    QString m_dbPassword;
    int m_dbPort;
    QString m_dbConnectionName;
    QString m_sqlQuery;
    QString m_dbCoding;
    QString m_charsetCoding;
};

#endif // RPTSQLCONNECTION_H
