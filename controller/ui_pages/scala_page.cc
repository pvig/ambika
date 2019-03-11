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

#include "controller/ui_pages/scala_page.h"

#include "avrlib/string.h"

#include "controller/display.h"
#include "controller/leds.h"

#include "controller/ui_pages/parameter_editor.h"
#include "avrlib/filesystem/directory.h"
#include "avrlib/filesystem/filesystem.h"

namespace ambika {

/* static */
const prog_EventHandlers ScalaPage::event_handlers_ PROGMEM = {
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
ScalaAction ScalaPage::action_;
StorageLocation ScalaPage::location_ = { STORAGE_OBJECT_SCALA, 0, 0 };
char ScalaPage::name_[16];
char const* ScalaPage::filename_;
Directory ScalaPage::directory_;
char* ScalaPage::readStatus_;
char* ScalaPage::dirpath_ = "/SCALA";
FilesystemStatus ScalaPage::fileStatus_;
/* </static> */


/* static */
void ScalaPage::OnInit(PageInfo* info) {
  UiPage::OnInit(info);
  if (storage.InitFilesystem() != FS_OK) {
    readStatus_ = "bad init";
  } else {
    fileStatus_ = directory_.Open(dirpath_, 1000);
    Browse();
  }
}

/* static */
void ScalaPage::Browse() {
  action_ = SCALA_ACTION_BROWSE;
  active_control_ = 1;
}

/* static */
uint8_t ScalaPage::OnIncrement(int8_t increment) {
  if (action_ == SCALA_ACTION_BROWSE) {
      int16_t slot = location_.slot;
      location_.slot = Clip(location_.slot + increment, 0, 127);

      fileStatus_ = directory_.Next();

      if(directory_.done()) {
        fileStatus_ = directory_.Rewind();
      }

      if(fileStatus_==FS_OK) {
        readStatus_="ok";
        //filename_ = directory_.entry().name();
        filename_ = directory_.entry().file_info.fname;
      } else {
        readStatus_ = "read error";
        filename_ = "";
      }
  }
  return 1;
}

/* static */
uint8_t ScalaPage::OnClick() {
  UiPage::OnClick();
  return 1;
}

/* static */
uint8_t ScalaPage::OnKey(uint8_t key) {
  return ParameterEditor::OnKey(key);
}

/* static */
uint8_t ScalaPage::OnKeyBrowse(uint8_t key) {
  return 1;
}

/* static */
uint8_t ScalaPage::OnKeySave(uint8_t key) {
  return 1;
}

/* static */
void ScalaPage::UpdateScreen() {
  
  // First line: 
  char* buffer = display.line_buffer(0) + 1;

  UnsafeItoa<int16_t>((location_.slot+1), 3, &buffer[0]);
  PadRight(&buffer[0], 3, ' ');

  strncpy(&buffer[6], readStatus_, 10);
  PadRight(&buffer[6], 10, ' ');

  // Second line: 
  buffer = display.line_buffer(1) + 1;
  strncpy_P(&buffer[12], filename_, sizeof(filename_));
  //PadRight(&buffer[12], 10, ' ');
  //memcpy_P(name_, blank_patch_name, sizeof(name_));


}

/* static */
void ScalaPage::UpdateLeds() {
}


}  // namespace ambika
