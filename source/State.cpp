#include "includes.h"
extern std::atomic<bool> terminateThread; //FLag to terminateThread
extern std::thread myThread;
/*************************
 * Idle State
 * 
 * 
 * 
 * *********************/
void Idle_state::enter()
{
    std::cout << "Entering Idle_state" << std::endl;
}

int Idle_state::update() 
{
    using namespace cv;
    
    if(GetAsyncKeyState(VK_LSHIFT))
    {
        
        return STATE_STOP;
    }

    Screenshot screenshot;    
    Mat templ = imread("./Picture/strt_inv.png"); // templ
    Mat result;             // Match result
    double minVal =99.0, maxVal;  // result max and min val
    Point minLoc, maxLoc;   // result max and min loc
    Mat img = screenshot.getScreenshot();
    resize(img,img,Size(1280,720));
    // Screenshot got BGRA
    cvtColor(img, img, COLOR_BGRA2BGR);
    Rect roi(400, 450, 500, 250);
    Mat roi_image = Mat::zeros(img.size(), img.type());
    img(roi).copyTo(roi_image(roi));
    matchTemplate(roi_image, templ, result, TM_SQDIFF_NORMED); 
    // //find best match in SQDIFF is minVal
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
    templ.release();
    img.release();
    roi_image.release();
    result.release();
    if (minVal < 0.14) 
    {        
        #ifdef DEBUG
        Rect rect(minLoc.x, minLoc.y, templ.cols, templ.rows);
        rectangle(img, rect, Scalar(0, 0, 255), 2);
        #endif
        return STATE_BATTLE;
    } 
    #ifdef DEBUG
    imshow("Result", img);
    waitKey(1);
    #endif
    return STAY_STATE;
}

void Idle_state::exit() 
{
    #ifdef DEBUG
    cv::destroyAllWindows();
    #endif
    std::cout << "Exiting Idle_state" << std::endl;
}

/*************************
 * Battle State
 * 
 * 
 * 
 * *********************/

void Battle_state::enter() 
{
    std::cout << "Entering Battle_state" << std::endl;
    terminateThread = false;
    myThread = std::thread(key_do,screen_type);
}

int Battle_state::update() 
{
    using namespace cv;
    if(GetAsyncKeyState(VK_LSHIFT))
    {
        return STATE_STOP;
    }

    Screenshot screenshot;    
    Mat templ = imread("./Picture/Finish.png"); // templ
    Mat result;             // Match result
    double minVal, maxVal;  // result max and min val
    Point minLoc, maxLoc;   // result max and min loc
    double threshold = 0.98;
    Mat img = screenshot.getScreenshot();
    resize(img,img,Size(1280,720));
    // Screenshot got BGRA
    cvtColor(img, img, COLOR_BGRA2BGR);
    Rect roi(400, 450, 200, 200);
    Mat roi_image = Mat::zeros(img.size(), img.type());
    img(roi).copyTo(roi_image(roi));
    matchTemplate(roi_image, templ, result, TM_SQDIFF_NORMED); 
    //find best match in SQDIFF is minVal
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
    if (minVal < 0.14) 
    {        
        #ifdef DEBUG
        Rect rect(minLoc.x, minLoc.y, templ.cols, templ.rows);
        rectangle(img, rect, Scalar(0, 0, 255), 2);
        #endif
        return STATE_IDLE;
    } 

    return STAY_STATE;
}

void Battle_state::exit() 
{
    std::cout << "Exiting Battle_state" << std::endl;
    terminateThread = true;
    myThread.join();
    
    int height, width;
    height = screen_size_table[screen_type].height;
    width = screen_size_table[screen_type].width;
    double zoom =  screen_size_table[screen_type].width /2560.0;
    mouse_click_wait((int)1280*zoom,(int)1350*zoom,  width, height, 2000,  false);
    mouse_click_wait((int)1280*zoom, (int)1350*zoom, width, height, 4000,  false);
    Mouse_click((int)1280*zoom, (int)1050*zoom,width,height);
}

/*************************
 * Stop State
 * 
 * 
 * 
 * *********************/

void Stop_state::enter() 
{
    std::cout << "Entering Stop_state" << std::endl;
    std::cout << "CONTROL to start" << std::endl;
    std::cout << "Shift to force stop" << std::endl;
}

int Stop_state::update() 
{
    if(GetAsyncKeyState(VK_LCONTROL))
    {
        Sleep(1000);
        return STATE_IDLE;
    }
    
    
    return STAY_STATE;
}

void Stop_state::exit() 
{
    std::cout << "Exiting Stop_state" << std::endl;
}

