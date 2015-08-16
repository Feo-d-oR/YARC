/*
Name: QXYZ
Version: 1.5.3
Web-site: http://www.qtrpt.tk
Programmer: Aleksey Osipov
E-mail: aliks-os@ukr.net
Web-site: http://www.aliks-os.tk

Copyright 2012-2015 Aleksey Osipov

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

#include "Qxyz_Label.h"

QxyzLabel::QxyzLabel(QWidget *parent) : QLabel(parent) {
    m_bHover = false;
    setCursor(Qt::PointingHandCursor);
}

QxyzLabel::QxyzLabel(const QString &Text, QWidget *parent) : QLabel(Text, parent) {
    m_bHover = false;
    setCursor(Qt::PointingHandCursor);
}

QxyzLabel::~QxyzLabel() {
}

void QxyzLabel::setHoverText(bool bHover) {
    m_bHover = bHover;
}

void QxyzLabel::enterEvent(QEvent *) {
    if( m_bHover ) {
        QFont font = this->font();
        font.setUnderline(m_bHover);
        setFont(font);
    }
}

void QxyzLabel::leaveEvent(QEvent *) {
    if( m_bHover ) {
        QFont font = this->font();
        font.setUnderline(false);
        setFont(font);
    }
}

void QxyzLabel::mouseReleaseEvent(QMouseEvent *) {
    emit clicked();
}
