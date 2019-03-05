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
// Sequence editor UI page.

#ifndef CONTROLLER_UI_PAGES_SEQUENCE_EDITOR_H_
#define CONTROLLER_UI_PAGES_SEQUENCE_EDITOR_H_

#include "controller/ui_pages/ui_page.h"

namespace ambika {

struct PartData;

class SequenceEditor : public UiPage {
 public:
  //SequenceEditor() { }
  
  static void OnInit(PageInfo* info);
  static void SetActiveControl(ActiveControl active_control);

  static uint8_t OnIncrement(int8_t increment);
  static uint8_t OnPot(uint8_t index, uint8_t value);
  static uint8_t OnClick();
  static uint8_t OnNote(uint8_t note, uint8_t velocity);
  
  static void UpdateScreen();
  
  static const prog_EventHandlers event_handlers_;
  
 private:
  static uint8_t actual_step(uint8_t index, uint8_t sequence);
   
  static PartData* mutable_part_data();
  static const PartData& part_data();
  
  static uint8_t step_;

  DISALLOW_COPY_AND_ASSIGN(SequenceEditor);
};

}  // namespace ambika

#endif  // CONTROLLER_UI_PAGES_SEQUENCE_EDITOR_H_
