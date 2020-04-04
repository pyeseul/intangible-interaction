/* 

Intangible Interaction Spring 2020

Squat Motivator: When you do 5 squats, an LED (or any physical digital output) turns on.

The sketch uses PoseNet to decide if you do a squat (by measuring distances between your hip and knee) 
and counts the number of squats. 
When it senses your 5th squat, the sketch sends 1 to Arduino over serial to turn on a physical digital output (e.g., LED) 

PoseNet https://ml5js.org/reference/api-PoseNet/
p5.serialport https://github.com/p5-serial/p5.serialport 

*/

let video;
let rightHipX = 0;
let rightHipY = 0;
let rightKneeX = 0;
let rightKneeY = 0;
let counter = 0;
let d_prev = 0;

// Serial Communication
var serial;         
var portName = '/dev/tty.usbmodem143201'; // your serial port name

function setup() {
  createCanvas(600, 400);
  video = createCapture(VIDEO);
  video.hide();
  
  // Create a new poseNet method and apply to video
  poseNet = ml5.poseNet(video, modelLoaded);

  // Listen to new 'pose' events and get the coordinates of left hip and left knee of a pose
  poseNet.on('pose', (poses) => {
    //console.log(poses);    
    rightHipX = poses[0].pose.keypoints[12].position.x;
    rightHipY = poses[0].pose.keypoints[12].position.y;
    rightKneeX = poses[0].pose.keypoints[14].position.x;
    rightKneeY = poses[0].pose.keypoints[14].position.y;
    
  });
  
  // Serial Communication
  serial = new p5.SerialPort();    
  serial.on('error', serialError); 
  serial.on('list', printList); 
  serial.open(portName); 
}

// Print out the message When the model is loaded
function modelLoaded() {
  console.log('model is ready!');
}

function draw() {
  
  // draw video
  image(video, 0, 0);  
  
  // calculate the distance between left hip and left knee
  let d = dist(rightHipX, rightHipY, rightKneeX, rightKneeY);
  
  // visualize the distance with an ellipse
  fill(0, 255, 0);
  ellipse(rightHipX, rightHipY, d);
  
  // if a squat is detected (when someone sits down, and up), increase the counter by 1
  if (d < 100 && d_prev >=100) {   
    counter ++;
  }
  
  // if the counter reaches at 5, write 1 to serial otherwise 0
  if (counter >= 5) {
    serial.write(1);    
  } else {
    serial.write(0);
  }
  
  // console.log(counter);
  // console.log(d);
  
  // save the current d to prev_d for comparison
  d_prev = d; 
  
}

// print serial port erros:
function serialError(err) {
  print('Something went wrong with the serial port. ' + err);
}
 
// get the list of ports:
function printList(portList) { 
 for (var i = 0; i < portList.length; i++) { 
 console.log(i + " " + portList[i]);
 }
}
