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
//#include "controller/midi_dispatcher.h"
#include "controller/ui_pages/parameter_editor.h"
#include "avrlib/filesystem/directory.h"
//#include "avrlib/filesystem/file.h"
#include "avrlib/devices/sd_card.h"

//#include "avrlib/filesystem/fat_file_reader.h"
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
//FRESULT ScalaPage::dirStatus_;
//DIR ScalaPage::dir_;
Directory ScalaPage::directory_;
//FILINFO ScalaPage::fileInfos_;
char* ScalaPage::readStatus_;
char* ScalaPage::dirpath_ = "/";
FilesystemStatus ScalaPage::fileStatus_;
/* </static> */

/*typedef SdCard<SpiMaster<SpiSS, MSB_FIRST, 4> > SdCardInterface;
FATFileReader<SdCardInterface> reader;
AddressBus address;
FsHandle h;*/

/* static */
void ScalaPage::OnInit(PageInfo* info) {
  UiPage::OnInit(info);

  if (storage.InitFilesystem() != FS_OK) {
    ShowDiskErrorMessage();
  }
  //directory_ = Directory::Directory();
  fileStatus_ = directory_.Open(dirpath_, 1000);
  //dirStatus_ = f_opendir(&dir_, dirpath_);
  //GetReadErrorCode();

  Browse();
}

/* static */
void ScalaPage::Browse() {
  action_ = SCALA_ACTION_BROWSE;
  //location_.name = name_;
  active_control_ = 1;
  /*if (storage.LoadName(location_) != FS_OK) {
    memcpy_P(name_, blank_patch_name, sizeof(name_));
  }*/
}

/* static */
uint8_t ScalaPage::OnIncrement(int8_t increment) {
  if (action_ == SCALA_ACTION_BROWSE) {
      int16_t slot = location_.slot;
      location_.slot = Clip(location_.slot + increment, 0, 127);
      //ScalaPage::getFileInfo(dirpath_, location_.slot);
      
      fileStatus_ = directory_.Next();
      //GetReadErrorCode();
      if(directory_.done()) {
        fileStatus_ = directory_.Rewind();
      }

      if(fileStatus_==FS_OK) {
        readStatus_="ok";
        filename_ = directory_.entry().name();
      } else {
        //ShowDiskErrorMessage();
        readStatus_ = "read error";
        filename_ = "";
      }
      //strcpy( filename_, directory_.entry().name());

      //filename_ = (char *)directory_.entry().is_directory()?"true":"false";
      //filename_ = (char *)dirStatus_.
  }
  return 1;
}

void ScalaPage::GetReadErrorCode() {
   /* if(fileStatus_==FS_OK) {
      readStatus_ = "ok";
    } else if(fileStatus_==FS_DISK_ERROR) {
      readStatus_ = "FS_DISK_ERROR";
    } else if(fileStatus_==FS_EXCEPTION) {
      readStatus_ = "FS_EXCEPTION";
    } else if(fileStatus_==FS_DRIVE_NOT_READY) {
      readStatus_ = "FS_DRIVE_NOT_READY";
    } else if(fileStatus_==FS_FILE_NOT_FOUND) {
      readStatus_ = "FS_FILE_NOT_FOUND";

    } else if(fileStatus_==FS_PATH_NOT_FOUND) {
      readStatus_ = "FS_PATH_NOT_FOUND";
    } else if(fileStatus_==FS_INVALID_NAME) {
      readStatus_ = "FS_INVALID_NAME";
    } else if(fileStatus_==FS_ACCESS_DENIED) {
      readStatus_ = "FS_ACCESS_DENIED";*/
    /*} else if(fileStatus_==FS_FILE_EXISTS) {
      readStatus_ = "FS_FILE_EXISTS";

    } else if(fileStatus_==FS_INVALID_OBJECT) {
      readStatus_ = "FS_INVALID_OBJECT";
    } else if(fileStatus_==FS_WRITE_PROTECTED) {
      readStatus_ = "FS_WRITE_PROTECTED";
    } else if(fileStatus_==FS_INVALID_DRIVE) {
      readStatus_ = "FS_INVALID_DRIVE";
    } else if(fileStatus_==FS_VOLUME_NOT_INITIALIZED) {
      readStatus_ = "FS_VOLUME_NOT_INITIALIZED";*/

    /*} else if(fileStatus_==FS_NO_FAT_VOLUME) {
      readStatus_ = "FS_NO_FAT_VOLUME";
    } else if(fileStatus_==FS_FORMAT_FAILED) {
      readStatus_ = "FS_FORMAT_FAILED";*/
    /*} else if(fileStatus_==FS_TIMEOUT) {
      readStatus_ = "FS_TIMEOUT";*/
    /*} else if(fileStatus_==FS_LOCKED) {
      readStatus_ = "FS_LOCKED";*/

    /*} else if(fileStatus_==FS_NOT_ENOUGH_MEMORY) {
      readStatus_ = "FS_NOT_ENOUGH_MEMORY";
    } else if(fileStatus_==FS_TOO_MANY_FILES) {
      readStatus_ = "FS_TOO_MANY_FILES";
    } else if(fileStatus_==FS_INVALID_PARAMETER) {
      readStatus_ = "FS_INVALID_PARAMETER";
    } else if(fileStatus_==FS_NOT_OPENED) {
      readStatus_ = "FS_NOT_OPENED";
    } else if(fileStatus_==FS_BAD_FILE_FORMAT) {
      readStatus_ = "FS_BAD_FILE_FORMAT";
    } else if(fileStatus_==FS_COPY_ERROR) {
      readStatus_ = "FS_COPY_ERROR";*/

    /*} else {
      readStatus_ = "autre erreur";
    }*/

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
  
  // First line: File browser
  char* buffer = display.line_buffer(0) + 1;
  //AlignLeft(&buffer[0], 15);

  //buffer[1] = location_.slot;
  UnsafeItoa<int16_t>((location_.slot+1), 3, &buffer[0]);
  PadRight(&buffer[0], 3, ' ');

  strncpy(&buffer[6], readStatus_, 20);
  //strncpy(&buffer[6], filename_, 20);

  buffer = display.line_buffer(1) + 1;
  //strncpy_P(&buffer[0], PSTR(filename_), 20);
  //memcpy(&buffer[0], filename_, sizeof(filename_) - 1);
  //strncpy_P(&buffer[15], PSTR("upgrade"), 7);
 
  //memcpy(&buffer[0], filename_, sizeof(filename_) - 1);
  //AlignLeft(&buffer[0], sizeof(filename_) - 1);

  strncpy(&buffer[1], readStatus_, 10);
  strncpy(&buffer[12], filename_, 28);

  //AlignLeft(&buffer[20], sizeof(name_) - 1);

  // Second line: buttons
  /*if (action_ == SCALA_ACTION_BROWSE) {
    buffer = display.line_buffer(1) + 1;
    strncpy_P(&buffer[0], filename_, 20);
    buffer[4] = kDelimiter;
    buffer[34] = kDelimiter;
  }*/

}

/* static */
void ScalaPage::UpdateLeds() {
  //leds.set_pixel(LED_8, 0xf0);
  //leds.set_pixel(LED_7, 0x0f);
}

/* static */
void ScalaPage::ShowDiskErrorMessage() {
  Dialog d;
  d.dialog_type = DIALOG_ERROR;
  d.text = PSTR("SD card I/O error");
  d.user_text = NULL;
  ui.ShowDialogBox(2, d, 0);
}

/* static */
void ScalaPage::OnDialogClosed(uint8_t dialog_id, uint8_t return_value) {
  switch (dialog_id) {
    // Handler for the init dialog box.
    case 1:
      break;
    case 3:
      break;
  }
}

FRESULT ScalaPage::getFileInfo (
    char* path,       /* Start node to be scanned (***also used as work area***) */
    uint8_t filepos
)
{
  FRESULT res;
 /* if (dirStatus_ == FR_OK) {
    for (uint8_t ii = 0; ii < filepos; ++ii) {
        filename_ =  (char*)filepos;
        res = f_readdir(&dir_, &fileInfos_);                   
        if (res != FR_OK || fileInfos_.fname[0] == 0) break;  
        if (fileInfos_.fattrib & AM_DIR) {                    
        } else {                         
            //printf("%s/%s\n", path, fno.fname);
            filename_ =  fileInfos_.fname;
        }
    }
  }*/
  return res;
}

}  // namespace ambika
