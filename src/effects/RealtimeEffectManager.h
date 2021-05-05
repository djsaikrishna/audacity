/**********************************************************************
 
 Audacity: A Digital Audio Editor
 
 RealtimeEffectManager.h
 
 Paul Licameli split from EffectManager.h
 
 **********************************************************************/

#ifndef __AUDACITY_REALTIME_EFFECT_MANAGER__
#define __AUDACITY_REALTIME_EFFECT_MANAGER__

#include <memory>
#include <vector>
#include <wx/thread.h>

class EffectProcessor;
class RealtimeEffectState;

class AUDACITY_DLL_API RealtimeEffectManager final
{
public:
   using EffectArray = std::vector <EffectProcessor*> ;

   /** Get the singleton instance of the RealtimeEffectManager. **/
   static RealtimeEffectManager & Get();

   // Realtime effect processing
   bool RealtimeIsActive();
   bool RealtimeIsSuspended();
   void RealtimeAddEffect(EffectProcessor &effect);
   void RealtimeRemoveEffect(EffectProcessor &effect);
   void RealtimeInitialize(double rate);
   void RealtimeAddProcessor(int group, unsigned chans, float rate);
   void RealtimeFinalize();
   void RealtimeSuspend();
   void RealtimeSuspendOne( EffectProcessor &effect );
   void RealtimeResume();
   void RealtimeResumeOne( EffectProcessor &effect );
   void RealtimeProcessStart();
   size_t RealtimeProcess(int group, unsigned chans, float **buffers, size_t numSamples);
   void RealtimeProcessEnd();
   int GetRealtimeLatency();

private:
   RealtimeEffectManager();
   ~RealtimeEffectManager();

   wxCriticalSection mRealtimeLock;
   std::vector< std::unique_ptr<RealtimeEffectState> > mStates;
   int mRealtimeLatency;
   bool mRealtimeSuspended;
   bool mRealtimeActive;
   std::vector<unsigned> mRealtimeChans;
   std::vector<double> mRealtimeRates;
};

#endif
