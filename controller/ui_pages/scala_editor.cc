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
// Special UI page for loading/saving operations.

#include "controller/ui_pages/scala_editor.h"

#include "avrlib/string.h"

#include "controller/display.h"
#include "controller/leds.h"
#include "controller/midi_dispatcher.h"

namespace ambika {

const prog_char blank_patch_name[] PROGMEM = "(empty)       \0";

/* static */
const prog_EventHandlers ScalaEditor::event_handlers_ PROGMEM = {
  OnInit,
  UiPage::SetActiveControl,
  OnIncrement,
  OnClick,
  UiPage::OnPot,
  OnKey,
  NULL,
  OnIdle,
  UpdateScreen,
  UpdateLeds,
  OnDialogClosed,
};

/* <static> */
ScalaAction ScalaEditor::action_;
StorageLocation ScalaEditor::location_ = { STORAGE_OBJECT_PROGRAM, 0, 0 };
char ScalaEditor::name_[16];
/* </static> */


/* static */
void ScalaEditor::OnInit(PageInfo* info) {
  UiPage::OnInit(info);

  if (storage.InitFilesystem() != FS_OK) {
    ShowDiskErrorMessage();
  }
  Browse();
}

/* static */
void ScalaEditor::Browse() {
  action_ = SCALA_ACTION_BROWSE;
  location_.name = name_;
  edit_mode_ = EDIT_IDLE;
  active_control_ = 1;

  if (storage.LoadName(location_) != FS_OK) {
    memcpy_P(name_, blank_patch_name, sizeof(name_));
  }
}

/* static */
uint8_t ScalaEditor::OnIncrement(int8_t increment) {
  if (action_ == SCALA_ACTION_BROWSE ||
      edit_mode_ == EDIT_STARTED_BY_ENCODER) {
    if (active_control_ == 0) {
      int8_t bank = location_.bank;
      location_.bank = Clip(bank + increment, 0, 25);
    } else if (active_control_ == 1){
      int16_t slot = location_.slot;
      location_.slot = Clip(location_.slot + increment, 0, 127);
    } else {
      char character = name_[active_control_ - 2];
      character = Clip(character + increment, 32, 127);
      name_[active_control_ - 2] = character;
    }
  }
  
  return 1;
}

/* static */
uint8_t ScalaEditor::OnClick() {
  if (action_ == SCALA_ACTION_BROWSE) {
    active_control_ = (active_control_ + 1) & 1;
  } else {
    UiPage::OnClick();
  }
  return 1;
}

/* static */
uint8_t ScalaEditor::OnKey(uint8_t key) {
  if (action_ == SCALA_ACTION_BROWSE) {
    return OnKeyBrowse(key);
  } else {
    return OnKeySave(key);
  }
}

/* static */
uint8_t ScalaEditor::OnKeyBrowse(uint8_t key) {

  switch (key) {
    case SWITCH_1:

      break;

    case SWITCH_2:

      break;

    case SWITCH_3:

      break;

    case SWITCH_4:

      break;

    case SWITCH_5:

      break;

    case SWITCH_7:

      break;

    case SWITCH_8:

      break;
  }

  return 1;
}

/* static */
uint8_t ScalaEditor::OnKeySave(uint8_t key) {
  switch (key) {
    case 6:

      break;
      
    case 7:

      break;
  }   
  return 1;
}

/* static */
void ScalaEditor::PrintActiveObjectName(char* buffer) {
    strcpy_P(&buffer[0], PSTR("blah"));
}


/* static */
void ScalaEditor::UpdateScreen() {
  
  // First line: File browser
  char* buffer = display.line_buffer(0) + 1;
  
  PrintActiveObjectName(&buffer[0]);
  AlignLeft(&buffer[0], 15);

  buffer[15] = 'A' + location_.bank;
  UnsafeItoa<int16_t>(location_.slot, 3, &buffer[16]);
  PadRight(&buffer[16], 3, '0');
  memcpy(&buffer[20], name_, sizeof(name_) - 1);
  AlignLeft(&buffer[20], sizeof(name_) - 1);

  // Second line: buttons
  if (action_ == SCALA_ACTION_BROWSE) {
    buffer = display.line_buffer(1) + 1;
    strncpy_P(&buffer[0], PSTR("pref|~ini|about               more|exit"), 39);
    buffer[4] = kDelimiter;
    buffer[34] = kDelimiter;
  } else {
    buffer = display.line_buffer(1) + 1;
    strncpy_P(&buffer[28], PSTR("save|cancel"), 11);
    buffer[32] = kDelimiter;
  }
  
  // And now the cursor.
  if (action_ == LIBRARY_ACTION_SAVE) {
    display.set_cursor_character(edit_mode_ == EDIT_IDLE ? 0xff : '_');
  } else {
    display.set_cursor_character(' ');
  }
  
  if (active_control_ == 0) {
    display.set_cursor_position(16);
  } else if (active_control_ == 1) {
    display.set_cursor_position(
        action_ == LIBRARY_ACTION_SAVE ? 19 : kLcdNoCursor);
  } else {
    display.set_cursor_position(19 + active_control_);
  }
}

/* static */
void ScalaEditor::UpdateLeds() {
  leds.set_pixel(LED_8, 0xf0);
  leds.set_pixel(LED_7, 0x0f);

}

/* static */
void ScalaEditor::ShowDiskErrorMessage() {
  Dialog d;
  d.dialog_type = DIALOG_ERROR;
  d.text = PSTR("SD card I/O error");
  d.user_text = NULL;
  ui.ShowDialogBox(2, d, 0);
}

/* static */
void ScalaEditor::OnDialogClosed(uint8_t dialog_id, uint8_t return_value) {
  switch (dialog_id) {
    // Handler for the init dialog box.
    case 1:
      break;
    case 3:
      break;
  }
}

}  // namespace ambika
