// DHMTBuoi1.cpp : This file contains the 'main' function. Program execution begins and ends there.



//GAMEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE


#include "Dependencies/glew/glew.h";
#include "Dependencies/freeglut/freeglut.h";
#include <stdio.h>

using namespace std;

#include <sys/timeb.h>
#include <sys/utime.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#define max_pl = 100;
// dùng thư viện math để tính căn bậc 2
double rtd = 5;
// bán kính của quỹ đạo trái đất

double anpha = 0;
double GocQuayCuaTraiCam = 0.0;
double BanKinhCuaTraiCam = 7.0;
double anpha_mt = 0;
double r_mt = 3;


int anpha_cam = 0;
// T1 là khối quay trong mặt phẳng YoZ và quanh Ox
// góc hiện tại của trái đất so với mặt trời

const int SoLuongCacDiem = 50;
const int SoLuongHinhSin = 10;
double bandaux[SoLuongCacDiem];
double bandauz[SoLuongCacDiem];
// đây là mảng 1 chiều chứa vị trí x hiện tại của các điểm
double mangx[SoLuongCacDiem];
// tạo mảng chứa z
double mangz[SoLuongCacDiem];
// mảng chứa tốc độ di chuyển của từng viên
double mangtocdo[SoLuongCacDiem];
// biến tùy chỉnh số lượng quả cầu
int soluongve = 10;
//bi duongthang sin end
double xsinend[SoLuongHinhSin];
double zsinend[SoLuongHinhSin];
//bi duongthang sin start
double xsinstart[SoLuongHinhSin];
double zsinstart[SoLuongHinhSin];
//bieudo sin
double xsin[SoLuongHinhSin];
double zsin[SoLuongHinhSin];
double speedsin[SoLuongHinhSin];
int soluongsin = 0;

//diem so
int diem1=0;
int diem2=0;
//ketthuc game
int end1 = 0;
int end2 = 0;

double GocCuaCamera = 0.0;
// cho cam quay  vòng vòng cũng vui


float x = 0.0;
float x_cam = 0.0; // la toa do x cua trai cam
float x_mt = 0.0;
// x là tọa độ của khối cầu
float z = 0.0;
float z_cam = 7.0; // la toa do z cua trai cam
float z_mt = 0.0;
// z là tọa độ theo trục z 
float y = 0.0;
float y_cam = 0.0; // la toa do y cua trai cam
float y_mt = 0.0;


int ChieuQuayCuaCamera = 1;
// là chiều theo kim đồng hồ, nếu -1 thì ngược lại

//player 1
double bankinhMT = 2.0;
double bankinhTD = 1.0;
double bankinhMTG = 0.5;
double bankinhBALL = 0.1;
double bankinhSIN = 0.2;

//player 2
double bankinhTD_2 = 1.0;
double bankinhMTG_2 = 0.5;
double xtd_pl2 = 0.0;
double ytd_pl2 = 0.0;
double ztd_pl2 = 0.0;
double xmt_pl2 = 0.0;
double ymt_pl2 = 0.0;
double zmt_pl2 = 0.0;
double red_mt = 1;
double green_mt = 1;
double blue_mt = 0;
double red_td = 1;
double green_td = 0;
double blue_td = 1;
double anpha_tdpl2 = 180;
double anpha_mtpl2 = 0;
double quydao_tdpl2 = 5;
double quydao_mtpl2 = 3;


// những biến có chữ z là hình cầu quay quanh trục z
double tocdo = 0.2;
double tocdo_mt = 0;
double tocdo_mtpl2 = 0;


double colorR1 = 0;
double colorR_cam = 1;
double colorR_mt = 1;
double colorG1 = 1.0;
double colorG_cam = 0.5;
double colorG_mt = 1;
double colorB1 = 0;
double colorB_cam = 0;
double colorB_mt = 1;
// dat bien mau cho trai cam, 1, 0.5, 0 voi hy la y dai vong se ra mau cam

double level = 0.0;
double level1 = 0.1;
double level2 = 0.2;
double level3 = 0.3;
double level4 = 0.4;
double level5 = 0.5;
double level6 = 0.6;
double level7 = 0.7;
double level8 = 0.8;
double level9 = 0.9;
double level10 = 1.0;

double day = 0.0;
bool pause = false;
// day la bien chi vi tri goc xoay của trái đất
int chieu = 1;
// chiều 1 tương ứng qua phải
// -1 là qua trái.
double camY = 10; // biến vị trí cam theo trục Y
double camX = 0; // biến vị trí cam theo trục Y
double camZ = 15;// đây là biến vị trí Z hiện tại, là vị trí mắt
double BanKinhCamera = 15; // số to nhìn cho xa
int maxFrame = 25;
int chuky = 1000 / maxFrame;
// code nào mà ko có khúc này
// mặc định là lụm trên mạng
// khỏi suy nghĩ, rớt môn
int getMilliCount() {
    timeb tb;
    ftime(&tb);
    int nCount = tb.millitm +(tb.time & 0xfffff)*1000;
    return nCount;
}
int tgbatdau = getMilliCount();
// lấy thời điểm hiện tại theo ms
void sleep(int sleeptime)
{
    int count = 0;
    int beginsleep = getMilliCount();
    while (getMilliCount() - beginsleep < sleeptime)
    {
        count++;
    }
}
// code trên mạng ko có hàm sleep này đâu, yên tâm mà copy
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    // đây là hàm khởi tạo các đối tượng ngay từ đầu.
    double vitribandau = 0;
    // khoi tao vi tri ket thuc
    for (int i = 0; i < SoLuongCacDiem; i++)
    {
        bandaux[i] = vitribandau;
        bandauz[i] = vitribandau;
        // ban đầu sẽ tạo ra 1 vị trí mà -5 đến 5
        int vitriketthuc = rand() % 11 - 5;
        // 
        if (vitriketthuc > 0)
        {
            // để khống chế vị trí mới sinh ra phải thiệt xa mặt trời
            mangx[i] = vitriketthuc + 2 + (rand() % 5);
        }
        else
        {
            // tương tự nhưng theo chiều âm
            mangx[i] = vitriketthuc - 2 - (rand() % 5);
        }

        // làm y chang vậy  cho việc khởi tạo z
        vitriketthuc = rand() % 11 - 5;
        // 
        if (vitriketthuc > 0)
        {
            // để khống chế vị trí mới sinh ra phải thiệt xa mặt trời
            mangz[i] = vitriketthuc + 2 + (rand() % 5);
        }
        else
        {
            // tương tự nhưng theo chiều âm
            mangz[i] = vitriketthuc - 2 - (rand() % 5);
        }


        // sau khi khởi tạo xong toa độ, tính được liền luôn 
        // tạo ra biến ngẫu nhiên từ 5-10
        int thoigiandichuyen = rand() % 5 + 5;
        // biến trên chính là thời gian di chuyển của hạt thứ i
        mangtocdo[i] = mangx[i] / (thoigiandichuyen * maxFrame);
        // theo công thức trên bảng, thời gian nhân với số frame
        // lấy quãng đường chia thời gian sẽ ra vận tốc di chuyển
    }

    //init sin
    vitribandau = 0;
    for (int i = 0; i < SoLuongHinhSin; i++)
    {
        xsinstart[i] = vitribandau;
        zsinstart[i] = vitribandau;
        int vitriketthuc = rand() % 11 - 5;
        // 
        if (vitriketthuc > 0)
        {
            xsinend[i] = vitriketthuc + 2 + (rand() % 5);
        }
        else
        {
            xsinend[i] = vitriketthuc - 2 - (rand() % 5);
        }
        vitriketthuc = rand() % 11 - 5;
        if (vitriketthuc > 0)
        {
            zsinend[i] = vitriketthuc + 2 + (rand() % 5);
        }
        else
        {
            zsinend[i] = vitriketthuc - 2 - (rand() % 5);
        }
        int thoigiandichuyen = rand() % 5 + 5;
        speedsin[i] = xsinend[i] / (thoigiandichuyen * maxFrame);
    }
}

void DrawCoordinate()
{
   // glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-1000.0, 0.0, 0.0);
    glVertex3f(1000.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -1000.0, 0.0);
    glVertex3f(0.0, 1000.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0.0, 0.0, -1000.0);
    glVertex3f(0.0, 0.0, 1000.0);
    glEnd();
   // glEnable(GL_LIGHTING);
    // rảnh rỗi chờ sv làm bài nộp,
    // nên t quyết định vẽ 3 đường thẳng nối tâm của 3 hình cầu đang có
    // đầu tiên, vẽ đường nối tâm mặt trời tới tâm trái đất
    //glBegin(GL_LINES);
    //glColor3f(1.0, 1.0, 1.0);
    //glVertex3f(0.0, 0.0, 0.0);
    //glVertex3f(x, y,z);
    //glEnd();
    //// làm y chang với 2 đường còn lại
    //glBegin(GL_LINES);
    //glColor3f(1.0, 1.0, 1.0);
    //glVertex3f(0.0, 0.0, 0.0);
    //glVertex3f(x_cam, y_cam, z_cam);
    //glEnd();

    //glBegin(GL_LINES);
    //glColor3f(1.0, 1.0, 1.0);
    //glVertex3f(x, y, z);
    //glVertex3f(x_cam, y_cam, z_cam);
    //glEnd();
}

double distanceAB(double xa, double xb, double za, double zb) {
    double d = sqrt(pow(xa - xb, 2) + pow(za - zb, 2));
    return d;
}

void DrawPoint(double toadox[SoLuongCacDiem], double toadoz[SoLuongCacDiem], int soluongve)
{
    // vẽ hết toàn bộ các điểm
    for (int i = 0; i < soluongve; i++)
    {
        // cất ma trận hiện hành
        glPushMatrix();
        // dịch chuyển con trỏ tới vị trí của điểm thứ i
        glTranslatef(toadox[i], 0.0, toadoz[i]);
        // chuẩn bị màu trắng
        glColor3f(1, 1, 1);
        // vẽ 1 khối cầu kích thước 0.2
        glutSolidSphere(bankinhBALL, 40, 30);
        // trả lại tọa độ ban đầu
        glPopMatrix();

    }
}

void DrawSin(double toadox[SoLuongHinhSin], double toadoz[SoLuongHinhSin], int soluongsin)
{
    for (int i = 0; i < soluongsin; i++)
    {
        // cất ma trận hiện hành
        glPushMatrix();
        // dịch chuyển con trỏ tới vị trí của điểm thứ i
        glTranslatef(toadox[i], 0.0, toadoz[i]);
        // chuẩn bị màu trắng
        glColor3f(1, 0, 1);
        // vẽ 1 khối cầu kích thước 0.2
        glutSolidSphere(bankinhSIN, 40, 30);
        // trả lại tọa độ ban đầu
        glPopMatrix();
    }
}

void printtext(int x, int y, string String) 
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 400, 0, 400, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glRasterPos2i(x, y);
    for (int i = 0; i < String.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
    }

    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void Paused()
{
    sleep(2000);
}

void render(void) {
    int beginframe = getMilliCount();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawCoordinate();
    //goi ham ve hat
    DrawPoint(bandaux, bandauz, soluongve);
    DrawSin(xsin, zsin, soluongsin);
    glPushMatrix();
    glColor3f(1.0, 0, 0);
    glutWireSphere(bankinhMT, 80, 80);
    //glutWireSphere(2.0, 50, 40);
    // vi tri cua trai dat se theo toa do x 0 z
    glTranslatef(x, 0.0, z);
    glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
    // chú ý thay x và z để chỉ định vị trí mới
    // y luôn  = 0
    glColor3f(colorR1, colorG1, colorB1);
    //glutSolidSphere(0.5, 100, 80);
    glutWireSphere(bankinhTD, 40, 30);
    // vi yeu cam trai cam to gap doi trai dat nen
    // ban kinh thanh 1.0
    glPopMatrix();
    // đoạn trên là vẽ hoàn thiện 1 khối tròn trắng
   // vay minh se Pop matrix T co san trong stack de
    // quay ve toa do tam cua mat troi roi moi ve trai cam
    // va cung lam thu tuc Push MAtrix de co san 1 ma tran T
    // trong stack, ti nua con Pop ra.

    //ghi diem
    char stringNC1[64];
    sprintf(stringNC1, "Player 1:");
    printtext(10, 385, stringNC1);
    char diemso1[64];
    sprintf(diemso1, "%d", diem1);
    printtext(10, 375, diemso1);
    if (end1 >= 10)
    {
        char over1[64];
        sprintf(over1, "LOSER!");
        printtext(10, 365, over1);
        char over2[64];
        sprintf(over2, "WINNER!");
        printtext(335, 365, over2);
        pause = true;
    }
    //nguoi choi 2
    char stringNC2[64];
    sprintf(stringNC2, "Player 2:");
    printtext(335, 385, stringNC2);
    char diemso2[64];
    sprintf(diemso2, "%d", diem2);
    printtext(335, 375, diemso2);
    if (end2 >= 10)
    {
        char over2[64];
        sprintf(over2, "LOSER!");
        printtext(335, 365, over2);
        char over1[64];
        sprintf(over1, "WINNER!");
        printtext(10, 365, over1);
        pause = true;
    }
    char lvl[64];
    sprintf(lvl, "Level: %.0f", level*10);
    printtext(315, 355, lvl);

    ////trai cam
    //glPushMatrix();
    //// copy toan do doan code cua ve trai dat chen xuong duoi
    //glTranslatef(x_cam, y_cam, z_cam);
    //// chú ý thay x và z để chỉ định vị trí mới
    //// y luôn  = 0
    //glColor3f(colorR_cam, colorG_cam, colorB_cam);
    //glutSolidSphere(1.0, 100, 80);
    //// vi yeu cam trai cam to gap doi trai dat nen
    //// ban kinh thanh 1.0
    //glPopMatrix();



    //mat trang.
    glPushMatrix();

    // toa do y_mt=0 de cung mat phang voi y, x_mt+x, z_mt+z de them
    glTranslatef(x_mt, y_mt, z_mt);
    // chú ý thay x và z để chỉ định vị trí mới
    // y luôn  = 0
    glColor3f(colorR_mt, colorG_mt, colorB_mt);
    glutWireSphere(bankinhMTG, 40, 30);
    glPopMatrix();  

    //trai dat pl2
    glPushMatrix();
    glTranslatef(xtd_pl2, ytd_pl2, ztd_pl2);
    glColor3f(red_td, green_td, blue_td);
    glutWireSphere(bankinhTD_2, 40, 30);
    glPopMatrix();
    //mattrang pl2
    glPushMatrix();
    glTranslatef(xmt_pl2, ymt_pl2, zmt_pl2);
    glColor3f(red_mt, green_mt, blue_mt);
    glutWireSphere(bankinhMTG_2, 40, 30);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glutSwapBuffers();

    int timeDiff = getMilliCount() - beginframe;
    if (timeDiff < chuky)
    {
        sleep(chuky - timeDiff);
    }
}
float float_rand(float min, float max)
{
    float scale = rand() / (float)RAND_MAX; /* [0, 1.0] */
    return min + scale * (max - min);      /* [min, max] */
}

void doimau()
{
    colorR1 = float_rand(0.0, 1.0);
    colorG1 = float_rand(0.0, 1.0);
    colorB1 = float_rand(0.0, 1.0);
}

int ChieuY = 1; // đây là biến thể hiện hướng lên hay xuống của camera theo trục Y
// tốc độ quay của chái đất


// tốc độ quay của chái đất
void update() {

    // mỗi frame, vị trí của trái đất sẽ tăng 1 độ
    anpha = anpha + 180 * tocdo * 0.01;
    // vi no quay cham hon mot nua so voi TD nen nhan voi 0.005
    GocQuayCuaTraiCam = GocQuayCuaTraiCam + 180 * tocdo * 0.005;
    //toc do mat trang
    anpha_mt = anpha_mt + 180 * tocdo_mt * 0.1285;
    //
    anpha_tdpl2 = anpha_tdpl2 + 180 * tocdo * 0.01;
    anpha_mtpl2 = anpha_mtpl2 + 180 * tocdo_mtpl2 * 0.1285;

    GocCuaCamera = GocCuaCamera + 180 * tocdo * 0.005;
    // 2 anpha chung công thức nhau, nghĩa là
    // tốc độ của 2 khối cầu y chang nhau
// đủ 360 độ sẽ quay về tính lại là 0
    if (anpha_tdpl2 > 180) anpha_tdpl2 = -180;
    if (anpha_mtpl2 > 180) anpha_mtpl2 = -180;

    if (anpha > 180)
    {
        anpha = -180;
    }
    // hieu chinh vi tri cuar GocQuayCuaTraiCam
    // neu no vuot qua 180 thi reset ve lai
    if (GocQuayCuaTraiCam > 180)
    {
        GocQuayCuaTraiCam = -180;

    }
    if (anpha_mt > 180) {
        anpha_mt = -180;
    }
    if (anpha_mt > 180)
    {
        anpha_mt = -180;

    }
    // theo trục x và z thì côgn thức học cấp
    // 3 cho biết thế này:
    x = rtd * sin(anpha * 3.14159265358979323846 / 180);
    z = rtd * cos(anpha * 3.14159265358979323846 / 180);
    // chỉnh x và z cho khối ban đầu
    // còn khối sau sẽ là y và z
  // tuong tu nhu trai dat, trai cam cung thay doi x va z
    //x_cam = BanKinhCuaTraiCam * sin(GocQuayCuaTraiCam * 3.14159265358979323846 / 180);
    //z_cam = BanKinhCuaTraiCam * cos(GocQuayCuaTraiCam * 3.14159265358979323846 / 180);

    //y_cam = 0.0; // chu y, vi trai cam quay trong mat phang XoZ nen
    // y luon luon bang 0. Hieu ko?

    // cứ mỗi frame thì góc của Camera cũng quay luôn cho vui
    //GocCuaCamera = anpha;
    camX = rtd * sin(GocCuaCamera * 3.14159265358979323846 / 180);
    camZ = rtd * cos(GocCuaCamera * 3.14159265358979323846 / 180);
        // camera sẽ quay cùng tốc độ của trái đất
    // thay đổi trục camY liên tục để chóng mặt chơi
    //camZ = camZ + 0.02 * ChieuY;
    //if (camY < -5 || camY > 5)
    //{
    //    ChieuY = -1 * ChieuY;
    //}

    x_mt = ((r_mt / 2) * sin(anpha_mt * 3.14159265358979323846 / 180)) + x;
    z_mt = ((r_mt / 2) * cos(anpha_mt * 3.14159265358979323846 / 180)) + z;

    // player 2
    xtd_pl2 = quydao_tdpl2 * sin(anpha_tdpl2 * 3.14159265358979323846 / 180);
    ztd_pl2 = quydao_tdpl2 * cos(anpha_tdpl2 * 3.14159265358979323846 / 180);
    xmt_pl2 = ((quydao_mtpl2 / 2) * sin(anpha_mtpl2 * 3.14159265358979323846 / 180)) + xtd_pl2;
    zmt_pl2 = ((quydao_mtpl2 / 2) * cos(anpha_mtpl2 * 3.14159265358979323846 / 180)) + ztd_pl2;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // chỗ này để thay đổi vị trí x và z của từng hạt
     // hteo tốc độ của mỗi hạt
     // đầu tiên vị trí của x mới, sau đó tính z mới
    for (int i = 0; i < soluongsin; i++)
    {
        double xmoi = xsinstart[i] + speedsin[i];
        double zmoi = zsinend[i] * xmoi / xsinend[i];
        xsin[i] = xmoi;
        zsin[i] = sin(xsin[i] * 140 * 3.14 / 180)+zmoi;
        if (xmoi * xmoi > xsinend[i] * xsinend[i])
        {
            xsinstart[i] = 0;
            zsinstart[i] = 0;
            int vitriketthuc = rand() % 11 - 5;
            // 
            if (vitriketthuc > 0)
            {
                xsinend[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                xsinend[i] = vitriketthuc - 2 - (rand() % 5);
            }
            vitriketthuc = rand() % 11 - 5;
            if (vitriketthuc > 0)
            {
                zsinend[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                zsinend[i] = vitriketthuc - 2 - (rand() % 5);
            }
            int thoigiandichuyen = rand() % 5 + 5;
            speedsin[i] = xsinend[i] / (thoigiandichuyen * maxFrame);
        }
        //hinh sin cham trai dat
        else if (distanceAB(xsin[i], x, zsin[i], z) <= (bankinhSIN + bankinhTD))
        {
            bankinhTD += 0.01;
            if (bankinhTD >= 1.1) {
                bankinhTD = 0.1;
            }
            end2++;
            xsinstart[i] = 0;
            zsinstart[i] = 0;
            int vitriketthuc = rand() % 11 - 5;
            // 
            if (vitriketthuc > 0)
            {
                xsinend[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                xsinend[i] = vitriketthuc - 2 - (rand() % 5);
            }
            vitriketthuc = rand() % 11 - 5;
            if (vitriketthuc > 0)
            {
                zsinend[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                zsinend[i] = vitriketthuc - 2 - (rand() % 5);
            }
            int thoigiandichuyen = rand() % 5 + 5;
            speedsin[i] = xsinend[i] / (thoigiandichuyen * maxFrame);
        }
        //hinh sin va cham mat trang
        else if (distanceAB(xsin[i], x_mt, zsin[i], z_mt) <= (bankinhSIN + bankinhMTG))
        {
            xsinstart[i] = 0;
            zsinstart[i] = 0;
            diem2 = diem2 + 2;
            int vitriketthuc = rand() % 11 - 5;
            // 
            if (vitriketthuc > 0)
            {
                xsinend[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                xsinend[i] = vitriketthuc - 2 - (rand() % 5);
            }
            vitriketthuc = rand() % 11 - 5;
            if (vitriketthuc > 0)
            {
                zsinend[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                zsinend[i] = vitriketthuc - 2 - (rand() % 5);
            }
            int thoigiandichuyen = rand() % 5 + 5;
            speedsin[i] = xsinend[i] / (thoigiandichuyen * maxFrame);
        }
        //hinh sin va cham trai dat 2
        else if (distanceAB(xsin[i], xtd_pl2, zsin[i], ztd_pl2) <= (bankinhSIN + bankinhTD_2))
        {
            bankinhTD_2 += 0.01;
            if (bankinhTD_2 >= 1.1) {
                bankinhTD_2 = 0.1;
            }
            end1++;
            xsinstart[i] = 0;
            zsinstart[i] = 0;
            int vitriketthuc = rand() % 11 - 5;
            // 
            if (vitriketthuc > 0)
            {
                xsinend[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                xsinend[i] = vitriketthuc - 2 - (rand() % 5);
            }
            vitriketthuc = rand() % 11 - 5;
            if (vitriketthuc > 0)
            {
                zsinend[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                zsinend[i] = vitriketthuc - 2 - (rand() % 5);
            }
            int thoigiandichuyen = rand() % 5 + 5;
            speedsin[i] = xsinend[i] / (thoigiandichuyen * maxFrame);
        }
        //hinh sin va cham mat trang 2
        else if (distanceAB(xsin[i], xmt_pl2, zsin[i], zmt_pl2) <= (bankinhSIN + bankinhMTG_2))
        {
            xsinstart[i] = 0;
            zsinstart[i] = 0;
            diem1 = diem1 + 2;
            int vitriketthuc = rand() % 11 - 5;
            // 
            if (vitriketthuc > 0)
            {
                xsinend[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                xsinend[i] = vitriketthuc - 2 - (rand() % 5);
            }
            vitriketthuc = rand() % 11 - 5;
            if (vitriketthuc > 0)
            {
                zsinend[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                zsinend[i] = vitriketthuc - 2 - (rand() % 5);
            }
            int thoigiandichuyen = rand() % 5 + 5;
            speedsin[i] = xsinend[i] / (thoigiandichuyen * maxFrame);
        }
        else
        {
            xsinstart[i] = xmoi;
            zsinstart[i] = zmoi;
        }
    }
    ////////////
    // va cham bi
    for (int i = 0; i < soluongve; i++)
    {

        // vị trí x mới sẽ update theo tốc độ
        //double xmoi = mangx[i] - mangtocdo[i];
        double xmoi = bandaux[i] + mangtocdo[i];
        // vị trí z mới sẽ thay đổi theo công thức
        // đường thẳng đc tính trên bảng
        double zmoi = mangz[i] * xmoi / mangx[i];
        // cập nhật lại vị trí mới thay cho vị trí cũ
        //distanceAB(xmoi, mangx[i], zmoi, mangz[i]) <= (bankinhBALL+bankinhMT)
        if (xmoi * xmoi > mangx[i] * mangx[i])
        {
            bandaux[i] = 0;
            bandauz[i] = 0;
            // ban đầu sẽ tạo ra 1 vị trí mà -5 đến 5
            int vitriketthuc = rand() % 11 - 5;
            // 
            if (vitriketthuc > 0)
            {
                // để khống chế vị trí mới sinh ra phải thiệt xa mặt trời
                mangx[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                // tương tự nhưng theo chiều âm
                mangx[i] = vitriketthuc - (rand() % 5);
            }

            // làm y chang vậy  cho việc khởi tạo z
            vitriketthuc = rand() % 11 - 5;
            // 
            if (vitriketthuc > 0)
            {
                // để khống chế vị trí mới sinh ra phải thiệt xa mặt trời
                mangz[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                // tương tự nhưng theo chiều âm
                mangz[i] = vitriketthuc - 2 - (rand() % 5);
            }


            // sau khi khởi tạo xong toa độ, tính được liền luôn 
            // tạo ra biến ngẫu nhiên từ 5-10
            int thoigiandichuyen = rand() % 5 + 5;
            // biến trên chính là thời gian di chuyển của hạt thứ i
            mangtocdo[i] = mangx[i] / (thoigiandichuyen * maxFrame);
            // theo công thức trên bảng, thời gian nhân với số frame
            // lấy quãng đường chia thời gian sẽ ra vận tốc di chuyển
        }

        // va cham trai dat
        else if (distanceAB(xmoi, x, zmoi, z) <= (bankinhBALL + bankinhTD))
        {
            bankinhTD += 0.01;
            if (bankinhTD >= 1.1) {
                bankinhTD = 0.1;
            }
            end2++;
            bandaux[i] = 0;
            bandauz[i] = 0;
            doimau();
            // ban đầu sẽ tạo ra 1 vị trí mà -5 đến 5
            int vitriketthuc = rand() % 11 - 5;
            // 
            if (vitriketthuc > 0)
            {
                // để khống chế vị trí mới sinh ra phải thiệt xa mặt trời
                mangx[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                // tương tự nhưng theo chiều âm
                mangx[i] = vitriketthuc - (rand() % 5);
            }

            // làm y chang vậy  cho việc khởi tạo z
            vitriketthuc = rand() % 11 - 5;
            // 
            if (vitriketthuc > 0)
            {
                // để khống chế vị trí mới sinh ra phải thiệt xa mặt trời
                mangz[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                // tương tự nhưng theo chiều âm
                mangz[i] = vitriketthuc - 2 - (rand() % 5);
            }


            // sau khi khởi tạo xong toa độ, tính được liền luôn 
            // tạo ra biến ngẫu nhiên từ 5-10
            int thoigiandichuyen = rand() % 5 + 5;
            // biến trên chính là thời gian di chuyển của hạt thứ i
            mangtocdo[i] = mangx[i] / (thoigiandichuyen * maxFrame);
            // theo công thức trên bảng, thời gian nhân với số frame
            // lấy quãng đường chia thời gian sẽ ra vận tốc di chuyển
        }

        // va cham mat trang
        else if (distanceAB(xmoi, x_mt, zmoi, z_mt) <= (bankinhBALL + bankinhMTG))
        {
            bandaux[i] = 0;
            bandauz[i] = 0;
            diem2++;
            // ban đầu sẽ tạo ra 1 vị trí mà -5 đến 5
            int vitriketthuc = rand() % 11 - 5;
            // 
            if (vitriketthuc > 0)
            {
                // để khống chế vị trí mới sinh ra phải thiệt xa mặt trời
                mangx[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                // tương tự nhưng theo chiều âm
                mangx[i] = vitriketthuc - (rand() % 5);
            }

            // làm y chang vậy  cho việc khởi tạo z
            vitriketthuc = rand() % 11 - 5;
            // 
            if (vitriketthuc > 0)
            {
                // để khống chế vị trí mới sinh ra phải thiệt xa mặt trời
                mangz[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                // tương tự nhưng theo chiều âm
                mangz[i] = vitriketthuc - 2 - (rand() % 5);
            }


            // sau khi khởi tạo xong toa độ, tính được liền luôn 
            // tạo ra biến ngẫu nhiên từ 5-10
            int thoigiandichuyen = rand() % 5 + 5;
            // biến trên chính là thời gian di chuyển của hạt thứ i
            mangtocdo[i] = mangx[i] / (thoigiandichuyen * maxFrame);
            // theo công thức trên bảng, thời gian nhân với số frame
            // lấy quãng đường chia thời gian sẽ ra vận tốc di chuyển
        }
        ////
        // va cham trai dat 2
        else if (distanceAB(xmoi, xtd_pl2, zmoi, ztd_pl2) <= (bankinhBALL + bankinhTD))
        {
            bankinhTD_2 += 0.01;
            if (bankinhTD_2 >= 1.1) {
                bankinhTD_2 = 0.1;
            }
            end1++;
            bandaux[i] = 0;
            bandauz[i] = 0;
            //doimau();
            // ban đầu sẽ tạo ra 1 vị trí mà -5 đến 5
            int vitriketthuc = rand() % 11 - 5;
            // 
            if (vitriketthuc > 0)
            {
                // để khống chế vị trí mới sinh ra phải thiệt xa mặt trời
                mangx[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                // tương tự nhưng theo chiều âm
                mangx[i] = vitriketthuc - (rand() % 5);
            }

            // làm y chang vậy  cho việc khởi tạo z
            vitriketthuc = rand() % 11 - 5;
            // 
            if (vitriketthuc > 0)
            {
                // để khống chế vị trí mới sinh ra phải thiệt xa mặt trời
                mangz[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                // tương tự nhưng theo chiều âm
                mangz[i] = vitriketthuc - 2 - (rand() % 5);
            }


            // sau khi khởi tạo xong toa độ, tính được liền luôn 
            // tạo ra biến ngẫu nhiên từ 5-10
            int thoigiandichuyen = rand() % 5 + 5;
            // biến trên chính là thời gian di chuyển của hạt thứ i
            mangtocdo[i] = mangx[i] / (thoigiandichuyen * maxFrame);
            // theo công thức trên bảng, thời gian nhân với số frame
            // lấy quãng đường chia thời gian sẽ ra vận tốc di chuyển
        }

        // va cham mat trang 2
        else if (distanceAB(xmoi, xmt_pl2, zmoi, zmt_pl2) <= (bankinhBALL + bankinhMTG))
        {
            bandaux[i] = 0;
            bandauz[i] = 0;
            diem1++;
            // ban đầu sẽ tạo ra 1 vị trí mà -5 đến 5
            int vitriketthuc = rand() % 11 - 5;
            // 
            if (vitriketthuc > 0)
            {
                // để khống chế vị trí mới sinh ra phải thiệt xa mặt trời
                mangx[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                // tương tự nhưng theo chiều âm
                mangx[i] = vitriketthuc - (rand() % 5);
            }

            // làm y chang vậy  cho việc khởi tạo z
            vitriketthuc = rand() % 11 - 5;
            // 
            if (vitriketthuc > 0)
            {
                // để khống chế vị trí mới sinh ra phải thiệt xa mặt trời
                mangz[i] = vitriketthuc + 2 + (rand() % 5);
            }
            else
            {
                // tương tự nhưng theo chiều âm
                mangz[i] = vitriketthuc - 2 - (rand() % 5);
            }


            // sau khi khởi tạo xong toa độ, tính được liền luôn 
            // tạo ra biến ngẫu nhiên từ 5-10
            int thoigiandichuyen = rand() % 5 + 5;
            // biến trên chính là thời gian di chuyển của hạt thứ i
            mangtocdo[i] = mangx[i] / (thoigiandichuyen * maxFrame);
            // theo công thức trên bảng, thời gian nhân với số frame
            // lấy quãng đường chia thời gian sẽ ra vận tốc di chuyển
        }

        else {
            bandaux[i] = xmoi;
            bandauz[i] = zmoi;
        }
    }


    // nếu mà hạt nào bay quá xa thì khởi tạo lại
    // cứ mỗi frame sinh ra, thì trái đất đi đc 180*tocdo*0.01
    // set cố định day = 360/24
    day = day + 15;
    // neu day mà lớn hơn 360 độ thì reset nó
    // nếu không chạy 1 lúc thì nó tràn biến
    if (day > 360)
    {
        day = 0;
    }


    if (getMilliCount() - tgbatdau > 5000)
    {
        level = level1;
        soluongve = 14;
        soluongsin = 1;
    }
    if (getMilliCount() - tgbatdau > 7000)
    {
        level = level2;
        soluongve = 18;
        soluongsin = 2;
    }
    if (getMilliCount() - tgbatdau > 9000)
    {
        level = level3;
        soluongve = 22;
        soluongsin = 3;
    }
    if (getMilliCount() - tgbatdau > 11000)
    {
        level = level4;
        soluongve = 26;
        soluongsin = 4;
    }
    if (getMilliCount() - tgbatdau > 13000)
    {
        level = level5;
        soluongve = 30;
        soluongsin = 5;
    }
    if (getMilliCount() - tgbatdau > 15000)
    {
        level = level6;
        soluongve = 34;
        soluongsin = 6;
    }
    if (getMilliCount() - tgbatdau > 17000)
    {
        level = level7;
        soluongve = 38;
        soluongsin = 7;
    }
    if (getMilliCount() - tgbatdau > 19000)
    {
        level = level8;
        soluongve = 42;
        soluongsin = 8;
    }
    if (getMilliCount() - tgbatdau > 21000)
    {
        level = level9;
        soluongve = 46;
        soluongsin = 9;
    }
    if (getMilliCount() - tgbatdau > 23000)
    {
        level = level10;
        soluongve = 50;
        soluongsin = 10;
    }


    if (pause == true) Paused();
    glutPostRedisplay();
}

void reshape(int w, int h) {

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


double tocdotemp = 0;
// biến lưu trữ tạm tốc độ hiện tại của trái đất
void inputProcess(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        // tốc độ sẽ đẩy lên 0.2 mỗi lần ấn 1
        tocdo++;
        break;
    case '2':
        tocdo--;
        break;
    case '3':
        if (tocdo != 0)
        {
            tocdotemp = tocdo;
            tocdo = 0;
        }
        else
        {
            tocdo = tocdotemp;
        }
        break;

    case 'w':
        camY = camY + 0.2;
        camZ= camZ + 0.2;
        break;
    case 's':
        camY = camY - 0.2;
        camZ = camZ - 0.2;
        break;
    case 'a':
        //camX = camX - 0.2;
        tocdo_mtpl2 = 0;
        tocdo_mtpl2 -= 0.1;
        tocdo_mtpl2 -= level;
        break;
    case 'd':
        //camX = camX + 0.2;
        tocdo_mtpl2 = 0;
        tocdo_mtpl2 += 0.1;
        tocdo_mtpl2 += level;
        break;
    case 'p':
        pause = !pause;
    case 'o':
        soluongve--;
        if (soluongve < 1)
        {
            soluongve = 1;
        }
        break;
    default:          break;
    }
}

void specialProcess(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        tocdo_mt = 0;
        tocdo_mt -= 0.1;
        tocdo_mt -= level;
        break;
    case GLUT_KEY_RIGHT:
        tocdo_mt = 0;
        tocdo_mt += 0.1;
        tocdo_mt += level;
        break;
    default:        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(inputProcess);
    glutSpecialFunc(specialProcess);
    glutIdleFunc(update);
    glutMainLoop();
    return 0;
}


