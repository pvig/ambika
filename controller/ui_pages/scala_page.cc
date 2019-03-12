
// Special UI page for scala operations.

#include "controller/ui_pages/scala_page.h"

#include "avrlib/string.h"

#include "controller/display.h"
#include "controller/leds.h"

#include "controller/ui_pages/parameter_editor.h"
#include "avrlib/filesystem/directory.h"
//#include "avrlib/filesystem/filesystem.h"

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
uint8_t ScalaPage::location_ = 0;
char ScalaPage::name_[16];
const char* ScalaPage::filename_;
Directory ScalaPage::directory_;
char* ScalaPage::readStatus_;
const char* ScalaPage::dirpath_ = "/SCALA";
FilesystemStatus ScalaPage::fileStatus_;
/* </static> */

/* static */
void ScalaPage::OnInit(PageInfo* info) {
  UiPage::OnInit(info);
  if (storage.InitFilesystem() != FS_OK) {
    readStatus_ = "bad init";
  } else {
    fileStatus_ = directory_.Open(dirpath_, 1000);
    if (fileStatus_ != FS_OK) {
      readStatus_ = "bad open";
    } else {
      Browse();
    }
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
      location_ = Clip(location_ + increment, 0, 127);

      fileStatus_ = directory_.Next();

      /*if(directory_.done()) {
        fileStatus_ = directory_.Rewind();
        readStatus_ = "read done";
      } */
      //{
        if(fileStatus_==FS_OK) {
          readStatus_="ok";
          filename_ = directory_.entry().name();
          
        } else {
          readStatus_ = "read error";
          //filename_ = "";
        }
      //}

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

  UnsafeItoa<int16_t>((location_+1), 3, &buffer[0]);
  PadRight(&buffer[0], 3, ' ');

  strncpy(&buffer[6], readStatus_, 10);
  PadRight(&buffer[6], 10, ' ');

  // Second line: 
  buffer = display.line_buffer(1) + 1;
  strncpy(&buffer[12], filename_, strlen(filename_));
  //PadRight(&buffer[12], 10, ' ');
  //memcpy_P(name_, blank_patch_name, sizeof(name_));

}

/* static */
void ScalaPage::UpdateLeds() {
}


}  // namespace ambika
