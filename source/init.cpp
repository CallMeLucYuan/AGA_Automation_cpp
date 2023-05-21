#include "includes.h"
extern int screen_type;
HWND game_hwnd;


void get_window_size()
{
    HWND hWnd = GetDesktopWindow();
    HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    // Get monitor logical width
    MONITORINFOEX monitorInfo;
    monitorInfo.cbSize = sizeof(monitorInfo);
    GetMonitorInfo(hMonitor, &monitorInfo);
    int cxLogical = (monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left);

    DEVMODE dm;
    dm.dmSize = sizeof(dm);
    dm.dmDriverExtra = 0;
    EnumDisplaySettings(monitorInfo.szDevice, ENUM_CURRENT_SETTINGS, &dm);
    int cxPhysical = dm.dmPelsWidth;
    switch(cxPhysical)
    {
        case 1024:
            screen_type = e_1024x768_enum;
        break;
        case 1600:
            screen_type = e_1600x900_enum;
        break;
        case 1920:
            screen_type = e_1920x1080_enum;
        break;
        case 2560:
            screen_type = e_2560x1440_enum;
        break;
        default:
            screen_type = e_1920x1080_enum;
        break;
    }
    std::cout <<"Screen width : " << screen_size_table[screen_type].width  << std::endl;
    std::cout <<"Screen height : "<< screen_size_table[screen_type].height << std::endl;
    return;
}

void get_game_window()
{
    std::cout <<"Getting AGA window press ENTER to procced"  << std::endl;
    std::cin.get();
    game_hwnd = FindWindowA("UnityWndClass", NULL);
    if (game_hwnd != NULL) 
    {
        std::cout <<"Got AGA window "  << std::endl;
        //Get window title
        int length = GetWindowTextLength(game_hwnd);       
        char* title = new char[length + 1];
        GetWindowText(game_hwnd, title, length + 1);
        
        std::cout <<"title : "<< title << std::endl;
        delete[] title;
    }
    else
    {
        std::cout <<"Window not found "<< std::endl;
    }
}

bool init()
{
    get_window_size();
    // get_game_window();
    // if (game_hwnd != NULL) 
    //     return TRUE;
    // else
    //     return FALSE;
    return TRUE;
}


