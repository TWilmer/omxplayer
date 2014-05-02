#pragma once

#include <dvdnav/dvdnav.h>
#include <string>

class OMXDvdPlayer
{
  public:
      OMXDvdPlayer(std::string filename);
      int  Read(uint8_t* buf, int size);
      void pressButton();
  private:
      dvdnav_t *m_dvdnav;
      bool m_open;

};
