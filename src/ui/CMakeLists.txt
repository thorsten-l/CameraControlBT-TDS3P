SET(SOURCES screens/ui_StartScreen.c
    screens/ui_BluetoothScreen.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_286491071.c
    images/ui_img_bluetooth3_64_png.c
    images/ui_img_1941201141.c
    images/ui_img_1803052213.c
    images/ui_img_766493279.c
    images/ui_img_wifi3_64_png.c)

add_library(ui ${SOURCES})
