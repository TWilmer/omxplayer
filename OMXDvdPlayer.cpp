/*
 * Copyright (C) 2014 by Thorsten Wilmer
 *
 * This file is part of omxplayer, based on libdvdnav's menu.c
 * Copyright (C) 2003 by the libdvdnav project
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with libdvdnav; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#include "OMXDvdPlayer.h"
#include <string.h>


/* shall we use libdvdnav's read ahead cache? */
#define DVD_READ_CACHE 1

/* which is the default language for menus/audio/subpictures? */
#define DVD_LANGUAGE "en"



OMXDvdPlayer::OMXDvdPlayer(std::string filename)
: m_dvdnav(0)
, m_open(false)
{
  /* open dvdnav handle */
  if (dvdnav_open(&m_dvdnav, filename.c_str()) != DVDNAV_STATUS_OK) {
    printf("Error on dvdnav_open\n");
    m_open=false;
    return;
  }
  /* set read ahead cache usage */
  if (dvdnav_set_readahead_flag(m_dvdnav, DVD_READ_CACHE) != DVDNAV_STATUS_OK) {
    printf("Error on dvdnav_set_readahead_flag: %s\n", dvdnav_err_to_string(m_dvdnav));
    m_open=false;
    return;
  }


  /* set the language */
  if (dvdnav_menu_language_select(m_dvdnav, DVD_LANGUAGE) != DVDNAV_STATUS_OK ||
      dvdnav_audio_language_select(m_dvdnav, DVD_LANGUAGE) != DVDNAV_STATUS_OK ||
      dvdnav_spu_language_select(m_dvdnav, DVD_LANGUAGE) != DVDNAV_STATUS_OK) {
    printf("Error on setting languages: %s\n", dvdnav_err_to_string(m_dvdnav));
    m_open=false;
    return;
  }

  /* set the PGC positioning flag to have position information relatively to the
   * whole feature instead of just relatively to the current chapter */
  if (dvdnav_set_PGC_positioning_flag(m_dvdnav, 1) != DVDNAV_STATUS_OK) {
    printf("Error on dvdnav_set_PGC_positioning_flag: %s\n", dvdnav_err_to_string(m_dvdnav));
    m_open=false;
    return;
  }

  

  
  m_open=true;
}

void OMXDvdPlayer::pressButton()
{
 pci_t *pci;
 pci =dvdnav_get_current_nav_pci(m_dvdnav);
 dvdnav_button_activate(m_dvdnav, pci);

}

int OMXDvdPlayer::Read(uint8_t* buf, int size)
{
  bool finished=false;
  int c=0;
  if(size % 2048 !=0)
  {
    printf("Error odd buffer size %d\n", size);
    return -1;
  }
  int d=size/2048;

  while(!finished)
  {
  int result,  event, len;
  result = dvdnav_get_next_block(m_dvdnav, buf+c*2048, &event, &len);

  if (result == DVDNAV_STATUS_ERR) {
      printf("Error getting next block: %s\n", dvdnav_err_to_string(m_dvdnav));
      return -1;
   }
   
    switch (event) {
    case DVDNAV_BLOCK_OK:
    {

      c++;
      if(d==c)
        return size;
   }
  case DVDNAV_STOP:
      /* Playback should end here. */
      {
        // finished = true;
      }
      break;
    case DVDNAV_STILL_FRAME:
      /* We have reached a still frame. A real player application would wait
       * the amount of time specified by the still's length while still handling
       * user input to make menus and other interactive stills work.
       * A length of 0xff means an indefinite still which has to be skipped
       * indirectly by some user interaction. */
      {
        dvdnav_still_event_t *still_event = (dvdnav_still_event_t *)buf;
        if (still_event->length < 0xff)
          printf("Skipping %d seconds of still frame\n", still_event->length);
        else
          printf("Skipping indefinite length still frame\n");
        dvdnav_still_skip(m_dvdnav);
      }
      break;
    case DVDNAV_WAIT:
      /* We have reached a point in DVD playback, where timing is critical.
       * Player application with internal fifos can introduce state
       * inconsistencies, because libdvdnav is always the fifo's length
       * ahead in the stream compared to what the application sees.
       * Such applications should wait until their fifos are empty
       * when they receive this type of event. */
      printf("Skipping wait condition\n");
      dvdnav_wait_skip(m_dvdnav);
      break;
    case DVDNAV_HIGHLIGHT:
      /* Player applications should inform their overlay engine to highlight the
       * given button */
      {
        dvdnav_highlight_event_t *highlight_event = (dvdnav_highlight_event_t *)buf;
        printf("Selected button %d\n", highlight_event->buttonN);
      }
      break;


   case DVDNAV_NAV_PACKET:
    {
        pci_t *pci;
        pci = dvdnav_get_current_nav_pci(m_dvdnav);
        dvdnav_get_current_nav_dsi(m_dvdnav);

        if(pci->hli.hl_gi.btn_ns > 0) {
          int button;

          printf("Found %i DVD menu buttons...\n", pci->hli.hl_gi.btn_ns);

          for (button = 0; button < pci->hli.hl_gi.btn_ns; button++) {
            btni_t *btni = &(pci->hli.btnit[button]);
            printf("Button %i top-left @ (%i,%i), bottom-right @ (%i,%i)\n",
                    button + 1, btni->x_start, btni->y_start,
                    btni->x_end, btni->y_end);
          }

          button = 0;
	 button=1;
          printf("Selecting button %i...\n", button);
          /* This is the point where applications with fifos have to hand in a NAV packet
           * which has traveled through the fifos. See the notes above. */
          dvdnav_button_select_and_activate(m_dvdnav, pci, button);
        }

     }
      break;
   default:
      printf("Not handled event yet %d\n", event);
   }

   }
   return 0;
}

