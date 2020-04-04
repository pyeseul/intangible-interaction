/* 

Intangible Interaction Spring 2020

The sketch uses PoseNet to decide if you sit down (by measuring distances between your hip and knee)
and if so it communicates over serial to turn on a physical digital output (e.g., LED)

See the end for the Arduino side code.
Use with p5.serialport 

PoseNet https://ml5js.org/reference/api-PoseNet/
p5.serialport https://github.com/p5-serial/p5.serialport 

*/

let video;

let leftHipX;
let leftHipY;
let leftKneeX;
let leftKneeY;

var serial;
var portName = '/dev/tty.usbmodem143201'; // your port name here

function setup() {
  createCanvas(600, 400);
  
  video = createCapture(VIDEO);  
  video.hide();
  
  // Create a new poseNet method
  poseNet = ml5.poseNet(video, modelLoaded);
  
  // Listen to new 'pose' events and get the coordinates of left hip and left knee of a pose
  poseNet.on('pose', (poses) => {
    //console.log(poses);
    leftHipX = poses[0].pose.keypoints[11].position.x;
    leftHipY = poses[0].pose.keypoints[11].position.y;
    leftKneeX = poses[0].pose.keypoints[13].position.x;
    leftKneeY = poses[0].pose.keypoints[13].position.y;
  });
  
  // Setting up serial communication
  serial = new p5.SerialPort();    
  serial.on('error', serialError); 
  serial.on('list', printList); 
  serial.open(portName); 
  
}

function draw() {
  
  // draw video
  image(video, 0, 0);
  
  // calculate the distance between left hip and left knee
  let d = dist(leftHipX, leftHipY, leftKneeX, leftKneeY); 
  
  // visualize the distance with an ellipse
  fill(0, 255, 0);
  noStroke();
  ellipse(leftHipX, leftHipY, d);
  ellipse(leftKneeX, leftKneeY, d);    
  // console.log(d);
  
  // if the distance is less than 100 (when the person sat down - the number can vary) write 1 to serial, otherwise 0
  if (d < 100) {
    serial.write(1);
  } else {
    serial.write(0);
  }
}

// Print out the message When the model is loaded
function modelLoaded() {
  console.log('model loaded!');
}

// printing serial port erros:
function serialError(err) {
  print('Something went wrong with the serial port. ' + err);
}
 
// get the list of ports:
function printList(portList) {
 // portList is an array of serial port names
 for (var i = 0; i < portList.length; i++) {
 // Display the list the console:
 console.log(i + " " + portList[i]);
 }
}


/* Arduino Code:

byte fromP5;

void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  
}
void loop() {
  if(Serial.available()){
    fromP5 = Serial.read();    
  } 
  if (fromP5 == 1) {
    digitalWrite(4, HIGH);
  
  } else {
    digitalWrite(4, LOW);
  
  }
}
*/
