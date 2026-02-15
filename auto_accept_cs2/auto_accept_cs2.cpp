#include <iostream>
#include <vector>
#include <windows.h>
#include <thread>
#include <chrono>
#include <opencv2/opencv.hpp>

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

cv::Mat CaptureScreen() {
    HWND hwnd = GetDesktopWindow();
    HDC hwindowDC = GetDC(hwnd);
    HDC hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

    int screenx = GetSystemMetrics(SM_CXSCREEN);
    int screeny = GetSystemMetrics(SM_CYSCREEN);

    HBITMAP hbwindow = CreateCompatibleBitmap(hwindowDC, screenx, screeny);
    BITMAPINFOHEADER bi = { 0 };
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = screenx;
    bi.biHeight = -screeny;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;

    SelectObject(hwindowCompatibleDC, hbwindow);
    StretchBlt(hwindowCompatibleDC, 0, 0, screenx, screeny, hwindowDC, 0, 0, screenx, screeny, SRCCOPY);

    cv::Mat src;
    src.create(screeny, screenx, CV_8UC4);
    GetDIBits(hwindowDC, hbwindow, 0, screeny, src.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwnd, hwindowDC);

    cv::Mat bgr;
    cv::cvtColor(src, bgr, cv::COLOR_BGRA2BGR);
    return bgr;
}

void DetectAndClick() {
    std::this_thread::sleep_for(std::chrono::seconds(3));

    cv::Scalar lowerBound(72, 173, 44);
    cv::Scalar upperBound(92, 193, 64);

    while (true) {
        cv::Mat screenImg = CaptureScreen();
        cv::Mat mask;

        cv::inRange(screenImg, lowerBound, upperBound, mask);

        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        double maxArea = 0;
        cv::Rect bestRect;

        for (size_t i = 0; i < contours.size(); i++) {
            double area = cv::contourArea(contours[i]);
            if (area > maxArea) {
                maxArea = area;
                bestRect = cv::boundingRect(contours[i]);
            }
        }

        if (maxArea > 500) {
            int clickX = bestRect.x + (bestRect.width / 2);
            int clickY = bestRect.y + (bestRect.height / 2);

            SetCursorPos(clickX, clickY);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            INPUT input = { 0 };
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            SendInput(1, &input, sizeof(INPUT));

            std::this_thread::sleep_for(std::chrono::milliseconds(30));
            input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
            SendInput(1, &input, sizeof(INPUT));

            SetColor(10);
            std::cout << "CLICKED IN AUTOACCEPT Successfully\n";
            std::cout << "ReStarting in 3 seconds !\n";
            SetColor(7);

            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
        else {
            std::cout << "Searching accept color... Retrying in 1 seconds...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

int main() {
    SetProcessDPIAware();

    SetColor(12);
    std::cout << "\n    _   _  _ _____ ___  \n";
    std::cout << "   /_\\ | || |_   _/ _ \\ \n";
    std::cout << "  / _ \\| || | | || (_) |\n";
    std::cout << " /_/ \\_\\\\_,_| |_| \\___/ \n";

    SetColor(9);
    std::cout << "\n           AutoAccept \n";

    SetColor(15);
    std::cout << "\n   https://github.com/limwengming \n\n";

    SetColor(10);
    std::cout << "Starting in 3 seconds !\n";
    SetColor(7);

    DetectAndClick();

    return 0;
}