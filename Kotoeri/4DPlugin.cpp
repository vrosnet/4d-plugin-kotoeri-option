/* --------------------------------------------------------------------------------
 #
 #	4DPlugin.cpp
 #	source generated by 4D Plugin Wizard
 #	Project : Kotoeri Option
 #	author : miyako
 #	2015/06/08
 #
 # --------------------------------------------------------------------------------*/


#include "4DPluginAPI.h"
#include "4DPlugin.h"

void PluginMain(PA_long32 selector, PA_PluginParameters params)
{
	try
	{
		PA_long32 pProcNum = selector;
		sLONG_PTR *pResult = (sLONG_PTR *)params->fResult;
		PackagePtr pParams = (PackagePtr)params->fParameters;

		CommandDispatcher(pProcNum, pResult, pParams); 
	}
	catch(...)
	{

	}
}

void CommandDispatcher (PA_long32 pProcNum, sLONG_PTR *pResult, PackagePtr pParams)
{
	switch(pProcNum)
	{
// --- Kotoeri

		case 1 :
			Kotoeri_Get_option(pResult, pParams);
			break;

		case 2 :
			Kotoeri_SET_OPTION(pResult, pParams);
			break;

	}
}

// ------------------------------------ Kotoeri -----------------------------------

void Kotoeri_Get_option(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT returnValue;

	Param1.fromParamAtIndex(pParams, 1);

    NSString *key = Param1.copyUTF16String();
    
    CFPropertyListRef value = CFPreferencesCopyAppValue((CFStringRef)key, kotoeri_app_id);

    if(value){
        
        if(CFGetTypeID(value) == CFStringGetTypeID()){
        
            returnValue.setUTF16String((NSString *)value);
            
        }else if(CFGetTypeID(value) == CFNumberGetTypeID()){
        
            returnValue.setUTF16String([(NSNumber *)value stringValue]);
        
        }else if(CFGetTypeID(value) == CFBooleanGetTypeID()){
        
            returnValue.setUTF16String([[NSNumber numberWithBool:CFBooleanGetValue((CFBooleanRef)value)]stringValue]);
        
        }
        
        CFRelease(value);
    }

    [key release];
    
	returnValue.setReturn(pResult);
}

void Kotoeri_SET_OPTION(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT Param3;

	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);

    NSString *key = Param1.copyUTF16String();
    NSString *value = Param2.copyUTF16String();
            
    switch(Param3.getIntValue()){
    
        case TYPE_Is_text:
        case TYPE_Is_string:  
        case TYPE_Is_alpha:  
            CFPreferencesSetAppValue(
            (CFStringRef)key, 
            (CFStringRef)value,
            kotoeri_app_id);            
        break;
        
        case TYPE_Is_long:   
            CFPreferencesSetAppValue(
            (CFStringRef)key, 
            (CFNumberRef)[NSNumber numberWithLongLong:[value longLongValue]],
            kotoeri_app_id);
        break;  
                    
        case TYPE_Is_int:   
            CFPreferencesSetAppValue(
            (CFStringRef)key, 
            (CFNumberRef)[NSNumber numberWithInt:[value intValue]],
            kotoeri_app_id);
        break;   
        
        case TYPE_Is_short:
            CFPreferencesSetAppValue(
            (CFStringRef)key, 
            (CFNumberRef)[NSNumber numberWithInteger:[value integerValue]],
            kotoeri_app_id);
        break;                                
        
        case TYPE_Is_real: 
            CFPreferencesSetAppValue(
            (CFStringRef)key, 
            (CFNumberRef)[NSNumber numberWithDouble:[value doubleValue]],
            kotoeri_app_id);
        break;              
        
        case TYPE_Is_boolean:   
            CFPreferencesSetAppValue(
            (CFStringRef)key, 
            (CFNumberRef)[NSNumber numberWithBool:[value boolValue]],
            kotoeri_app_id);
        break;  
        
    }

    [value release];        
    [key release];
    
    if(!CFPreferencesAppSynchronize(kotoeri_app_id)){
        NSLog(@"Kotoeri Option[4D]:%@", @"Failed to updated com.apple.inputmethod.Kotoeri.plist");
    }

}