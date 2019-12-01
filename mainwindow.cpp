/*******************************************************************************
 *
 * FILE NAME: mainwindow.cpp
 *
 * DESCRIPTION:
 *  Main window class.
 *  This code was generated by qmake.
 *
 * AUTHOR: James P. Parziale
 *
 * DATE CREATED: 03/29/2010
 *
 * This file may be distributed under the terms of the GNU Public License.
 *
 *******************************************************************************
 * HISTORY:
 * 00 03/29/2010
 *   Original version
 ******************************************************************************/

#include "mainwindow.h"
#include "ui_securePassGen.h"
#include "about.h"

#include <QtCore>
#include <QtGui>

#include <QFile>
#include <QMessageBox>

//******************************************************************************

#define INITIAL_NUMBER_OF_PASSWORDS 20
#define INITIAL_PASSWORD_LENGTH 8
#define OUTPUT_FILENAME "securePassGen_output.txt"

//******************************************************************************

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // Set up default flags.
  useLower   = true;
  useUpper   = false;
  useNumber  = false;
  useSpecial = false;
  usePattern = true;

  // Set the practice text edit box to hide input characters.
  ui->testTextEdit->setEchoMode(QLineEdit::Password);

  // Set initial checkbox settings based on flag defaults.
  if (useLower)
    ui->lowerCaseCheck->setCheckState(Qt::Checked);
  else
    ui->lowerCaseCheck->setCheckState(Qt::Unchecked);

  if (useUpper)
    ui->upperCaseCheck->setCheckState(Qt::Checked);
  else
    ui->upperCaseCheck->setCheckState(Qt::Unchecked);

  if (useNumber)
    ui->numbersCheck->setCheckState(Qt::Checked);
  else
    ui->numbersCheck->setCheckState(Qt::Unchecked);

  if (useSpecial)
    ui->specialsCheck->setCheckState(Qt::Checked);
  else
    ui->specialsCheck->setCheckState(Qt::Unchecked);

  if (usePattern)
    ui->patternCheck->setCheckState(Qt::Checked);
  else
    ui->patternCheck->setCheckState(Qt::Unchecked);
  on_patternCheck_clicked();

  // Set initial number of characters per password
  charsPerPassword = INITIAL_PASSWORD_LENGTH;
  ui->lengthEdit->setText(QString().setNum(charsPerPassword));

  // Set initial number of passwords to generate
  numToGenerate = INITIAL_NUMBER_OF_PASSWORDS;
  ui->totalEdit->setText(QString().setNum(numToGenerate));

  // Initial seeding of the RNG.
  // qrand is called in MainWindow::PickCharacter
  qsrand((uint)QTime::currentTime().msec());
}


MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::changeEvent(QEvent *e)
{
  QMainWindow::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

//******************************************************************************

void MainWindow::on_aboutButton_clicked()
{
  About about_dialog(this);
  about_dialog.exec();
}

//******************************************************************************

void MainWindow::on_generateButton_clicked()
{
  ui->statusbar->clearMessage();

  // First check options
  if (charsPerPassword < 1) {
    ui->statusbar->showMessage("ERROR: Invalid parameter, charsPerPassword");
    return;
  }
  if (numToGenerate < 1) {
    ui->statusbar->showMessage("ERROR: Invalid parameter, numToGenerate");
    return;
  }
  ui->statusbar->clearMessage();

  if (!InitializeValidChars()) {
    ui->statusbar->showMessage("ERROR: Need at least one character-type option turned ON!");
    return;
  }

  // Clear output and test edit boxes.
  on_clearButton_clicked();

  QString line;
  bool addNewline = false;

  // Create list of passwords
  for (int count = 0; count < numToGenerate; count++) {
    QString newPassword;

    if (usePattern)
      newPassword = GeneratePatternPW();
    else
      newPassword = GeneratePW();

    // Set max length of password.
    if (newPassword.length() > charsPerPassword)
      newPassword.resize(charsPerPassword);

    if (newPassword.length() > 0) {
      if (usePattern) {
        QString newPatPassword;
        int i;

        for (i = 0; i < newPassword.length(); i++) {
          newPatPassword.append(newPassword[i]);
          if ( (i > 0) && ((i % 3) == 2) && (i < (newPassword.length() - 1)) ) {
            newPatPassword.append("-");
          }
        }

        line.append(newPatPassword);
      } else {
          line.append(newPassword);
      }

    } else {
      ui->statusbar->showMessage("Error - no password generated.");
    }

    if (addNewline) {
        ui->outputBox->appendPlainText(line);
        line.clear();
    } else {
        line.append("   ");
    }
    addNewline = !addNewline;

  } // end for(count)

  if (addNewline) {
      ui->outputBox->appendPlainText(line);
      line.clear();
  }
}

//******************************************************************************

void MainWindow::on_clearButton_clicked()
{
  ui->outputBox->clear();
  ui->testTextEdit->clear();
}

void MainWindow::on_testClearButton_clicked()
{
  ui->testTextEdit->clear();
}

//******************************************************************************

void MainWindow::on_saveButton_clicked()
{
  // Open the output file
  QFile outfile(OUTPUT_FILENAME);
  if (!outfile.open(QIODevice::WriteOnly)) {
    QMessageBox::warning(this, tr("Unable to open file"), outfile.errorString());
      return;
  }

  // Write the text from the output window to the output file.
  QString outtext = ui->outputBox->toPlainText();

  outfile.write(outtext.toStdString().c_str());
  outfile.write("\n");

  // Close the output file
  outfile.close();

  ui->statusbar->showMessage("Output written to " + outfile.fileName());
}

//******************************************************************************

void MainWindow::on_lowerCaseCheck_clicked()
{
  useLower = (ui->lowerCaseCheck->checkState() == Qt::Checked);
}

void MainWindow::on_upperCaseCheck_clicked()
{
  useUpper = (ui->upperCaseCheck->checkState() == Qt::Checked);
}

void MainWindow::on_numbersCheck_clicked()
{
  useNumber = (ui->numbersCheck->checkState() == Qt::Checked);
}

void MainWindow::on_specialsCheck_clicked()
{
  useSpecial = (ui->specialsCheck->checkState() == Qt::Checked);
}

void MainWindow::on_patternCheck_clicked()
{
  usePattern = (ui->patternCheck->checkState() == Qt::Checked);

  if (usePattern) {
    useNumber  = false;
    ui->numbersCheck->setCheckState(Qt::Unchecked);
    ui->numbersCheck->setEnabled(false);

    useSpecial = false;
    ui->specialsCheck->setCheckState(Qt::Unchecked);
    ui->specialsCheck->setEnabled(false);
  } else {
    ui->numbersCheck->setEnabled(true);
    ui->specialsCheck->setEnabled(true);
  }
}

//******************************************************************************

void MainWindow::on_lengthEdit_textChanged()
{
  QString lengthText = ui->lengthEdit->text();
  bool ok = true;
  charsPerPassword = lengthText.toInt(&ok);
  if (!ok) {
    ui->statusbar->showMessage("ERROR: Invalid number for length.");
    charsPerPassword = INITIAL_PASSWORD_LENGTH;
  } else {
    ui->statusbar->clearMessage();
  }
}

void MainWindow::on_totalEdit_textChanged()
{
  QString totalText = ui->totalEdit->text();
  bool ok = true;
  numToGenerate = totalText.toInt(&ok);
  if (!ok) {
    ui->statusbar->showMessage("ERROR: Invalid number entered.");
    numToGenerate = INITIAL_NUMBER_OF_PASSWORDS;
  } else {
    ui->statusbar->clearMessage();
  }
}

void MainWindow::on_testTextEdit_editingFinished()
{
  QString pwText = ui->testTextEdit->text();
  int pwSize = pwText.length();
  QString msg = QString("Length %1; ").arg(pwSize);

  if (pwSize > 0) {
     // Try and match the entered password with what's in the output window.
     QString outtext = ui->outputBox->toPlainText();
     QStringList outlines = outtext.split("\n", QString::SkipEmptyParts);
     foreach (QString line, outlines) {
       line.replace("-","");
       if ((pwText.length() == charsPerPassword) && line.contains(pwText)) {
         ui->statusbar->showMessage(msg + "Password matches!", 5000);
         return;
       }
     }
     ui->statusbar->showMessage(msg + "No match found.", 5000);
  }
}

//******************************************************************************
