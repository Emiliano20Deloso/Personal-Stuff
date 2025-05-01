/*
Emiliano Delgadillo 
30/04/2025
Breakout game 
*/

"use strict";
const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');

// Paddle
const paddleWidth = 100;
const paddleHeight = 20;
let paddleX = (canvas.width - paddleWidth) / 2;
const paddleSpeed = 7;

// Bola
const ballRadius = 10;
let ballX = canvas.width / 2;
let ballY = canvas.height - 30;
let ballDX = 3;
let ballDY = -3;

// Ladrillos
const brickRowCount = 5;
const brickColumnCount = 9;
const brickWidth = 75;
const brickHeight = 20;
const brickPadding = 10;
const brickOffsetTop = 30;
const brickOffsetLeft = 30;
const bricks = [];
for (let c = 0; c < brickColumnCount; c++) {
  bricks[c] = [];
  for (let r = 0; r < brickRowCount; r++) {
    bricks[c][r] = { x: 0, y: 0, status: 1 };
  }
}

// Vidas y contador de golpes
let lives = 3;
let hitCount = 1;

let gameStarted = false;
let canCountHit = true;

let leftPressed = false;
let rightPressed = false;
document.addEventListener('keydown', keyDownHandler);
document.addEventListener('keyup', keyUpHandler);

function keyDownHandler(e) {
  if (e.key === 'a' || e.key === 'A')      leftPressed = true;
  if (e.key === 'l' || e.key === 'L')      rightPressed = true;
  if (e.code === 'Space')                  gameStarted = true;
}

function keyUpHandler(e) {
  if (e.key === 'a' || e.key === 'A')      leftPressed = false;
  if (e.key === 'l' || e.key === 'L')      rightPressed = false;
}

// Colisiones con ladrillos
function collisionDetection() {
  for (let c = 0; c < brickColumnCount; c++) {
    for (let r = 0; r < brickRowCount; r++) {
      const b = bricks[c][r];
      if (b.status === 1 &&
          ballX > b.x &&
          ballX < b.x + brickWidth &&
          ballY > b.y &&
          ballY < b.y + brickHeight) {
        ballDY = -ballDY;
        b.status = 0;
      }
    }
  }
}

function drawBricks() {
  for (let c = 0; c < brickColumnCount; c++) {
    for (let r = 0; r < brickRowCount; r++) {
      if (bricks[c][r].status === 1) {
        const brickX = c * (brickWidth + brickPadding) + brickOffsetLeft;
        const brickY = r * (brickHeight + brickPadding) + brickOffsetTop;
        bricks[c][r].x = brickX;
        bricks[c][r].y = brickY;
        ctx.beginPath();
        ctx.rect(brickX, brickY, brickWidth, brickHeight);
        ctx.fillStyle = '#f90';
        ctx.fill();
        ctx.closePath();
      }
    }
  }
}

function drawBall() {
  ctx.beginPath();
  ctx.arc(ballX, ballY, ballRadius, 0, Math.PI * 2);
  ctx.fillStyle = '#fff';
  ctx.fill();
  ctx.closePath();
}

function drawPaddle() {
  ctx.beginPath();
  ctx.rect(paddleX, canvas.height - paddleHeight - 10, paddleWidth, paddleHeight);
  ctx.fillStyle = '#0ff';
  ctx.fill();
  ctx.closePath();
}

function drawHUD() {
  ctx.font = "16px Arial";
  ctx.fillStyle = "#fff";
  ctx.fillText("Vidas: " + lives, canvas.width - 100, 20);
  ctx.fillText("Golpes: " + hitCount, 20, 20);
}

function drawStartMessage() {
  ctx.font = "24px Arial";
  ctx.fillStyle = "#fff";
  ctx.textAlign = "center";
  ctx.fillText("Presiona ESPACIO para empezar", canvas.width / 2, canvas.height / 2);
}

function draw() {
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  drawBricks();
  drawBall();
  drawPaddle();
  drawHUD();

  if (!gameStarted) {
    drawStartMessage();
    requestAnimationFrame(draw);
    return;
  }

  collisionDetection();

  if (ballX + ballDX > canvas.width - ballRadius || ballX + ballDX < ballRadius) {
    ballDX = -ballDX;
  }
  if (ballY + ballDY < ballRadius) {
    ballDY = -ballDY;
  } 

  else if (ballY + ballDY > canvas.height - ballRadius - paddleHeight - 10) {
    if (ballDY > 0 && ballX > paddleX && ballX < paddleX + paddleWidth) {
      if (canCountHit) {
        hitCount++;
        canCountHit = false;
      }
      ballDY = -ballDY;
    } 

    else if (ballY + ballDY > canvas.height - ballRadius) {
      lives--;
      if (lives === 0) {
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        ctx.font = "48px Arial";
        ctx.fillStyle = "#f00";
        ctx.textAlign = "center";
        ctx.fillText("GAME OVER", canvas.width / 2, canvas.height / 2);
        return;
      }

      ballX = canvas.width / 2;
      ballY = canvas.height - 30;
      ballDX = 3;
      ballDY = -3;
      paddleX = (canvas.width - paddleWidth) / 2;
      canCountHit = true;
      gameStarted = false; // volver a esperar espacio
    }
  }

  // Reset cuando sube fuera de zona paddle
  if (ballDY < 0) canCountHit = true;

  ballX += ballDX;
  ballY += ballDY;
  if (leftPressed && paddleX > 0) paddleX -= paddleSpeed;
  if (rightPressed && paddleX < canvas.width - paddleWidth) 
    paddleX += paddleSpeed;

  requestAnimationFrame(draw);
}

draw();

