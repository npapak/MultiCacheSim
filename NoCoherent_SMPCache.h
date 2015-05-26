#include "CacheCore.h"
#include "SMPCache.h"
#include "NoCoherent_SMPCacheState.h"
#include <vector>

class NoCoherent_SMPCache : public SMPCache{

public:

  //FIELDS
  //This cache's ID
  int CPUId;


  //METHODS
  //Constructor
  NoCoherent_SMPCache(int cpuid,
               std::vector<SMPCache * > * cacheVector,
               int csize,
               int cassoc,
               int cbsize,
               int caddressable,
               const char * repPol,
               bool cskew);

  //Readline performs a read
  virtual void readLine(uint32_t rdPC, uint32_t addr);//SMPCache Interface Function

  //Writeline performs a write
  virtual void writeLine(uint32_t wrPC, uint32_t addr);//SMPCache Interface Function

  //Fill line touches cache state, bringing addr's block in
  virtual void fillLine(uint32_t addr,uint32_t state);//SMPCache Interface Function

  virtual char *Identify();

  //Dump the stats for this cache to outFile
  //virtual void dumpStatsToFile(FILE* outFile);

  //Destructor
  ~NoCoherent_SMPCache();
};


