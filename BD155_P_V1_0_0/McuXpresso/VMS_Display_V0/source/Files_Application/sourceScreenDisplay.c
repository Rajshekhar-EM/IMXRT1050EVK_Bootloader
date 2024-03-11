#include "sourceScreenDisplay.h"

void ProcessDisplayData(void)
{
	void (*funcScreenPtr[])(void) = {ProcessScreen00, ProcessScreen01, ProcessScreen02, ProcessScreen03,  ProcessScreen04,
									 ProcessScreen05, ProcessScreen06, ProcessScreen07, ProcessScreen08,  ProcessScreen09,
									 ProcessScreen10, ProcessScreen11, ProcessScreen12, ProcessScreen13,  ProcessScreen14,
									 ProcessScreen15, ProcessScreen16, ProcessScreen17, ProcessScreen18,  ProcessScreen19,
									 ProcessScreen20, ProcessScreen21, ProcessScreen22, ProcessScreen23,  ProcessScreen24,
									 ProcessScreen25, ProcessScreen26, ProcessScreen27, ProcessScreen28,  ProcessScreen29,
									 ProcessScreen30, ProcessScreen31,ProcessScreen32,
									};
	(*funcScreenPtr[giScreenSwitch])();
}

void ProcessScreen00(void)
{}
void ProcessScreen01(void)
{}
void ProcessScreen02(void)
{}
void ProcessScreen03(void)
{}
void ProcessScreen04(void)
{}
void ProcessScreen05(void)
{}
void ProcessScreen23(void)
{}
void ProcessScreen24(void)
{}
void ProcessScreen25(void)
{}
/* Main Screen */
void ProcessScreen06(void)
{
	switch(gucKeyPressed)
	{
		case KEY_ONE	:
							if(giNaviPopUp == 1)
							{
								giNaviPopUp = 0;
								giIntensityPopUp	= 0;
								giDMPopUp 			= 0;
								/*********added on 29.10.2022 By Rajashekhar*********/
								if(giMode == 1)
								{
									Homescreen_select_night();
								}
								else
								{
									Homescreen_select_day();
								}
							}
							else
							{

							}
							break;
		case KEY_TWO	:
							if(giNaviPopUp == 1)
							{
								giNaviPopUp=0;
								giIntensityPopUp	= 0;
								if(giMode == 0)
								{
									giMode = 1;
								}
								else
								{
									giMode = 0;
								}

								Writedataintofram(MODE);

								if(giMode == 1)
								{
									giScreenSwitch = 26;
								}
								else
								{
									giScreenSwitch = 6;
								}
								Read_brightness_from_FRAM();
								set_brightness(giIntensityPercent);
							}
							break;
		case KEY_THREE	:

							break;
		case KEY_FOUR	:
							if(giDMPopUp == 1)
							{
								previous_button_pressed = 1;

								if(err_index < 1)
								{
									err_index = (NO_OF_DM1_MESSAGES - 1);
								}
								else
								{
									err_index--;
								}
							}
							else
							{
								/* RAW ADC - IO 2 SCREEN */
								//giScreenSwitch = 9;
								giNaviPopUp 		= 0;
								giDMPopUp 			= 0;
								giIntensityPopUp	= 0;
								gucDm1FaultPtr		= 0;

								if(digi_onoff_status == ON)
								{
									giScreenSwitch = 9;
								}
								else if(analog_onoff_status == ON)
								{
									giScreenSwitch = 8;
								}
								else if(giMode == 1)
								{
									if(trans_onoff_status == ON)
									{
										giScreenSwitch = 27;
									}
									else if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 26;//This will be change in the future
									}
									else
									{
										giScreenSwitch = 26;
									}
								}
								else
								{
									if(trans_onoff_status == ON)
									{
										giScreenSwitch = 7;
									}
									else if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 6;//This will be change in future
									}
									else
									{
										giScreenSwitch = 6;
									}
								}
							}
							break;
		case KEY_FIVE	:
							/*
							if(giDMPopUp == 1)
							{
								bDm1FaultPtr = 1;
							}
							else
							{
								if(gucFaultsActive == 1)
								{
									giDMPopUp = 1;
									bDm1FaultPtr = 1;
								}
							}
							*/
							if(giDMPopUp == 1)
							{
								giDMPopUp = 0;

								err_index = 0;

								next_button_pressed = 0;
								previous_button_pressed = 0;

								Currnt_err_no 	= 0;
							}
							else if(gucFaultsActive == 1)
							{
								giDMPopUp = 1;

								err_index = 0;

								next_button_pressed = 1;
								previous_button_pressed = 0;

								Currnt_err_no 	= 0;
							}
							break;
		case KEY_SIX	:
							if(giNaviPopUp == 1)
							{
								giIntensityPopUp = 1;

								giIntensityPercent = giIntensityPercent + 10;
								if(giIntensityPercent > 100)
								{
									giIntensityPercent = 100;
								}
								Write_brightness_to_FRAM();
								set_brightness(giIntensityPercent);
							}
							break;
		case KEY_SEVEN	:
							if(giNaviPopUp == 1)
							{
								giIntensityPopUp = 1;

								giIntensityPercent = giIntensityPercent - 10;
								if(giIntensityPercent < 0)
								{
									giIntensityPercent = 0;
								}
								Write_brightness_to_FRAM();
								set_brightness(giIntensityPercent);
							}
							break;
		case KEY_EIGHT	:
							if(giDMPopUp == 1)
							{
								next_button_pressed = 1;

								if(err_index >= (NO_OF_DM1_MESSAGES - 1))
								{
									err_index = 0;
								}
								else
								{
									err_index++;
								}
							}
							else
							{
								/* ADC GUAGE SCREEN */
								if(giMode == 1)
								{
									//giScreenSwitch = 27;
									if(trans_onoff_status == ON)
									{
										giScreenSwitch = 27;
									}
									else if(analog_onoff_status == ON)
									{
										giScreenSwitch = 8;
									}
									else if(digi_onoff_status == ON)
									{
										giScreenSwitch = 9;
									}
									else if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 26;//This will be change in the future
									}
									else
									{
										giScreenSwitch = 26;
									}
								}
								else
								{
									//giScreenSwitch = 7;
									if(trans_onoff_status == ON)
									{
										giScreenSwitch = 7;
									}
									else if(analog_onoff_status == ON)
									{
										giScreenSwitch = 8;
									}
									else if(digi_onoff_status == ON)
									{
										giScreenSwitch = 9;
									}
									else if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 6;//This will be change in the future
									}
									else
									{
										giScreenSwitch = 6;
									}
								}

								giNaviPopUp 		= 0;
								giDMPopUp 			= 0;
								giIntensityPopUp	= 0;
								gucDm1FaultPtr		= 0;
							}
							break;
		case KEY_MENU	:

							if(giNaviPopUp == 1 || giDMPopUp == 1 || giIntensityPopUp == 1)
							{
								giNaviPopUp 		= 0;
								giDMPopUp 			= 0;
								giIntensityPopUp	= 0;
							}
							else
							{
								/* PASSWORD SCREEN */
								giScreenSwitch = 10;
								guiIconScreen=0;
							}
							break;
		case KEY_ENTER	:
							giNaviPopUp = 1;
							break;
		default 		:
							break;
	}
}
/* Main Screen 2 */
void ProcessScreen07(void)
{
	switch(gucKeyPressed)
	{
		case KEY_ONE	:
							if(giNaviPopUp == 1)
							{
								giNaviPopUp = 0;
								giIntensityPopUp	= 0;
								giDMPopUp 			= 0;
								/*********added on 29.10.2022 By Rajashekhar*********/
								if(giMode == 1)
								{
									Homescreen_select_night();
								}
								else
								{
									Homescreen_select_day();
								}
							}
							else
							{}
							break;
		case KEY_TWO	:
							if(giNaviPopUp == 1)
							{
								giNaviPopUp=0;
								giIntensityPopUp	= 0;
								if(giMode == 0)
								{
									giMode = 1;
								}
								else
								{
									giMode = 0;
								}

								Writedataintofram(MODE);

								if(giMode == 1)
								{
									giScreenSwitch = 27;
								}
								else
								{
									giScreenSwitch = 7;
								}
								Read_brightness_from_FRAM();
								set_brightness(giIntensityPercent);
							}
							break;
		case KEY_THREE	:

							break;
		case KEY_FOUR	:
							if(giDMPopUp == 1)
							{
								previous_button_pressed = 1;

								if(err_index < 1)
								{
									err_index = (NO_OF_DM1_MESSAGES - 1);
								}
								else
								{
									err_index--;
								}
							}
							else
							{
								/* Main SCREEN */
								if(giMode == 1)
								{
									//giScreenSwitch = 26;
									if(speedo_onoff_status == ON)
									{
										giScreenSwitch = 26;
									}
									else if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 26;//This will be change in the future
									}
									else if(digi_onoff_status == ON)
									{
										giScreenSwitch = 9;
									}
									else if(analog_onoff_status == ON)
									{
										giScreenSwitch = 8;
									}
									else
									{
										giScreenSwitch = 27;
									}
								}
								else
								{
									//giScreenSwitch = 6;
									if(speedo_onoff_status == ON)
									{
										giScreenSwitch = 6;
									}
									else if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 6;//This will be change in the future
									}
									else if(digi_onoff_status == ON)
									{
										giScreenSwitch = 9;
									}
									else if(analog_onoff_status == ON)
									{
										giScreenSwitch = 8;
									}
									else
									{
										giScreenSwitch = 7;
									}
								}
								giNaviPopUp 		= 0;
								giDMPopUp 			= 0;
								giIntensityPopUp	= 0;
							}
							break;
		case KEY_FIVE	:
							/*
							if(giDMPopUp == 1)
							{
								bDm1FaultPtr = 1;
							}
							else
							{
								if(gucFaultsActive == 1)
								{
									giDMPopUp = 1;
									bDm1FaultPtr = 1;
								}
							}
							*/
							if(giDMPopUp == 1)
							{
								giDMPopUp = 0;

								err_index = 0;

								next_button_pressed = 0;
								previous_button_pressed = 0;

								Currnt_err_no 	= 0;
							}
							else if(gucFaultsActive == 1)
							{
								giDMPopUp = 1;

								err_index = 0;

								next_button_pressed = 1;
								previous_button_pressed = 0;

								Currnt_err_no 	= 0;
							}
							break;
		case KEY_SIX	:
							if(giNaviPopUp == 1)
							{
								giIntensityPopUp = 1;

								giIntensityPercent = giIntensityPercent + 10;
								if(giIntensityPercent > 100)
								{
									giIntensityPercent = 100;
								}
								Write_brightness_to_FRAM();
								set_brightness(giIntensityPercent);
							}
							break;
		case KEY_SEVEN	:
							if(giNaviPopUp == 1)
							{
								giIntensityPopUp = 1;

								giIntensityPercent = giIntensityPercent - 10;
								if(giIntensityPercent < 0)
								{
									giIntensityPercent = 0;
								}
								Write_brightness_to_FRAM();
								set_brightness(giIntensityPercent);
							}
							break;
		case KEY_EIGHT	:
							if(giDMPopUp == 1)
							{
								next_button_pressed = 1;

								if(err_index >= (NO_OF_DM1_MESSAGES - 1))
								{
									err_index = 0;
								}
								else
								{
									err_index++;
								}
							}
							else
							{
								/* Raw ADC1 SCREEN */
								//giScreenSwitch = 8;
								giNaviPopUp 		= 0;
								giDMPopUp 			= 0;
								giIntensityPopUp	= 0;

								if(analog_onoff_status == ON)
								{
									giScreenSwitch = 8;
								}
								else if(digi_onoff_status == ON)
								{
									giScreenSwitch = 9;
								}
								else if(giMode == 1)
								{
									if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 26;//This will be change in future
									}
									else if(speedo_onoff_status == ON)
									{
										giScreenSwitch = 26;
									}
									else
									{
										giScreenSwitch = 27;
									}
								}
								else
								{
									if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 6;//This will be change in future
									}
									else if(speedo_onoff_status == ON)
									{
										giScreenSwitch = 6;
									}
									else
									{
										giScreenSwitch = 7;
									}
								}
							}
							break;
		case KEY_MENU	:

							if(giNaviPopUp == 1 || giDMPopUp == 1 || giIntensityPopUp == 1)
							{
								giNaviPopUp 		= 0;
								giDMPopUp 			= 0;
								giIntensityPopUp	= 0;
							}
							else
							{
								/* PASSWORD SCREEN */
								giScreenSwitch = 10;
							}
							break;
		case KEY_ENTER	:
							giNaviPopUp = 1;
							break;
		default 		:
							break;
	}
}


/* Raw ADC IO 1 Screen */
void ProcessScreen08(void)
{
	switch(gucKeyPressed)
	{
		case KEY_ONE	:
							if(giNaviPopUp == 1)
							{
								giNaviPopUp = 0;
								giIntensityPopUp	= 0;
								giDMPopUp 			= 0;
								/*********added on 29.10.2022 By Rajashekhar*********/
								if(giMode == 1)
								{
									Homescreen_select_night();
								}
								else
								{
									Homescreen_select_day();
								}
							}
							else
							{}
							break;
		case KEY_TWO	:
							if(giNaviPopUp == 1)
							{
								giNaviPopUp=0;
								giIntensityPopUp	= 0;
								if(giMode == 0)
								{
									giMode = 1;
								}
								else
								{
									giMode = 0;
								}
								Writedataintofram(MODE);
							}
							break;
		case KEY_THREE	:

							break;
		case KEY_FOUR	:
							if(giDMPopUp == 1)
							{
								previous_button_pressed = 1;

								if(err_index < 1)
								{
									err_index = (NO_OF_DM1_MESSAGES - 1);
								}
								else
								{
									err_index--;
								}
							}
							else
							{
								/* Main 2 SCREEN */
								if(giMode == 1)
								{
									//giScreenSwitch = 27;
									if(trans_onoff_status == ON)
									{
										giScreenSwitch = 27;
									}
									else if(speedo_onoff_status == ON)
									{
										giScreenSwitch = 26;
									}
									else if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 26;//This will be changed in the future
									}
									else if(digi_onoff_status == ON)
									{
										giScreenSwitch = 9;
									}
									else
									{
										giScreenSwitch = 8;
									}
								}
								else
								{
									//giScreenSwitch = 7;
									if(trans_onoff_status == ON)
									{
										giScreenSwitch = 7;
									}
									else if(speedo_onoff_status == ON)
									{
										giScreenSwitch = 6;
									}
									else if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 6;//This will be changed in the future
									}
									else if(digi_onoff_status == ON)
									{
										giScreenSwitch = 9;
									}
									else
									{
										giScreenSwitch = 8;
									}
								}
								giNaviPopUp 		= 0;
								giDMPopUp 			= 0;
								giIntensityPopUp	= 0;
							}
							break;
		case KEY_FIVE	:
							/*
							if(giDMPopUp == 1)
							{
								bDm1FaultPtr = 1;
							}
							else
							{
								if(gucFaultsActive == 1)
								{
									giDMPopUp = 1;
									bDm1FaultPtr = 1;
								}
							}
							*/
							if(giDMPopUp == 1)
							{
								giDMPopUp = 0;

								err_index = 0;

								next_button_pressed = 0;
								previous_button_pressed = 0;

								Currnt_err_no 	= 0;
							}
							else if(gucFaultsActive == 1)
							{
								giDMPopUp = 1;

								err_index = 0;

								next_button_pressed = 1;
								previous_button_pressed = 0;

								Currnt_err_no 	= 0;
							}
							break;
		case KEY_SIX	:
							if(giNaviPopUp == 1)
							{
								giIntensityPopUp = 1;

								giIntensityPercent = giIntensityPercent + 10;
								if(giIntensityPercent > 100)
								{
									giIntensityPercent = 100;
								}
								set_brightness(giIntensityPercent);
							}
							break;
		case KEY_SEVEN	:
							if(giNaviPopUp == 1)
							{
								giIntensityPopUp = 1;
								giIntensityPercent = giIntensityPercent - 10;
								if(giIntensityPercent < 0)
								{
									giIntensityPercent = 0;
								}
								set_brightness(giIntensityPercent);
							}
							break;
		case KEY_EIGHT	:
							if(giDMPopUp == 1)
							{
								next_button_pressed = 1;

								if(err_index >= (NO_OF_DM1_MESSAGES - 1))
								{
									err_index = 0;
								}
								else
								{
									err_index++;
								}
							}
							else
							{
								/* Raw ADC 2 SCREEN */
								//giScreenSwitch = 9;
								giNaviPopUp 		= 0;
								giDMPopUp 			= 0;
								giIntensityPopUp	= 0;

								if(digi_onoff_status == ON)
								{
									giScreenSwitch = 9;
								}
								else if(giMode == 1)
								{
									if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 26;//This will be changed in the future
									}
									else if(speedo_onoff_status == ON)
									{
										giScreenSwitch = 26;
									}
									else if(trans_onoff_status == ON)
									{
										giScreenSwitch = 27;
									}
									else
									{
										giScreenSwitch = 8;
									}
								}
								else
								{
									if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 6;//This will be changed in the future
									}
									else if(speedo_onoff_status == ON)
									{
										giScreenSwitch = 6;
									}
									else if(trans_onoff_status == ON)
									{
										giScreenSwitch = 7;
									}
									else
									{
										giScreenSwitch = 8;
									}
								}
							}
							break;
		case KEY_MENU	:
							if(giNaviPopUp == 1 || giDMPopUp == 1 || giIntensityPopUp == 1)
							{
								giNaviPopUp 		= 0;
								giDMPopUp 			= 0;
								giIntensityPopUp	= 0;
							}
							else
							{
								/* PASSWORD SCREEN */
								giScreenSwitch = 10;
							}
							break;
		case KEY_ENTER	:
							giNaviPopUp = 1;
							break;
		default 		:
							break;
	}

}

/* Raw ADC IO 2 Screen */

void ProcessScreen09(void)
{
	switch(gucKeyPressed)
	{
		case KEY_ONE	:
							if(giNaviPopUp == 1)
							{
								giNaviPopUp = 0;
								giIntensityPopUp	= 0;
								giDMPopUp 			= 0;
								/*********added on 29.10.2022 By Rajashekhar*********/
								if(giMode == 1)
								{
									Homescreen_select_night();
								}
								else
								{
									Homescreen_select_day();
								}
							}
							else
							{}
							break;
		case KEY_TWO	:
							if(giNaviPopUp == 1)
							{
								giNaviPopUp=0;
								giIntensityPopUp	= 0;
								if(giMode == 0)
								{
									giMode = 1;
								}
								else
								{
									giMode = 0;
								}
								Writedataintofram(MODE);
							}
							break;
		case KEY_THREE	:
							break;
		case KEY_FOUR	:
							if(giDMPopUp == 1)
							{
								previous_button_pressed = 1;

								if(err_index < 1)
								{
									err_index = (NO_OF_DM1_MESSAGES - 1);
								}
								else
								{
									err_index--;
								}
							}
							else
							{
								/* RAW ADC - IO 1 SCREEN */
								//giScreenSwitch = 8;
								giNaviPopUp 		= 0;
								giDMPopUp 			= 0;
								giIntensityPopUp	= 0;

								if(analog_onoff_status == ON)
								{
									giScreenSwitch = 8;
								}
								else if(giMode == 1)
								{
									if(trans_onoff_status == ON)
									{
										giScreenSwitch = 27;
									}
									else if(speedo_onoff_status == ON)
									{
										giScreenSwitch = 26;
									}
									else if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 26;//This will be changed in the future
									}
									else
									{
										giScreenSwitch = 9;
									}
								}
								else
								{
									if(trans_onoff_status == ON)
									{
										giScreenSwitch = 7;
									}
									else if(speedo_onoff_status == ON)
									{
										giScreenSwitch = 6;
									}
									else if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 6;//This will be changed in the future
									}
									else
									{
										giScreenSwitch = 9;
									}
								}
							}
							break;
		case KEY_FIVE	:
							/*
							if(giDMPopUp == 1)
							{
								bDm1FaultPtr = 1;
							}
							else
							{
								if(gucFaultsActive == 1)
								{
									giDMPopUp = 1;
									bDm1FaultPtr = 1;
								}
							}
							*/
							if(giDMPopUp == 1)
							{
								giDMPopUp = 0;

								err_index = 0;

								next_button_pressed = 0;
								previous_button_pressed = 0;

								Currnt_err_no 	= 0;
							}
							else if(gucFaultsActive == 1)
							{
								giDMPopUp = 1;

								err_index = 0;

								next_button_pressed = 1;
								previous_button_pressed = 0;

								Currnt_err_no 	= 0;
							}
							break;
		case KEY_SIX	:
							if(giNaviPopUp == 1)
							{
								giIntensityPopUp = 1;

								giIntensityPercent = giIntensityPercent + 10;
								if(giIntensityPercent > 100)
								{
									giIntensityPercent = 100;
								}
								set_brightness(giIntensityPercent);
							}
							break;
		case KEY_SEVEN	:
							if(giNaviPopUp == 1)
							{
								giIntensityPopUp = 1;

								giIntensityPercent = giIntensityPercent - 10;
								if(giIntensityPercent < 0)
								{
									giIntensityPercent = 0;
								}
								set_brightness(giIntensityPercent);
							}
							break;
		case KEY_EIGHT	:
							if(giDMPopUp == 1)
							{
								next_button_pressed = 1;

								if(err_index >= (NO_OF_DM1_MESSAGES - 1))
								{
									err_index = 0;
								}
								else
								{
									err_index++;
								}
							}
							else
							{
								/* Main SCREEN */
								if(giMode == 1)
								{
									//giScreenSwitch = 26;
									if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 26;//This will be changed in the future
									}
									else if(speedo_onoff_status == ON)
									{
										giScreenSwitch = 26;
									}
									else if(trans_onoff_status == ON)
									{
										giScreenSwitch = 27;
									}
									else if(analog_onoff_status == ON)
									{
										giScreenSwitch = 8;
									}
									else
									{
										giScreenSwitch = 9;
									}
								}
								else
								{
									//giScreenSwitch = 6;
									if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 6;//This will be changed in the future
									}
									else if(speedo_onoff_status == ON)
									{
										giScreenSwitch = 6;
									}
									else if(trans_onoff_status == ON)
									{
										giScreenSwitch = 7;
									}
									else if(analog_onoff_status == ON)
									{
										giScreenSwitch = 8;
									}
									else
									{
										giScreenSwitch = 9;
									}
								}
								giNaviPopUp 		= 0;
								giDMPopUp 			= 0;
								giIntensityPopUp	= 0;
							}
							break;
		case KEY_MENU	:
							if(giNaviPopUp == 1 || giDMPopUp == 1 || giIntensityPopUp == 1)
							{
								giNaviPopUp 		= 0;
								giDMPopUp 			= 0;
								giIntensityPopUp	= 0;
							}
							else
							{
								/* PASSWORD SCREEN */
								giScreenSwitch = 10;
							}
							break;
		case KEY_ENTER	:
							giNaviPopUp = 1;
							break;
		default 		:
							break;
	}
}

/* Password Screen */
void ProcessScreen10(void)
{
	unsigned char lucLoop = 0;

	switch(gucKeyPressed)
	{
		case KEY_ONE	:   if(giInvalidPassword==1)
							{

							}
							else if(gucPasswordEnterCount < 5)
							{
								gucPasswordArray[gucPasswordEnterCount] = 1;
								gucCursorArray[gucPasswordEnterCount++] = 1;
							}
							break;
		case KEY_TWO	:	if(giInvalidPassword==1)
							{

							}
							else if(gucPasswordEnterCount < 5)
							{
								gucPasswordArray[gucPasswordEnterCount] = 2;
								gucCursorArray[gucPasswordEnterCount++] = 1;
							}
							break;
		case KEY_THREE	:	if(giInvalidPassword==1)
							{

							}
							else if(gucPasswordEnterCount < 5)
							{
								gucPasswordArray[gucPasswordEnterCount] = 3;
								gucCursorArray[gucPasswordEnterCount++] = 1;
							}
							break;
		case KEY_FOUR	:
							if(giInvalidPassword==1)
							{

							}
							else if(gucPasswordEnterCount < 5)
							{
								gucPasswordArray[gucPasswordEnterCount] = 4;
								gucCursorArray[gucPasswordEnterCount++] = 1;
							}
							break;
		case KEY_FIVE	:
							if(giInvalidPassword==1)
							{

							}
							else if(gucPasswordEnterCount < 5)
							{
								gucPasswordArray[gucPasswordEnterCount] = 5;
								gucCursorArray[gucPasswordEnterCount++] = 1;
							}
							break;
		case KEY_SIX	:
							if(giInvalidPassword==1)
							{

							}
							else if(gucPasswordEnterCount < 5)
							{
								gucPasswordArray[gucPasswordEnterCount] = 6;
								gucCursorArray[gucPasswordEnterCount++] = 1;
							}
							break;
		case KEY_SEVEN	:
							if(giInvalidPassword==1)
							{

							}
							else if(gucPasswordEnterCount < 5)
							{
								gucPasswordArray[gucPasswordEnterCount] = 7;
								gucCursorArray[gucPasswordEnterCount++] = 1;
							}
							break;
		case KEY_EIGHT	:
							if(giInvalidPassword==1)
							{

							}
							else if(gucPasswordEnterCount < 5)
							{
								gucPasswordArray[gucPasswordEnterCount] = 8;
								gucCursorArray[gucPasswordEnterCount++] = 1;
							}
							break;
		case KEY_MENU	:
							if(bRetryPwdEntry == 1)
							{
								giInvalidPassword=0;
								bRetryPwdEntry = 0;
								giPasswordRetry = 0;
							}
							else
							{
								if(giMode == 1)
								{
									//giScreenSwitch = 26;
									Homescreen_select_night();
								}
								else
								{
									//giScreenSwitch = 6;
									Homescreen_select_day();
								}
							}

							gucPasswordEnterCount = 0;
							memset(&gucPasswordArray,0,sizeof(gucPasswordArray));
							memset(&gucCursorArray,0,sizeof(gucCursorArray));
							break;
		case KEY_ENTER	:
							bPasswordTest = 1;

							for(lucLoop = 0; lucLoop < 5; lucLoop++)
							{
								if(gucPasswordArray[lucLoop] != gucSetPassword[lucLoop])
								{
									bPasswordTest = 0;
									break;
								}
							}
							if(bPasswordTest == 1)
							{
								/* Menu Screen */
								giScreenSwitch = 11;
								bRetryPwdEntry = 0;
								giPasswordRetry = 0;
								gucPasswordEnterCount = 0;
								memset(&gucPasswordArray,0,sizeof(gucPasswordArray));
								memset(&gucCursorArray,0,sizeof(gucCursorArray));
							}
							else
							{
								giInvalidPassword=1;
								bRetryPwdEntry = 1;
								giPasswordRetry = 1;
								gucPasswordEnterCount = 0;
								memset(&gucPasswordArray,0,sizeof(gucPasswordArray));
								memset(&gucCursorArray,0,sizeof(gucCursorArray));
							}
							break;
		default 		:
							break;
	}
}

/* Menu Screen */
void ProcessScreen11(void)
{
	switch(gucKeyPressed)
	{
		case KEY_ONE	:
							/* Main Screen */
							if(giMode == 1)
							{
								giScreenSwitch = 26;
							}
							else
							{
								giScreenSwitch = 6;
							}
							break;
		case KEY_TWO	:
							/* Diagnostic Screen */
							//giScreenSwitch = 12;
							guiDiagCounter=0;
							guiDiagCounttemp=0;
							guiDiagPopUp = 1;
							guiRequestDM1Data=0;
							guiDiagTimer=1;

							giScreenSwitch = 31;
							get_faults = 1;
							break;
		case KEY_THREE	:
							/* User Setting Screen */
							giScreenSwitch = 13;

							gcUserScroll = 0;
							guiDate		= strDateTime.Date;
							guiMonth	= strDateTime.Month;
							guiYear		= strDateTime.Year;
							guiHour		= strDateTime.Hour;
							guiMinute	= strDateTime.Minute;
							guiSecond	= strDateTime.Second;
							guiMeridian = strDateTime.Meredian;

							if(guiYear == 0)
							{
								guiYear = 2021;
							}

							vms.flag.screen_onoff_home_read = 1;
							guiselct_screen = 1;

							save_status = 0;
							break;
		case KEY_FOUR	:
							/* Utility Screen */
							giScreenSwitch = 14;
							break;
		case KEY_FIVE	:
							engfulrt_popup = 0;

							if(enghrs_popup == 1)
							{enghrs_popup = 0;}
							else
							{enghrs_popup = 1;}
							break;
		case KEY_SIX	:
						#ifdef DOZER_P_VER
							enghrs_popup = 0;
							engfulrt_popup = 0;
							/* Engine Hours Edit Screen */
							giScreenSwitch = 32;
							ehe_scroll = 0;
							adjd_eng_hrs = MemoryReadVariable(PRIMARY_MEMORY, ADJ_ENG_HRS, 4);
							enghrs_en_dis = MemoryReadVariable(PRIMARY_MEMORY, ENGHRS_EN_DIS, 1);
						#else
							enghrs_popup = 0;

							if(engfulrt_popup == 1)
							{engfulrt_popup = 0;}
							else
							{engfulrt_popup = 1;}
						#endif
							break;
		case KEY_SEVEN	:
							/* Shiftwise clock Setting Screen */
							giScreenSwitch = 29;
							swcs_cntr = 0;
							save_status = 0;
							read_swcs_data();
							break;
		case KEY_EIGHT	:
							/* Ststem Setting Screen */
							giScreenSwitch = 15;
							break;
		case KEY_MENU	:
							if(enghrs_popup == 1)
							{enghrs_popup = 0;}
							else if(engfulrt_popup == 1)
							{engfulrt_popup = 0;}
							else
							{
								/* Main Screen */
								guiDiagTimer=0;
								guiDiagCounter=0;
								guiDiagCounttemp=0;
								guiDiagPopUp = 0;
								guiRequestDM1Data=0;
								/*
								if(giMode == 1)
								{
									giScreenSwitch = 26;
								}
								else
								{
									giScreenSwitch = 6;
								}
								*/
								/*****************added on 29.10.2022 By Rajashekhar*********/
								read_onoff_home_setting_status();
								if(giMode == 1)
								{
									Homescreen_select_night();
								}
								else
								{
									Homescreen_select_day();
								}
							}
							break;
		case KEY_ENTER	:

							break;
		default 		:
							break;
	}
}

/* Diagnostic Screen */
void ProcessScreen12(void)
{
	switch(gucKeyPressed)
	{
		case KEY_ONE	:

							break;
		case KEY_TWO	:

							break;
		case KEY_THREE	:

							break;
		case KEY_FOUR	:

							break;
		case KEY_FIVE	:

							break;
		case KEY_SIX	:
							gcDiagScroll--;
							if(gcDiagScroll < 0 || gcDiagScroll > 250)
							{
								gcDiagScroll = 0;
							}
							break;
		case KEY_SEVEN	:
							gcDiagScroll++;
							if(gcDiagScroll > 9)
							{
								gcDiagScroll = 9;
							}
							break;
		case KEY_EIGHT	:

							break;
		case KEY_MENU	:
							/* Menu Screen */
							giScreenSwitch = 11;
							break;
		case KEY_ENTER	:

							break;
		default 		:
							break;
	}
}

/* User Setting Screen */
void ProcessScreen13(void)
{

	if(vms.flag.screen_onoff_home_read == 1)
	{
		vms.flag.screen_onoff_home_read = 0;
		read_screen_setting_data();
	}else{}

	switch(gucKeyPressed)
	{
		case KEY_ONE	:
							WarningPopUp=1;
							WarningMsg = 0;//You're ready discard your changes!!
							break;
		case KEY_TWO	:
							gcUserScroll--;
							if(gcUserScroll < 0 || gcUserScroll > 250)
							{
								gcUserScroll = 0;
							}
							break;
		case KEY_THREE	:
//							gcUserScroll++;
//							if(gcUserScroll > 8)
//							{
//								gcUserScroll = 8;
//							}
							gcUserScroll++;
							if(gcUserScroll > 11)
							{
								gcUserScroll = 11;
							}
							break;
		case KEY_FOUR	:

							break;
		case KEY_FIVE	:

							break;
		case KEY_SIX	:
							save_status = 0;
							switch(gcUserScroll)
							{
								case 0 :	if(giMode == 0)
											{
												giMode = 1;
											}
											else
											{
												giMode = 0;
											}
											Read_brightness_from_FRAM();
											break;
								case 1 :
											giIntensityPercent = giIntensityPercent + 10;
											if(giIntensityPercent > 100)
											{
												giIntensityPercent = 100;
											}
											Write_brightness_to_FRAM();
											break;
								case 2 :
											guiDate++;
											if(guiDate > 31)
											{
												guiDate = 1;
											}
											break;
								case 3 :
											guiMonth++;
											if(guiMonth > 12)
											{
												guiMonth = 1;
											}
											break;
								case 4 :
											guiYear++;
											break;
								case 5 :

											guiHour++;
											if(guiHour > 12)
											{
												guiHour = 1;
											}
											break;
								case 6 :
											guiMinute++;
											if(guiMinute > 59)
											{
												guiMinute = 0;
											}
											break;
								case 7 :
											guiSecond++;
											if(guiSecond > 59)
											{
												guiSecond = 0;
											}
											break;
								case 8 :
											guiMeridian++;
											if(guiMeridian >2)
											{
												guiMeridian = 1;
											}
											break;

								case 9 :   	guiselct_screen++;
											if(guiselct_screen > 5)
											{
												guiselct_screen = 1;
											}
											read_screen_setting_data();
											break;
								case 10 :
											guiscreen_on_off++;
											if(guiscreen_on_off > 1)
											{
												guiscreen_on_off = 0;
											}
											store_onoff_screen_sel_data();
											break;
								case 11 :
											guiselct_home_screen++;
											if(guiselct_home_screen > 1)
											{
												guiselct_home_screen = 0;
											}
											store_home_screen_sel_data();
											break;
							}
							break;
		case KEY_SEVEN	:
							save_status = 0;
							switch(gcUserScroll)
							{
								case 0 :	if(giMode == 0)
											{
												giMode = 1;
											}
											else
											{
												giMode = 0;
											}
											Read_brightness_from_FRAM();
											break;
								case 1 :
											giIntensityPercent = giIntensityPercent - 10;
											if(giIntensityPercent <= 0 || giIntensityPercent > 230)
											{
												giIntensityPercent = 0;
											}
											Write_brightness_to_FRAM();
											break;
								case 2 :
											guiDate--;
											if(guiDate < 1 || guiDate > 250)
											{
												guiDate = 31;
											}
											break;
								case 3 :
											guiMonth--;
											if(guiMonth < 1 || guiMonth > 250)
											{
												guiMonth = 12;
											}
											break;
								case 4 :
											guiYear--;
											break;
								case 5 :
											guiHour--;
											if(guiHour < 1 || guiHour > 250)
											{
												guiHour = 12;
											}
											break;
								case 6 :
											guiMinute--;
											if(guiMinute < 0 || guiMinute > 250)
											{
												guiMinute = 59;
											}
											break;
								case 7 :
											guiSecond--;
											if(guiSecond < 0 || guiSecond > 250)
											{
												guiSecond = 59;
											}
											break;
								case 8 :
											guiMeridian--;
											if(guiMeridian < 1 || guiMeridian > 250)
											{
												guiMeridian = 2;
											}
											break;

								case 9 :   	guiselct_screen--;
											if(guiselct_screen < 1 || guiselct_screen > 250)
											{
												guiselct_screen = 5;
											}
											read_screen_setting_data();
											break;
								case 10 :
											guiscreen_on_off--;
											if(guiscreen_on_off < 0 || guiscreen_on_off > 250)
											{
												guiscreen_on_off = 1;
											}
											store_onoff_screen_sel_data();
											break;
								case 11 :
											guiselct_home_screen--;
											if(guiselct_home_screen < 0 || guiselct_home_screen > 250)
											{
												guiselct_home_screen = 1;
											}
											store_home_screen_sel_data();
											break;
							}
							break;
		case KEY_EIGHT	:
							WriteRTC();
							Writedataintofram(MODE);

							/******By returning back to menu screen change the brightness with respect to which mode**/
							Read_brightness_from_FRAM();
							set_brightness(giIntensityPercent);
							/***************************************************************************************/
							save_status = 1;//DATA SAVED

							rtc_datetime_edited = 1;
							rtc_edited = 1;
							rtc_datetime_edited_enghrs = 1;
							break;
		case KEY_MENU	:
							if(WarningPopUp==1)
							{
								WarningPopUp=0;
							}
							else
							{
								//commented by Rajashekhar on 20231103
								//WriteRTC();
								//Writedataintofram(MODE);

								/* Menu Screen */
								giScreenSwitch = 11;

								save_status = 0;
							}
							read_onoff_home_setting_status();//added on 28.10.22
							/******By returning back to menu screen change the brightness with respect to which mode**/
							Read_brightness_from_FRAM();
							set_brightness(giIntensityPercent);
							/***************************************************************************************/
							break;
		case KEY_ENTER	:
			                if(WarningPopUp==1)
			                {
			                	WarningPopUp=0;

			                	/*Mode*/
								giMode = 0;/*Select to Day Mode*/
								/*Brightness*/
								giIntensityPercent = 50;/*set brightness to 50%*/
								Write_brightness_to_FRAM();
								set_brightness(giIntensityPercent);

								/*Real time Date and Time*/
								guiDate 	= strDateTime.Date;
								guiMonth	= strDateTime.Month;
								guiYear  	= strDateTime.Year;
								guiHour	 	= strDateTime.Hour;
								guiMinute	= strDateTime.Minute;
								guiSecond	= strDateTime.Second;
								guiMeridian = strDateTime.Meredian;

								/*Screen setting*/
								write_default_scr_sel_setting();
								vms.flag.screen_onoff_home_read = 1;//added on 28.10.2022
								guiselct_screen = 1;

								save_status = 1;
			                }
			                else
			                {}
							break;
		default 		:
							break;
	}
}
/* Utilities Screen */
void ProcessScreen14(void)
{
	volatile unsigned char  k = 0;
	switch(gucKeyPressed)
	{
		case KEY_ONE	:
							/* System Setup Screen */
							giScreenSwitch = 16;
							break;
		case KEY_TWO	:
							/* Service Reminder Screen */
							giScreenSwitch = 17;

						    /*SERVICE REMAINDER SCREEN*/
						    Service_remainder_hrs_calculation(giHourMeter);
							break;
		case KEY_THREE	:
							/* Password Setting Screen */
							giScreenSwitch = 18;
							for(k=0;k<5;k++)
							{
								gucprevSetPassword[k] = gucSetPassword[k];
							}
							break;
		case KEY_FOUR	:
							/* Identification Screen */
							giScreenSwitch = 19;
							//Read_identification_details();
							break;
		case KEY_FIVE	:
							/* WorkingHrsLogging Screen */
							giScreenSwitch = 30;
							start_pendrive_timeout=0;
							gucCopyStatus	  = IDLE;

							guiLogFileSize = Read_no_of_logs(START_SWWHLOG_LOC_WINBOND,SWWH_LOG_CURRENT_PTR,SWWH_LOG_LENGTH);
							break;
		case KEY_SIX	:
							/* Raw CAN Data Screen */
							giScreenSwitch = 20;
							giCloseOpenScreens = 10;
							bStartRawFrameLog 	= 0;
//							gucRecTimeCount 	= 0;
							guiRawLogCount		= 0;
							gucRecordingStatus  = 0;
							bStartRawFrameUsb 	= 0;
							guiLogFileSize		= 0;
							gucRecTimeCount		= 30;
							start_pendrive_timeout=0;
							timer_updated=0;

							gucCopyStatus	  	= IDLE;
							break;
		case KEY_SEVEN	:
							/* Min Max Log Screen */
							giScreenSwitch = 21;
							start_pendrive_timeout=0;
							gucCopyStatus	  = IDLE;

							guiLogFileSize = Read_no_of_logs(START_DATALOG_LOC_WINBOND,DATA_LOG_CURRENT_PTR,DATA_LOG_LENGTH);
							break;
		case KEY_EIGHT	:
							/* Fault Logging Screen */
							giScreenSwitch = 22;
							start_pendrive_timeout=0;
							gucCopyStatus	  = IDLE;

							guiLogFileSize = Read_no_of_logs(START_ERRORLOG_LOC_WINBOND,ERROR_LOG_CURRENT_PTR,ERROR_LOG_LENGTH);
							break;
		case KEY_MENU	:
							/* Menu Screen */
							giScreenSwitch = 11;
							break;
		case KEY_ENTER	:

							break;
		default 		:
							break;
	}
}


/* System Setting Screen */
void ProcessScreen15(void)
{
	switch(gucKeyPressed)
	{
		case KEY_ONE	:

							break;
		case KEY_TWO	:

							break;
		case KEY_THREE	:

							break;
		case KEY_FOUR	:

							break;
		case KEY_FIVE	:

							break;
		case KEY_SIX	:

							break;
		case KEY_SEVEN	:

							break;
		case KEY_EIGHT	:

							break;
		case KEY_MENU	:
							/* Main Menu Screen */
							giScreenSwitch = 11;
							break;
		case KEY_ENTER	:

							break;
		default 		:
							break;
	}
}

/* System Setup Screen */
void ProcessScreen16(void)
{
	switch(gucKeyPressed)
	{
		case KEY_ONE	:

							break;
		case KEY_TWO	:

							break;
		case KEY_THREE	:

							break;
		case KEY_FOUR	:

							break;
		case KEY_FIVE	:

							break;
		case KEY_SIX	:

							break;
		case KEY_SEVEN	:

							break;
		case KEY_EIGHT	:

							break;
		case KEY_MENU	:
							/* Utilities Screen */
							giScreenSwitch = 14;
							break;
		case KEY_ENTER	:

							break;
		default 		:
							break;
	}
}

/* Service Reminder Screen */
void ProcessScreen17(void)
{
	switch(gucKeyPressed)
	{
		case KEY_ONE	:

							break;
		case KEY_TWO	:
							/*
							if(gucEditService == 1)
							{
								switch(gcScrollSel)
								{
									case 0 :
												guiEngOilInterval++;
												break;
									case 1 :
												guiAirFilterInterval++;
												break;
									case 2 :
												guiHydOilInterval++;
												break;
									case 3 :
												guiSerEngInterval++;
												break;
									case 4 :
												guiSerMacInterval++;
												break;
								}
							}
							else
							*/
							{
								gcScrollSel--;
								if(gcScrollSel < 0 || gcScrollSel > 250)
								{
									gcScrollSel = 0;
								}
							}

							break;
		case KEY_THREE	:
							/*
							if(gucEditService == 1)
							{
								switch(gcScrollSel)
								{
									case 0 :
												guiEngOilInterval--;
												if(guiEngOilInterval < 0 || guiEngOilInterval > 500)
												{
													guiEngOilInterval = 500;
												}
												break;
									case 1 :
												guiAirFilterInterval--;
												if(guiAirFilterInterval < 0 || guiAirFilterInterval > 500)
												{
													guiAirFilterInterval = 500;
												}
												break;
									case 2 :
												guiHydOilInterval--;
												if(guiHydOilInterval < 0 || guiHydOilInterval > 500)
												{
													guiHydOilInterval = 500;
												}
												break;
									case 3 :
												guiSerEngInterval--;
												if(guiSerEngInterval < 0 || guiSerEngInterval > 500)
												{
													guiSerEngInterval = 500;
												}
												break;
									case 4 :
												guiSerMacInterval--;
												if(guiSerMacInterval < 0 || guiSerMacInterval > 500)
												{
													guiSerMacInterval = 500;
												}
												break;
								}
							}
							else
							*/
							{
								gcScrollSel++;
								if(gcScrollSel > 4)
								{
									gcScrollSel = 4;
								}
							}

							break;
		case KEY_FOUR	:

							break;
		case KEY_FIVE	:

							break;
		case KEY_SIX	:
							if(gucEditService == 0)
							{
								gucEditService = 1;

								giScreenSwitch = 28;/*added on 02.11.2022*/
								gcCharSelect = 0;
								gucChCount = 0;
								guiXAxis = 132;
								guiYAxis = 154;
								gcAlphabetSel = 0;

								use_only_numericals = 1;
							}
							else
							{
								gucEditService = 0;
							}
							break;
		case KEY_SEVEN	:

							break;

		case KEY_EIGHT	:   /*
							guiEngOilInterval = 250;
							guiAirFilterInterval = 250;
							guiHydOilInterval = 250;
							guiSerEngInterval = 250;
							guiSerMacInterval = 250;

							guiEngOilNext = 250;
							guiAirFilterNext = 250;
							guiHydOilNext = 250;
							guiSerEngNext = 250;
							guiSerMacNext = 250;

							guiEngOilRemain = 250;
							guiAirFilterRemain = 250;
							guiHydOilRemain = 250;
							guiSerEngRemain = 250;
							guiSerMacRemain = 250;
							*/
							guiEngOilInterval = 250;
							MemoryWriteVariable(PRIMARY_MEMORY, CHANGE_ENGINE_OIL_INTERVAL_ADDR, guiEngOilInterval, 2);
							guiAirFilterInterval = 250;
							MemoryWriteVariable(PRIMARY_MEMORY, CHANGE_AIRFILTERS_INTERVAL_ADDR, guiAirFilterInterval, 2);
							guiHydOilInterval = 250;
							MemoryWriteVariable(PRIMARY_MEMORY, CHANGE_HYDRAULIC_OIL_INTERVAL_ADDR, guiHydOilInterval, 2);
							guiSerEngInterval = 250;
							MemoryWriteVariable(PRIMARY_MEMORY, SERVICE_ENGINE_INTERVAL_ADDR, guiSerEngInterval, 2);
							guiSerMacInterval = 250;
							MemoryWriteVariable(PRIMARY_MEMORY, SERVICE_MACHINE_INTERVAL_ADDR, guiSerMacInterval, 2);

							guiEngOilNext = guiEngOilInterval;
							guiAirFilterNext = guiAirFilterInterval;
							guiHydOilNext = guiHydOilInterval;
							guiSerEngNext = guiSerEngInterval;
							guiSerMacNext = guiSerMacInterval;

							guiEngOilRemain = guiEngOilInterval;
							guiAirFilterRemain = guiAirFilterInterval;
							guiHydOilRemain = guiHydOilInterval;
							guiSerEngRemain = guiSerEngInterval;
							guiSerMacRemain = guiSerMacInterval;
							break;
		case KEY_MENU	:
							/* Utilities Screen */
							giScreenSwitch = 14;
							gcScrollSel = 0;
							break;
		case KEY_ENTER	:

							break;
		default 		:
							break;
	}
}

/* Password Setting Screen Screen */
void ProcessScreen18(void)
{
	unsigned char lucLoop = 0;
	unsigned char k=0;

	switch(gucKeyPressed)
	{
		case KEY_ONE	:
							if(gucPasswordEnterCount < 5)
							{
								gucSetPassword[gucPasswordEnterCount] = 1;
								gucCursorArray[gucPasswordEnterCount++] = 1;
							}
							break;
		case KEY_TWO	:
							if(gucPasswordEnterCount < 5)
							{
								gucSetPassword[gucPasswordEnterCount] = 2;
								gucCursorArray[gucPasswordEnterCount++] = 1;
							}
							break;
		case KEY_THREE	:
							if(gucPasswordEnterCount < 5)
							{
								gucSetPassword[gucPasswordEnterCount] = 3;
								gucCursorArray[gucPasswordEnterCount++] = 1;
							}
							break;
		case KEY_FOUR	:
							if(gucPasswordEnterCount < 5)
							{
								gucSetPassword[gucPasswordEnterCount] = 4;
								gucCursorArray[gucPasswordEnterCount++] = 1;
							}
							break;
		case KEY_FIVE	:
							if(gucPasswordEnterCount < 5)
							{
								gucSetPassword[gucPasswordEnterCount] = 5;
								gucCursorArray[gucPasswordEnterCount++] = 1;
							}
							break;
		case KEY_SIX	:
							if(gucPasswordEnterCount < 5)
							{
								gucSetPassword[gucPasswordEnterCount] = 6;
								gucCursorArray[gucPasswordEnterCount++] = 1;
							}
							break;
		case KEY_SEVEN	:
							if(gucPasswordEnterCount < 5)
							{
								gucSetPassword[gucPasswordEnterCount] = 7;
								gucCursorArray[gucPasswordEnterCount++] = 1;
							}
							break;
		case KEY_EIGHT	:
							if(gucPasswordEnterCount < 5)
							{
								gucSetPassword[gucPasswordEnterCount] = 8;
								gucCursorArray[gucPasswordEnterCount++] = 1;
							}
							break;
		case KEY_MENU	:
							if(bRetryPwdEntry == 1)
							{
								bRetryPwdEntry = 0;
								giPasswordRetry = 0;
							}
							else
							{
								/* Utilities Screen */
								giScreenSwitch = 14;

								for(k=0;k<5;k++)
								{
									gucSetPassword[k]=gucprevSetPassword[k];
								}
							}

							gucPasswordEnterCount = 0;
							memset(&gucPasswordArray,0,sizeof(gucPasswordArray));
							memset(&gucCursorArray,0,sizeof(gucCursorArray));
							break;
		case KEY_ENTER	:
							bPasswordTest = 1;

							if(gucPasswordEnterCount < 5)
							{
								bPasswordTest = 0;
							}

							if(bPasswordTest == 1)
							{
								/* Utilities Screen */
								giScreenSwitch = 14;

								gucPasswordEnterCount = 0;
								bRetryPwdEntry = 0;
								giPasswordRetry = 0;
								memset(&gucCursorArray,0,sizeof(gucCursorArray));
								Writedataintofram(PASSWORD);
							}
							else
							{
								bRetryPwdEntry = 1;
								giPasswordRetry = 1;
								gucPasswordEnterCount = 0;

//								gucSetPassword[0] = 4;
//								gucSetPassword[1] = 3;
//								gucSetPassword[2] = 3;
//								gucSetPassword[3] = 2;
//								gucSetPassword[4] = 8;

								memset(&gucPasswordArray,0,sizeof(gucPasswordArray));
								memset(&gucCursorArray,0,sizeof(gucCursorArray));
							}
							break;
		default 		:
							break;
	}
}


/* Identification Screen */
void ProcessScreen19(void)
{
	switch(gucKeyPressed)
	{
		case KEY_ONE	:

							break;
		case KEY_TWO	:
							gcScrollSel--;
							if(gcScrollSel < 0 || gcScrollSel > 250)
							{
								gcScrollSel = 4;
							}
							break;
		case KEY_THREE	:
							gcScrollSel++;
							if(gcScrollSel > 4)
							{
								gcScrollSel = 0;
							}
							break;
		case KEY_FOUR	:

							break;
		case KEY_FIVE	:

							break;
		case KEY_SIX	:
							/* Text Edit Screen */
							giScreenSwitch = 28;
							gcCharSelect = 0;
							gucChCount = 0;
							guiXAxis = 132;
							guiYAxis = 154;
							gcAlphabetSel = 0;

							use_only_numericals = 0;
							break;
		case KEY_SEVEN	:

							break;
		case KEY_EIGHT	:

							break;
		case KEY_MENU	:
							/* Utilities Screen */
							giScreenSwitch = 14;
							gcScrollSel   = 0;
							break;
		case KEY_ENTER	:
							break;
		default 		:
							break;
	}
}


/* Raw Can Data Screen */
void ProcessScreen20(void)
{
	switch(gucKeyPressed)
	{
		case KEY_ONE	:

							break;
		case KEY_TWO	:
							if(bStartRawFrameLog == 0)
							{
								gucRecTimeCount = 30;
								bStartRawFrameLog = 1;
								gucRecordingStatus = 1;
								guiLogFileSize		= 0;
								gucCopyStatus = 0;
							}
							else
							{

							}
							break;
		case KEY_THREE	:

							break;
		case KEY_FOUR	:

							break;
		case KEY_FIVE	:

							break;
		case KEY_SIX	:

							break;
		case KEY_SEVEN	:
							if(bStartRawFrameUsb == 0)
							{
								bStartRawFrameUsb = 1;
								//gucCopyStatus	  = 1;
								gucCopyStatus	  	= IDLE;
								//if(SDCardfuncBegin==0)
								{
									guiPendrivePoPup=1;
									guiPendriveStatus = DETECTING_PENDRIVE;
									start_pendrive_timeout=1;
									pendrivestatuscounter=0;
									pendrivestatusstrttimer=0;
									popeup_out_once=1;
								}
								#ifdef PENDRIVE_USED
								#else
									usb_attached = 1;
								#endif
							}
							break;
		case KEY_EIGHT	:
			                if(unlink_rawCandatalog==0)
			                {
			                	unlink_rawCandatalog=1;
			                	guiPendrivePoPup=1;
								pendrivestatusstrttimer=1;
			                }
							break;
		case KEY_MENU	:
							/* Utilities Screen */
							giScreenSwitch = 14;

							bStartRawFrameLog 	= 0;
//							gucRecTimeCount 	= 0;
							guiRawLogCount		= 0;
							gucRecordingStatus  = 0;
							bStartRawFrameUsb 	= 0;
							guiLogFileSize		= 0;
							gucRecTimeCount		= 30;
							start_pendrive_timeout=0;
							pendrive_counter_timeout=0;
							pendrive_detected_timeout=0;
							guiPendrivePoPup=0;
							guiPendriveStatus = DETECTING_PENDRIVE;
							pendrivestatusstrttimer=0;
							pendrivestatuscounter=0;

							gucCopyStatus	  	= IDLE;
							break;
		case KEY_ENTER	:

							break;
		default 		:
							break;
	}
}

/* Data Logging Screen */
void ProcessScreen21(void)
{
	switch(gucKeyPressed)
	{
		case KEY_ONE	:

							break;
		case KEY_TWO	:

							break;
		case KEY_THREE	:

							break;
		case KEY_FOUR	:

							break;
		case KEY_FIVE	:

							break;
		case KEY_SIX	:

							break;
		case KEY_SEVEN	:
#ifdef MIN_MAX_LOGGING_REQ
							if(bStartMinMaxFrameLog == 0)
							{
								bStartMinMaxFrameLog = 1;
//								gucCopyStatus	  	 = 1;
								if(SDCardfuncBegin==0)
								{
									guiPendrivePoPup=1;
									guiPendriveStatus = DETECTING_PENDRIVE;
									start_pendrive_timeout=1;
									pendrivestatusstrttimer=0;
									pendrivestatuscounter=0;
									popeup_out_once=1;
								}
							}
#else
							if(bStartDataLogging == 0)
							{
								bStartDataLogging = 1;
								//gucCopyStatus	  	 = 1;
								gucCopyStatus	  	= IDLE;
								//if(SDCardfuncBegin==0)
								{
									guiPendrivePoPup=1;
									guiPendriveStatus = DETECTING_PENDRIVE;
									start_pendrive_timeout=1;
									pendrivestatusstrttimer=0;
									pendrivestatuscounter=0;
									popeup_out_once=1;
								}
								#ifdef PENDRIVE_USED
								#else
									usb_attached = 1;
								#endif
							}
#endif
							break;
		case KEY_EIGHT	:
							if(unlink_datalog==0)
							{
								unlink_datalog=1;
			                	guiPendrivePoPup=1;
								pendrivestatusstrttimer=1;
							}
							break;
		case KEY_MENU	:
							/* Utilities Screen */
							giScreenSwitch = 14;
#ifdef MIN_MAX_LOGGING_REQ
							bStartMinMaxFrameLog = 0;
#else
							bStartDataLogging=0;
#endif
							guiLogFileSize		 = 0;
							start_pendrive_timeout=0;
							pendrive_counter_timeout=0;
							pendrive_detected_timeout=0;
							guiPendrivePoPup=0;
							guiPendriveStatus = DETECTING_PENDRIVE;
							pendrivestatusstrttimer=0;
							pendrivestatuscounter=0;
							popeup_out_once=0;

							gucCopyStatus	  	= IDLE;
							break;
		case KEY_ENTER	:

							break;
		default 		:
							break;
	}
}

/* Fault Log Screen */
void ProcessScreen22(void)
{
	switch(gucKeyPressed)
	{
		case KEY_ONE	:

							break;
		case KEY_TWO	:
							if(bStartFaultFrameLog == 0)
							{
								bStartFaultFrameLog  = 1;
								gucRecordingStatus	 = 1;
							}
							break;
		case KEY_THREE	:

							break;
		case KEY_FOUR	:

							break;
		case KEY_FIVE	:

							break;
		case KEY_SIX	:

							break;
		case KEY_SEVEN	:
							if(bStartFaultFrameUsb == 0)
							{
								bStartFaultFrameUsb = 1;
								//gucCopyStatus	  = 1;
								gucCopyStatus	  	= IDLE;
								//if(SDCardfuncBegin==0)
								{
									guiPendrivePoPup=1;
									guiPendriveStatus = DETECTING_PENDRIVE;
									start_pendrive_timeout=1;
									pendrivestatusstrttimer=0;
									pendrivestatuscounter=0;
									popeup_out_once=1;
								}
								#ifdef PENDRIVE_USED
								#else
									usb_attached = 1;
								#endif
							}
							break;
		case KEY_EIGHT	:
			                if(unlink_faultlog==0)
			                {
			                	unlink_faultlog=1;
			                	guiPendrivePoPup=1;
								pendrivestatusstrttimer=1;
			                }
							break;
		case KEY_MENU	:
							/* Utilities Screen */
							giScreenSwitch = 14;
							bStartFaultFrameUsb = 0;
							bStartFaultFrameLog = 0;
							gucRecordingStatus  = 0;
							guiLogFileSize		= 0;
							start_pendrive_timeout=0;
							pendrive_counter_timeout=0;
							pendrive_detected_timeout=0;
							guiPendrivePoPup=0;
							guiPendriveStatus = DETECTING_PENDRIVE;
							pendrivestatusstrttimer=0;
							pendrivestatuscounter=0;
							popeup_out_once=0;

							gucCopyStatus	  	= IDLE;
							break;
		case KEY_ENTER	:

							break;
		default 		:
							break;
	}
}

/* Night Main Screen */
void ProcessScreen26(void)
{
	switch(gucKeyPressed)
	{
		case KEY_ONE	:
							if(giNaviPopUp == 1)
							{
								giNaviPopUp = 0;
								giIntensityPopUp	= 0;
								giDMPopUp 			= 0;
								/*********added on 29.10.2022 By Rajashekhar*********/
								if(giMode == 1)
								{
									Homescreen_select_night();
								}
								else
								{
									Homescreen_select_day();
								}
							}
							else
							{}
							break;
		case KEY_TWO	:
							if(giNaviPopUp == 1)
							{
								giNaviPopUp=0;
								giIntensityPopUp	= 0;
								if(giMode == 0)
								{
									giMode = 1;
								}
								else
								{
									giMode = 0;
								}

								Writedataintofram(MODE);

								if(giMode == 1)
								{
									giScreenSwitch = 26;
								}
								else
								{
									giScreenSwitch = 6;
								}

								Read_brightness_from_FRAM();
								set_brightness(giIntensityPercent);
							}
							break;
		case KEY_THREE	:

							break;
		case KEY_FOUR	:
							if(giDMPopUp == 1)
							{
								previous_button_pressed = 1;

								if(err_index < 1)
								{
									err_index = (NO_OF_DM1_MESSAGES - 1);
								}
								else
								{
									err_index--;
								}
							}
							else
							{
								/* RAW ADC - IO 2 SCREEN */
								//giScreenSwitch = 9;
								giNaviPopUp 		= 0;
								giDMPopUp 			= 0;
								giIntensityPopUp	= 0;
								gucDm1FaultPtr		= 0;

								if(digi_onoff_status == ON)
								{
									giScreenSwitch = 9;
								}
								else if(analog_onoff_status == ON)
								{
									giScreenSwitch = 8;
								}
								else if(giMode == 1)
								{
									if(trans_onoff_status == ON)
									{
										giScreenSwitch = 27;
									}
									else if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 26;//This will be changed in the future
									}
									else
									{
										giScreenSwitch = 26;
									}
								}
								else
								{
									if(trans_onoff_status == ON)
									{
										giScreenSwitch = 7;
									}
									else if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 6;//This will be changed in the future
									}
									else
									{
										giScreenSwitch = 6;
									}
								}
							}
							break;
		case KEY_FIVE	:
							/*
							if(giDMPopUp == 1)
							{
								bDm1FaultPtr = 1;
							}
							else
							{
								if(gucFaultsActive == 1)
								{
									giDMPopUp = 1;
									bDm1FaultPtr = 1;
								}
							}
							*/
							if(giDMPopUp == 1)
							{
								giDMPopUp = 0;

								err_index = 0;

								next_button_pressed = 0;
								previous_button_pressed = 0;

								Currnt_err_no 	= 0;
							}
							else if(gucFaultsActive == 1)
							{
								giDMPopUp = 1;

								err_index = 0;

								next_button_pressed = 1;
								previous_button_pressed = 0;

								Currnt_err_no 	= 0;
							}
							break;
		case KEY_SIX	:
							if(giNaviPopUp == 1)
							{
								giIntensityPopUp = 1;

								giIntensityPercent = giIntensityPercent + 10;
								if(giIntensityPercent > 100)
								{
									giIntensityPercent = 100;
								}
								Write_brightness_to_FRAM();
								set_brightness(giIntensityPercent);
							}
							break;
		case KEY_SEVEN	:
							if(giNaviPopUp == 1)
							{
								giIntensityPopUp = 1;

								giIntensityPercent = giIntensityPercent - 10;
								if(giIntensityPercent < 0)
								{
									giIntensityPercent = 0;
								}
								Write_brightness_to_FRAM();
								set_brightness(giIntensityPercent);
							}
							break;
		case KEY_EIGHT	:
							if(giDMPopUp == 1)
							{
								next_button_pressed = 1;

								if(err_index >= (NO_OF_DM1_MESSAGES - 1))
								{
									err_index = 0;
								}
								else
								{
									err_index++;
								}
							}
							else
							{
								/* ADC GUAGE SCREEN */
								if(giMode == 1)
								{
									//giScreenSwitch = 27;
									if(trans_onoff_status == ON)
									{
										giScreenSwitch = 27;
									}
									else if(analog_onoff_status == ON)
									{
										giScreenSwitch = 8;
									}
									else if(digi_onoff_status == ON)
									{
										giScreenSwitch = 9;
									}
									else if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 26;//This will be change in the future
									}
									else
									{
										giScreenSwitch = 26;
									}
								}
								else
								{
									//giScreenSwitch = 7;
									if(trans_onoff_status == ON)
									{
										giScreenSwitch = 7;
									}
									else if(analog_onoff_status == ON)
									{
										giScreenSwitch = 8;
									}
									else if(digi_onoff_status == ON)
									{
										giScreenSwitch = 9;
									}
									else if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 6;//This will be change in the future
									}
									else
									{
										giScreenSwitch = 6;
									}
								}

								giNaviPopUp 		= 0;
								giDMPopUp 			= 0;
								giIntensityPopUp	= 0;
								gucDm1FaultPtr		= 0;
							}
							break;
		case KEY_MENU	:

							if(giNaviPopUp == 1 || giDMPopUp == 1 || giIntensityPopUp == 1)
							{
								giNaviPopUp 		= 0;
								giDMPopUp 			= 0;
								giIntensityPopUp	= 0;
							}
							else
							{
								/* PASSWORD SCREEN */
								giScreenSwitch = 10;
							}
							break;
		case KEY_ENTER	:
							giNaviPopUp = 1;
							break;
		default 		:
							break;
	}
}

/* Night Main Screen 2 */
void ProcessScreen27(void)
{
	switch(gucKeyPressed)
	{
		case KEY_ONE	:
							if(giNaviPopUp == 1)
							{
								giNaviPopUp = 0;
								giIntensityPopUp	= 0;
								giDMPopUp 			= 0;
								/*********added on 29.10.2022 By Rajashekhar*********/
								if(giMode == 1)
								{
									Homescreen_select_night();
								}
								else
								{
									Homescreen_select_day();
								}
							}
							else
							{}
							break;
		case KEY_TWO	:
							if(giNaviPopUp == 1)
							{
								giNaviPopUp=0;
								giIntensityPopUp	= 0;
								if(giMode == 0)
								{
									giMode = 1;
								}
								else
								{
									giMode = 0;
								}

								Writedataintofram(MODE);

								if(giMode == 1)
								{
									giScreenSwitch = 27;
								}
								else
								{
									giScreenSwitch = 7;
								}
								Read_brightness_from_FRAM();
								set_brightness(giIntensityPercent);
							}
							break;
		case KEY_THREE	:

							break;
		case KEY_FOUR	:
							if(giDMPopUp == 1)
							{
								previous_button_pressed = 1;

								if(err_index < 1)
								{
									err_index = (NO_OF_DM1_MESSAGES - 1);
								}
								else
								{
									err_index--;
								}
							}
							else
							{
								/* Main SCREEN */
								if(giMode == 1)
								{
									//giScreenSwitch = 26;
									if(speedo_onoff_status == ON)
									{
										giScreenSwitch = 26;
									}
									else if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 26;//This will be change in the future
									}
									else if(digi_onoff_status == ON)
									{
										giScreenSwitch = 9;
									}
									else if(analog_onoff_status == ON)
									{
										giScreenSwitch = 8;
									}
									else
									{
										giScreenSwitch = 27;
									}
								}
								else
								{
									//giScreenSwitch = 6;
									if(speedo_onoff_status == ON)
									{
										giScreenSwitch = 6;
									}
									else if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 6;//This will be change in the future
									}
									else if(digi_onoff_status == ON)
									{
										giScreenSwitch = 9;
									}
									else if(analog_onoff_status == ON)
									{
										giScreenSwitch = 8;
									}
									else
									{
										giScreenSwitch = 7;
									}
								}
								giNaviPopUp 		= 0;
								giDMPopUp 			= 0;
								giIntensityPopUp	= 0;
							}
							break;
		case KEY_FIVE	:
							/*
							if(giDMPopUp == 1)
							{
								bDm1FaultPtr = 1;
							}
							else
							{
								if(gucFaultsActive == 1)
								{
									giDMPopUp = 1;
									bDm1FaultPtr = 1;
								}
							}
							*/
							if(giDMPopUp == 1)
							{
								giDMPopUp = 0;

								err_index = 0;

								next_button_pressed = 0;
								previous_button_pressed = 0;

								Currnt_err_no 	= 0;
							}
							else if(gucFaultsActive == 1)
							{
								giDMPopUp = 1;

								err_index = 0;

								next_button_pressed = 1;
								previous_button_pressed = 0;

								Currnt_err_no 	= 0;
							}
							break;
		case KEY_SIX	:
							if(giNaviPopUp == 1)
							{
								giIntensityPopUp = 1;

								giIntensityPercent = giIntensityPercent + 10;
								if(giIntensityPercent > 100)
								{
									giIntensityPercent = 100;
								}
								set_brightness(giIntensityPercent);
								MemoryWriteVariable(PRIMARY_MEMORY,NIGHT_MODE_BRIGHTNESS_ADDR, giIntensityPercent, 1);
							}
							break;
		case KEY_SEVEN	:
							if(giNaviPopUp == 1)
							{
								giIntensityPopUp = 1;

								giIntensityPercent = giIntensityPercent - 10;
								if(giIntensityPercent < 0)
								{
									giIntensityPercent = 0;
								}
								set_brightness(giIntensityPercent);
								MemoryWriteVariable(PRIMARY_MEMORY,NIGHT_MODE_BRIGHTNESS_ADDR, giIntensityPercent, 1);
							}
							break;
		case KEY_EIGHT	:
							if(giDMPopUp == 1)
							{
								next_button_pressed = 1;

								if(err_index >= (NO_OF_DM1_MESSAGES - 1))
								{
									err_index = 0;
								}
								else
								{
									err_index++;
								}
							}
							else
							{
								/* Raw ADC1 SCREEN */
								//giScreenSwitch = 8;
								giNaviPopUp 		= 0;
								giDMPopUp 			= 0;
								giIntensityPopUp	= 0;

								if(analog_onoff_status == ON)
								{
									giScreenSwitch = 8;
								}
								else if(digi_onoff_status == ON)
								{
									giScreenSwitch = 9;
								}
								else if(giMode == 1)
								{
									if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 26;//This will be change in future
									}
									else if(speedo_onoff_status == ON)
									{
										giScreenSwitch = 26;
									}
									else
									{
										giScreenSwitch = 27;
									}
								}
								else
								{
									if(eng_rpm_onoff_status == ON)
									{
										giScreenSwitch = 6;//This will be change in future
									}
									else if(speedo_onoff_status == ON)
									{
										giScreenSwitch = 6;
									}
									else
									{
										giScreenSwitch = 7;
									}
								}
							}
							break;
		case KEY_MENU	:

							if(giNaviPopUp == 1 || giDMPopUp == 1 || giIntensityPopUp == 1)
							{
								giNaviPopUp 		= 0;
								giDMPopUp 			= 0;
								giIntensityPopUp	= 0;
							}
							else
							{
								/* PASSWORD SCREEN */
								giScreenSwitch = 10;
							}
							break;
		case KEY_ENTER	:
							giNaviPopUp = 1;
							break;
		default 		:
							break;
	}
}
uint16_t extr_3digit_int_numbersonly(void)
{
	/* 0 --> space and 1 --> numbers
	 * 000 =>0
	 * 001 =>[2]
	 * 010 =>[1]
	 * 011 =>[1][2]
	 * 100 =>[0]
	 * 101 =>[0][2]
	 * 110 =>[0][1]
	 * 111 =>[0][1][2]
	 */
	uint8_t it_is_a_number[3],it_is_a_space[3];
	uint16_t Temp_var = 0;
	memset(&it_is_a_number,0,sizeof(it_is_a_number));
	memset(&it_is_a_space,0,sizeof(it_is_a_space));

	for(int pos = 0; pos < 3;pos++)
	{
		for(int num = 0x30; num <= 0x39; num++)
		{
			if(gucArrayLine[pos] == ' ')/*compare to SPACE*/
			{
				it_is_a_space[pos] = 1;
				break;
			}
			else if(gucArrayLine[pos] == num)/*compare to Numbers[0,1,2,3,4,5,6,7,8,9]*/
			{
				it_is_a_number[pos] = 1;
				break;
			}
			else{}
		}
	}

	if(it_is_a_space[0] == 1)/*0*/
	{
		if(it_is_a_space[1] == 1)/*0*/
		{
			if(it_is_a_space[2] == 1)/*0*/
			{
				Temp_var = 0;
			}
			else if(it_is_a_number[2] == 1)/*1*/
			{
				Temp_var = gucArrayLine[2];
				Temp_var = Temp_var - 0x30;/*ascii to decimal*/
			}
			else
			{
				Temp_var = 0;
			}
		}
		else if(it_is_a_number[1] == 1)/*1*/
		{
			if(it_is_a_space[2] == 1)/*0*/
			{
				Temp_var = gucArrayLine[1];
				Temp_var = Temp_var - 0x30;/*ascii to decimal*/
			}
			else if(it_is_a_number[2] == 1)/*1*/
			{
				Temp_var = Character_concatination(2, gucArrayLine, 1, 0);
			}
			else
			{
				Temp_var = 0;
			}
		}
		else
		{
			Temp_var = 0;
		}
	}
	else if(it_is_a_number[0] == 1)/*1*/
	{
		if(it_is_a_space[1] == 1)/*0*/
		{
			if(it_is_a_space[2] == 1)/*0*/
			{
				Temp_var = gucArrayLine[0];
				Temp_var = Temp_var - 0x30;/*ascii to decimal*/
			}
			else if(it_is_a_number[2] == 1)/*1*/
			{
				Temp_var = Character_concatination(2, gucArrayLine, 0, 1);
				/* 101 1-->is a number and 0-->is space
				i.e inbetween number is to be discard and concatinate the first and last digits*/
			}
			else
			{
				Temp_var = 0;
			}
		}
		else if(it_is_a_number[1] == 1)/*1*/
		{
			if(it_is_a_space[2] == 1)/*0*/
			{
				Temp_var = Character_concatination(2, gucArrayLine, 0, 0);
			}
			else if(it_is_a_number[2] == 1)/*1*/
			{
				Temp_var = Character_concatination(3, gucArrayLine, 0, 0);
			}
			else
			{
				Temp_var = 0;
			}
		}
		else
		{
			Temp_var = 0;
		}
	}
	else
	{
		Temp_var = 0;
	}

	memset(&it_is_a_number,0,sizeof(it_is_a_number));
	memset(&it_is_a_space,0,sizeof(it_is_a_space));

	return Temp_var;
}
uint16_t extr_3digits_float_only(void)
{
	uint8_t it_is_dot[4],it_is_a_number[4];
	uint16_t Temp_var = 0;
	memset(&it_is_dot,0,sizeof(it_is_dot));
	memset(&it_is_a_number,0,sizeof(it_is_a_number));

	for(int pos = 0; pos < 4 ; pos++)
	{
		for(int num = 0x30; num <= 0x39; num++)
		{
			if(gucArrayLine[pos] == '.')/*compare to SPACE*/
			{
				it_is_dot[pos] = 1;
				break;
			}
			else if(gucArrayLine[pos] == num)/*compare to Numbers[0,1,2,3,4,5,6,7,8,9]*/
			{
				it_is_a_number[pos] = 1;
				break;
			}
			else{}
		}
	}
	if(it_is_dot[0] == 1)
	{
		Temp_var = 0;
	}
	else if(it_is_dot[1] == 1)/*[0][2]*/
	{
		if(it_is_a_number[0] == 1 && it_is_a_number[2] == 1)
		{
			Temp_var = Character_concatination(2, gucArrayLine, 0, 1);
		}
		else
		{
			Temp_var = 0;
		}
	}
	else if(it_is_dot[2] == 1)/*[0][1][3]*/
	{
		if(it_is_a_number[0] == 1 && it_is_a_number[1] == 1 && it_is_a_number[3] == 1)
		{
			Temp_var = Character_concatination(3, gucArrayLine, 0, 1);
		}
		else
		{
			Temp_var = 0;
		}
	}
	else if(it_is_dot[3] == 1)/*[0][1][2]*/
	{
		if(it_is_a_number[0] == 1 && it_is_a_number[1] == 1 && it_is_a_number[2] == 1)
		{
			Temp_var = Character_concatination(3, gucArrayLine, 0, 0);
		}
		else
		{
			Temp_var = 0;
		}
	}
	else if(it_is_a_number[0] == 1 && it_is_a_number[1] == 1 && it_is_a_number[2] == 1)/*[0][1][2]*/
	{
		Temp_var = Character_concatination(3, gucArrayLine, 0, 0);
	}
	else
	{
		Temp_var = 0;
	}

	memset(&it_is_dot,0,sizeof(it_is_dot));
	memset(&it_is_a_number,0,sizeof(it_is_a_number));

	return Temp_var;
}
uint16_t extr_4digits_float_only(void)
{
	uint8_t it_is_dot[5],it_is_a_number[5];
	uint16_t Temp_var = 0;
	memset(&it_is_dot,0,sizeof(it_is_dot));
	memset(&it_is_a_number,0,sizeof(it_is_a_number));

	for(int pos = 0; pos < 5 ; pos++)
	{
		for(int num = 0x30; num <= 0x39; num++)
		{
			if(gucArrayLine[pos] == '.')/*compare to SPACE*/
			{
				it_is_dot[pos] = 1;
				break;
			}
			else if(gucArrayLine[pos] == num)/*compare to Numbers[0,1,2,3,4,5,6,7,8,9]*/
			{
				it_is_a_number[pos] = 1;
				break;
			}
			else{}
		}
	}
	if(it_is_dot[0] == 1)
	{
		Temp_var = 0;
	}
	else if(it_is_dot[1] == 1)
	{
		if(it_is_a_number[0] == 1 && it_is_a_number[2] == 1)
		{
			Temp_var = Character_concatination(2, gucArrayLine, 0, 1);
		}
		else
		{
			Temp_var = 0;
		}
	}
	else if(it_is_dot[2] == 1)/*[0][1][3]*/
	{
		if(it_is_a_number[0] == 1 && it_is_a_number[1] == 1 && it_is_a_number[3] == 1)
		{
			Temp_var = Character_concatination(3, gucArrayLine, 0, 1);
		}
		else
		{
			Temp_var = 0;
		}
	}
	else if(it_is_dot[3] == 1)/*[0][1][2][4]*/
	{
		if(it_is_a_number[0] == 1 && it_is_a_number[1] == 1 && it_is_a_number[2] == 1 && it_is_a_number[4] == 1)
		{
			Temp_var = Character_concatination(4, gucArrayLine, 0, 1);
		}
		else
		{
			Temp_var = 0;
		}
	}
	else if(it_is_dot[4] == 1)/*[0][1][2][3]*/
	{
		if(it_is_a_number[0] == 1 && it_is_a_number[1] == 1 && it_is_a_number[2] == 1 && it_is_a_number[3] == 1)
		{
			Temp_var = Character_concatination(4, gucArrayLine, 0, 0);
		}
		else
		{
			Temp_var = 0;
		}
	}
	else if(it_is_a_number[0] == 1 && it_is_a_number[1] == 1 && it_is_a_number[2] == 1 && it_is_a_number[3] == 1)
	{
		Temp_var = Character_concatination(4, gucArrayLine, 0, 0);
	}
	else
	{

	}

	memset(&it_is_dot,0,sizeof(it_is_dot));
	memset(&it_is_a_number,0,sizeof(it_is_a_number));

	return Temp_var;
}

/* Text Edit Screen */
void ProcessScreen28(void)
{
	unsigned char lucLoop = 0;
	switch(gucKeyPressed)
	{
		case KEY_ONE	:
							if(gucEditService == 1)
							{
								gucEditService = 0;
								MemoryWriteVariable(PRIMARY_MEMORY, ENGINE_HOUR_METER_ADDR, giHourMeter, 4);
								switch(gcScrollSel)
								{
									case 0:
										guiEngOilInterval 		= extr_3digit_int_numbersonly();
										MemoryWriteVariable(PRIMARY_MEMORY, CHANGE_ENGINE_OIL_INTERVAL_ADDR, guiEngOilInterval, 2);
											break;
									case 1:
										guiAirFilterInterval	= extr_3digit_int_numbersonly();
										MemoryWriteVariable(PRIMARY_MEMORY, CHANGE_AIRFILTERS_INTERVAL_ADDR, guiAirFilterInterval, 2);
											break;
									case 2:
										guiHydOilInterval 		= extr_3digit_int_numbersonly();
										MemoryWriteVariable(PRIMARY_MEMORY, CHANGE_HYDRAULIC_OIL_INTERVAL_ADDR, guiHydOilInterval, 2);
											break;
									case 3:
										guiSerEngInterval 		= extr_3digit_int_numbersonly();
										MemoryWriteVariable(PRIMARY_MEMORY, SERVICE_ENGINE_INTERVAL_ADDR, guiSerEngInterval, 2);
											break;
									case 4:guiSerMacInterval	= extr_3digit_int_numbersonly();
										MemoryWriteVariable(PRIMARY_MEMORY, SERVICE_MACHINE_INTERVAL_ADDR, guiSerMacInterval, 2);
											break;
								}
								Service_remainder_hrs_calculation(giHourMeter);
								for(lucLoop =0;lucLoop<16;lucLoop++)
								{
									gucArrayLine[lucLoop] = ' ';
								}
								giScreenSwitch = 17;/*back to service reminder screen*/
							}
//							else if(guieditcalibration == 1)
//							{
//								guieditcalibration = 0;
//								switch(gcUserScroll)
//								{
//									case 0:maxcapacitydata = extr_4digits_float_only();
//										break;
//									case 1:calcapacitydata = extr_4digits_float_only();
//										break;
//									case 2:zercaldata = extr_3digits_float_only();
//										break;
//									case 3:spandata = extr_3digits_float_only();
//										break;
//									default:
//										break;
//								}
//								for(lucLoop =0;lucLoop<16;lucLoop++)
//								{
//									gucArrayLine[lucLoop] = ' ';
//								}
//								giScreenSwitch = 32;/*back to Load calibration screen*/
//							}
							else
							{
								switch(gcScrollSel)
								{
									case 0:
											//memcpy(&acAPPW_Language_0 + OFFSET_0,gucArrayLine,16);
											for(lucLoop =0;lucLoop<16;lucLoop++)
											{
												acAPPW_Language_0[OFFSET_0 + lucLoop] = gucArrayLine[lucLoop];
											}
											Writedataintofram(UIN);
											break;
									case 1:
											//memcpy(&acAPPW_Language_0 + OFFSET_1,gucArrayLine,16);
											for(lucLoop =0;lucLoop<16;lucLoop++)
											{
												acAPPW_Language_0[OFFSET_1 + lucLoop] = gucArrayLine[lucLoop];
											}
											Writedataintofram(MAKE);
											break;
									case 2:
											//memcpy(&acAPPW_Language_0 + OFFSET_2,gucArrayLine,16);
											for(lucLoop =0;lucLoop<16;lucLoop++)
											{
												acAPPW_Language_0[OFFSET_2 + lucLoop] = gucArrayLine[lucLoop];
											}
											Writedataintofram(MODEL);
											break;
									case 3:
											//memcpy(&acAPPW_Language_0 + OFFSET_3,gucArrayLine,16);
											for(lucLoop =0;lucLoop<16;lucLoop++)
											{
												acAPPW_Language_0[OFFSET_3 + lucLoop] = gucArrayLine[lucLoop];
											}
											Writedataintofram(SERIAL_NO);
											break;
									case 4:
											//memcpy(&acAPPW_Language_0 + OFFSET_4,gucArrayLine,16);
											for(lucLoop =0;lucLoop<16;lucLoop++)
											{
												acAPPW_Language_0[OFFSET_4 + lucLoop] = gucArrayLine[lucLoop];
											}
											Writedataintofram(UNIT_NO);
											break;
								}
								gucChCount = 0;
								//memset(&gucArrayLine,' ',sizeof(gucArrayLine));
								for(lucLoop =0;lucLoop<16;lucLoop++)
								{
									gucArrayLine[lucLoop] = ' ';
									acAPPW_Language_0[OFFSET_5 + lucLoop] = gucArrayLine[lucLoop];
								}
								giScreenSwitch = 19;/*back to identification screen*/

								Read_identification_details();
							}
							break;
		case KEY_TWO	:
							if(((gcAlphabetSel % 11) + 1) == 11)
							{

							}
							else if(gcAlphabetSel < 44)
							{
								gcAlphabetSel++;
								guiXAxis = guiXAxis + 50;
							}
							else if(gcAlphabetSel >= 44)
							{

								if(gcAlphabetSel == 44)
								{
									gcAlphabetSel++;
									guiXAxis = 132 + (50 * 5);
								}
								else if(gcAlphabetSel == 45)
								{
									gcAlphabetSel++;
									guiXAxis = 132 + (50 * 9);
								}
								else if(gcAlphabetSel == 46)
								{
//									guiXAxis = 132 + (50 * 9);
								}
							}
							break;
		case KEY_THREE	:
							if((gcAlphabetSel % 11) == 0 || gcAlphabetSel == 0)
							{

							}
							else if(gcAlphabetSel < 44)
							{
								gcAlphabetSel--;
								guiXAxis = guiXAxis - 50;
							}
							else if(gcAlphabetSel >= 44)
							{

								if(gcAlphabetSel == 44)
								{
									guiXAxis = 132;
								}
								else if(gcAlphabetSel == 45)
								{
									gcAlphabetSel--;
									guiXAxis = 132 + 50;
								}
								else if(gcAlphabetSel == 46)
								{
									gcAlphabetSel--;
									guiXAxis = 132 + (50 * 5);
								}
							}
							break;
		case KEY_FOUR	:
							gucChCount = 0;
							memset(&gucArrayLine,' ',sizeof(gucArrayLine));
							for(lucLoop =0;lucLoop<16;lucLoop++)
							{
								acAPPW_Language_0[OFFSET_5 + lucLoop] = gucArrayLine[lucLoop];
							}
							break;
		case KEY_FIVE	:

							break;
		case KEY_SIX	:
							if(gcAlphabetSel >= 11 && gcAlphabetSel < 44)
							{
								gcAlphabetSel = gcAlphabetSel - 11;
								guiYAxis = guiYAxis - 50;
							}
							else if(gcAlphabetSel >= 44 & gcAlphabetSel < 47)
							{
								if(gcAlphabetSel == 44)
								{
									gcAlphabetSel = 34;
									guiXAxis = 132 + 50;
								}
								else if(gcAlphabetSel == 45)
								{
									gcAlphabetSel = 38;
									guiXAxis = 132 + (50 * 5);
								}
								else if(gcAlphabetSel == 46)
								{
									gcAlphabetSel = 42;
									guiXAxis = 132 + (50 * 9);
								}
								guiYAxis = 304;
							}
							break;
		case KEY_SEVEN	:
							if(gcAlphabetSel < 33)
							{
								gcAlphabetSel = gcAlphabetSel + 11;
								guiYAxis = guiYAxis + 50;
							}
							else if(gcAlphabetSel >= 33 && gcAlphabetSel < 44)
							{
								if(gcAlphabetSel == 33 || gcAlphabetSel == 34 || gcAlphabetSel == 35)
								{
									gcAlphabetSel = 44;
									guiXAxis = 132 + 50;
								}
								if(gcAlphabetSel == 36 || gcAlphabetSel == 37 || gcAlphabetSel == 38 || gcAlphabetSel == 39 || gcAlphabetSel == 40)
								{
									gcAlphabetSel = 45;
									guiXAxis = 132 + (50 * 5);

								}
								else if(gcAlphabetSel == 41 || gcAlphabetSel == 42 || gcAlphabetSel == 43)
								{
									gcAlphabetSel = 46;
									guiXAxis = 132 + (50 * 9);
								}
								guiYAxis = 354;
							}
							break;
		case KEY_EIGHT	:
							switch(gcAlphabetSel)
							{
								case 0 : gcCharSelect = '1';
										 break;
								case 1 : gcCharSelect = '2';
										 break;
								case 2 : gcCharSelect = '3';
										 break;
								case 3 : gcCharSelect = '4';
										 break;
								case 4 : gcCharSelect = '5';
										 break;
								case 5 : gcCharSelect = '6';
										 break;
								case 6 : gcCharSelect = '7';
										 break;
								case 7 : gcCharSelect = '8';
										 break;
								case 8 : gcCharSelect = '9';
										 break;
								case 9 : gcCharSelect = '0';
										 break;
								case 10: gcCharSelect = '#';
										 break;
								case 11: gcCharSelect = 'Q';
										 break;
								case 12: gcCharSelect = 'W';
										 break;
								case 13: gcCharSelect = 'E';
										 break;
								case 14: gcCharSelect = 'R';
										 break;
								case 15: gcCharSelect = 'T';
										 break;
								case 16: gcCharSelect = 'Y';
										 break;
								case 17: gcCharSelect = 'U';
										 break;
								case 18: gcCharSelect = 'I';
										 break;
								case 19: gcCharSelect = 'O';
										 break;
								case 20: gcCharSelect = 'P';
										 break;
								case 21: gcCharSelect = '@';
										 break;
								case 22: gcCharSelect = 'A';
										 break;
								case 23: gcCharSelect = 'S';
										 break;
								case 24: gcCharSelect = 'D';
										 break;
								case 25: gcCharSelect = 'F';
										 break;
								case 26: gcCharSelect = 'G';
										 break;
								case 27: gcCharSelect = 'H';
										 break;
								case 28: gcCharSelect = 'J';
										 break;
								case 29: gcCharSelect = 'K';
										 break;
								case 30: gcCharSelect = 'L';
										 break;
								case 31: gcCharSelect = '\'';
										 break;
								case 32: gcCharSelect = '+';
										 break;
								case 33: gcCharSelect = 'Z';
										 break;
								case 34: gcCharSelect = 'X';
										 break;
								case 35: gcCharSelect = 'C';
										 break;
								case 36: gcCharSelect = 'V';
										 break;
								case 37: gcCharSelect = 'B';
										 break;
								case 38: gcCharSelect = 'N';
										 break;
								case 39: gcCharSelect = 'M';
										 break;
								case 40: gcCharSelect = '-';
										 break;
								case 41: gcCharSelect = '_';
										 break;
								case 42: gcCharSelect = '.';
										 break;
								case 43: gcCharSelect = ',';
										 break;
								case 44:
										 gcCharSelect = ' ';
										 gucArrayLine[--gucChCount] = ' ';
										 break;
								case 45: gcCharSelect = ' ';
										 break;
								case 46:
										 break;
							}
							if(gucChCount < 16 && gcAlphabetSel != 44)
							{
								gucArrayLine[gucChCount++] = gcCharSelect;
							}
							//memcpy(&(acAPPW_Language_0 + OFFSET_5),&gucArrayLine,16);
							for(lucLoop =0;lucLoop<16;lucLoop++)
							{
								acAPPW_Language_0[OFFSET_5 + lucLoop] = gucArrayLine[lucLoop];
							}
							break;
		case KEY_MENU	:
							//giScreenSwitch = 19;
							if(gucEditService == 1)
							{
								giScreenSwitch = 17;/* Service reminder Screen */
								gucEditService = 0;
							}
//							else if(guieditcalibration == 1)
//							{
//								giScreenSwitch = 32;/* Load calibration screen */
//								guieditcalibration = 0;
//							}
							else
							{
								giScreenSwitch = 19;/* vehicle identification Screen */
							}
							break;
		case KEY_ENTER	:
							break;
		default 		:
							break;
	}
}

void store_home_screen_sel_data(void)
{
//	uint16_t
//	SCREEN_SPEEDO_ONOFF_ADDR 	= 0x100,
//	SCREEN_TRANS_ONOFF_ADDR 	= 0x101,
//	SCREEN_DIGI_IO_ONOFF_ADDR 	= 0x102,
//	SCREEN_ANALOG_IO_ONOFF_ADDR = 0x103,
//	SCREEN_ENG_RPM_ONOFF_ADDR 	= 0x104,
//
//	SCREEN_SPEEDO_HOME_ADDR 	= 0x105,
//	SCREEN_TRANS_HOME_ADDR 		= 0x106,
//	SCREEN_DIGI_IO_HOME_ADDR 	= 0x107,
//	SCREEN_ANALOG_IO_HOME_ADDR	= 0x108,
//	SCREEN_ENG_RPM_HOME_ADDR 	= 0x109;
	/*******************home screen selection *******************/
	if(guiselct_screen == SPEEDOMETER_SCREEN && guiselct_home_screen == ON)
	{
     	MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_SPEEDO_HOME_ADDR,ON,1);
	}
	else if(guiselct_screen == SPEEDOMETER_SCREEN && guiselct_home_screen == OFF)
	{
     	 MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_SPEEDO_HOME_ADDR,OFF,1);
	}
	else{}

	if(guiselct_screen == TRANSMISSION_SCREEN && guiselct_home_screen == ON)
	{
		MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_TRANS_HOME_ADDR,ON,1);
	}
	else if(guiselct_screen == TRANSMISSION_SCREEN && guiselct_home_screen == OFF)
	{
		MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_TRANS_HOME_ADDR,OFF,1);
	}
	else{}

	if(guiselct_screen == DIGITAL_IO_SCREEN && guiselct_home_screen == ON)
	{
		MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_DIGI_IO_HOME_ADDR,ON,1);
	}
	else if(guiselct_screen == DIGITAL_IO_SCREEN && guiselct_home_screen == OFF)
	{
		MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_DIGI_IO_HOME_ADDR,OFF,1);
	}
	else{}

	if(guiselct_screen == ANALOG_IO_SCREEN && guiselct_home_screen == ON)
	{
		MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_ANALOG_IO_HOME_ADDR,ON,1);
	}
	else if(guiselct_screen == ANALOG_IO_SCREEN && guiselct_home_screen == OFF)
	{
		MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_ANALOG_IO_HOME_ADDR,OFF,1);
	}
	else{}

	if(guiselct_screen == ENGINE_RPM_SCREEN && guiselct_home_screen == ON)
	{
     	MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_ENG_RPM_HOME_ADDR,ON,1);
	}
	else if(guiselct_screen == ENGINE_RPM_SCREEN && guiselct_home_screen == OFF)
	{
     	MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_ENG_RPM_HOME_ADDR,OFF,1);
	}
	else{}
}
void store_onoff_screen_sel_data(void)
{
//	uint16_t
//	SCREEN_SPEEDO_ONOFF_ADDR 	= 0x100,
//	SCREEN_TRANS_ONOFF_ADDR 	= 0x101,
//	SCREEN_DIGI_IO_ONOFF_ADDR 	= 0x102,
//	SCREEN_ANALOG_IO_ONOFF_ADDR = 0x103,
//	SCREEN_ENG_RPM_ONOFF_ADDR 	= 0x104,
//
//	SCREEN_SPEEDO_HOME_ADDR 	= 0x105,
//	SCREEN_TRANS_HOME_ADDR 		= 0x106,
//	SCREEN_DIGI_IO_HOME_ADDR 	= 0x107,
//	SCREEN_ANALOG_IO_HOME_ADDR	= 0x108,
//	SCREEN_ENG_RPM_HOME_ADDR 	= 0x109;
	/********************onoff screen selection***************/
	if(guiselct_screen == SPEEDOMETER_SCREEN && guiscreen_on_off == ON)
	{
		MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_SPEEDO_ONOFF_ADDR,ON,1);
	}
	else if(guiselct_screen == SPEEDOMETER_SCREEN && guiscreen_on_off == OFF)
	{
		MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_SPEEDO_ONOFF_ADDR,OFF,1);

	}
	else{}

	if(guiselct_screen == TRANSMISSION_SCREEN && guiscreen_on_off == ON)
	{
		MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_TRANS_ONOFF_ADDR,ON,1);
	}
	else if(guiselct_screen == TRANSMISSION_SCREEN && guiscreen_on_off == OFF)
	{
		MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_TRANS_ONOFF_ADDR,OFF,1);
	}
	else{}

	if(guiselct_screen == DIGITAL_IO_SCREEN && guiscreen_on_off == ON)
	{
		MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_DIGI_IO_ONOFF_ADDR,ON,1);
	}
	else if(guiselct_screen == DIGITAL_IO_SCREEN && guiscreen_on_off == OFF)
	{
		MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_DIGI_IO_ONOFF_ADDR,OFF,1);
	}
	else{}

	if(guiselct_screen == ANALOG_IO_SCREEN && guiscreen_on_off == ON)
	{
		MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_ANALOG_IO_ONOFF_ADDR,ON,1);
	}
	else if(guiselct_screen == ANALOG_IO_SCREEN && guiscreen_on_off == OFF)
	{
		MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_ANALOG_IO_ONOFF_ADDR,OFF,1);
	}
	else{}

	if(guiselct_screen == ENGINE_RPM_SCREEN && guiscreen_on_off == ON)
	{
		MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_ENG_RPM_ONOFF_ADDR,ON,1);
	}
	else if(guiselct_screen == ENGINE_RPM_SCREEN && guiscreen_on_off == OFF)
	{
		MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_ENG_RPM_ONOFF_ADDR,OFF,1);
	}
	else{}
}

void read_screen_setting_data(void)
{
//	uint16_t
//	SCREEN_SPEEDO_ONOFF_ADDR 	= 0x100,
//	SCREEN_TRANS_ONOFF_ADDR 	= 0x101,
//	SCREEN_DIGI_IO_ONOFF_ADDR 	= 0x102,
//	SCREEN_ANALOG_IO_ONOFF_ADDR = 0x103,
//	SCREEN_ENG_RPM_ONOFF_ADDR 	= 0x104,
//
//	SCREEN_SPEEDO_HOME_ADDR 	= 0x105,
//	SCREEN_TRANS_HOME_ADDR 		= 0x106,
//	SCREEN_DIGI_IO_HOME_ADDR 	= 0x107,
//	SCREEN_ANALOG_IO_HOME_ADDR	= 0x108,
//	SCREEN_ENG_RPM_HOME_ADDR 	= 0x109;
	if(guiselct_screen == SPEEDOMETER_SCREEN)
	{
		guiscreen_on_off= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_SPEEDO_ONOFF_ADDR,1);
		guiselct_home_screen= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_SPEEDO_HOME_ADDR,1);
	}
	else if(guiselct_screen == TRANSMISSION_SCREEN)
	{
		guiscreen_on_off= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_TRANS_ONOFF_ADDR,1);
		guiselct_home_screen= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_TRANS_HOME_ADDR,1);
	}
	else if(guiselct_screen == DIGITAL_IO_SCREEN)
	{
		guiscreen_on_off= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_DIGI_IO_ONOFF_ADDR,1);
		guiselct_home_screen= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_DIGI_IO_HOME_ADDR,1);
	}
	else if(guiselct_screen == ANALOG_IO_SCREEN)
	{
		guiscreen_on_off= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_ANALOG_IO_ONOFF_ADDR,1);
		guiselct_home_screen= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_ANALOG_IO_HOME_ADDR,1);
	}
	else if(guiselct_screen == ENGINE_RPM_SCREEN)
	{
		guiscreen_on_off= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_ENG_RPM_ONOFF_ADDR,1);
		guiselct_home_screen= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_ENG_RPM_HOME_ADDR,1);
	}else{}
}

/*******select default screen onoff and home ***********/
void write_default_scr_sel_setting(void)
{
 	MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_SPEEDO_ONOFF_ADDR		,ON		,1);
 	MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_SPEEDO_HOME_ADDR		,ON		,1);

 	MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_TRANS_ONOFF_ADDR		,ON		,1);
 	MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_TRANS_HOME_ADDR		,OFF	,1);

 	MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_DIGI_IO_ONOFF_ADDR	,ON		,1);
 	MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_DIGI_IO_HOME_ADDR		,OFF	,1);

 	MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_ANALOG_IO_ONOFF_ADDR	,ON		,1);
 	MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_ANALOG_IO_HOME_ADDR	,OFF	,1);

 	MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_ENG_RPM_ONOFF_ADDR	,OFF	,1); /*This will be changed in the future**/
 	MemoryWriteVariable(PRIMARY_MEMORY,SCREEN_ENG_RPM_HOME_ADDR		,OFF	,1);
}

void read_onoff_home_setting_status(void)
{
//	uint16_t
//	SCREEN_SPEEDO_ONOFF_ADDR 	= 0x100,
//	SCREEN_TRANS_ONOFF_ADDR 	= 0x101,
//	SCREEN_DIGI_IO_ONOFF_ADDR 	= 0x102,
//	SCREEN_ANALOG_IO_ONOFF_ADDR = 0x103,
//	SCREEN_ENG_RPM_ONOFF_ADDR 	= 0x104,
//
//	SCREEN_SPEEDO_HOME_ADDR 	= 0x105,
//	SCREEN_TRANS_HOME_ADDR 		= 0x106,
//	SCREEN_DIGI_IO_HOME_ADDR 	= 0x107,
//	SCREEN_ANALOG_IO_HOME_ADDR	= 0x108,
//	SCREEN_ENG_RPM_HOME_ADDR 	= 0x109;
	speedo_onoff_status	= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_SPEEDO_ONOFF_ADDR,1);
	speedo_home_status	= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_SPEEDO_HOME_ADDR,1);

	trans_onoff_status	= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_TRANS_ONOFF_ADDR,1);
	trans_home_status	= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_TRANS_HOME_ADDR,1);

	digi_onoff_status	= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_DIGI_IO_ONOFF_ADDR,1);
	digi_home_status	= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_DIGI_IO_HOME_ADDR,1);

	analog_onoff_status	= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_ANALOG_IO_ONOFF_ADDR,1);
	analog_home_status	= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_ANALOG_IO_HOME_ADDR,1);

	eng_rpm_onoff_status= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_ENG_RPM_ONOFF_ADDR,1);
	eng_rpm_home_status	= MemoryReadVariable(PRIMARY_MEMORY,SCREEN_ENG_RPM_HOME_ADDR,1);
}
/*
void Homescreen_select_day(void)
{
	if(speedo_home_status == ON)
	{
		giScreenSwitch = 6;
	}
	else if(trans_home_status == ON)
	{
		giScreenSwitch = 7;
	}
	else if(digi_home_status == ON)
	{
		giScreenSwitch = 9;
	}
	else if(analog_home_status == ON)
	{
		giScreenSwitch = 8;
	}
	else if(eng_rpm_home_status == ON)
	{
		giScreenSwitch = 6;
	}else{}
}

void Homescreen_select_night(void)
{
	if(speedo_home_status == ON)
	{
		giScreenSwitch = 26;
	}
	else if(trans_home_status == ON)
	{
		giScreenSwitch = 27;
	}
	else if(digi_home_status == ON)
	{
		giScreenSwitch = 9;
	}
	else if(analog_home_status == ON)
	{
		giScreenSwitch = 8;
	}
	else if(eng_rpm_home_status == ON)
	{
		giScreenSwitch = 26;
	}else{}
}
*/
void Homescreen_select_day(void)
{
	if(speedo_onoff_status == ON && speedo_home_status == ON)
	{
		giScreenSwitch = 6;
	}
	else if(trans_onoff_status == ON && trans_home_status == ON)
	{
		giScreenSwitch = 7;
	}
	else if(digi_onoff_status == ON && digi_home_status == ON)
	{
		giScreenSwitch = 9;
	}
	else if(analog_onoff_status == ON && analog_home_status == ON)
	{
		giScreenSwitch = 8;
	}
	else if(eng_rpm_onoff_status == ON && eng_rpm_home_status == ON)
	{
		giScreenSwitch = 6;
	}
	else
	{
		giScreenSwitch = 6;
	}
}
void Homescreen_select_night(void)
{
	if(speedo_onoff_status == ON && speedo_home_status == ON)
	{
		giScreenSwitch = 26;
	}
	else if(trans_onoff_status == ON && trans_home_status == ON)
	{
		giScreenSwitch = 27;
	}
	else if(digi_onoff_status == ON && digi_home_status == ON)
	{
		giScreenSwitch = 9;
	}
	else if(analog_onoff_status == ON && analog_home_status == ON)
	{
		giScreenSwitch = 8;
	}
	else if(eng_rpm_onoff_status == ON && eng_rpm_home_status == ON)
	{
		giScreenSwitch = 26;
	}
	else
	{
		giScreenSwitch = 26;
	}
}
/*
uint16_t Character_concatination(uint8_t no_of_char,uint8_t start_index)
{
	uint16_t data = 0;
	uint8_t temp[6] = {0,0,0,0,0,0};
	unsigned int temp_data1 = 0,temp_data2 = 0;

	memset(&temp,0,sizeof(temp));
	switch(no_of_char)
	{
	case 0x02 : temp[0] = gucArrayLine[start_index];
				start_index++;
				temp[1] = gucArrayLine[start_index];

				temp[0] = ascii_bcd(temp[0]);
				temp[1] = ascii_bcd(temp[1]);
				data = concatenate(temp[0],temp[1]);
				break;
	case 0x03 : temp[0] = gucArrayLine[start_index];
				start_index++;
				temp[1] = gucArrayLine[start_index];

				temp[0] = ascii_bcd(temp[0]);
				temp[1] = ascii_bcd(temp[1]);
				temp_data1 = concatenate(temp[0],temp[1]);

				start_index++;
				temp[2] = gucArrayLine[start_index];

				temp[2] = ascii_bcd(temp[2]);
				data = concatenate(temp_data1,temp[2]);
				break;

	case 0x04 : temp[0] = gucArrayLine[start_index];
				start_index++;
				temp[1] = gucArrayLine[start_index];

				temp[0] = ascii_bcd(temp[0]);
				temp[1] = ascii_bcd(temp[1]);
				temp_data1 = concatenate(temp[0],temp[1]);

				start_index++;
				temp[2] = gucArrayLine[start_index];

				temp[2] = ascii_bcd(temp[2]);
				temp_data2 = concatenate(temp_data1,temp[2]);

				start_index++;
				temp[3] = gucArrayLine[start_index];

				temp[3] = ascii_bcd(temp[3]);
				data = concatenate(temp_data2,temp[3]);
				break;

	default:	break;

	}

	return data;
}
*/
uint16_t Character_concatination(uint8_t no_of_char, uint8_t array[], uint8_t start_index, bool inbetween)
{
	uint16_t data = 0;
	uint8_t temp[100];
	unsigned int temp_data1 = 0,temp_data2 = 0;

	memset(&temp,0,sizeof(temp));
	switch(no_of_char)
	{
	case 0x02 : temp[0] = array[start_index];
				if(inbetween != 1)
				{
					start_index++;
				}
				else
				{
					start_index = start_index + 2;
					/*for example 	array[0] = 2
									array[1] = 3
									array[2] = 4
					I want [0]th and [2]nd to concatinate i.e 24
					*/
				}
				temp[1] = array[start_index];

				temp[0] = ascii_bcd(temp[0]);
				temp[1] = ascii_bcd(temp[1]);
				data = concatenate(temp[0],temp[1]);
				break;
	case 0x03 : temp[0] = array[start_index];
				start_index++;
				temp[1] = array[start_index];

				temp[0] = ascii_bcd(temp[0]);
				temp[1] = ascii_bcd(temp[1]);
				temp_data1 = concatenate(temp[0],temp[1]);

				if(inbetween != 1)
				{
					start_index++;
				}
				else
				{
					start_index = start_index + 2;
				}
				temp[2] = array[start_index];

				temp[2] = ascii_bcd(temp[2]);
				data = concatenate(temp_data1,temp[2]);
				break;

	case 0x04 : temp[0] = array[start_index];
				start_index++;
				temp[1] = array[start_index];

				temp[0] = ascii_bcd(temp[0]);
				temp[1] = ascii_bcd(temp[1]);
				temp_data1 = concatenate(temp[0],temp[1]);

				start_index++;
				temp[2] = array[start_index];

				temp[2] = ascii_bcd(temp[2]);
				temp_data2 = concatenate(temp_data1,temp[2]);

				if(inbetween != 1)
				{
					start_index++;
				}
				else
				{
					start_index = start_index + 2;
				}
				temp[3] = array[start_index];

				temp[3] = ascii_bcd(temp[3]);
				data = concatenate(temp_data2,temp[3]);
				break;

	default:	break;

	}

	return data;
}
unsigned concatenate(unsigned x, unsigned y)
{
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;
}

uint8_t ascii_bcd(uint8_t character)
{
	uint8_t mem_sel_data = 0;

    if(character >= 'A')
    {
        mem_sel_data = character - 0x37;
    }
    else
    {
        mem_sel_data = character- 0x30;
    }

    return mem_sel_data;
}


void Read_brightness_from_FRAM(void)
{
	if(giMode == DAY)
	{
		giIntensityPercent = MemoryReadVariable(PRIMARY_MEMORY,DAY_MODE_BRIGHTNESS_ADDR,1);
	}
	else if(giMode == NIGHT)
	{
		giIntensityPercent = MemoryReadVariable(PRIMARY_MEMORY,NIGHT_MODE_BRIGHTNESS_ADDR,1);
	}
	else{}
}

void Write_brightness_to_FRAM(void)
{
	if(giMode == DAY)
	{
		MemoryWriteVariable(PRIMARY_MEMORY,DAY_MODE_BRIGHTNESS_ADDR, giIntensityPercent, 1);
	}
	else if(giMode == NIGHT)
	{
		MemoryWriteVariable(PRIMARY_MEMORY,NIGHT_MODE_BRIGHTNESS_ADDR, giIntensityPercent, 1);
	}else{}
}

void Service_remainder_hrs_calculation(Uint32 diff_eng_hrs)
{
	Uint32 Enghourmeter		= 0;

    Enghourmeter = MemoryReadVariable(PRIMARY_MEMORY, ENGINE_HOUR_METER_ADDR, 4);

    guiEngOilInterval = MemoryReadVariable(PRIMARY_MEMORY, CHANGE_ENGINE_OIL_INTERVAL_ADDR, 2);
    guiAirFilterInterval = MemoryReadVariable(PRIMARY_MEMORY, CHANGE_AIRFILTERS_INTERVAL_ADDR, 2);
    guiHydOilInterval = MemoryReadVariable(PRIMARY_MEMORY, CHANGE_HYDRAULIC_OIL_INTERVAL_ADDR, 2);
    guiSerEngInterval = MemoryReadVariable(PRIMARY_MEMORY, SERVICE_ENGINE_INTERVAL_ADDR, 2);
    guiSerMacInterval = MemoryReadVariable(PRIMARY_MEMORY, SERVICE_MACHINE_INTERVAL_ADDR, 2);

    guiEngOilNext = guiEngOilInterval;
    guiAirFilterNext = guiAirFilterInterval;
    guiHydOilNext = guiHydOilInterval;
    guiSerEngNext = guiSerEngInterval;
    guiSerMacNext = guiSerMacInterval;

    if(giHourMeter != 0)
    {
        diff_eng_hrs = giHourMeter - Enghourmeter;
    }
    else
    {
    	//diff_eng_hrs = Enghourmeter - giHourMeter;
    }

    guiEngOilRemain = guiEngOilInterval - diff_eng_hrs;
    guiAirFilterRemain = guiAirFilterInterval - diff_eng_hrs;
    guiHydOilRemain = guiHydOilInterval - diff_eng_hrs;
    guiSerEngRemain = guiSerEngInterval - diff_eng_hrs;
    guiSerMacRemain = guiSerMacInterval - diff_eng_hrs;
}

/* Shiftwise clock settings Screen */
void ProcessScreen29(void)
{
	switch(gucKeyPressed)
	{
		case KEY_ONE	:   memcpy(swcs_values,swcs_def_values,sizeof(swcs_values));
							/*for(int i = 0; i <= 17;i++)
							{
								swcs_values[i] = swcs_def_values[i];
							}*/

							store_swcs_data();
							read_swcs_data();
							break;
		case KEY_TWO	:
							swcs_cntr--;
							if(swcs_cntr < 0 || swcs_cntr > 250)
							{
								swcs_cntr = 17;
							}
							break;
		case KEY_THREE	:
							swcs_cntr++;
							if(swcs_cntr > 17)
							{
								swcs_cntr = 0;
							}
							break;
		case KEY_FOUR	:
							break;
		case KEY_FIVE	:
							break;
		case KEY_SIX	:save_status = 0;
							if(swcs_cntr == 0 || swcs_cntr == 3  || swcs_cntr == 6 ||
							   swcs_cntr == 9 || swcs_cntr == 12 || swcs_cntr == 15)
							{
								swcs_values[swcs_cntr]++;
								if(swcs_values[swcs_cntr] > 12)
								{
									swcs_values[swcs_cntr] = 1;
								}
							}
							else if(swcs_cntr == 1  || swcs_cntr == 4  || swcs_cntr == 7 ||
								    swcs_cntr == 10 || swcs_cntr == 13 || swcs_cntr == 16)
							{
								swcs_values[swcs_cntr]++;
								if(swcs_values[swcs_cntr] > 59)
								{
									swcs_values[swcs_cntr] = 0;
								}
							}
							else if(swcs_cntr == 2  || swcs_cntr == 5  || swcs_cntr == 8 ||
								    swcs_cntr == 11 || swcs_cntr == 14 || swcs_cntr == 17)
							{
								swcs_values[swcs_cntr]++;
								if(swcs_values[swcs_cntr] > 2)
								{
									swcs_values[swcs_cntr] = 1;
								}
							}
							break;
		case KEY_SEVEN	:save_status = 0;
							if(swcs_cntr == 0 || swcs_cntr == 3 || swcs_cntr == 6 ||
							   swcs_cntr == 9 || swcs_cntr == 12 || swcs_cntr == 15)
							{
								swcs_values[swcs_cntr]--;
								if(swcs_values[swcs_cntr] < 1 || swcs_values[swcs_cntr] > 250)
								{
									swcs_values[swcs_cntr] = 12;
								}
							}
							else if(swcs_cntr == 1  || swcs_cntr == 4  || swcs_cntr == 7 ||
								    swcs_cntr == 10 || swcs_cntr == 13 || swcs_cntr == 16)
							{
								swcs_values[swcs_cntr]--;
								if(swcs_values[swcs_cntr] < 0 || swcs_values[swcs_cntr] > 250)
								{
									swcs_values[swcs_cntr] = 59;
								}
							}
							else if(swcs_cntr == 2  || swcs_cntr == 5  || swcs_cntr == 8 ||
								    swcs_cntr == 11 || swcs_cntr == 14 || swcs_cntr == 17)
							{
								swcs_values[swcs_cntr]--;
								if(swcs_values[swcs_cntr] < 1 || swcs_values[swcs_cntr] > 250)
								{
									swcs_values[swcs_cntr] = 2;
								}
							}
							break;
		case KEY_EIGHT	:	store_swcs_data();
							read_swcs_data();
							break;
		case KEY_MENU	:
							swcs_cntr = 0;
							/* Menu Screen */
							giScreenSwitch = 11;
							save_status = 0;
							break;
		case KEY_ENTER	:

							break;
		default 		:
							break;
	}
}

void store_swcs_data(void)
{
	uint8_t temp_values[18] = {0};

	memcpy(temp_values,swcs_values,sizeof(swcs_values));

	for(uint8_t i = 2, j = 0; i <= 17, j <= 15; i = i+3, j = j+3)
	{
		if(temp_values[i] == MER_AM)
		{
			if(temp_values[j] == 12)
			{
				temp_values[j] = temp_values[j] - 12;/**convert to 24hrs format**/
			}
		}
		else if(temp_values[i] == MER_PM)
		{
			if(temp_values[j] < 12)
			{
				temp_values[j] = temp_values[j] + 12;/**convert to 24hrs format**/
			}
		}
	}

	for(uint8_t i = 0, addr = S1START_HH; i <= 17;i++,addr++)
	{
		MemoryWriteVariable(PRIMARY_MEMORY, addr, temp_values[i], 1);
	}
	save_status = 1;
}
void read_swcs_data(void)
{
	uint8_t temp_values[18] = {0};

    for(uint8_t i = 0, addr = S1START_HH; i <= 17;i++,addr++)
	{
    	temp_values[i] = MemoryReadVariable(PRIMARY_MEMORY, addr, 1);
		//values_of_swcs[i] = temp_values[i];
	}
    memcpy(values_of_swcs,temp_values,sizeof(temp_values));

	for(uint8_t i = 2, j = 0; i <= 17, j <= 15; i = i+3, j = j+3)
	{
		if(temp_values[i] == MER_AM)
		{
			if(temp_values[j] == 0)
			{
				temp_values[j] = temp_values[j] + 12;/**convert back to 12hrs format**/
			}
		}
		else if(temp_values[i] == MER_PM)
		{
			if(temp_values[j] > 12)
			{
				temp_values[j] = temp_values[j] - 12;/**convert back  to 12hrs format**/
			}
		}
	}
    memcpy(swcs_values,temp_values,sizeof(temp_values));
}
/* Shiftwise Working Hours Logging Screen */
void ProcessScreen30(void)
{
	switch(gucKeyPressed)
	{
		case KEY_ONE	:

							break;
		case KEY_TWO	:

							break;
		case KEY_THREE	:

							break;
		case KEY_FOUR	:

							break;
		case KEY_FIVE	:

							break;
		case KEY_SIX	:

							break;
		case KEY_SEVEN	:
							if(bStrtWorkinghrsLogging == 0)
							{
								bStrtWorkinghrsLogging = 1;
								//gucCopyStatus	  	 = 1;
								gucCopyStatus	  	= IDLE;
								//if(SDCardfuncBegin==0)
								{
									guiPendrivePoPup=1;
									guiPendriveStatus = DETECTING_PENDRIVE;
									start_pendrive_timeout=1;
									pendrivestatusstrttimer=0;
									pendrivestatuscounter=0;
									popeup_out_once=1;
								}
								#ifdef PENDRIVE_USED
								#else
									usb_attached = 1;
								#endif
							}
							break;
		case KEY_EIGHT	:
							if(unlink_datalog==0)
							{
								unlink_datalog=1;
			                	guiPendrivePoPup=1;
								pendrivestatusstrttimer=1;
							}
							break;
		case KEY_MENU	:
							/* Utilities Screen */
							giScreenSwitch = 14;

							bStrtWorkinghrsLogging=0;
							guiLogFileSize		 = 0;
							start_pendrive_timeout=0;
							pendrive_counter_timeout=0;
							pendrive_detected_timeout=0;
							guiPendrivePoPup=0;
							guiPendriveStatus = DETECTING_PENDRIVE;
							pendrivestatusstrttimer=0;
							pendrivestatuscounter=0;
							popeup_out_once=0;

							gucCopyStatus	  	= IDLE;
							break;
		case KEY_ENTER	:

							break;
		default 		:
							break;
	}
}
/*Diagnostics_2 screen*/
void ProcessScreen31(void)
{
	switch(gucKeyPressed)
	{
		case KEY_ONE	:
							guiDiagCounter=0;
							guiDiagCounttemp=0;
							guiDiagPopUp = 1;
							guiRequestDM1Data=0;
							guiDiagTimer=1;

							get_faults = 1;
							break;
		case KEY_TWO	:

							break;
		case KEY_THREE	:

							break;
		case KEY_FOUR	:

							break;
		case KEY_FIVE	:
#ifdef DOZER_P_VER
							SourceAdrr = 0;//VMS;
#else
							SourceAdrr--;
							if(SourceAdrr < 0 || SourceAdrr > 250)
							{
								SourceAdrr = 1;
							}
#endif
							break;
		case KEY_SIX	:
#ifdef DOZER_P_VER
							SourceAdrr = 0;//VMS;
#else
							SourceAdrr++;
							if(SourceAdrr > 1)
							{
								SourceAdrr = 0;
							}
#endif
							break;
		case KEY_SEVEN	:
							blue_upbutton_pressed = 1;
							if(Err_index[SourceAdrr] >= (NO_OF_DM1_MESSAGES - 1))
							{
								Err_index[SourceAdrr] = 0;
							}
							else
							{
								Err_index[SourceAdrr]++;
							}

							break;
		case KEY_EIGHT	:
							blue_downbutton_pressed = 1;
							if(Err_index[SourceAdrr] < 1)
							{
								Err_index[SourceAdrr] = (NO_OF_DM1_MESSAGES - 1);
							}
							else
							{
								Err_index[SourceAdrr]--;
							}

							break;
		case KEY_MENU	:
							/* Menu Screen */
							giScreenSwitch = 11;
							break;
		case KEY_ENTER	:

							break;
		default 		:
							break;
	}
}

/*Engine Hours Edit*/
void ProcessScreen32(void)
{
	switch(gucKeyPressed)
	{
		case KEY_ONE	:
							break;
		case KEY_TWO	:
							ehe_scroll--;
							if(ehe_scroll < 0 || ehe_scroll > 250)
							{
								ehe_scroll = 2;
							}
							break;
		case KEY_THREE	:
							ehe_scroll++;
							if(ehe_scroll > 2)
							{
								ehe_scroll = 0;
							}
							break;
		case KEY_FOUR	:

							break;
		case KEY_FIVE	:
							break;
		case KEY_SIX	:   save_status = 0;
							if(ehe_scroll == 0)//Engine Hours Reset
							{
								WarningPopUp=1;
								WarningMsg = 1;//You're ready reset your changes!!
							}
							else if(ehe_scroll == 1)//Adjusted Engine Hours
							{adjd_eng_hrs+= 1;}
							else if(ehe_scroll == 2)//Engine Hours
							{enghrs_en_dis= 0;}//Enable
							break;
		case KEY_SEVEN	:	save_status = 0;
							if(ehe_scroll == 0)//Engine Hours Reset
							{}
							else if(ehe_scroll == 1)//Adjusted Engine Hours
							{
								adjd_eng_hrs-= 1;
								if(adjd_eng_hrs < 0)
								{
									adjd_eng_hrs = 0;
								}
							}
							else if(ehe_scroll == 2)//Engine Hours
							{enghrs_en_dis= 1;}//Disable
							break;
		case KEY_EIGHT	:
							break;
		case KEY_MENU	:
							save_status = 0;
							if(WarningPopUp==1)
							{
								WarningPopUp=0;
								WarningMsg = 0;//You're ready discard your changes!!
							}
							else
							{
								/* Menu Screen */
								giScreenSwitch = 11;
							}
							break;
		case KEY_ENTER	:
							if(WarningPopUp==1)
							{
								WarningPopUp=0;
								WarningMsg = 0;//You're ready discard your changes!!
								save_status = 0;
							/********************Engine Hours reset completed******************************/
								eng_seconds_cntr = 0;
								eng_fractn_hr = 0;
								eng_actual_hr = 0;
								EngineHourMeter = 0;

								MemoryWriteVariable(PRIMARY_MEMORY, ENGINE_SEC_CNTR  , eng_seconds_cntr,2);
								MemoryWriteVariable(PRIMARY_MEMORY, ENGINE_FRACTN_HRS, eng_fractn_hr, 1);
								MemoryWriteVariable(PRIMARY_MEMORY, ENGINE_ACTUAL_HRS, eng_actual_hr, 4);
							/*****************************************************************************/
							}
							else
							{
								//adjd_eng_hrs;//save to memory
								MemoryWriteVariable(PRIMARY_MEMORY, ADJ_ENG_HRS, adjd_eng_hrs, 4);
								MemoryWriteVariable(PRIMARY_MEMORY, ENGHRS_EN_DIS, enghrs_en_dis, 1);
								save_status = 1;
							}
							break;
		default 		:
							break;
	}
}
