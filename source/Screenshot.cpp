#include "includes.h"
using cv::Mat;

Screenshot::Screenshot()
{
    double zoom = getZoom();
    m_width = GetSystemMetrics(SM_CXSCREEN) * zoom;
    m_height = GetSystemMetrics(SM_CYSCREEN) * zoom;
    m_screenshotData = new char[m_width * m_height * 4];
    memset(m_screenshotData, 0, m_width);

    // Get Screen DC
    m_screenDC = GetDC(NULL);
    m_compatibleDC = CreateCompatibleDC(m_screenDC);

    //Create Bitmap
    m_hBitmap = CreateCompatibleBitmap(m_screenDC, m_width, m_height);
    SelectObject(m_compatibleDC, m_hBitmap);
}
Screenshot::~Screenshot()
{
    delete[] static_cast<char*>(m_screenshotData);
}
/* Get all screen screenshot */
Mat Screenshot::getScreenshot()
{
    //Get Bitmap
    BitBlt(m_compatibleDC, 0, 0, m_width, m_height, m_screenDC, 0, 0, SRCCOPY);
    GetBitmapBits(m_hBitmap, m_width * m_height * 4, m_screenshotData);

    // Get bitmap
    Mat screenshot(m_height, m_width, CV_8UC4, m_screenshotData);

    return screenshot;
}

/** @brief get cut picture
 * @param x screenshot left top 
 * @param y screenshot left top 
 * @param width 
 * @param height 
 */
Mat Screenshot::getScreenshot(int x, int y, int width, int height)
{
    Mat screenshot = getScreenshot();
    return screenshot(cv::Rect(x, y, width, height));
}

/* Getzoom */
double Screenshot::getZoom()
{
    // get Current Window
    HWND hWnd = GetDesktopWindow();
    HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    // Get monitor logical width
    MONITORINFOEX monitorInfo;
    monitorInfo.cbSize = sizeof(monitorInfo);
    GetMonitorInfo(hMonitor, &monitorInfo);
    int cxLogical = (monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left);

    // Get monitor physical width
    DEVMODE dm;
    dm.dmSize = sizeof(dm);
    dm.dmDriverExtra = 0;
    EnumDisplaySettings(monitorInfo.szDevice, ENUM_CURRENT_SETTINGS, &dm);
    int cxPhysical = dm.dmPelsWidth;

    return cxPhysical * 1.0 / cxLogical;
}

Mat Screenshot::getWinodwshot()
{
    int width,height;
    Mat screenshot = getScreenshot();
    m_hwnd = FindWindowA("UnityWndClass", NULL);
    RECT rect;
    POINT windowPosition = { rect.left, rect.top };
    GetWindowRect(m_hwnd, &rect);
    
    width = rect.right - rect.left;
    height =rect.bottom - rect.top;
    //std::cout << width << std::endl;
    //std::cout << height << std::endl;
    return screenshot(cv::Rect(rect.left, rect.top, width, height));
}
