
#include <stdbool.h>
#include "core/main.h"

#include"flash.h"



void flash_load_user_data(void) {

  MSC_Init();

  //load the data
  memcpy(&leaderboard_score, USERDATA_FLASH_BASE, sizeof(leaderboard_score));

  if (leaderboard_score.unqiue_var != 0x4321){

  }

}

void flash_save_user_data(void) {

    MSC_ErasePage(USERDATA_FLASH_BASE);  // Ensure flash is erased before writing
    MSC_WriteWord(USERDATA_FLASH_BASE, &leaderboard_score, sizeof(leaderboard_score));

}

