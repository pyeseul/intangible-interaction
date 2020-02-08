/* 
Class 2 exercise for Intangible Interaciton at ITP by Yeseul Song

This is a p5.js sketch for the serial communication with Arduino
that receives 1 binary value from Arduino and triggers a sound file when the incoming value is 0

The serial communication part of this code is based on the example code here:
https://itp.nyu.edu/physcomp/labs/labs-serial-communication/lab-serial-input-to-the-p5-js-ide/
*/


var serial;          // variable to hold an instance of the serialport library
var portName = '/dev/tty.usbmodem144101'; // fill in your serial port name here
var fromSerial;                            // for incoming serial data
var fromSerial_prev;
 
function preload() {
    
  soundFormats('wav');             // set the global sound format as .wav 
  mySound = loadSound('toilet_flushing.wav');  // and load the file
}

function setup() {
  createCanvas(600, 600);          // make the canvas
  serial = new p5.SerialPort();    // make a new instance of the serialport library
  serial.on('data', serialEvent);  // callback for when new data arrives
  serial.on('error', serialError); // callback for errors
  serial.on('list', printList);  // set a callback function for the serialport list
  serial.list(); // list the serial ports
  serial.open(portName);           // open a serial port
  
  mySound.setVolume(0.5);          // set the volume of the sound to 0.5
}

function draw() {
  background(255);
  text("Value:" + fromSerial, 30, 30);   // display the value of fromSerial as texts on the screen
  if (fromSerial == 0 && fromSerial_prev ==1) {  // if the previous value is 0 and current value is 1 (this is step is to play the sound only when the value changes from 1 to 0 so the sound is not triggered repetitively, which will cause a lot of noises
    mySound.play();                              // play the sound
  }
  fromSerial_prev = fromSerial;                  // assign fromSerial to fromSerial_prev
}

function serialEvent() {
	// this is called when data is recieved, data will then live in fromSerial	
	fromSerial = serial.read();
}

function printList(portList) {
 // portList is an array of serial port names
 for (var i = 0; i < portList.length; i++) {
 // Display the list the console:
 console.log(i + " " + portList[i]);
 }
}

function serialError(err) {
  println('Something went wrong with the serial port. ' + err);
}
 
