/* 

Intangible Interaction Spring 2021

Depending on which sound you make, it turns on differenet physical digital output on Arduino.

Train your own audio/image/pose at 
Teachable Machine https://teachablemachine.withgoogle.com/

ml5 https://ml5js.org/

*/

// Global variable to store the classifier
let classifier;

// Label (start by showing listening)
let label = "listening";

// Teachable Machine model URL:
let soundModelURL = 'https://teachablemachine.withgoogle.com/models/U0pEeTrca/model.json';

// Serial Communication
var serial;         
var portName = '/dev/tty.usbmodem141201'; // your serial port name

function preload() {
  // Load the model
  classifier = ml5.soundClassifier(soundModelURL);
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
  text(label, width / 2, height / 2);
  
  if (label == 'glass1') {
    //text('GLASS', 100, 100);
    serial.write(1);
  } 
  else if (label == 'glass2') {
    //text('BELL', 100, 100);
    serial.write(2);
  } 
  else {
    //text('NOTHING', 100, 200);
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