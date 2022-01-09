#include <Windows.h>
#include <fileapi.h>
#include <Tchar.h>

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
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
        switch (uMsg)
        {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            
            DWORD dwSectPerClust, dwBytesPerSect, dwFreeClusters, dwTotalClusters;
            BOOL fResult;
           
            /*
            ������� �� ����� �:
            ���������� �������� � ��������,
            ���������� ������ � �������,
            ����� ���������� ��������� ��������� �� �����,
            ����� ���������� ��������� �� �����
            */

            fResult = GetDiskFreeSpaceA("C:\\",
                &dwSectPerClust,
                &dwBytesPerSect,
                &dwFreeClusters,
                &dwTotalClusters);


            // ������� �� �����

            wchar_t  wcsSomeStr[64];

            _itow_s(dwSectPerClust, wcsSomeStr, 10);
            TextOut(hdc, 10, 10, L"���������� �������� � ��������:", _tcslen(L"���������� �������� � ��������:"));
            TextOut(hdc, 10, 25, wcsSomeStr, _tcslen(wcsSomeStr));

            _itow_s(dwBytesPerSect, wcsSomeStr, 10);
            TextOut(hdc, 10, 50, L"���������� ������ � �������:", _tcslen(L"���������� ������ � �������:"));
            TextOut(hdc, 10, 65, wcsSomeStr, _tcslen(wcsSomeStr));

            _itow_s(dwFreeClusters, wcsSomeStr, 10);
            TextOut(hdc, 10, 90, L"����� ���������� ��������� ��������� �� �����:", _tcslen(L"����� ���������� ��������� ��������� �� �����:"));
            TextOut(hdc, 10, 105, wcsSomeStr, _tcslen(wcsSomeStr));

            _itow_s(dwTotalClusters, wcsSomeStr, 10);
            TextOut(hdc, 10, 130, L"����� ���������� ��������� �� �����:", _tcslen(L"����� ���������� ��������� �� �����:"));
            TextOut(hdc, 10, 145, wcsSomeStr, _tcslen(wcsSomeStr));

            

            EndPaint(hWnd, &ps);
        }
        return 0;

        case WM_DESTROY:
        {
            
            PostQuitMessage(EXIT_SUCCESS);
        }
        return 0;
        }
        return DefWindowProc(hWnd, uMsg, wParam, lParam); // ���������� � ������ ���� ��������� �� ��������������
    };
    wc.lpszClassName = L"MyAppClass";
    wc.lpszMenuName = nullptr;
    wc.style = CS_VREDRAW | CS_HREDRAW;
   

    if (!RegisterClassEx(&wc))
        return EXIT_FAILURE;

    if (hwnd = CreateWindow(wc.lpszClassName, L"Star wars! v2", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)
        return EXIT_FAILURE;
    
    ShowWindow(hwnd, nCmdShow); // ����� ����
    UpdateWindow(hwnd);         // ����������� ���� (��������� HANDLE)

    while (GetMessage(&msg, nullptr, 0, 0)) // ���� ��������� ���������
    {
        TranslateMessage(&msg); // ������� �������������� ��������� ���������
        DispatchMessage(&msg);  // �������  ������� ��������� � ������� ��������� �� ���������
    }

    return int (msg.wParam); // ������������ �������� ����� �����



    // hWnd - ������������� ����.
    // nullptr - ������� ���������.
}