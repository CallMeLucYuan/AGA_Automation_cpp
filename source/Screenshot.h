#pragma once
#include "includes.h"

class Screenshot
{
public:
    Screenshot();
    double static getZoom();
    cv::Mat getScreenshot();
    cv::Mat getScreenshot(int x, int y, int width, int height);
    cv::Mat getWinodwshot();
    ~Screenshot();
private:
    int m_width;
    int m_height;
    HWND m_hwnd;
    HDC m_screenDC;
    HDC m_compatibleDC;
    HBITMAP m_hBitmap;
    LPVOID m_screenshotData = nullptr;
};
