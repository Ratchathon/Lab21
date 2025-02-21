#include <windows.h>
#include <stdlib.h>
#include <cstdio>

HWND textfield,input1,input2,Button1,Button2,Button3,Button4;
char textSaved[100];
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		case WM_CREATE:
			textfield = CreateWindow("Static","     Please input two numbers",WS_VISIBLE | WS_CHILD,25,20,200,20,hwnd,NULL,NULL,NULL);
			input1 = CreateWindow("Edit","", WS_BORDER | WS_CHILD | WS_VISIBLE,50,50,150,20,hwnd, NULL, NULL, NULL);
			input2 = CreateWindow("Edit","", WS_BORDER | WS_CHILD | WS_VISIBLE,50,75,150,20,hwnd, NULL, NULL, NULL);
			Button1 = CreateWindow("Button","+",WS_BORDER | WS_CHILD | WS_VISIBLE,75,120,20,20,hwnd, (HMENU) 1, NULL, NULL);
			Button2 = CreateWindow("Button","-",WS_BORDER | WS_CHILD | WS_VISIBLE,100,120,20,20,hwnd, (HMENU) 2, NULL, NULL);
			Button3 = CreateWindow("Button","*",WS_BORDER | WS_CHILD | WS_VISIBLE,125,120,20,20,hwnd, (HMENU) 3, NULL, NULL);
			Button4 = CreateWindow("Button","/",WS_BORDER | WS_CHILD | WS_VISIBLE,150,120,20,20,hwnd,(HMENU) 4, NULL, NULL);
		break;
		case WM_PAINT: {
            HDC hdc;
            PAINTSTRUCT ps;
            hdc = BeginPaint(hwnd, &ps);

            HBRUSH hBrush = CreateSolidBrush(RGB(255, 182, 193));
            RECT rect;
            GetClientRect(hwnd, &rect);
            FillRect(hdc, &rect, hBrush);
            EndPaint(hwnd, &ps);
        }
        break;
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case 1:
                case 2:
                case 3:
                case 4:
                    double num1, num2, result;

                    GetWindowText(input1, textSaved, 100);
                    num1 = atof(textSaved);

                    GetWindowText(input2, textSaved, 100);
                    num2 = atof(textSaved);

                    switch (LOWORD(wParam)) {
                        case 1: result = num1 + num2; break;
                        case 2: result = num1 - num2; break;
                        case 3: result = num1 * num2; break;
                        case 4: if (num2 != 0) {result = num1 / num2;} 
								else {MessageBox(hwnd, "Error", "Error", NULL);
                                return 0;}
                            break;
                    }

                    sprintf(textSaved, "%0.2f", result);
                    MessageBox(hwnd, textSaved, "Result", MB_OK);
                    break;
			}
		break;
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		650, /* x */
		300, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
