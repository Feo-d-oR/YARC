/*
Name: QtRpt
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

#ifndef QTRPTNAMESPACE_H
#define QTRPTNAMESPACE_H
#include <QObject>
#include <QMetaType>

namespace QtRptName {
    enum BandType {
        Undefined,
        ReportTitle,
        PageHeader,
        DataGroupHeader,
        MasterHeader,
        MasterData,
        MasterFooter,
        DataGroupFooter,
        ReportSummary,
        PageFooter
    };

    enum FieldType {
        Text,
        TextImage,
        TextRich,
        Image,
        Diagram,
        Reactangle,
        RoundedReactangle,
        Circle,
        Triangle,
        Rhombus,
        Line,
        Barcode,
        DatabaseImage,
        CrossTab
    };

    enum BorderStyle {
        Dashed,
        Dot_dash,
        Dot_dot_dash,
        Dotted,
        Double,
        Groove,
        Inset,
        Outset,
        Ridge,
        Solid,
        BorderNone
    };

    enum Command {
        None,
        Name,
        Bold,
        Italic,
        Underline,
        Strikeout,
        Font,
        FontSize,
        FontColor,
        FontName,
        Frame,
        FrameLeft,
        FrameRight,
        FrameTop,
        FrameBottom,
        FrameNo,
        FrameAll,
        FrameStyle,
        FrameWidth,
        AligmentH,
        AligmentV,
        Left,
        Top,
        Width,
        Height,
        Length,
        BackgroundColor,
        BorderColor,
        Printing,
        StartNewNumeration,
        ShowInGroup,
        StartNewPage,
        AutoHeight,
        ArrowStart,
        ArrowEnd,
        IgnoreRatioAspect,
        BarcodeType,
        BarcodeFrameType,
        TextWrap
    };
}

Q_DECLARE_METATYPE(QtRptName::FieldType)



//Q_ENUMS(QtRptName::FieldType)
//qRegisterMetaType<QtRptName::FieldType>( "FieldType" );
//qRegisterMetaTypeStreamOperators()

#endif // QTRPTNAMESPACE_H


