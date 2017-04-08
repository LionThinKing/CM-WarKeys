#include <windows.h>
#include <iostream>
#include <winable.h>

#define ID_STATIC 20
#define ID_HOT 40
#define ID_TEXT 60
#define ID_BUTTON 1 
#define ID_MENSAJES 2
#define ID_ITEMS 3
#define ID_PODERES 4
#define ID_ISTATIC 200
#define ID_IHOT 300 
#define ID_MAX  150
#define ID_PHOT 400
#define ID_PSTC 450
#define DELAYCLICK 40
#define ID_IMAGE 600
#define ID_SCROLL 700
#define ID_ALT1 810
#define ID_SHIFT1 820
#define ID_CTRL1 830 
#define ID_ALT2 840
#define ID_SHIFT2 850
#define ID_CTRL2 860

char INFO[100][100];
int MAX;
HFONT hf;
HICON hIcon;
HINSTANCE hInstance;
HWND active=NULL,war,hwnd;
RECT size;
POINT pos;
bool R_Click,Power_Click=true,Alt,Ctrl,Shift,Items=false,Mensajes=false;

void Mostrar_Items(bool val,HWND hwnd, int Show);
void Mostrar_Poderes(bool val,HWND hwnd, int Show);

typedef DWORD WINAPI (CALLBACK *ReadKey)(int vKey);
ReadKey Key;

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

char szClassName[ ] = "CM_WARKEY";

void limpiar()
{
    for(int c=0;c<20;c++)
    {
        ZeroMemory(INFO, sizeof(INFO[c]));
    }
}

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{               
    MSG messages;            
    WNDCLASSEX wincl;        
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      
    wincl.style = CS_DBLCLKS;                 
    wincl.cbSize = sizeof (WNDCLASSEX);
   
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 
    wincl.cbClsExtra = 0;                      
    wincl.cbWndExtra = 0;                      
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND+2;

    if (!RegisterClassEx (&wincl))
	{
        return 0;
	}

    hwnd = CreateWindowEx
	(
    0,                   
	szClassName,         
	"CM WarKey 0.1 Coded By LionThinKing (CM Labs)",       
	WS_OVERLAPPED | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_BORDER | WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_EX_WINDOWEDGE | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_APPWINDOW,
	//WS_TABSTOP | WS_OVERLAPPED | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_BORDER | WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_EX_WINDOWEDGE | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_APPWINDOW,
	CW_USEDEFAULT,       
	CW_USEDEFAULT,       
	557,                 
	375,                 
	HWND_DESKTOP,        
	NULL,                
	hThisInstance,       
	NULL                 
	);
           
    ShowWindow (hwnd, nFunsterStil);
	
    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return messages.wParam;
}

void ClipBoard(char *copy)
{
            HGLOBAL hText;
            char *pText;
            
            hText = GlobalAlloc(GMEM_DDESHARE|GMEM_MOVEABLE, 100);
            pText = (char*)GlobalLock(hText);
            
            strcpy(pText, copy);
            GlobalUnlock(hText);
            OpenClipboard(NULL);
            EmptyClipboard();
            SetClipboardData(CF_TEXT, hText);
            CloseClipboard();
}

void send(HWND window)
{
            SendMessage(window, WM_KEYDOWN,VK_RETURN, 1);
            SendMessage(window, WM_KEYUP, VK_RETURN, 1);             
            
            SendMessage(window, WM_KEYDOWN,VK_CONTROL, 1);
            SendMessage(window, WM_KEYDOWN,'V', 1);
            SendMessage(window, WM_KEYUP,'V', 1);
            SendMessage(window, WM_KEYUP,VK_CONTROL, 1);
            
            SendMessage(window, WM_KEYDOWN,VK_RETURN, 1);
            SendMessage(window, WM_KEYUP, VK_RETURN, 1);
}


void LeftClick_Power(int x, int y)
{
    GetCursorPos(&pos);
    SetCursorPos(x,y);
    Sleep(DELAYCLICK);
    SendMessage(war, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(x,y));
    SendMessage(war, WM_LBUTTONUP, 0, MAKELPARAM(x,y));
    SetCursorPos(pos.x,pos.y);
}

void RigthClick_Power(int x, int y)
{
    GetCursorPos(&pos);
    SetCursorPos(x,y);
    Sleep(DELAYCLICK);
    SendMessage(war, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(x,y));
    SendMessage(war, WM_RBUTTONUP, 0, MAKELPARAM(x,y));
    SetCursorPos(pos.x,pos.y);
}

LRESULT CALLBACK MouseKey(int nCode, WPARAM wParam, LPARAM lParam) 
{
    if(wParam==WM_LBUTTONDOWN)
    {
        if(active!=NULL)
        {
            Power_Click=true;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}


LRESULT CALLBACK HookKey(int nCode, WPARAM wParam, LPARAM lParam) 
{
    PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) (lParam);
    char H[20];
    RECT size;
    POINT pos;
    
    if (wParam == WM_KEYDOWN)
    {
        if(p->vkCode==VK_CONTROL)
        {
            //GetKeyChar(vkCode, shift)
             SetWindowText(GetDlgItem(hwnd,(ID_HOT)),(char*)p->vkCode);
        }
        if(active!=NULL)
        {
            if(p->vkCode==VK_ESCAPE)
            {
                Power_Click=true;
            }
            
            if(p->vkCode==VK_RETURN)
            {
                if(Power_Click==false)
                {
                    Power_Click=true;
                }
                else
                {
                    Power_Click=false;
                }
            }
            GetWindowRect(active,&size);
                        
            //Items Hook
            if(Items==true)
            {
                for(int c=0;c<6;c++)
                {
                    GetWindowText(GetDlgItem(hwnd,(ID_IHOT+c)),H,20);
                    if(H[0]==p->vkCode)
                    {
                        if(c==0)
                        {
                            //MessageBox(NULL,"CM","CM",MB_OK);
                           SendMessage(war, WM_KEYDOWN,VK_NUMPAD7, 1);
                           SendMessage(war, WM_KEYUP, VK_NUMPAD7, 1);
                           return 3;
                        }
                        if(c==1)
                        {
                        
                                SendMessage(war, WM_KEYDOWN,VK_NUMPAD8, 1);
                                SendMessage(war, WM_KEYUP, VK_NUMPAD8, 1);
                                return 3;
                        
                        }
                        if(c==2)
                        {
                                SendMessage(war, WM_KEYDOWN,VK_NUMPAD4, 1);
                                SendMessage(war, WM_KEYUP, VK_NUMPAD4, 1);
                                return 3;
                        }             
                        if(c==3)
                        {
                         
                                SendMessage(war, WM_KEYDOWN,VK_NUMPAD5, 1);
                                SendMessage(war, WM_KEYUP, VK_NUMPAD5, 1);
                                return 3;
                         
                        }
                        if(c==5)
                        {
                                SendMessage(war, WM_KEYDOWN,VK_NUMPAD2, 1);
                                SendMessage(war, WM_KEYUP, VK_NUMPAD2, 1);
                                return 3;
                        }
                        if(c=4)
                        {
                                SendMessage(war, WM_KEYDOWN,VK_NUMPAD1, 1);
                                SendMessage(war, WM_KEYUP, VK_NUMPAD1, 1);
                                return 3;
                        }
                    }
                }
            }
            
            if(Power_Click==true)
            {
                for(int c=0;c<6;c++)
                {
                    if(R_Click==true)
                    {
                        GetWindowText(GetDlgItem(hwnd,(ID_PHOT+c)),H,20);
						if(p->vkCode==H[0])
						{
							if(c==0)
							{
                                RigthClick_Power((size.right*79/100),(size.bottom*95/100));
								return 3;
							}
							if(c==1)
							{
								RigthClick_Power((size.right*85/100),(size.bottom*95/100));
								return 3;
							}
							if(c==2)
							{
								RigthClick_Power((size.right*91/100),(size.bottom*95/100));
								return 3;
							}
							if(c==3)
							{
								RigthClick_Power((size.right*96/100),(size.bottom*95/100));
								return 3;
							}
                            if(c==4)
                            {
								RigthClick_Power((size.right*85/100),(size.bottom*89/100));
								return 3;
                            }
                            if(c==5)
                            {
								RigthClick_Power((size.right*91/100),(size.bottom*89/100));
								return 3;
                            }           
						}
					}
					else
					{   
						GetWindowText(GetDlgItem(hwnd,(ID_PHOT+c)),H,20);
						if(p->vkCode==H[0])
						{
							if(c==0)
							{
								LeftClick_Power((size.right*79/100),(size.bottom*95/100));
								return 3;
							}
							if(c==1)
							{
								LeftClick_Power((size.right*85/100),(size.bottom*95/100));
								return 3;
							}
							if(c==2)
							{
                                LeftClick_Power((size.right*91/100),(size.bottom*95/100));
								return 3;
							}
							if(c==3)
							{
								LeftClick_Power((size.right*96/100),(size.bottom*95/100));
								return 3;
							}
                            if(c==4)
                            {
                                LeftClick_Power((size.right*85/100),(size.bottom*89/100));
								return 3;
                            }
                            if(c==5)
                            {
                                LeftClick_Power((size.right*91/100),(size.bottom*89/100));
								return 3;
                            }           
						}
					}
                }
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int GetKeyBoard(HWND window)
{
    
    char H[2],Message[100];
    while(true)
    {
        if(GetForegroundWindow() == window)
        {
            active=window;
        }
        else
        {
            active=NULL;
        }
        
        if(Key(VK_CONTROL) & 0x8000)
        {
            R_Click=true;
            Ctrl=true;
        }
        else
        {
            R_Click=false;
            Ctrl=false;
        }
        Sleep(10);
        //HotKeys
        
        if(Key(VK_MENU) & 0x8000)
        {
            Alt=true;
        }
        else
        {
            Alt=false;
        }
        
        if(Key(VK_SHIFT) & 0x8000)
        {
            Shift=true;
        }
        else
        {
            Shift=false;
        }
        
        
        
        //revisa que checkbox's estan activos 
        if(IsDlgButtonChecked(hwnd, ID_ALT1)!= BST_CHECKED){Alt=true;}
        if(IsDlgButtonChecked(hwnd, ID_CTRL1)!= BST_CHECKED){Ctrl=true;}
        if(IsDlgButtonChecked(hwnd, ID_SHIFT1)!= BST_CHECKED){Shift=true;}     
        
        //Items
        /*
        if(Alt2)
            {
                if(Ctrl2)
                {
                    if(Shift2)
                    {
                        for(int c=0;c<6;c++)
                        {
                            GetWindowText(GetDlgItem(hwnd,(ID_IHOT+c)),H,20);
                            if(Key(H[0])==-32767)
                        	{
                                if(c==0)
                                {
                                    SendMessage(war, WM_KEYDOWN,VK_NUMPAD7, 1);
                                    SendMessage(war, WM_KEYUP, VK_NUMPAD7, 1);
                                    break;
                                }
                                if(c==1)
                                {
                                    SendMessage(war, WM_KEYDOWN,VK_NUMPAD8, 1);
                                    SendMessage(war, WM_KEYUP, VK_NUMPAD8, 1);
                                    break;
                                }
                                if(c==2)
                                {
                                    SendMessage(war, WM_KEYDOWN,VK_NUMPAD4, 1);
                                    SendMessage(war, WM_KEYUP, VK_NUMPAD4, 1);
                                    break;
                                }             
                                if(c==3)
                                {
                                    SendMessage(war, WM_KEYDOWN,VK_NUMPAD5, 1);
                                    SendMessage(war, WM_KEYUP, VK_NUMPAD5, 1);
                                    break;
                                }
                                if(c==5)
                                {
                                    SendMessage(war, WM_KEYDOWN,VK_NUMPAD2, 1);
                                    SendMessage(war, WM_KEYUP, VK_NUMPAD2, 1);
                                    break;
                                }
                                if(c=4)
                                {
                                    SendMessage(war, WM_KEYDOWN,VK_NUMPAD1, 1);
                                    SendMessage(war, WM_KEYUP, VK_NUMPAD1, 1);
                                    break;
                                }
                            }
                        }
                    }
                }
            }*/
        
        
        //Mensajes
        if(Alt)
        {
            if(Ctrl)
            {
                if(Shift)
                {
                    for(int c=0;c<MAX;c++)
                    {
                        GetWindowText(GetDlgItem(hwnd,(ID_HOT+c)),H,20);
                        if(Key(H[0])==-32767)
                    	{
                            GetWindowText(GetDlgItem(hwnd,ID_TEXT+c),Message,100);
                            ClipBoard(Message);
                            send(window);
                        }
                    }
                }
            }
        }   
        //Items
    }               
}

void Leer_Data()
{
    int c,ln=0,cl=0,i=0,j=-1;
    FILE *data;
    if(data=fopen("Data/Data.ini", "r"))
    {
        do
        {
            c=getc(data);
            cl+=1;
            if(c=='\n'){ln+=1;cl=0;i=0;}
            
            if(ln>4)
            {
                if(cl==14)
                {
                    j+=1;
                }
                if(cl>14)
                {
                    INFO[j][i]=c;
                    i+=1;
                }
            }
        }while(c!=EOF);
    }
    MAX=atoi(INFO[6]);
    fclose(data);
}

void save(HWND hwnd)
{
    char INFO[20][100];
    char info[100]; 
    DeleteFile("Data/Data.ini");
    int c,ln=0,cl=0,i=0,j=-1,max;
    FILE *data;
    
    if(data=fopen("Data/Data.ini", "w"))
    {
        GetWindowText(GetDlgItem(hwnd,ID_MAX),info,100);
        fprintf(data,"[*] CM_WarKey 0.1\n[*] Warkey for Dota(Warcraft).\n[*] Author: LionThinKing(CM_LABS)\n[*] Thanks to: <Coded Masters Labs>)\n\n");
        
        //Botones
        //Mensajes
        if(IsDlgButtonChecked(hwnd, ID_ALT1)== BST_CHECKED)
        {
            fprintf(data,"[*]MenajeAlt:\t1\n");
        }
        else
        {
            fprintf(data,"[*]MenajeAlt:\t0\n");
        }
        
        if(IsDlgButtonChecked(hwnd, ID_CTRL1)== BST_CHECKED)
        {
            fprintf(data,"[*]MsjContrl:\t1\n");
        }
        else
        {
            fprintf(data,"[*]MsjContrl:\t0\n");
        }
        
        if(IsDlgButtonChecked(hwnd, ID_SHIFT1)== BST_CHECKED)
        {
            fprintf(data,"[*]MsjShift :\t1\n");
        }
        else
        {
            fprintf(data,"[*]MsjShift :\t0\n");
        }
        
        //Items
        if(IsDlgButtonChecked(hwnd, ID_ALT2)== BST_CHECKED)
        {
            fprintf(data,"[*]Poder_Alt:\t1\n");
        }
        else
        {
            fprintf(data,"[*]Poder_Alt:\t0\n");
        }
        
        if(IsDlgButtonChecked(hwnd, ID_CTRL2)== BST_CHECKED)
        {
            fprintf(data,"[*]PodContrl:\t1\n");
        }
        else
        {
            fprintf(data,"[*]PodContrl:\t0\n");
        }
        
        if(IsDlgButtonChecked(hwnd, ID_SHIFT2)== BST_CHECKED)
        {
            fprintf(data,"[*]PodShift :\t1\n");
        }
        else
        {
            fprintf(data,"[*]PodShift :\t0\n");
        }
        
        fprintf(data,"[*] #HotKeys:\t%s\n",info);
        max=atoi(info);

        //Mensajes
        for(int c=0;c<max;c++)
        {
            GetWindowText(GetDlgItem(hwnd,ID_HOT+c),info,100);
            fprintf(data,"[*] Hotkey %d:\t%s\n",c+1,info);
            GetWindowText(GetDlgItem(hwnd,ID_TEXT+c),info,100);
            fprintf(data,"[*] TextKey%d:\t%s\n",c+1,info);
        }
        
        //Items
        for(int c=0;c<6;c++)
        {
            GetWindowText(GetDlgItem(hwnd,ID_IHOT+c),info,100);
            fprintf(data,"[*] ItemKey%d:\t%s\n",c+1,info);
        }
        
        //Poderes
        for(int c=0;c<6;c++)
        {
            GetWindowText(GetDlgItem(hwnd,ID_PHOT+c),info,100);
            fprintf(data,"[*] PwKey# %d:\t%s\n",c+1,info);
        }
    }
    fclose(data);    
}

void Mostrar_Mensajes(bool val,HWND hwnd,int Show)
{
    if(Show!=2){Mostrar_Items(false,hwnd,1);}
    ShowWindow(GetDlgItem(hwnd,(ID_MAX)),val);
    ShowWindow(GetDlgItem(hwnd,(ID_ALT1)),val);
    ShowWindow(GetDlgItem(hwnd,(ID_CTRL1)),val);
    ShowWindow(GetDlgItem(hwnd,(ID_SHIFT1)),val);
    for(int c=0;c<=MAX+1;c++)
    {
        ShowWindow(GetDlgItem(hwnd,(ID_STATIC+c)),val);
        ShowWindow(GetDlgItem(hwnd,(ID_HOT+c)),val);
        ShowWindow(GetDlgItem(hwnd,(ID_TEXT+c)),val);
    }
}

void Mostrar_Items(bool val,HWND hwnd, int Show)
{
    
    if(Show!=1){Mostrar_Mensajes(false,hwnd,2);}
    if(Show!=3){Mostrar_Poderes(false,hwnd,2);}
    ShowWindow(GetDlgItem(hwnd,(ID_IMAGE)),val);
    ShowWindow(GetDlgItem(hwnd,(ID_ALT2)),val);
    ShowWindow(GetDlgItem(hwnd,(ID_CTRL2)),val);
    ShowWindow(GetDlgItem(hwnd,(ID_SHIFT2)),val);
    for(int c=0;c<6;c++)
    {
        ShowWindow(GetDlgItem(hwnd,(ID_ISTATIC+c)),val);
        ShowWindow(GetDlgItem(hwnd,(ID_IHOT+c)),val);
    }
}

void Mostrar_Poderes(bool val,HWND hwnd, int Show)
{
   if(Show!=2){Mostrar_Mensajes(false,hwnd,3);}
   if(Show!=2){Mostrar_Items(false,hwnd,3);}
   for(int c=0;c<6;c++)
    {
        ShowWindow(GetDlgItem(hwnd,(ID_PSTC+c)),val);
        ShowWindow(GetDlgItem(hwnd,(ID_PHOT+c)),val);
    }
}


DWORD WINAPI Get_HWND(LPVOID Data)
{
    HWND window=NULL;
    do
    {
        window=FindWindow(NULL,TEXT("Warcraft III"));
    }while(window==NULL);
    war=window;
    GetKeyBoard(window);
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HANDLE GetKey=0;
    int Data,y=50,j=0;

    switch (message)                  
    {
        case WM_CREATE:
            limpiar();
            HMODULE hIns;
            hIns=(HMODULE)LoadLibrary("user32.dll");
            if(hIns)
            {
                Key=(ReadKey)GetProcAddress(hIns,"GetAsyncKeyState"); 
            }
            else
            {
                return 0;
            }
            
            hIcon = (HICON)LoadImage(NULL, "Data/Dota.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
            SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
            
            Leer_Data();
            //Mensajes
            CreateWindowEx(0,"STATIC", "# HotKeys", WS_VISIBLE | WS_CHILD, 10, y, 70, 20,hwnd, (HMENU)(ID_STATIC+MAX), NULL, NULL);
            CreateWindow("EDIT",INFO[6],WS_OVERLAPPED | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_TABSTOP | WS_EX_NOPARENTNOTIFY | WS_EX_CLIENTEDGE | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR,110,y,20,20,hwnd,(HMENU)(ID_MAX),NULL,NULL);                   
            SendMessage(GetDlgItem(hwnd,(ID_MAX)),EM_LIMITTEXT, 2, 2);
            
            CreateWindowEx(0,"BUTTON", "Alt",BS_AUTOCHECKBOX | WS_OVERLAPPED | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR, 10, 80, 50, 25,hwnd, (HMENU)ID_ALT1, NULL, NULL);    
            CreateWindowEx(0,"BUTTON", "Ctrl",BS_AUTOCHECKBOX | WS_OVERLAPPED | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR, 100, 80, 50, 25,hwnd, (HMENU)ID_CTRL1, NULL, NULL);
            CreateWindowEx(0,"BUTTON", "Shift",BS_AUTOCHECKBOX | WS_OVERLAPPED | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR, 200, 80, 50, 25,hwnd, (HMENU)ID_SHIFT1, NULL, NULL);
            y+=70;
            for(int c=0;c<MAX;c++)
            {
                CreateWindowEx(0,"STATIC", "HotKey", WS_VISIBLE | WS_CHILD, 10, y, 50, 20,hwnd, (HMENU)(ID_STATIC+c), NULL, NULL);
                CreateWindow("EDIT",INFO[c+7+c],WS_OVERLAPPED | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_TABSTOP | WS_EX_NOPARENTNOTIFY | WS_EX_CLIENTEDGE | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR,80,y,20,20,hwnd,(HMENU)(ID_HOT+c),NULL,NULL);
                SendMessage(GetDlgItem(hwnd,(ID_HOT+c)),EM_LIMITTEXT, 1, 1);       
                CreateWindow("EDIT",INFO[c+8+c],WS_OVERLAPPED | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_TABSTOP | WS_EX_NOPARENTNOTIFY | WS_EX_CLIENTEDGE | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR,110,y,400,20,hwnd,(HMENU)(ID_TEXT+c),NULL,NULL);
                
                y+=30;
            }
           
            //Items
            hf=CreateFont(0, 0, 0, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");
            y=135;
            
            CreateWindowEx(0,"BUTTON", "Alt",BS_AUTOCHECKBOX | WS_OVERLAPPED | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR, 10, 60, 50, 25,hwnd, (HMENU)ID_ALT2, NULL, NULL);    
            CreateWindowEx(0,"BUTTON", "Ctrl",BS_AUTOCHECKBOX | WS_OVERLAPPED | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR, 100, 60, 50, 25,hwnd, (HMENU)ID_CTRL2, NULL, NULL);
            CreateWindowEx(0,"BUTTON", "Shift",BS_AUTOCHECKBOX | WS_OVERLAPPED | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR, 200, 60, 50, 25,hwnd, (HMENU)ID_SHIFT2, NULL, NULL);
            for(int c=0;c<6;c++)
            {
                CreateWindow("EDIT",INFO[(2*MAX)+c+7],WS_OVERLAPPED | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_TABSTOP | WS_EX_NOPARENTNOTIFY | WS_EX_CLIENTEDGE | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR,250,y,40,40,hwnd,(HMENU)(ID_IHOT+c),NULL,NULL);
                SendMessage(GetDlgItem(hwnd,(ID_IHOT+c)),EM_LIMITTEXT, 1, 1); 
                c++;
                CreateWindow("EDIT",INFO[(2*MAX)+c+7],WS_OVERLAPPED | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_TABSTOP | WS_EX_NOPARENTNOTIFY | WS_EX_CLIENTEDGE | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR,300,y,40,40,hwnd,(HMENU)(ID_IHOT+c),NULL,NULL);
                SendMessage(GetDlgItem(hwnd,(ID_IHOT+c)),EM_LIMITTEXT, 1, 1);
                y+=50;
            }
            CreateWindowEx(0, "STATIC","",SS_CENTERIMAGE | SS_REALSIZEIMAGE | SS_BITMAP | WS_CHILD | WS_VISIBLE,100,110,103,179,hwnd,(HMENU)ID_IMAGE,NULL,NULL);
            HBITMAP bitmap = (HBITMAP)LoadImage(NULL,"Data\\Items.bmp", IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
            SendMessage(GetDlgItem(hwnd, ID_IMAGE), STM_SETIMAGE,  (WPARAM)IMAGE_BITMAP, (LPARAM)bitmap);

            //Poderes
            y=140;
            for(int c=0;c<6;c++)
            {
                if(c>3)
                {
                    CreateWindow("EDIT",INFO[(2*MAX+c+13)],WS_OVERLAPPED | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_TABSTOP | WS_EX_NOPARENTNOTIFY | WS_EX_CLIENTEDGE | WS_EX_LEFT | WS_EX_LTRREADING ,y,120,50,50,hwnd,(HMENU)(ID_PHOT+c),NULL,NULL);
                }
                else
                {
                    CreateWindow("EDIT",INFO[(2*MAX+c+13)],WS_OVERLAPPED | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_TABSTOP | WS_EX_NOPARENTNOTIFY | WS_EX_CLIENTEDGE | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR,y,200,50,50,hwnd,(HMENU)(ID_PHOT+c),NULL,NULL);
                }
                SendMessage(GetDlgItem(hwnd,(ID_PHOT+c)),EM_LIMITTEXT, 1, 1);
                if(c==3){y=140;}
                y+=60;
            }
            
            
            
            //Set  a los botones
            if(INFO[0][0]=='1'){SendDlgItemMessage(hwnd, ID_ALT1,BM_SETCHECK, 1, 0);}else{SendDlgItemMessage(hwnd, ID_ALT1,BM_SETCHECK, 0, 0);}
            if(INFO[1][0]=='1'){SendDlgItemMessage(hwnd, ID_CTRL1,BM_SETCHECK, 1, 0);}else{SendDlgItemMessage(hwnd, ID_CTRL1,BM_SETCHECK, 0, 0);}
            if(INFO[2][0]=='1'){SendDlgItemMessage(hwnd, ID_SHIFT1,BM_SETCHECK, 1, 0);}else{SendDlgItemMessage(hwnd, ID_SHIFT1,BM_SETCHECK, 0, 0);}
            if(INFO[3][0]=='1'){SendDlgItemMessage(hwnd, ID_ALT2,BM_SETCHECK, 1, 0);}else{SendDlgItemMessage(hwnd, ID_ALT2,BM_SETCHECK, 0, 0);}
            if(INFO[4][0]=='1'){SendDlgItemMessage(hwnd, ID_CTRL2,BM_SETCHECK, 1, 0);}else{SendDlgItemMessage(hwnd, ID_CTRL2,BM_SETCHECK, 0, 0);}
            if(INFO[5][0]=='1'){SendDlgItemMessage(hwnd, ID_SHIFT2,BM_SETCHECK, 1, 0);}else{SendDlgItemMessage(hwnd, ID_SHIFT2,BM_SETCHECK, 0, 0);}
                                    
            CreateWindowEx(0,"BUTTON", "Mensajes",BS_RADIOBUTTON | WS_OVERLAPPED | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR, 10, 10, 120, 25,hwnd, (HMENU)ID_MENSAJES, NULL, NULL);    
            CreateWindowEx(0,"BUTTON", "Items",BS_RADIOBUTTON | WS_OVERLAPPED | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR, 200, 10, 120, 25,hwnd, (HMENU)ID_ITEMS, NULL, NULL);
            CreateWindowEx(0,"BUTTON", "Poderes",BS_RADIOBUTTON | WS_OVERLAPPED | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR, 400, 10, 120, 25,hwnd, (HMENU)ID_PODERES, NULL, NULL);
            CreateWindowEx(0,"BUTTON", "Iniciar",WS_CHILD | WS_VISIBLE | WS_TABSTOP, 400, 50, 120, 25,hwnd, (HMENU)ID_BUTTON, NULL, NULL);    
            SendDlgItemMessage(hwnd, ID_MENSAJES,BM_SETCHECK, 1, 0);
            Mostrar_Mensajes(true,hwnd,1);
            delete &INFO;
            hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
            HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL,HookKey,hInstance,0);
            HHOOK mouseHook = SetWindowsHookEx(WH_MOUSE_LL,MouseKey,hInstance,0);
            break;
            
            case WM_COMMAND:  
                switch(LOWORD(wParam)) 
                {                        
                    case ID_BUTTON:
                        //Creamos el hilo a sniffear el teclado
                        GetKey=CreateThread(NULL, 0, Get_HWND, &Data, 0, NULL);
                        if(GetKey==NULL)
                        {
                            ExitProcess(Data);
                        }  
                        EnableWindow(GetDlgItem(hwnd,ID_BUTTON),false);
                        break;
                    case ID_MENSAJES:
                        if(IsDlgButtonChecked(hwnd, ID_MENSAJES)!= BST_CHECKED)
                        {
                            SendDlgItemMessage(hwnd, ID_MENSAJES,BM_SETCHECK, 1, 0);
                            SendDlgItemMessage(hwnd, ID_ITEMS,BM_SETCHECK, 0, 0);
                            SendDlgItemMessage(hwnd, ID_PODERES,BM_SETCHECK, 0, 0);
                            Mostrar_Mensajes(true,hwnd,1);  
                        }
                        
                        break;
                    
                    case ID_ITEMS:
                        if(IsDlgButtonChecked(hwnd, ID_ITEMS)!= BST_CHECKED)
                        {
                            Mostrar_Items(true,hwnd,2);
                            SendDlgItemMessage(hwnd, ID_MENSAJES,BM_SETCHECK, 0, 0);
                            SendDlgItemMessage(hwnd, ID_ITEMS,BM_SETCHECK, 1, 0);
                            SendDlgItemMessage(hwnd, ID_PODERES,BM_SETCHECK, 0, 0);
                        }
                        break;
                        
                    case ID_PODERES:
                        if(IsDlgButtonChecked(hwnd, ID_PODERES)!= BST_CHECKED)
                        {
                            Mostrar_Poderes(true,hwnd,3);
                            SendDlgItemMessage(hwnd, ID_MENSAJES,BM_SETCHECK, 0, 0);
                            SendDlgItemMessage(hwnd, ID_ITEMS,BM_SETCHECK, 0, 0);
                            SendDlgItemMessage(hwnd, ID_PODERES,BM_SETCHECK, 1, 0);
                        }
                        break;
                }
                break;
        case WM_DESTROY:
            save(hwnd);
            PostQuitMessage (0);       
            break;
        default:                      
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
