/********************************************************************************
** Form generated from reading UI file 'glowneokno.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLOWNEOKNO_H
#define UI_GLOWNEOKNO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QDial>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GlowneOkno
{
public:
    QWidget *centralWidget;
    QTextBrowser *textBrowser;
    QLineEdit *lineEdit;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label_1;
    QLabel *label_StanGry;
    QLCDNumber *lcdNumber_nrTury;
    QGroupBox *groupBox_gracze;
    QRadioButton *radioButton_1gracz;
    QRadioButton *radioButton_2graczy;
    QDial *dial_szybkoscGry;
    QDial *dial_zlotoPoczatkowe;
    QLCDNumber *lcdNumber_zlotoPoczatkowe;
    QLCDNumber *lcdNumber_szybkoscGry;
    QLabel *label_3;
    QLabel *label_4;
    QCommandLinkButton *commandLinkButton_akcja;
    QLabel *label_gracz1;
    QLabel *label_gracz2;
    QLabel *label;
    QLineEdit *lineEdit_AdresIP;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GlowneOkno)
    {
        if (GlowneOkno->objectName().isEmpty())
            GlowneOkno->setObjectName(QStringLiteral("GlowneOkno"));
        GlowneOkno->resize(683, 532);
        centralWidget = new QWidget(GlowneOkno);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(20, 300, 651, 141));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 450, 651, 20));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 10, 204, 80));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_1 = new QLabel(gridLayoutWidget);
        label_1->setObjectName(QStringLiteral("label_1"));

        gridLayout->addWidget(label_1, 0, 0, 1, 1);

        label_StanGry = new QLabel(gridLayoutWidget);
        label_StanGry->setObjectName(QStringLiteral("label_StanGry"));

        gridLayout->addWidget(label_StanGry, 0, 1, 1, 1);

        lcdNumber_nrTury = new QLCDNumber(gridLayoutWidget);
        lcdNumber_nrTury->setObjectName(QStringLiteral("lcdNumber_nrTury"));
        lcdNumber_nrTury->setProperty("intValue", QVariant(-1));

        gridLayout->addWidget(lcdNumber_nrTury, 1, 1, 1, 1);

        groupBox_gracze = new QGroupBox(centralWidget);
        groupBox_gracze->setObjectName(QStringLiteral("groupBox_gracze"));
        groupBox_gracze->setGeometry(QRect(250, 10, 121, 80));
        radioButton_1gracz = new QRadioButton(groupBox_gracze);
        radioButton_1gracz->setObjectName(QStringLiteral("radioButton_1gracz"));
        radioButton_1gracz->setGeometry(QRect(10, 20, 82, 17));
        radioButton_2graczy = new QRadioButton(groupBox_gracze);
        radioButton_2graczy->setObjectName(QStringLiteral("radioButton_2graczy"));
        radioButton_2graczy->setGeometry(QRect(10, 50, 82, 17));
        radioButton_2graczy->setChecked(true);
        dial_szybkoscGry = new QDial(centralWidget);
        dial_szybkoscGry->setObjectName(QStringLiteral("dial_szybkoscGry"));
        dial_szybkoscGry->setGeometry(QRect(140, 200, 50, 64));
        dial_szybkoscGry->setMinimum(3);
        dial_szybkoscGry->setMaximum(50);
        dial_szybkoscGry->setValue(30);
        dial_zlotoPoczatkowe = new QDial(centralWidget);
        dial_zlotoPoczatkowe->setObjectName(QStringLiteral("dial_zlotoPoczatkowe"));
        dial_zlotoPoczatkowe->setGeometry(QRect(140, 110, 50, 64));
        dial_zlotoPoczatkowe->setMaximum(10000);
        dial_zlotoPoczatkowe->setSingleStep(50);
        dial_zlotoPoczatkowe->setValue(1000);
        lcdNumber_zlotoPoczatkowe = new QLCDNumber(centralWidget);
        lcdNumber_zlotoPoczatkowe->setObjectName(QStringLiteral("lcdNumber_zlotoPoczatkowe"));
        lcdNumber_zlotoPoczatkowe->setGeometry(QRect(40, 140, 64, 23));
        lcdNumber_zlotoPoczatkowe->setProperty("intValue", QVariant(1000));
        lcdNumber_szybkoscGry = new QLCDNumber(centralWidget);
        lcdNumber_szybkoscGry->setObjectName(QStringLiteral("lcdNumber_szybkoscGry"));
        lcdNumber_szybkoscGry->setGeometry(QRect(40, 220, 64, 23));
        lcdNumber_szybkoscGry->setSmallDecimalPoint(false);
        lcdNumber_szybkoscGry->setProperty("intValue", QVariant(30));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 120, 91, 16));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 200, 81, 16));
        commandLinkButton_akcja = new QCommandLinkButton(centralWidget);
        commandLinkButton_akcja->setObjectName(QStringLiteral("commandLinkButton_akcja"));
        commandLinkButton_akcja->setGeometry(QRect(490, 240, 172, 41));
        label_gracz1 = new QLabel(centralWidget);
        label_gracz1->setObjectName(QStringLiteral("label_gracz1"));
        label_gracz1->setGeometry(QRect(520, 190, 111, 16));
        label_gracz2 = new QLabel(centralWidget);
        label_gracz2->setObjectName(QStringLiteral("label_gracz2"));
        label_gracz2->setGeometry(QRect(520, 210, 111, 16));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(440, 30, 121, 16));
        lineEdit_AdresIP = new QLineEdit(centralWidget);
        lineEdit_AdresIP->setObjectName(QStringLiteral("lineEdit_AdresIP"));
        lineEdit_AdresIP->setGeometry(QRect(440, 60, 161, 20));
        GlowneOkno->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GlowneOkno);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 683, 21));
        GlowneOkno->setMenuBar(menuBar);
        statusBar = new QStatusBar(GlowneOkno);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GlowneOkno->setStatusBar(statusBar);

        retranslateUi(GlowneOkno);

        QMetaObject::connectSlotsByName(GlowneOkno);
    } // setupUi

    void retranslateUi(QMainWindow *GlowneOkno)
    {
        GlowneOkno->setWindowTitle(QApplication::translate("GlowneOkno", "GlowneOkno", 0));
        label_2->setText(QApplication::translate("GlowneOkno", "Nr \"tury\"", 0));
        label_1->setText(QApplication::translate("GlowneOkno", "StanGry", 0));
        label_StanGry->setText(QApplication::translate("GlowneOkno", "Wybor warunkow", 0));
        groupBox_gracze->setTitle(QApplication::translate("GlowneOkno", "Ilosc Graczy", 0));
        radioButton_1gracz->setText(QApplication::translate("GlowneOkno", "1 gracz", 0));
        radioButton_2graczy->setText(QApplication::translate("GlowneOkno", "2 graczy", 0));
        label_3->setText(QApplication::translate("GlowneOkno", "Zloto poczatkowe", 0));
        label_4->setText(QApplication::translate("GlowneOkno", "Szybkosc gry", 0));
        commandLinkButton_akcja->setText(QApplication::translate("GlowneOkno", "Utworz serwer", 0));
        label_gracz1->setText(QApplication::translate("GlowneOkno", "Gracz 1", 0));
        label_gracz2->setText(QApplication::translate("GlowneOkno", "Gracz 2", 0));
        label->setText(QApplication::translate("GlowneOkno", "Adres IPv4 serwera", 0));
    } // retranslateUi

};

namespace Ui {
    class GlowneOkno: public Ui_GlowneOkno {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLOWNEOKNO_H
