#include <stdio.h>
#include <windows.h>

int num[3], col[10+5];
int N; //N<10

void set_text_color (int textColor, int backColor){
	HANDLE consoleHandle = GetStdHandle (STD_OUTPUT_HANDLE);
	int colorAttribute = backColor << 4 | textColor;
	SetConsoleTextAttribute(consoleHandle, colorAttribute);
}

void gotoxy(int x, int y){
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	fflush(stdout);
	dwCursorPosition.X=x;
	dwCursorPosition.Y=y;
	hConsoleOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void delay(float t){
	int i;
	for (i=0; i<1000*1000*100*t; i++);
}

void prepro(int column){ //more thinking
	gotoxy(25*column, 11);
	int i;
	set_text_color(8,8); //more thinking
	for (i=1; i<=21; i++)
		printf("_");
}

void prepro1(){ //more thinking
	col[1] = 15;
	col[2] = 14;
	col[3] = 10;
	col[4] = 2;
	col[5] = 3;
	col[6] = 11;
	col[7] = 9;
	col[8] = 1;
	col[9] = 5;
}

void draw_disc(int n, int x, int y, int c){ //nth disc
	gotoxy(x,y);
	int i;
	set_text_color(0,0);
	for (i=1; i<=(2*N-2*n+1)/2; i++)
		printf(" ");
	for (i=1; i<=2*n+1; i++){
		if (c!=0 && i==(2*n+1)/2+1){
			set_text_color(0,c);
			printf("%d", n);
		}
		else{
			set_text_color(c,c);
			printf(" ");
		}
	}
}

void move_up(int n, int from){
	int i;
	for (i=10-num[from]; i>1; i--){
		draw_disc(n,25*from+(20-2*N+1)/2,i,0);
		draw_disc(n,25*from+(20-2*N+1)/2,i-1,col[n]);
		delay(0.1);
	}
}

void move_hor(int n, int from, int to){
	int i;
	if (to>from)
		for (i=25*from+(20-2*N+1)/2; i<25*to+(20-2*N+1)/2; i++){
			draw_disc(n,i,1,0);
			draw_disc(n,i+1,1,col[n]);
			delay(0.1);
		}
	else
		for (i=25*from+(20-2*N+1)/2; i>25*to+(20-2*N+1)/2; i--){
			draw_disc(n,i,1,0);
			draw_disc(n,i-1,1,col[n]);
			delay(0.1);
		}
}

void move_down(int n, int to){
	int i;
	for (i=1; i<10-num[to]; i++){
		draw_disc(n,25*to+(20-2*N+1)/2,i,0);
		draw_disc(n,25*to+(20-2*N+1)/2,i+1,col[n]);
		if (i==10-num[to]-1)
			printf("%c", 7);
		delay(0.1);
	}
}

void move(int n, int from, int to){ //nth disc
	num[from]--;
	move_up(n,from);
	move_hor(n,from,to);
	move_down(n,to);
	num[to]++;
}

void trans(int n, int from, int to, int temp){ //n discs
	if (n==1){
		move(n, from, to);
		return;
	}
	trans(n-1, from, temp, to);
	move(n, from, to);
	trans(n-1, temp, to, from);
}

int main(){
	prepro1();
	prepro(0);
	prepro(1);
	prepro(2);
	gotoxy(0,0);
	set_text_color(15,0);
	scanf("%d", &N);
	int i;
	for (i=N; i>0; i--){
		draw_disc(i, 25*0+(20-2*N+1)/2, 10-num[0], col[i]);
		num[0]++;
	}
	delay(1);
	trans(N, 0, 2, 1);
	gotoxy(0,15);
	set_text_color(15,0);
	return 0;
}
