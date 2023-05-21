#include "includes.h"

int Mouse_click(int x, int y ,int width, int height) 
{
    INPUT input;
    if(x > width || y > height )
    {
        return FALSE;
    } 
    else
    {
        input.type = INPUT_MOUSE;
        input.mi.dx =  (x * 65536) / width; 
        input.mi.dy =  (y * 65536) / height;
        input.mi.mouseData = 0;
        input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
        input.mi.time = 0;
        input.mi.dwExtraInfo = 0;
    }
    return SendInput(1, &input, sizeof(INPUT));
}

int mouse_click_wait(int x, int y ,int width, int height,int time, bool flag)
{
    if(!flag)
    {        
        Mouse_click(x, y,width,height);
    }
    else
    {
        return FALSE;
    }
    for(int i=0;i<time/100;i++)
    {
        Sleep(100);
        if(flag)
        {
        return FALSE;
        }
    }
    return TRUE;
}


int Key_press(int VK, int time, bool extended)
{
    SHORT key;
    UINT mappedkey;
    INPUT input = { 0 };
    mappedkey= MapVirtualKey(VK, MAPVK_VK_TO_VSC);
    input.type = INPUT_KEYBOARD;       
    input.ki.dwFlags = KEYEVENTF_SCANCODE;
    if(extended)
    {
        input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
    }
    input.ki.wScan = mappedkey;
    SendInput(1, &input, sizeof(input));
    Sleep(time); 
    input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    return SendInput(1, &input, sizeof(input));
}

int Key_down(int VK,bool extended)
{
    SHORT key;
    UINT mappedkey;
    INPUT input = { 0 };
    mappedkey= MapVirtualKey(VK, MAPVK_VK_TO_VSC);
    input.type = INPUT_KEYBOARD;       
    input.ki.dwFlags = KEYEVENTF_SCANCODE;
    if(extended)
    {
        input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
    }
    input.ki.wScan = mappedkey;
    return SendInput(1, &input, sizeof(input));
}

int Key_up(int VK,bool extended)
{
    SHORT key;
    UINT mappedkey;
    INPUT input = { 0 };
    mappedkey= MapVirtualKey(VK, MAPVK_VK_TO_VSC);
    input.ki.wScan = mappedkey;
    input.type = INPUT_KEYBOARD;       
    input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    if(extended)
    {
        input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
    }
    return SendInput(1, &input, sizeof(input));
}

int Char_press(char c,int time)
{
    SHORT key;
    key = VkKeyScan(c); 
    return  Key_press(LOBYTE(key), time ,0);
}


int Char_down(char c,bool extended)
{
    SHORT key;
    key = VkKeyScan(c); 
    return  Key_down(LOBYTE(key),0);

}

int Char_up(char c)
{
    SHORT key;
    key = VkKeyScan(c); 
    return  Key_up(LOBYTE(key) , 0);
}


extern std::atomic<bool> terminateThread;  

void key_do(int screen_type) 
{
    printf("Thread started\n");
    int i;
    int height, width;
    height = screen_size_table[screen_type].height;
    width = screen_size_table[screen_type].width;
    double zoom =  screen_size_table[screen_type].width /2560.0;
    mouse_click_wait((int)1500*zoom,(int)1225*zoom,  width, height, 5000,  terminateThread);
    Mouse_click((int)1280*zoom, (int)620*zoom,width,height);
    Sleep(100);
    mouse_click_wait((int)1280*zoom, (int)620*zoom,  width, height, 2000,  terminateThread);
    mouse_click_wait((int)1280*zoom, (int)1225*zoom, width, height,10000,  terminateThread);

    
    while (!terminateThread) 
    {
        Key_down(VK_RIGHT, 1);
        Key_down(VK_UP, 1);
            for(i=0;i<100;i++)
            {
                Char_press('x', 100);
                if(25 == i)
                {
                    Char_press(' ', 50);
                    Sleep(100);

                } 
                if(50 == i)
                {
                    Char_press('d', 50);
                    Sleep(100);
                }
                if(75 == i)
                {
                    Char_press('s', 50);
                    Sleep(100);
                }         
                Sleep(100);
                if(terminateThread)
                {
                    break;
                }
            }

        Key_up(VK_RIGHT,1);
        Key_up(VK_UP,1);
        Char_press('r', 100);
        Sleep(100);
    }
    std::cout << "Thread is terminated." << std::endl;
}
