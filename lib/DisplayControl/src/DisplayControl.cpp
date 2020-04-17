/*
  Copyright (C) 2019 Axel Ruder

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "DisplayControl.h"

DisplayControl *DisplayControl::instance = 0;

DisplayControl::~DisplayControl() {
}

DisplayControl *DisplayControl::getInstance()
{
	// The only instance
	// Guaranteed to be lazy initialized
	// Guaranteed that it will be destroyed correctly
	if (!DisplayControl::instance)
	{
		DisplayControl::instance = new DisplayControl();
	}
	return DisplayControl::instance;
}

void DisplayControl::setup() { 
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_WHITE, TFT_BLACK); // Note: the new fonts do not draw the background colour
  tft.drawString("EspTemp 1.0", 0, 0, 2);
  tft.drawRightString("IP: 192.168.178.45", 320, 0, 2);

  tft.drawCentreString("25 °C", 160, 120 - tft.fontHeight(4) - 5, 4);

}

const char *DisplayControl::getName() {
    return "DisplayControl";
}

void DisplayControl::displayOutsideTemperature(double outsideTemperature) {
    char buffer[100];
    sprintf(buffer, "%.2f° C", outsideTemperature);
    tft.drawCentreString(buffer, 160, 120 - tft.fontHeight(4) - 5, 4);
}



