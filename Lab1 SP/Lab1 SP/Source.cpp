#include <Windows.h>

int CALLBACK  wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
/*CALLBACK - #define для stdcall (соглашение для вызовов, вызываемый объект будет сам за собой очищать стек
 wWinMain - идентификатор
 HINSTANCE  hInstance - указатель на начало исполняемого модуля, мз сигнатуры. адрес памяти.
 HINSTANCE - не используется был акт. для 16 битных версий виндовс.
 PWSTR szCmdLine - указатель на строку UNICOD символов оканчивающихся нулём. По сути просто аргументы.
 int nCmdShow - параметр отвечающий за то как будет показываться окно (свёрнуто, развёрнуто, на весь экран и т.д.).
*/
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
                    InvalidateRect(hWnd, NULL, TRUE); // если оставить FALSE - фон не будет перерисовываться.
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
        return DefWindowProc(hWnd, uMsg, wParam, lParam); // вызывается в случае если сообщение не обрабатывается
    };
    wc.lpszClassName = L"MyAppClass";
    wc.lpszMenuName = nullptr;
    wc.style = CS_VREDRAW | CS_HREDRAW;
    /*
    wc.cbClsExtra = 0; Отвечают за дополнительное выделение памяти в
    wc.cbWndExtra = 0; классе нашего окна (для записи какой либо информации в окно).

    hbrBackground - Это поле принимает дескриптор кисти которая окрашивает окно.
    GetStockObject - Возвращает GDI объект который мы можем привести к типу HBRUSH.

    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);     - HANDLE курсора.
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);   - HANDLE иконки.
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION); - HANDLE иконки (отображается сверху слева в заголовке окна).

    wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT
    - Эта процедура отвечает за обработку сообщений (MSG msg{};)
      Принимает 4 обязательных параметра и возвращает LRESULT (результат).
      HWND hWnd     - дескриптор окна к которому приходит сообщение.
      UINT uMsg     - код сообщения.
      WPARAM wParam - указатель в нём храниться необходимая для сообщения информация.
      LPARAM lParam - указатель в нём храниться необходимая для сообщения информация.

      wc.lpszClassName = L"MyAppClass";   - имя класса (любое).
      wc.lpszMenuName = nullptr;          - указатель на имя меню.
      wc.style = CS_VREDRAW | CS_HREDRAW; - стиль окна (2 флага по умолчанию)
 */

    if (!RegisterClassEx(&wc))
        return EXIT_FAILURE;

    if (hwnd = CreateWindow(wc.lpszClassName, L"Star wars!", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)
        return EXIT_FAILURE;
    /*
     if (!RegisterClassEx(&wc)) - регистрация в системе класса нашего окна.
      return EXIT_FAILURE;

     if (hwnd = CreateWindow(wc.lpszClassName, L"Заголовок!", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, wc.hInstance, nullptr ); hwnd == INVALID_HANDLE_VALUE)
      return EXIT_FAILURE;
      - Создание нашего окна.
      wc.lpszClassName    - имя класса.
      L"Заголовок!"       - заголовок окна.
      WS_OVERLAPPEDWINDOW - стиль окна (стили посмотреть в msdn).
      0, 0,               - X и Y координаты окна (отсчитываются от левой верхней точки).
      600, 600,           - ширина, высота.


     */
    ShowWindow(hwnd, nCmdShow); // показ окна
    UpdateWindow(hwnd);         // перерисовка окна (передаётся HANDLE)

    while (GetMessage(&msg, nullptr, 0, 0)) // Цикл обработки сообщений
    {
        TranslateMessage(&msg); // функция расшифровывает системное сообщение
        DispatchMessage(&msg);  // функция  передаёт сообщение в оконную процедуру на обработку
    }

    return static_cast<int> (msg.wParam); // возвращаемое значение точки входа



    // hWnd - идентификатор окна.
    // nullptr - нулевой указатель.
}