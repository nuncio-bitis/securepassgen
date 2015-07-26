/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/*******************************************************************************
 *
 * FILE NAME: securePassGen.cpp
 *
 * DESCRIPTION:
 *  Code for securePassGen GUI.
 *
 * AUTHOR: James P. Parziale
 *
 * DATE CREATED: 03/29/2010
 *
 *******************************************************************************
 * HISTORY:
 * 00 11/9/2004
 *    Original version
 * 01 03/29/2010
 *    Converted to Qt GUI application.
 ******************************************************************************/

#include "mainwindow.h"
#include "ui_securePassGen.h"
#include <stdint.h>

using namespace std;

//******************************************************************************

#define MAX_VALID_CHARS 85
#define MAX_PASSWORD_LENGTH 32

//******************************************************************************
// Local Variables

// Possible characters that can be used in password
QString validChars_left;
QString validChars_right;

QString validVowels_left;
QString validVowels_right;

const QString lower_left = "bcdfgqrstvwxz";
const QString lower_right = "hjklmnpy";
const QString upper_left = "BCDFGQRSTVWXZ";
const QString upper_right = "HJKLMNPY";

const QString lowerVowel_left = "ae";
const QString lowerVowel_right = "iou";
const QString upperVowel_left = "AE";
const QString upperVowel_right = "IOU";

const QString number_left = "12345";
const QString number_right = "67890";

const QString special_left  = "!@#$%";
const QString special_right = "^&*-_=+,<.>/?";

//******************************************************************************
//
// InitializeValidChars
//   This routine is used to initialize a string containing all valid
//   characters that may be used to generate a random password.
//   This function must be called at initialization.
//
// RETURNS:
//   If the valid-char string is empty (due to all input flags turned OFF),
//   this function will return FALSE, otherwise TRUE.
//
//******************************************************************************
bool MainWindow::InitializeValidChars(void)
{
  bool returnStatus = false;

  validChars_left.clear();
  validChars_right.clear();
  validVowels_left.clear();
  validVowels_right.clear();

  if (useLower) {
    validChars_left.append(lower_left);
    validChars_right.append(lower_right);

    validVowels_left.append(lowerVowel_left);
    validVowels_right.append(lowerVowel_right);

    returnStatus = true;
  }
  if (useUpper) {
    validChars_left.append(upper_left);
    validChars_right.append(upper_right);

    validVowels_left.append(upperVowel_left);
    validVowels_right.append(upperVowel_right);

    returnStatus = true;
  }
  if (useNumber) {
    validChars_left.append(number_left);
    validChars_right.append(number_right);

    returnStatus = true;
  }
  if (useSpecial) {
    validChars_left.append(special_left);
    validChars_right.append(special_right);

    returnStatus = true;
  }

  if (!usePattern) {
    validChars_left.append(validVowels_left);
    validChars_right.append(validVowels_right);
  }

//  if (debugOn) {
//    printf ("validChars_left:  \n  %s\n", validChars_left);
//    printf ("validChars_right: \n  %s\n", validChars_right);
//    printf ("validVowels_left: \n  %s\n", validVowels_left);
//    printf ("validVowels_right:\n  %s\n", validVowels_right);
//    printf ("\n");
//  }

  return returnStatus;
}

//******************************************************************************
//
// PickCharacter
//   Choose a random character from the input string.
//
//******************************************************************************
QChar MainWindow::PickCharacter(QString inputValidChars)
{
  uint32_t index;

  index = qrand() & 0xFF;
  return inputValidChars[index % inputValidChars.length()];
}


//******************************************************************************
//******************************************************************************


//******************************************************************************
//
// GeneratePW
//   This routine is used to generate a random password based on the user's
//   selection for possible characters and requested size.
//
//******************************************************************************
QString MainWindow::GeneratePW()
{
  QString password;

  QString sValidChars;
  QChar sTemp;
  int i;

  // Need to check if there are no available characters
  if ((validChars_left.length() == 0) ||
      (validChars_right.length() == 0))
    return password; // return empty password

  // Just fill the password string
  for (i = 0; i < MAX_PASSWORD_LENGTH; i++) {
    if (i & 0x01) {
      sValidChars = validChars_right;
    } else {
      sValidChars = validChars_left;
    }
    sTemp = PickCharacter(sValidChars);
    password[i] = sTemp;
  }

  return password;
}

//******************************************************************************
//
// GeneratePatternPW
//  This routine is used to generate a random password based
//  on the user's selection for possible characters and
//  requested size.
//  The generated password will be of the format:
//  [cL,vR,cL],[cR,vL,cR],...
//  where:
//  c = consonant, v = vowel
//  L = left hand character, R = right hand character
//
//******************************************************************************
QString MainWindow::GeneratePatternPW()
{
  QString password;

  int i;

  // Need to check if there are no available characters
  if ((validChars_left.length() == 0) ||
      (validChars_right.length() == 0))
    return password; // return empty password

  // Just fill the password string
  i = 0;
  while (i < MAX_PASSWORD_LENGTH) {
    //-------------
    // [cL, vR, cL]
    //-------------
    password[i++] = PickCharacter(validChars_left);
    password[i++] = PickCharacter(validVowels_right);
    password[i++] = PickCharacter(validChars_left);

    //-------------
    // [cR, vL, cR]
    //-------------
    password[i++] = PickCharacter(validChars_right);
    password[i++] = PickCharacter(validVowels_left);
    password[i++] = PickCharacter(validChars_right);

    password[i+1] = '\0';
  }

  return password;
}

//******************************************************************************
