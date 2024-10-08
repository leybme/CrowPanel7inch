// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"
#include "message.h"





///////////////////// VARIABLES ////////////////////

// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
lv_obj_t *ui_Screen1;
lv_obj_t *ui_TabView1;
lv_obj_t *ui_TabPage1;
lv_obj_t *ui_Container1;
lv_obj_t *ui_Container6;
lv_obj_t *ui_Label2;
lv_obj_t *ui_Container2;
lv_obj_t *ui_Chart2;
lv_chart_series_t * ui_Chart2_series_1;
lv_obj_t *ui_Label1;
lv_obj_t *ui_Container3;
void ui_event_Button1(lv_event_t *e);
lv_obj_t *ui_Button1;
lv_obj_t *ui_LabelBtn1;
void ui_event_Button2(lv_event_t *e);
lv_obj_t *ui_Button2;
lv_obj_t *ui_LabelBtn2;
void ui_event_Button3(lv_event_t *e);
lv_obj_t *ui_Button3;
lv_obj_t *ui_LabelBtn3;
void ui_event_Button4(lv_event_t *e);
lv_obj_t *ui_Button4;
lv_obj_t *ui_LabelBtn4;
lv_obj_t *ui_Label3;
lv_obj_t *ui_TabPage2;
lv_obj_t *ui_Container4;
lv_obj_t *ui_TaskContainer;
lv_obj_t *ui_labeltask;
lv_obj_t *ui_DropdownTemperature;
lv_obj_t *ui_DropdownCondition;
lv_obj_t *ui_ConditionValue;
lv_obj_t *ui_LabelDo;
lv_obj_t *ui_DropdownAction;
lv_obj_t *ui_ActionValue;
lv_obj_t *ui_TaskContainer1;
lv_obj_t *ui_labeltask1;
lv_obj_t *ui_DropdownTemperature1;
lv_obj_t *ui_DropdownCondition1;
lv_obj_t *ui_ConditionValue1;
lv_obj_t *ui_LabelDo1;
lv_obj_t *ui_DropdownAction1;
lv_obj_t *ui_ActionValue1;
lv_obj_t *ui_TaskContainer2;
lv_obj_t *ui_labeltask2;
lv_obj_t *ui_DropdownTemperature2;
lv_obj_t *ui_DropdownCondition2;
lv_obj_t *ui_ConditionValue2;
lv_obj_t *ui_LabelDo2;
lv_obj_t *ui_DropdownAction2;
lv_obj_t *ui_ActionValue2;
lv_obj_t *ui_Keyboard3;
lv_obj_t *ui_TabPage3;
lv_obj_t *ui_Container5;
lv_obj_t *ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
#error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP != 0
#error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_Button1(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        outgoingMessage.type = MSG_CONTROL;
        outgoingMessage.target = TARGET_STEPPER1;
        outgoingMessage.value.value_int = 0;
        // Send message to all peers
        for (int i = 0; i < peerCount; ++i)
        {
            esp_err_t result = esp_now_send(peers[i].peer_addr, (uint8_t *)&outgoingMessage, sizeof(outgoingMessage));
            Serial.printf("Size of outgoingMessage: %d\n", sizeof(outgoingMessage));
            if (result == ESP_OK)
            {
                Serial.println("Sent with success");
            }
            else
            {
                Serial.println("Error sending the data");
            }
        }
    }
}
void ui_event_Button2(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        outgoingMessage.type = MSG_CONTROL;
        outgoingMessage.target = TARGET_STEPPER1;
        outgoingMessage.value.value_int = 20000;
        // Send message to all peers
        for (int i = 0; i < peerCount; ++i)
        {
            esp_err_t result = esp_now_send(peers[i].peer_addr, (uint8_t *)&outgoingMessage, sizeof(outgoingMessage));
            Serial.printf("Size of outgoingMessage: %d\n", sizeof(outgoingMessage));
            if (result == ESP_OK)
            {
                Serial.println("Sent with success");
            }
            else
            {
                Serial.println("Error sending the data");
            }
        }
    }
}

void ui_event_Button3(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        outgoingMessage.type = MSG_CONTROL;
        outgoingMessage.target = TARGET_STEPPER2;
        outgoingMessage.value.value_int = 0;
        // Send message to all peers
        for (int i = 0; i < peerCount; ++i)
        {
            esp_err_t result = esp_now_send(peers[i].peer_addr, (uint8_t *)&outgoingMessage, sizeof(outgoingMessage));
            Serial.printf("Size of outgoingMessage: %d\n", sizeof(outgoingMessage));
            if (result == ESP_OK)
            {
                Serial.println("Sent with success");
            }
            else
            {
                Serial.println("Error sending the data");
            }
        }
    }
}
void ui_event_Button4(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        outgoingMessage.type = MSG_CONTROL;
        outgoingMessage.target = TARGET_STEPPER2;
        outgoingMessage.value.value_int = 10000;
        // Send message to all peers
        for (int i = 0; i < peerCount; ++i)
        {
            esp_err_t result = esp_now_send(peers[i].peer_addr, (uint8_t *)&outgoingMessage, sizeof(outgoingMessage));
            Serial.printf("Size of outgoingMessage: %d\n", sizeof(outgoingMessage));
            if (result == ESP_OK)
            {
                Serial.println("Sent with success");
            }
            else
            {
                Serial.println("Error sending the data");
            }
        }
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                              false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen1);
}
