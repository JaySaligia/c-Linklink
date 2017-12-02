#include"headers.h"
int init[12][12];
int test[12][12];
int random_num[100];
int init_width = 320;
int init_height = 130;
int width = 10;
int height = 10;
int color1 = -1;
struct spot
{
  int cx;
  int cy;
}corrod = {-1,-1};

void zhexuezhixin(int x)
{
  switch (x){
  case 0:PlaySound(TEXT("0.wav"),NULL,SND_ASYNC | SND_NODEFAULT);break;
  case 1:PlaySound(TEXT("1.wav"),NULL,SND_ASYNC | SND_NODEFAULT);break;
  case 2:PlaySound(TEXT("2.wav"),NULL,SND_ASYNC | SND_NODEFAULT);break;
  case 3:PlaySound(TEXT("3.wav"),NULL,SND_ASYNC | SND_NODEFAULT);break;
  case 4:PlaySound(TEXT("4.wav"),NULL,SND_ASYNC | SND_NODEFAULT);break;
  case 5:PlaySound(TEXT("5.wav"),NULL,SND_ASYNC | SND_NODEFAULT);break;
  case 6:PlaySound(TEXT("6.wav"),NULL,SND_ASYNC | SND_NODEFAULT);break;
  case 7:PlaySound(TEXT("7.wav"),NULL,SND_ASYNC | SND_NODEFAULT);break;
  case 8:PlaySound(TEXT("8.wav"),NULL,SND_ASYNC | SND_NODEFAULT);break;
  case 9:PlaySound(TEXT("9.wav"),NULL,SND_ASYNC | SND_NODEFAULT);break;
  }
}

void create_randome_num()
{
	for (int i = 0;i <=99 ;i++)
	 {
	    random_num[i] = i;
	 }
	srand((unsigned)time(NULL));
	for (int i = 0;i <= 99 ;i++)
	{
		int r = rand() % 100;
		int temp = random_num[i];
		random_num[i] = random_num[r];
		random_num[r] = temp;
	}
	for (int i = 0;i <= 11;i ++)
		for(int j = 0;j <= 11;j ++)
			if (i == 0 || i == 11 || j == 0 || j == 11)
			init[i][j] = 10;
			else
			init[random_num[10 * (i - 1) + j - 1] / 10 + 1][random_num[10 * (i - 1) + j - 1] % 10 + 1] = i - 1;  
}

void setcolor(int x)
{
	switch(x){
  case 0:
    setfillcolor(RGB(127,127,127));
    break;
  case 1:
    setfillcolor(YELLOW);
    break;
  case 2:
    setfillcolor(GREEN);
    break;
  case 3:
    setfillcolor(CYAN);
    break;
  case 4:
    setfillcolor(RED);
    break;
  case 5:
    setfillcolor(MAGENTA);
    break;
  case 6:
    setfillcolor(BROWN);
    break;
  case 7:
    setfillcolor(BLUE);
    break;
  case 8:
    setfillcolor(DARKGRAY);
    break;
  case 9:
    setfillcolor(LIGHTRED);
    break;
	}
    
}

void draw_rec(int x,int y,int color)
{
  setcolor(color);
  fillrectangle(init_width + 50 * (x - 1),init_height + 50 * (y - 1),init_width + 50 * (x - 1) + 50,init_height + 50 * (y - 1) + 50);
}

void draw_bigrec(int x,int y,int color)
{
  setcolor(color);
  fillrectangle(init_width + 50 * (x - 1) - 5,init_height + 50 * (y - 1) - 5,init_width + 50 * (x - 1) + 55,init_height + 50 * (y - 1) + 55);
}

void init_test()
{
  for (int i = 0;i <= 11;i ++)
		for(int j = 0;j <= 11;j ++)
		test[i][j] = -1;
}

void draw_board()
{ 
	setfillcolor(BLACK);
	fillrectangle(0,0,1200,800);
	for (int i = 0;i <= 11;i ++)
		for(int j = 0;j <= 11;j ++)
		{   
			if (init[i][j] != 10)
			  draw_rec(i,j,init[i][j]);			
		}
}


void init_board()
{
    create_randome_num();
	draw_board();
}


void click()
{  
   init_test();
   corrod.cx = -1;
   corrod.cy = -1;
   init_test();
   MOUSEMSG m;
   color1 = -1;
   while (true)
   {
     m = GetMouseMsg();
	 if (m.mkLButton)
	 {
	 if (m.x > init_width && m.y > init_height && m.x < init_width + 50 * width && m.y < init_height + 50 * height)
	 {
	   corrod.cx = (m.x - init_width) / 50 + 1;
	   corrod.cy = (m.y - init_height) / 50 + 1;
	 }
	 if (corrod.cx >= 0 && corrod.cy >= 0)
	 {
	   color1 = init[corrod.cx][corrod.cy];
	   if (color1 <= 9 && color1 >= 0)
		   break;
	 }
	 }
   }
   test[corrod.cx][corrod.cy] = 0;
   draw_bigrec(corrod.cx,corrod.cy,color1);
}
struct qu
{
  int cx;
  int cy;
  int deepth;
};


bool judget(int x,int y,int m)
{
queue<qu> queue0;
qu a;
qu b;
qu b1;
qu te;
if (m == 0)
  {
   for(int i = x -1;  i >= 0;i --)
   {
     if(test[i][y] == 1)
		 return true;
	 else if(init[i][y] == 10)
	 {
	   a.cx = i;
	   a.cy = y;
	   a.deepth = 1;
	   queue0.push(a);
	 }
	 else break;
   }
    for(int i = x + 1;  i <= 11;i ++)
   {
     if(test[i][y] == 1)
		 return true;
	 else if(init[i][y] == 10)
	 {
	   a.cx = i;
	   a.cy = y;
	   a.deepth = 1;
	   queue0.push(a);
	 }
	 else break;
   }
  
    while(!queue0.empty())
	{
	  te = queue0.front();
	  if(te.deepth == 1)
	  { 
       b = queue0.front();
	   queue0.pop();
	   for(int i = b.cy - 1;i >= 0;i --)
	   {
	     if(test[b.cx][i] == 1)
			 return true;
		 else if(init[b.cx][i] == 10)
		 {		   
		   b1.cx = b.cx;
		   b1.cy = i;
		   b1.deepth = 2;
		   queue0.push(b1);
		 }
		 else break;
	   }
	   for(int i = b.cy + 1;i <= 11;i ++)
	   {
	     if(test[b.cx][i] == 1)
			 return true;
		 else if(init[b.cx][i] == 10)
		 {
		   b1.cx = b.cx;
		   b1.cy = i;
		   b1.deepth = 2;
		   queue0.push(b1);
		 }
		 else break;
	   }
	  }
	  else break;
	}

	while(!queue0.empty())
	{
	  te = queue0.front();
	  if (te.deepth == 2)
	  {
	  b = queue0.front();
	  queue0.pop();
	  for(int i = b.cx -1 ;i >= 0;i --)
	  {
	    if (test[i][b.cy] == 1)
			return true;
		else if(init[i][b.cy] != 10)
		{
			break;
		}
	  }
	  for(int i = b.cx + 1 ;i <= 11;i ++)
	  {
	    if (test[i][b.cy] == 1)
			return true;
		else if(init[i][b.cy] != 10)
		{
			break;
		}
	  }
	  }
   	 }
  }

  else
  {
     for(int i = y -1;  i >= 0;i --)
   {
     if(test[x][i] == 1)
		 return true;
	 else if(init[x][i] == 10)
	 {
	   a.cx = x;
	   a.cy = i;
	   a.deepth = 1;
	   queue0.push(a);
	 }
	 else break;
   }
    for(int i = y + 1;  i <= 11;i ++)
   {
     if(test[x][i] == 1)
		 return true;
	 else if(init[x][i] == 10)
	 {
	   a.cx = x;
	   a.cy = i;
	   a.deepth = 1;
	   queue0.push(a);
	 }
	 else break;
   }
     while(!queue0.empty())
	{
	   te = queue0.front();
	   if(te.deepth == 1)
	   {
       b = queue0.front();
	   queue0.pop();
	   for(int i = b.cx - 1;i >= 0;i --)
	   {
	     if(test[i][b.cy] == 1)
			 return true;
		 else if(init[i][b.cy] == 10)
		 {		   
		   b1.cx = i;
		   b1.cy = b.cy;
		   b1.deepth = 2;
		   queue0.push(b1);
		 }
		 else break;
	   }
	   for(int i = b.cx + 1;i <= 11;i ++)
	   {
	     if(test[i][b.cy] == 1)
			 return true;
		 else if(init[i][b.cy] == 10)
		 {
		   b1.cx = i;
		   b1.cy = b.cy;
		   b1.deepth = 2;
		   queue0.push(b1);
		 }
		 else break;
	   }
	   }
	   else break;
	}
	
	 while(!queue0.empty())
	{
	  te = queue0.front();
	  if(te.deepth == 2)
	  {
	  b = queue0.front();
	  queue0.pop();
	  for(int i = b.cy -1 ;i >= 0;i --)
	  {
	    if (test[b.cx][i] == 1)
			return true;
		else if(init[b.cx][i] != 10)
		{
			break;
		}
	  }
	  for(int i = b.cy + 1 ;i <= 11;i ++)
	  {
	    if (test[b.cx][i] == 1)
			return true;
		else if(init[b.cx][i] != 10)
		{
			break;
		}
	  }
	}
	}
}
while (!queue0.empty())
	queue0.pop();
return false;
}

void try_click()
{   
   MOUSEMSG m;
   while (true)
   {
     m = GetMouseMsg();
	 if (m.mkLButton)
	 {
	   if(m.x > init_width && m.y > init_height && m.x < init_width + 50 * width && m.y < init_height + 50 * height)
	   {
		 if(init[(m.x - init_width) / 50 + 1][(m.y - init_height) / 50 + 1] == color1 && !((m.x - init_width) / 50 + 1 == corrod.cx && (m.y - init_height) / 50 + 1 == corrod.cy))
		 {
          test[(m.x - init_width) / 50 + 1][(m.y - init_height) / 50 + 1] = 1;
	      if(judget(corrod.cx,corrod.cy,0) == true || judget(corrod.cx,corrod.cy,1) == true)
	      {
		   zhexuezhixin(rand() % 10);
		   init[(m.x - init_width) / 50 + 1][(m.y - init_height) / 50 + 1] = 10;
		   init[corrod.cx][corrod.cy] = 10;
		   draw_board();
		   break;
	      }
		 }
		 else if ((m.x - init_width) / 50 + 1 == corrod.cx && (m.y - init_height) / 50 + 1 == corrod.cy)
		 {
			 draw_board();
		     test[corrod.cx][corrod.cy] = -1;
		     color1 = -1;
		     break;
		 }
	   }
	 
	 }
   
   }
   
}
bool check_win()
{
  for(int i = 1;i <= 11 ;i ++)
	  for(int j = 1;j <= 11 ;j ++)
	  {
	    if (init[i][j] != 10)
			return false;
	  }
  return true;
}
void main()
{ 
  PlaySound(TEXT("zhexue.wav"),NULL,SND_ASYNC | SND_NODEFAULT);
  initgraph(1200,800);
  IMAGE img,img0;
  loadimage(&img,_T("ban.jpg"));
  loadimage(&img0,_T("van.jpg"));
  settextstyle(50,0,_T("楷体"));
  outtextxy(400,150,_T("哲学♂连♂连♂看"));
  outtextxy(300,200,_T("欢迎进入deep♂dark♂fantasy！"));
  outtextxy(400,250,_T("按任意键开始"));
  BeginBatchDraw();
  putimage(350,300,&img0);
  FlushBatchDraw();
  EndBatchDraw();
  while (true)
  {
	  char c =_getch();
	  if (c = 'v')
		  break;
	
  }
  init_board();
  while (true)
  {
    click();
	try_click();
	if(check_win() == true)
	{
	    settextstyle(50,0,_T("楷体"));
		outtextxy(350,200,_T("大吉大利，连完吃鸡！"));
		BeginBatchDraw();
        putimage(320,260,&img);
        FlushBatchDraw();
        EndBatchDraw();
		PlaySound(TEXT("clap.wav"),NULL,SND_ASYNC | SND_NODEFAULT);
	}
  }
  while (1)
    char end = _getch();
}