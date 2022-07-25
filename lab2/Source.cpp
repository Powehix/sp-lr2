#include <windows.h>
#include <stdio.h>

LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS w;

	memset(&w, 0, sizeof(WNDCLASS));
	w.style = CS_HREDRAW | CS_VREDRAW;

	//ƒополнительное задание: помен€ть иконку у первого проекта
	w.hIcon = LoadIcon(NULL, IDI_ASTERISK);


	w.lpfnWndProc = WndProc;
	w.hInstance = hInstance;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.lpszClassName = "My Class";
	RegisterClass(&w);
	hwnd = CreateWindow("My Class", "First project", WS_OVERLAPPEDWINDOW,
		300, 200, 200, 180, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LONG WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam)
{
	HDC hdc = GetDC(hwnd);
	DWORD x, y;

	//ƒополнительное задание: помен€ть размер шрифта у текста
	static LOGFONT font;
	font.lfHeight = 30;
	HFONT hfont = CreateFontIndirect(&font);

	switch (Message)
	{
	//1 задание: при каждом щелчке правой кнопки мыши в окне программы в месте нахождени€ курсора мыши должен печататьс€ текст, сообщающий об этом событии
	case WM_RBUTTONDOWN:
	{
		y = lparam >> 16;
		x = lparam & 0xFFFF;
		SelectObject(hdc, hfont);
		TextOut(hdc, x, y, "You pressed the right mouse button!", 35);
	}
	break;
	//2 задание:  при каждом щелчке левой кнопки мыши в окно приложени€ должны выводитьс€ координаты указател€ мыши в момент щелчка по ее кнопке
	case WM_LBUTTONDOWN:
	{
		y = HIWORD(lparam);
		x = LOWORD(lparam);
		char s[255];
		SelectObject(hdc, hfont);
		wsprintf(s, "x = %i y = %i", x, y);
		TextOut(hdc, x, y, s, 15);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
	break; default:
		return DefWindowProc(hwnd, Message, wparam, lparam);
	}
	return 0;
}