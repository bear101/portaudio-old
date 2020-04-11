#include "pa_win_ds_dynlink.h"

//added by bdr

int GetDSoundDeviceWaveDeviceID(const GUID* dsguid, int capture)
{
    typedef HRESULT (CALLBACK *DllGetClassObjectFunc)(REFCLSID clsid, REFIID iid, LPVOID *ppv);

    DllGetClassObjectFunc DllGetClassObject = (DllGetClassObjectFunc)
        GetProcAddress( paWinDsDSoundEntryPoints.hInstance_, "DllGetClassObject"); 

    if(!DllGetClassObject)
        return -1;

    HRESULT hr;
    LPCLASSFACTORY pClassFactory = NULL; 
    LPKSPROPERTYSET pKsPropertySet;

    GUID CLSID_DirectSoundPrivate_ = GUID_NULL;
    hr = CLSIDFromString(OLESTR("{11AB3EC0-25EC-11d1-A4D8-00C04FC28ACA}" /*CLSID_DirectSoundPrivate*/), 
        &CLSID_DirectSoundPrivate_);

    hr = DllGetClassObject(CLSID_DirectSoundPrivate_, 
        IID_IClassFactory, 
        (LPVOID *)&pClassFactory);

    // Create the DirectSoundPrivate object and query for an IKsPropertySet 
    // interface 
    if(!SUCCEEDED(hr))
        return -1;

    hr = pClassFactory->CreateInstance ( NULL, IID_IKsPropertySet, 
                            (LPVOID *)&pKsPropertySet);
    if(!SUCCEEDED(hr))
    {
        pClassFactory->Release();
        return -1;
    }

    ULONG bytesReturned = 0;
    GUID DSPROPSETID_DirectSoundDevice_ = GUID_NULL;
    hr = CLSIDFromString(OLESTR("{84624F82-25EC-11d1-A4D8-00C04FC28ACA}" /*DSPROPSETID_DirectSoundDevice*/), 
        &DSPROPSETID_DirectSoundDevice_);

    DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_DATA descrip;
    descrip.DeviceId = *dsguid;
    descrip.DataFlow = capture?DIRECTSOUNDDEVICE_DATAFLOW_CAPTURE:DIRECTSOUNDDEVICE_DATAFLOW_RENDER;
    hr = pKsPropertySet->Get(DSPROPSETID_DirectSoundDevice_, 
        DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION, NULL, 0, 
        &descrip, sizeof(descrip), &bytesReturned);

    ULONG waveid = descrip.WaveDeviceId;

    pClassFactory->Release();
    pKsPropertySet->Release();

    if(SUCCEEDED(hr))
        return waveid;
    return -1;
}

//end bdr