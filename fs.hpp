#pragma once
#include <stdio.h>
#include <assert.h>
#include <string>

inline bool
gettext(const char *filepath, std::string &outval)
{
   bool outstatus = false;
   FILE *f = fopen(filepath, "rb");
   if (f)
   {
      fseek(f, 0, SEEK_END);
      long fsize = ftell(f);
      fseek(f, 0, SEEK_SET);

      if (fsize)
      {
         outval.resize(fsize);
         int val = fread(&outval[0], 1, fsize, f);
         assert(val == fsize);
         (void)val;
      }
      outstatus = true;
      fclose(f);
   }
   return outstatus;
}
inline std::string
gettext(const char *filepath)
{
   std::string outbuffer;
   static_cast<void>(gettext(filepath, outbuffer));
   return outbuffer;
}