
//Incluir las librerías para utilizar la pantalla
#include <TouchScreen.h>
#include <Adafruit_GFX.h>
#include <UTFTGLUE.h>
#include <stdint.h>

UTFTGLUE myGLCD(0x9481, A2, A1, A3, A4, A0);

//Definir pines para controlar la pantalla
#define XP 9   //Pin de control digital
#define YP A2  //Pin análogo de control
#define XM A3  //Pin análogo de control
#define YM 8   //Pin digital de control

// Definir los niveles de presión mínima y máxima
#define MINPRESSURE 10
#define MAXPRESSURE 1000

//Definir los valores para calibrar la pantalla táctil
#define X_STPT  75    // Valor de X inicial
#define X_ENPT  905    // Valor de X final
#define Y_STPT  145    // Valor de Y inicial
#define Y_ENPT  880    // Valor de Y final

TouchScreen myTouch = TouchScreen(XP, YP, XM, YM, 300);

//Definir códigos de los colores más utilizados
#define NEGRO   0x0000
#define AZUL    0x001F
#define ROJO     0xF800
#define VERDE   0x07E0
#define CIAN    0x07FF
#define MAGENTA 0xF81F
#define AMARILLO  0xFFE0
#define BLANCO   0xFFFF

int led = 10; //Pin PWM donde va conectado el LED

//Define el ancho y largo de la pantalla en pixeles
int x_size = 480; int y_size = 320;
bool settscrsize(int w, int h) {
  if ((w <= 0) || (h <= 0)) return false;
  x_size = w; y_size = h;
  return true;
}

int x, y;  //Variables para obtener las coordenadas X y Y donde se presiona la pantalla

int color = CIAN; //Inicia en color CIAN por defecto

void setup() {

  //Inicializacion de la pantalla
  myGLCD.InitLCD(1);  //Inicia en modo horizontal
  pantallaLimpia();
}

void loop() {

  TSPoint p;

  if (checktouch(&myTouch, &p))
  {
    x = p.x; y = p.y;

    myGLCD.setColor(color);
    myGLCD.fillCircle(x, y, 3);

    if ( x >= 445 && x <= 480 && y >= 252 && y <= 320)
    {
      pantallaLimpia();  //Llama la función de limpiar la pantalla
    }

    if (x >= 445 && x <= 480 && y >= 0 && y <= 35)
    {
      myGLCD.fillRoundRect(445, 0, 479, 35);
      color = CIAN;   //Selecciona el color CIAN
    }

    if (x >= 445 && x <= 480 && y >= 36 && y <= 71)
    {
      myGLCD.fillRoundRect(445, 36, 479, 71);
      color = AZUL;   //Selecciona el color azul
    }

    if (x >= 445 && x <= 480 && y >= 72 && y <= 107)
    {
      myGLCD.fillRoundRect(445, 72, 479, 107);
      color = ROJO;   //Selecciona el color rojo
    }

    if (x >= 445 && x <= 480 && y >= 108 && y <= 143)
    {
      myGLCD.fillRoundRect(445, 108, 479, 143);
      color = VERDE;    //Selecciona el color verde
    }

    if (x >= 445 && x <= 480 && y >= 144 && y <= 179)
    {
      myGLCD.fillRoundRect(445, 144, 479, 179);
      color = AMARILLO;    //Selecciona el color amarillo
    }

    if (x >= 445 && x <= 480 && y >= 180 && y <= 215)
    {
      myGLCD.fillRoundRect(445, 180, 479, 215);
      color = MAGENTA;    //Selecciona el color magenta
    }

    if (x >= 445 && x <= 480 && y >= 216 && y <= 251)
    {
      myGLCD.fillRoundRect(445, 216, 479, 251);
      color = BLANCO;     //Selecciona el color blanco
    }
  }
}

void pantallaLimpia()
{
  myGLCD.clrScr();
  //Cuadrados para escoger colores
  myGLCD.setColor(CIAN);
  myGLCD.fillRoundRect(445, 0, 479, 35);
  myGLCD.setColor(AZUL);
  myGLCD.fillRoundRect(445, 36, 479, 71);
  myGLCD.setColor(ROJO);
  myGLCD.fillRoundRect(445, 72, 479, 107);
  myGLCD.setColor(VERDE);
  myGLCD.fillRoundRect(445, 108, 479, 143);
  myGLCD.setColor(AMARILLO);
  myGLCD.fillRoundRect(445, 144, 479, 179);
  myGLCD.setColor(MAGENTA);
  myGLCD.fillRoundRect(445, 180, 479, 215);
  myGLCD.setColor(BLANCO);
  myGLCD.fillRoundRect(445, 216, 479, 251);
  myGLCD.setColor(AMARILLO);
  myGLCD.drawRoundRect(445, 252, 479, 319);
  //Botón limpiar
  myGLCD.setColor(CIAN);
  myGLCD.setTextSize(1);
  myGLCD.print("C", 460, 254);
  myGLCD.print("L", 460, 268);
  myGLCD.print("E", 460, 282);
  myGLCD.print("A", 460, 296);
  myGLCD.print("R", 460, 310);
}

bool checktouch_core(TouchScreen *ts, TSPoint *pp, bool calflg) {
  // variables
  bool rlt = false;
  int rtry = 10;

  // Leer el sensor táctil de la pantalla
  delay(1);
  TSPoint p = ts->getPoint();
  if ((p.z < MINPRESSURE) || (p.z > MAXPRESSURE)) goto rsmpt;
  if (pp == 0) {
    rlt = true;
    goto rsmpt;
  }

  // Volver a leer el sensor táctil
  if (p.x < (X_STPT + 100)) {
    for (int i = 0 ; i < 2 ; i++) {
      delay(1);
      p = ts->getPoint();
      if (p.x > (X_STPT + 100)) break;
      if (p.x == 0) {
        if (rtry > 0) {
          rtry--;
          i = 0;
        }
      }
    }
  }
  if (p.x == 0) return false;

  // Obtener las coordenadas X y Y en donde se toca la pantalla
  if (pp != 0) {
#ifdef X_INVERSE
    p.x = 1100 - p.x;
#endif
    if (calflg) {
      pp->x = p.x; pp->y = p.y;
    } else {
      pp->x = ((long)(p.x - X_STPT) * (long)x_size) / (long)(X_ENPT - X_STPT);
      if (pp->x < 0) pp->x = 0;
      pp->y = ((long)(p.y - Y_STPT) * (long)y_size) / (long)(Y_ENPT - Y_STPT);
      if (pp->y < 0) pp->y = 0; if (pp->y >= y_size) pp->y = y_size - 1;
    }
    pp->z = p.z;
  }
  rlt = true;

  // Restaurar los pines para volver a ser utilizados para la función táctil
rsmpt:
  pinMode(XP, OUTPUT); pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT); pinMode(YM, OUTPUT);

  return rlt;
}

// Verificar el sensor touch para usarlo
bool checktouch(TouchScreen *ts, TSPoint *pp) {
  return checktouch_core(ts, pp, false);
}
