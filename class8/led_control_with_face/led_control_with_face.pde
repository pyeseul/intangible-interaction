// This example detects faces, picks the first face in the array, and send the x coordinate of the face over serial   
// Intangible Interaction Spring 2020

import gab.opencv.*;
import processing.video.*;
import java.awt.*;
import processing.serial.*;

Capture video;
OpenCV opencv;
Serial myPort;

int myColor = color(0,0,0);
int faceX = 0;
int faceX_prev = 0;
int len;

void setup() {
  size(640, 480);
  video = new Capture(this, 640/2, 480/2);
  opencv = new OpenCV(this, 640/2, 480/2);
  opencv.loadCascade(OpenCV.CASCADE_FRONTALFACE);  

  video.start();
  
  String portName = Serial.list()[1]; // change the port number in []
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  scale(2);
  opencv.loadImage(video);

  image(video, 0, 0 );

  noFill();
  stroke(0, 255, 0);
  strokeWeight(2);
  Rectangle[] faces = opencv.detect();
  
  println(faces.length); // print how many faces are in the frame

  for (int i = 0; i < faces.length; i++) {
    rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
  
    faceX = int(map(faces[i].x, 0, width/2, 0, 255));
    
      if (faceX != faceX_prev ){ // if new reading is different than the old one
        myPort.write(faces[0].x); // send the x coordinate of the first face in the frame to serial                   
        println("sent");  
        delay(1); // slight delay
        faceX_prev = faceX; //set prev
      }
  }
}

void captureEvent(Capture c) {
  c.read(); // this function is to capture each frame of the video to display in the draw() loop
}

// Arduino Code

//char incomingVal;
//int ledPin = 5;

//void setup() {
//  pinMode(ledPin, OUTPUT);
//  Serial.begin(9600);
//}

//void loop() {
//  while (Serial.available()) {
//    incomingVal = Serial.read();
//  }
//  analogWrite(ledPin, incomingVal);

//}
