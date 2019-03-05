// Copyright 2011 Olivier Gillet.
//
// Author: Olivier Gillet (ol.gillet@gmail.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------------------------
//
// Special UI page for scala parameters.

#ifndef CONTROLLER_UI_PAGES_SCALA_EDITOR_H_
#define CONTROLLER_UI_PAGES_SCALA_EDITOR_H_

#include "controller/storage.h"
#include "controller/ui_pages/ui_page.h"

namespace ambika {

enum ScalaAction {
  SCALA_ACTION_BROWSE,
  SCALA_ACTION_LOAD
};

class ScalaEditor : public UiPage {
 public:
  ScalaEditor() { }
  
  static void OnInit(PageInfo* info);
  static void SetActiveControl(ActiveControl active_control);

  static uint8_t OnIncrement(int8_t increment);
  static uint8_t OnClick();
  static uint8_t OnKey(uint8_t key);

  static void UpdateScreen();
  static void UpdateLeds();
  
  static const prog_EventHandlers event_handlers_;
  
  static void OnDialogClosed(uint8_t dialog_id, uint8_t return_value);
  static void SaveState() {}

  static StorageLocation* mutable_location() { return &location_; }
  static const StorageLocation& location() { return location_; }

  static void PrintActiveObjectName(char* buffer);
  static void UpdateLocation();

 private:
  static void Browse();
  static void ShowDiskErrorMessage();

  static uint8_t OnKeyBrowse(uint8_t key);
  static uint8_t OnKeySave(uint8_t key);
  
  static ScalaAction action_;
  static StorageLocation location_;

  static char name_[16];
  
  DISALLOW_COPY_AND_ASSIGN(ScalaEditor);
};

}  // namespace ambika

#endif  // CONTROLLER_UI_PAGES_LIBRARY_H_
