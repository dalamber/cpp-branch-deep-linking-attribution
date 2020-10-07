// TestBed.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "TestBed.h"

#include <BranchIO/String.h>

#include "Button.h"
#include "TextField.h"
#include "Util.h"

#include "BranchOperations.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

using namespace BranchIO;
using namespace std;

// Static layout
// Define any further buttons here
static int const ID_TEXT_FIELD = 1000;
static int const ID_OPEN_BUTTON = 1001;
static int const ID_LOGIN_BUTTON = 1002;
static int const ID_LOGOUT_BUTTON = 1003;
static int const ID_STANDARD_EVENT_BUTTON = 1004;
static int const ID_CUSTOM_EVENT_BUTTON = 1005;
static int const ID_GET_SHORT_URL_BUTTON = 1006;
static int const ID_CLOSE_BUTTON = 1007;
static int const ID_TRACKING_BUTTON = 1008;
static int const ID_GET_IDENTITY_BUTTON = 1009;
static int const ID_SHOW_SESSION_BUTTON = 1010;

TextField outputTextField(L"Initializing...", 440, 20, 400, 400, ID_TEXT_FIELD);
Button openButton(L"Open", 20, 20, 190, 50, ID_OPEN_BUTTON);
Button closeButton(L"Close", 20, 90, 190, 50, ID_CLOSE_BUTTON);
Button loginButton(L"Login", 20, 160, 190, 50, ID_LOGIN_BUTTON);
Button logoutButton(L"Logout", 20, 230, 190, 50, ID_LOGOUT_BUTTON);
Button standardEventButton(L"Standard Event", 230, 20, 190, 50, ID_STANDARD_EVENT_BUTTON);
Button customEventButton(L"Custom Event", 230, 90, 190, 50, ID_CUSTOM_EVENT_BUTTON);
Button getShortURLButton(L"Get Short URL", 230, 160, 190, 50, ID_GET_SHORT_URL_BUTTON);
Button trackingButton(L"Disable Tracking", 230, 230, 190, 50, ID_TRACKING_BUTTON);
Button getIdentityButton(L"Get Identity", 20, 300, 190, 50, ID_GET_IDENTITY_BUTTON);
Button showSessionButton(L"Show Session", 230, 300, 190, 50, ID_SHOW_SESSION_BUTTON);

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);

    // Initialize global strings
    LoadStringW(hInstance, IDC_TESTBED, szWindowClass, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);

    // Initialize Branch
    BranchOperations::initBranch(lpCmdLine ? lpCmdLine : L"", &outputTextField);

    // While the Branch open request is in flight, try to obtain the named mutex.
    if (Util::isInstanceRunning())
    {
        // Wait for response from Branch, send to running instance, then exit
        BranchOperations::waitForOpen(INFINITE);
        String sResponse(BranchOperations::getOpenResponse().stringify());
        Util::sendToRunningInstance(szWindowClass, sResponse.wstr());
        // Now exit
        return 0;
    }

    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTBED));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTBED));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TESTBED);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);

   /*
    * Set up any further buttons here.
    */

   outputTextField.create(hWnd);
   openButton.create(hWnd);
   loginButton.create(hWnd);
   logoutButton.create(hWnd);
   standardEventButton.create(hWnd);
   customEventButton.create(hWnd);
   getShortURLButton.create(hWnd);
   closeButton.create(hWnd);
   trackingButton.create(hWnd);
   getIdentityButton.create(hWnd);
   showSessionButton.create(hWnd);

   trackingButton.setText(BranchOperations::getTrackingButtonLabel());

   openButton.setButtonPressCallback([]() {
       BranchOperations::openURL(L"https://win32.app.link/crtafBueu9");
   });
   loginButton.setButtonPressCallback([]() {
       BranchOperations::login(L"user1");
   });
   logoutButton.setButtonPressCallback(BranchOperations::logout);
   standardEventButton.setButtonPressCallback(BranchOperations::logStandardEvent);
   customEventButton.setButtonPressCallback(BranchOperations::logCustomEvent);
   getShortURLButton.setButtonPressCallback(BranchOperations::getShortURL);
   closeButton.setButtonPressCallback(BranchOperations::closeSession);
   trackingButton.setButtonPressCallback([]() {
       BranchOperations::toggleTracking();
       trackingButton.setText(BranchOperations::getTrackingButtonLabel());
   });
   getIdentityButton.setButtonPressCallback([]() {
       wstring identity = BranchOperations::getIdentity();
       if (identity.empty()) {
           outputTextField.appendText(L"No developer identity is set.");
       }
       else {
           outputTextField.appendText(wstring(L"Developer identity is \"") + identity + L"\"");
       }
   });
   showSessionButton.setButtonPressCallback([]() {
       outputTextField.appendText(BranchOperations::getSessionInfo());
   });

   BranchOperations::showInitializationMessage();

   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;

            // Add any further buttons here
            case ID_OPEN_BUTTON:
                openButton.onPress();
                break;
            case ID_LOGIN_BUTTON:
                loginButton.onPress();
                break;
            case ID_LOGOUT_BUTTON:
                logoutButton.onPress();
                break;
            case ID_STANDARD_EVENT_BUTTON:
                standardEventButton.onPress();
                break;
            case ID_CUSTOM_EVENT_BUTTON:
                customEventButton.onPress();
                break;
            case ID_GET_SHORT_URL_BUTTON:
                getShortURLButton.onPress();
                break;
            case ID_CLOSE_BUTTON:
                closeButton.onPress();
                break;
            case ID_TRACKING_BUTTON:
                trackingButton.onPress();
                break;
            case ID_GET_IDENTITY_BUTTON:
                getIdentityButton.onPress();
                break;
            case ID_SHOW_SESSION_BUTTON:
                showSessionButton.onPress();
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COPYDATA:
        {
            COPYDATASTRUCT* cds = (COPYDATASTRUCT*)lParam;
            if (cds->dwData == 'BNC')
            {
                // Open response received from another instance
                const wchar_t* buffer((const wchar_t*)cds->lpData);
                size_t length((size_t)cds->cbData / sizeof(wchar_t) - 1);

                wstring payload(buffer, buffer + length);
                outputTextField.appendText(wstring(L"Forwarded open response: ") + payload);
            }
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}