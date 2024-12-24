// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2
import QT

Window {
    width: Screen.width / 2
    height: Screen.height / 2

    visible: true
    title: "Hello"

    Text {
        id: hello
        text: qsTr("Hello world")
        color: "red"
    }

}

