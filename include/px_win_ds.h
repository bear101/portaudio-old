#if !defined(PX_WIN_DSOUND_H)
#define PX_WIN_DSOUND_H

#include <portaudio.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef float PxVolume;
typedef float PxFrequency;

PxVolume Px_DsGetOutputVolume( PaStream* pa_stream );
void Px_DsSetOutputVolume( PaStream* pa_stream, PxVolume volume );

void Px_DsSetFrequency(PaStream* pa_stream, PxFrequency freq);
PxFrequency Px_DsGetFrequency(PaStream* pa_stream);

void Px_DsSetPosition(PaStream* pa_stream, float x, float y, float z);
void Px_DsGetPosition(PaStream* pa_stream, float* x, float* y, float* z);

void Px_DsSetPan(PaStream* pa_stream, int x);
int Px_DsGetPan(PaStream* pa_stream);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
