#pragma once

#include <dvdnav/dvdnav.h>

class OMXDvdPlayer
{
  public:
      OMXDvdPlayer();
  private:
      dvdnav_t *dvdnav;

};
