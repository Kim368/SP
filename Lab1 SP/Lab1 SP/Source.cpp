#include <Windows.h>

int CALLBACK  wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
/*CALLBACK - #define ��� stdcall (���������� ��� �������, ���������� ������ ����� ��� �� ����� ������� ����
 wWinMain - �������������
 HINSTANCE  hInstance - ��������� �� ������ ������������ ������, �� ���������. ����� ������.
 HINSTANCE - �� ������������ ��� ���. ��� 16 ������ ������ �������.
 PWSTR szCmdLine - ��������� �� ������ UNICOD �������� �������������� ����. �� ���� ������ ���������.
 int nCmdShow - �������� ���������� �� �� ��� ����� ������������ ���� (�������, ���������, �� ���� ����� � �.�.).
*/
{
    MSG msg{};                             // ���������, ������� �������� � ���� ���������� � ����������� (����� Windows � ����� ��� ����� ������).
    HWND hwnd{};                          // ���������� ���� ( HANDLE ����. �� ������ ���� � ������� ��������� ���������� � ����� ����).
    WNDCLASSEX wc{ sizeof(WNDCLASSEX) }; // ��� ��������� �������� �� ����� �-�� ���� (� �������� ������� �������).���. ���������� �������������.
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hInstance = hInstance;
    wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT
    {   
        static int x = 300;
        static int y = 500;
        switch (uMsg)
        {
            case WM_CREATE:
            {
                // MessageBox(hWnd, L"Hello!", L"ok", MB_ICONINFORMATION);
                HWND hButton1 = CreateWindow(
                    L"BUTTON",
                    L"START",
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    0, 530, 300, 25,
                    hWnd, reinterpret_cast<HMENU>(1), nullptr, nullptr
                );
                HWND hButton2 = CreateWindow(
                    L"BUTTON",
                    L"STOP",
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    300, 530, 290, 25,
                    hWnd, reinterpret_cast<HMENU>(0), nullptr, nullptr
                );
 
            }
            return 0;

            case WM_COMMAND:
            {   
                switch (LOWORD(wParam))
                {
                
                    case 1: {
                        SetTimer(hWnd, 11, 10, NULL);
                    }
                      break;
                    case 0: {
                        KillTimer(hWnd, 11);
                    }
                          break;
                }
            }
            return 0;

            case WM_TIMER: {
                if (wParam == 11)
                {
                    y -= 2;
                    InvalidateRect(hWnd, NULL, TRUE); // ���� �������� FALSE - ��� �� ����� ����������������.
                }
            }
            return 0;

            case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);
                
                TextOut(hdc, x, y, L"can", 4);

                EndPaint(hWnd, &ps);
            }
            return 0;

            case WM_DESTROY:
            {
                KillTimer(hWnd, 11);
                PostQuitMessage(EXIT_SUCCESS);
            }
            return 0;
        }
        return DefWindowProc(hWnd, uMsg, wParam, lParam); // ���������� � ������ ���� ��������� �� ��������������
    };
    wc.lpszClassName = L"MyAppClass";
    wc.lpszMenuName = nullptr;
    wc.style = CS_VREDRAW | CS_HREDRAW;
    /*
    wc.cbClsExtra = 0; �������� �� �������������� ��������� ������ �
    wc.cbWndExtra = 0; ������ ������ ���� (��� ������ ����� ���� ���������� � ����).

    hbrBackground - ��� ���� ��������� ���������� ����� ������� ���������� ����.
    GetStockObject - ���������� GDI ������ ������� �� ����� �������� � ���� HBRUSH.

    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);     - HANDLE �������.
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);   - HANDLE ������.
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION); - HANDLE ������ (������������ ������ ����� � ��������� ����).

    wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT
    - ��� ��������� �������� �� ��������� ��������� (MSG msg{};)
      ��������� 4 ������������ ��������� � ���������� LRESULT (���������).
      HWND hWnd     - ���������� ���� � �������� �������� ���������.
      UINT uMsg     - ��� ���������.
      WPARAM wParam - ��������� � �� ��������� ����������� ��� ��������� ����������.
      LPARAM lParam - ��������� � �� ��������� ����������� ��� ��������� ����������.

      wc.lpszClassName = L"MyAppClass";   - ��� ������ (�����).
      wc.lpszMenuName = nullptr;          - ��������� �� ��� ����.
      wc.style = CS_VREDRAW | CS_HREDRAW; - ����� ���� (2 ����� �� ���������)
 */

    if (!RegisterClassEx(&wc))
        return EXIT_FAILURE;

    if (hwnd = CreateWindow(wc.lpszClassName, L"Star wars!", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)
        return EXIT_FAILURE;
    /*
     if (!RegisterClassEx(&wc)) - ����������� � ������� ������ ������ ����.
      return EXIT_FAILURE;

     if (hwnd = CreateWindow(wc.lpszClassName, L"���������!", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, wc.hInstance, nullptr ); hwnd == INVALID_HANDLE_VALUE)
      return EXIT_FAILURE;
      - �������� ������ ����.
      wc.lpszClassName    - ��� ������.
      L"���������!"       - ��������� ����.
      WS_OVERLAPPEDWINDOW - ����� ���� (����� ���������� � msdn).
      0, 0,               - X � Y ���������� ���� (������������� �� ����� ������� �����).
      600, 600,           - ������, ������.


     */
    ShowWindow(hwnd, nCmdShow); // ����� ����
    UpdateWindow(hwnd);         // ����������� ���� (��������� HANDLE)

    while (GetMessage(&msg, nullptr, 0, 0)) // ���� ��������� ���������
    {
        TranslateMessage(&msg); // ������� �������������� ��������� ���������
        DispatchMessage(&msg);  // �������  ������� ��������� � ������� ��������� �� ���������
    }

    return static_cast<int> (msg.wParam); // ������������ �������� ����� �����



    // hWnd - ������������� ����.
    // nullptr - ������� ���������.
}