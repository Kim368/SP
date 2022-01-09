#include <Windows.h>
#include <fileapi.h>
#include <Tchar.h>

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
    MSG msg{};                             // Структура, которая содержит в себе информацию о соообщениях (между Windows и окном или между окнами).
    HWND hwnd{};                          // Дескриптор окна ( HANDLE указ. на объект ядра в котором храниться информация о нашем окне).
    WNDCLASSEX wc{ sizeof(WNDCLASSEX) }; // Эта структура отвечает за некие х-ки окна (в фигурных скобках размеры).Исп. агрегатная инициализация.
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
            Находим на диске С:
            количество секторов в кластере,
            количество байтов в секторе,
            общее количество свободных кластеров на диске,
            общее количество кластеров на диске
            */

            fResult = GetDiskFreeSpaceA("C:\\",
                &dwSectPerClust,
                &dwBytesPerSect,
                &dwFreeClusters,
                &dwTotalClusters);


            // Выводим на экран

            wchar_t  wcsSomeStr[64];

            _itow_s(dwSectPerClust, wcsSomeStr, 10);
            TextOut(hdc, 10, 10, L"количество секторов в кластере:", _tcslen(L"количество секторов в кластере:"));
            TextOut(hdc, 10, 25, wcsSomeStr, _tcslen(wcsSomeStr));

            _itow_s(dwBytesPerSect, wcsSomeStr, 10);
            TextOut(hdc, 10, 50, L"количество байтов в секторе:", _tcslen(L"количество байтов в секторе:"));
            TextOut(hdc, 10, 65, wcsSomeStr, _tcslen(wcsSomeStr));

            _itow_s(dwFreeClusters, wcsSomeStr, 10);
            TextOut(hdc, 10, 90, L"общее количество свободных кластеров на диске:", _tcslen(L"общее количество свободных кластеров на диске:"));
            TextOut(hdc, 10, 105, wcsSomeStr, _tcslen(wcsSomeStr));

            _itow_s(dwTotalClusters, wcsSomeStr, 10);
            TextOut(hdc, 10, 130, L"общее количество кластеров на диске:", _tcslen(L"общее количество кластеров на диске:"));
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
        return DefWindowProc(hWnd, uMsg, wParam, lParam); // вызывается в случае если сообщение не обрабатывается
    };
    wc.lpszClassName = L"MyAppClass";
    wc.lpszMenuName = nullptr;
    wc.style = CS_VREDRAW | CS_HREDRAW;
   

    if (!RegisterClassEx(&wc))
        return EXIT_FAILURE;

    if (hwnd = CreateWindow(wc.lpszClassName, L"Star wars! v2", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)
        return EXIT_FAILURE;
    
    ShowWindow(hwnd, nCmdShow); // показ окна
    UpdateWindow(hwnd);         // перерисовка окна (передаётся HANDLE)

    while (GetMessage(&msg, nullptr, 0, 0)) // Цикл обработки сообщений
    {
        TranslateMessage(&msg); // функция расшифровывает системное сообщение
        DispatchMessage(&msg);  // функция  передаёт сообщение в оконную процедуру на обработку
    }

    return int (msg.wParam); // возвращаемое значение точки входа



    // hWnd - идентификатор окна.
    // nullptr - нулевой указатель.
}