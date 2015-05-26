#include "NoCoherent_SMPCache.h"

NoCoherent_SMPCache::NoCoherent_SMPCache(int cpuid,
		std::vector<SMPCache * > * cacheVector,
		int csize,
		int cassoc,
		int cbsize,
		int caddressable,
		const char * repPol,
		bool cskew) :
	SMPCache(cpuid,cacheVector){

		fprintf(stderr,"Making a NoCoherent SMP cache with cpuid %d\n",cpuid);
		CacheGeneric<NoCoherent_SMPCacheState> *c =
			CacheGeneric<NoCoherent_SMPCacheState>::create(csize,
					cassoc,
					cbsize,
					caddressable,
					repPol,
					cskew);
		cache = (CacheGeneric<StateGeneric<> >*)c;

	}

void NoCoherent_SMPCache::fillLine(uint32_t addr, uint32_t state){

  //this gets the state of whatever line this address maps to
  NoCoherent_SMPCacheState *st = (NoCoherent_SMPCacheState *)cache->findLine2Replace(addr);

  if(st==0){
    /*No state*/
    return;
  }

  /*Set the tags to the tags for the newly cached block*/
  st->setTag(cache->calcTag(addr));
	st->changeStateTo((Cachestate_t)state);

  return;

}


void NoCoherent_SMPCache::readLine(uint32_t rdPC, uint32_t addr){
  /*
   *This method implements actions taken on a read access to address addr
   *at instruction rdPC
   */

  /*Get the state of the line to which this address maps*/
  NoCoherent_SMPCacheState *st = (NoCoherent_SMPCacheState *)cache->findLine(addr);

  /*Read Miss - tags didn't match, or line is invalid*/
  if(!st || (st && !(st->isValid())) ){

    /*Update event counter for read misses*/
    numReadMisses++;

    if(st){

      /*Tag matched, but state was invalid*/
      numReadOnInvalidMisses++;

    }

		/* Bring the date from lower level memory */
    fillLine(addr,NC_VALID);

  }else{

    /*Read Hit - any state but Invalid*/
    numReadHits++;
    return;

  }

}

void NoCoherent_SMPCache::writeLine(uint32_t wrPC, uint32_t addr){
  /*This method implements actions taken when instruction wrPC
   *writes to memory location addr*/

  /*Find the line to which this address maps*/
  NoCoherent_SMPCacheState * st = (NoCoherent_SMPCacheState *)cache->findLine(addr);

  /*
   *If the tags didn't match, or the line was invalid, it is a
   *write miss
   */
  if(!st || (st && !(st->isValid())) ){

    numWriteMisses++;

    if(st){

      /*We're writing to an invalid line*/
      numWriteOnInvalidMisses++;

    }

    /* Bring the line from lower level memory
    /* Fill the line with the new written block */
    fillLine(addr,NC_VALID);

  }else{ //Write Hit

    /*Already have it writable: No coherence action required!*/
    numWriteHits++;
  }

	return;
}

char *NoCoherent_SMPCache::Identify(){
  return (char *)" No Cache Coherence";
}

NoCoherent_SMPCache::~NoCoherent_SMPCache(){

}

extern "C" SMPCache *Create(int num, std::vector<SMPCache*> *cvec, int csize, int casso, int bs, int addrble, const char *repl, bool skw){

  return new NoCoherent_SMPCache(num,cvec,csize,casso,bs,addrble,repl,skw);

}
