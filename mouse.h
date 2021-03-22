INPUT_RECORD rec;
DWORD dwNOER;
HANDLE CIN = 0;

void GetMouseState(int *xx, int *yy, int *lr) {
    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
    while (1) {
        ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &rec, 1, &dwNOER);
        if (rec.EventType == MOUSE_EVENT){
            if (rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED){
                int mouse_x = rec.Event.MouseEvent.dwMousePosition.X;
                int mouse_y = rec.Event.MouseEvent.dwMousePosition.Y;

                *xx = mouse_x;
                *yy = mouse_y;
                *lr = 1;

                break;
            }
            else if (rec.Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED){
                int mouse_x = rec.Event.MouseEvent.dwMousePosition.X;
                int mouse_y = rec.Event.MouseEvent.dwMousePosition.Y;

                *xx = mouse_x;
                *yy = mouse_y;
                *lr = 1;

                break;
            }
        }
    }
}