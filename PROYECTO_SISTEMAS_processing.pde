import processing.serial.*;
Serial Myserial; 
/////DATOS QUE VAN A SER RECIBIDOS POR LA COMUNICACION SERIAL
float Angle;
float distancia;
/// NOTA:cada circunferencia tiene 50 de distancia 
float distancia_object=250, angulo_object=0;
float angulo=0;
float centro = 400;//320
float radio_radar = 300;//300
float radio_1=0;
float radio_2=100;
float radio_3=200;
float radio_4=300;
float radio_5=400;
float radio_6=500;
float X_texto_externo =800;
///float velocidad=0.15;
float distancia_1=0;  
float distancia_2=0;
void setup(){
  size(1920,750);///640,720
  background(255);
  String  myPort= Serial.list()[0]; //AQUI ESTOY PONIENDO QUE MI PUERTO SERIAL ES EL COM0
 Myserial = new Serial(this, myPort,9600);  
}
void draw(){
  background(255);
  if(Myserial.available()>0){
    // println(Myserial.read());
    while(Myserial.read()!=255);
    angulo=Myserial.read();
    distancia_1=Myserial.read();
    distancia_2=Myserial.read();

//   if(Myserial.available()==255){
  //   println(Myserial.read());
     //println(Myserial.read());
     //println(Myserial.read());
  //   angulo=Myserial.available();
    //distancia_1=Myserial.availab
    //  distancia = Myserial.read();
    //if(distancia>=0&&distancia<60){
    //  distancia_1=distancia;
    //}
    //if(distancia>=128){
    //  distancia=distancia-128;
    //  distancia_2=distancia; 
    //}
  }
  dibujo_radar();
  linea(round(angulo*1.8));
  Object_detection( distancia_1,distancia_2,round(angulo*1.8),0,round(angulo*1.8));
  
  radio_1=animacion_de_refresco(radio_1);
  radio_2=animacion_de_refresco(radio_2);
  radio_3=animacion_de_refresco(radio_3);
  radio_4=animacion_de_refresco(radio_4);
  radio_5=animacion_de_refresco(radio_5);
  radio_6=animacion_de_refresco(radio_6);
  Text_radar(distancia_1,distancia_2,round(angulo*1.8));
}

void linea(float angulo){
  pushMatrix();
  noFill();
  strokeWeight(5);
  stroke(0,255,0);
  translate(centro,centro); // moves the starting coordinats to new location
  line(0,0,radio_radar*cos(radians(angulo)),-radio_radar*sin(radians(angulo))); // draws the line according to the angle
  line(0,0,-radio_radar*cos(radians(angulo)),radio_radar*sin(radians(angulo)));
  popMatrix();
}
void Object_detection(float distancia_object_1,float distancia_object_2, float angulo_object,float radio_radar,float angulo){
  if((distancia_object_1<=60)&&(distancia_object_2<=60)){
  pushMatrix();
  noFill();
  strokeWeight(5);
  stroke(255,0,0);
  translate(centro,centro); // moves the starting coordinats to new location
  ///distancia del objeto del primer sensor
  line(5*distancia_object_1*cos(radians(angulo_object)),-5*distancia_object_1*sin(radians(angulo_object)),5*radio_radar*cos(radians(angulo)),-5*radio_radar*sin(radians(angulo))); // draws the line according to the angle
  //distancia de objeto del segundo sensor 
  line(-5*distancia_object_2*cos(radians(angulo_object)),5*distancia_object_2*sin(radians(angulo_object)),-5*radio_radar*cos(radians(angulo)),5*radio_radar*sin(radians(angulo))); 
  popMatrix();
  }
  
}
void dibujo_radar(){
  pushMatrix();
  stroke(0,255,0);
  fill(0,0,0);
  ellipseMode(CENTER);
  stroke(255,0,0);
  strokeWeight(0.5);
  ellipse(centro,centro,700,700);
  stroke(0,255,0);
  strokeWeight(0.5);
  ellipse(centro,centro,600,600);
  noFill();
  stroke(0,255,0);
  strokeWeight(0.5);///0.5
  ellipse(centro,centro,500,500);
  ellipse(centro,centro,400,400);
  ellipse(centro,centro,300,300);
  ellipse(centro,centro,200,200);
  ellipse(centro,centro,100,100);
  translate(centro,centro);
  line(0,0,radio_radar*cos(radians(30)),-radio_radar*sin(radians(30)));
  line(0,0,radio_radar*cos(radians(60)),-radio_radar*sin(radians(60)));
  line(0,0,-radio_radar*cos(radians(30)),-radio_radar*sin(radians(30)));
  line(0,0,-radio_radar*cos(radians(60)),-radio_radar*sin(radians(60)));
  line(0,0,radio_radar*cos(radians(90)),radio_radar*sin(radians(90)));
  line(0,0,-radio_radar*cos(radians(90)),-radio_radar*sin(radians(90)));
  line(0,0,-radio_radar*cos(radians(0)),radio_radar*sin(radians(0)));
  line(0,0,radio_radar*cos(radians(0)),-radio_radar*sin(radians(0)));
  line(0,0,-radio_radar*cos(radians(30)),radio_radar*sin(radians(30)));
  line(0,0,-radio_radar*cos(radians(60)),radio_radar*sin(radians(60)));
  line(0,0,radio_radar*cos(radians(30)),radio_radar*sin(radians(30)));
  line(0,0,radio_radar*cos(radians(60)),radio_radar*sin(radians(60)));
  popMatrix();
}
float animacion_de_refresco(float radio){
  pushMatrix();
  noFill();
  strokeWeight(0.5);
  translate(centro,centro);
  stroke(0,255,0);
  radio=radio+3;
  circle(0,0,radio);
//radio=radio+3;
  if(radio>=600){
    radio=0;
  }
  popMatrix();
  return radio;
}
void Text_radar(float distancia_1,float distancia_2, float angulo){
  pushMatrix();
  translate(centro,centro);
  fill(0,255,0);
  textSize(10);
  text("10cm",50,0);
  text("20cm",100,0);
  text("30cm",150,0);
  text("40cm",200,0);
  text("50cm",250,0);
  text("60cm",300,0);
  popMatrix();
  pushMatrix();
  translate(centro,centro);
  fill(0,255,0); ///el sistema empieza en 90° 
  translate(radio_radar*cos(radians(30)),-radio_radar*sin(radians(30)));
  rotate(-radians(-60));
  text("30°",0,0);
  popMatrix();
  pushMatrix();
  translate(centro,centro);
  fill(0,255,0);
  textSize(10);
  fill(0,255,0); ///el sistema empieza en 90° 
  translate(radio_radar*cos(radians(60)),-radio_radar*sin(radians(60)));
  rotate(-radians(-30));
  text("60°",0,0);
  popMatrix();
  pushMatrix();
  translate(centro,centro);
  fill(0,255,0);
  textSize(10);
  fill(0,255,0); ///el sistema empieza en 90° 
  translate(radio_radar*cos(radians(90)),-radio_radar*sin(radians(90)));
  text("90°",0,0);
  popMatrix();
  pushMatrix();
  translate(centro,centro);
  fill(0,255,0);
  textSize(10);
  fill(0,255,0); ///el sistema empieza en 90° 
  translate(radio_radar*cos(radians(120)),-radio_radar*sin(radians(120)));
  rotate(-radians(30));
  text("120°",0,0);
  popMatrix();
  pushMatrix();
  translate(centro,centro);
  fill(0,255,0);
  textSize(10);
  fill(0,255,0); ///el sistema empieza en 90° 
  translate(radio_radar*cos(radians(150)),-radio_radar*sin(radians(150)));
  rotate(-radians(60));
  text("150°",0,0);
  popMatrix();
  pushMatrix();
  translate(centro,centro);
  fill(0,255,0);
  textSize(10);
  fill(0,255,0); ///el sistema empieza en 90° 
  translate(-20+radio_radar*cos(radians(180)),-radio_radar*sin(radians(180)));
  text("180°",0,0);
  popMatrix();
  pushMatrix();
  translate(centro,centro);
  fill(0,255,0);
  textSize(10);
  fill(0,255,0); ///el sistema empieza en 90° 
  translate(-20+radio_radar*cos(radians(210)),10-radio_radar*sin(radians(210)));
  rotate(-radians(30));
  text("210°",0,0);
  popMatrix();
  pushMatrix();
  translate(centro,centro);
  fill(0,255,0);
  textSize(10);
  fill(0,255,0); ///el sistema empieza en 90° 
  translate(-10+radio_radar*cos(radians(240)),15-radio_radar*sin(radians(240)));
  rotate(-radians(60));
  text("240°",0,0);
  popMatrix();
  pushMatrix();
  translate(centro,centro);
  fill(0,255,0);
  textSize(10);
  fill(0,255,0); ///el sistema empieza en 90° 
  translate(-20+radio_radar*cos(radians(270)),10-radio_radar*sin(radians(270)));
  //rotate(-radians(60));
  text("270°",0,0);
  popMatrix();
  pushMatrix();
  translate(centro,centro);
  fill(0,255,0);
  textSize(10);
  fill(0,255,0); ///el sistema empieza en 90° 
  translate(radio_radar*cos(radians(300)),20-radio_radar*sin(radians(300)));
  rotate(-radians(60));
  text("300°",0,0);
  popMatrix();
  pushMatrix();
  translate(centro,centro);
  fill(0,255,0);
  textSize(10);
  fill(0,255,0); ///el sistema empieza en 90° 
  translate(radio_radar*cos(radians(330)),20-radio_radar*sin(radians(330)));
  rotate(-radians(60));
  text("330°",0,0);
  popMatrix();
  ////AHORA VAMOS A COLOCAR LOS TEXTOS FUERA DEL RADAR
  pushMatrix();
  fill(0);
  translate(X_texto_externo,0);
  textSize(100);
  text("RADAR",50,150);
  textSize(60);
  text("Sensor1:",0,250);
  textSize(50);
  text("DISTANCIA:",0,350);
  text("ANGULO:",0,400);
  textSize(60);
  text("Sensor2:",0,600);
  textSize(50);
  text("DISTANCIA:",0,650);
  text("ANGULO:",0,700);
  noFill();
  stroke(0);
  text(int(distancia_1),290,350);
  
  text(int(distancia_2),290,650);
  
  text(int(angulo)+"°",290,400);
  text(int(angulo+180)+"°",290,700);
  noFill();
  popMatrix();
}
