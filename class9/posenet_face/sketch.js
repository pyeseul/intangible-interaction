/* 
Intangible Interaction Spring 2020

Mickeymouse Ear Creator: the sketch detects one person's face, find ears, and put mickey mouse ears 

ml5 PoseNet https://ml5js.org/reference/api-PoseNet/

*/

let video;
let leftEarX;
let leftEarY;
let rightEarX;
let rightEarY;


function setup() {
  
  createCanvas(600, 400);
  
  video = createCapture(VIDEO);  
  video.hide();
  
  // Create a new poseNet method and apply to video
  poseNet = ml5.poseNet(video, modelLoaded);
  
  // Listen to new 'pose' events and get the coordinates of left ear and right of a face
  poseNet.on('pose', (poses) => {
    //console.log(poses);
    leftEarX = poses[0].pose.keypoints[3].position.x;
    leftEarY = poses[0].pose.keypoints[3].position.y;
    rightEarX = poses[0].pose.keypoints[4].position.x;
    rightEarY = poses[0].pose.keypoints[4].position.y;
  });
  
}

function draw() {
  
  // display the video
  image(video, 0, 0);
  
  // draw mickeymouse ears (the location and size of the ears might be off depending on how close/far the face is. how would you solve this? 
  fill(0);
  noStroke();
  ellipse(leftEarX, leftEarY-120, 70);
  ellipse(rightEarX, rightEarY-120, 70);  
}

// Print out the message When the model is loaded
function modelLoaded() {
  console.log('model loaded!');
}