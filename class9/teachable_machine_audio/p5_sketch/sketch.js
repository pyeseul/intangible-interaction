/* 

Intangible Interaction Spring 2020

Depending on which sound you make, it turns on differenet physical digital output on Arduino.

Train your own audio/image/pose at 
Teachable Machine https://teachablemachine.withgoogle.com/

ml5 https://ml5js.org/

*/

let classifier;

// Label
let label = 'listening...';

// Teachable Machine model URL:
let soundModel = 'https://teachablemachine.withgoogle.com/models/knk1pQUTr/';

// Serial Communication
var serial;         
var portName = '/dev/tty.usbmodem143201'; // your serial port name

function preload() {
  // Load the model
  classifier = ml5.soundClassifier(soundModel + 'model.json');
}

function setup() {
  createCanvas(320, 240);
  
  // Start classifying
  // The sound model will continuously listen to the microphone
  classifier.classify(gotResult);
  
  // Serial Communication
  serial = new p5.SerialPort();    
  serial.on('error', serialError); 
  serial.on('list', printList); 
  serial.open(portName);     
}

function draw() {
  background(0);
  
  // Draw the label in the canvas
  fill(255);
  textSize(32);
  textAlign(CENTER, CENTER);
  
  if (label == 'shaker') {
    text('SHAKER', 100, 100);
    serial.write(1);
  } else if (label == 'bell') {
    text('BELL', 100, 100);
    serial.write(2);
  } else {
    serial.write(0);
  }  
}


// The model recognizing a sound will trigger this event
function gotResult(error, results) {
  if (error) {
    console.error(error);
    return;
  }
  // The results are in an array ordered by confidence.
  // console.log(results[0]);
  label = results[0].label;
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