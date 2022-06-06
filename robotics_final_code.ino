#include <Arduino.h>
#include <NewPing.h>

#define echoPin 4 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 // attach pin D3 Arduino to pin Trig of HC-SR04
#define spoint 103
#define MAX_DISTANCE 200

int m1a = 9;
int m1b = 10;
int m2a = 11;
int m2b = 12;

NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

char command;

void setup()
{
    Serial.begin(9600);
    pinMode(A0, OUTPUT);
    analogWrite(A0, 1023);
    pinMode(A1, OUTPUT);
    analogWrite(A1, 1023);
    pinMode(A2, OUTPUT);
    analogWrite(A2, 1023);
    pinMode(m1a, OUTPUT); // Digital pin 10 set as output Pin
    pinMode(m1b, OUTPUT); // Digital pin 11 set as output Pin
    pinMode(m2a, OUTPUT); // Digital pin 12 set as output Pin
    pinMode(m2b, OUTPUT); // Digital pin 13 set as output Pin
    pinMode(7, OUTPUT);
    digitalWrite(7, HIGH);
    pinMode(6, OUTPUT);
    digitalWrite(6, LOW);
}

void loop()
{
    if (Serial.available() > 0)
    {
        int distance = sonarPing();

        Serial.println(distance);

        command = Serial.read();

        if (distance <= 20)
        {
            command = 'S';
            backward();
        }
        else
        {
            // command = Serial.read();
            stop();
            switch (command)
            {
            case 'F':
                forward();
                break;
            case 'B':
                backward();
                break;
            case 'L':
                leftmove();
                break;
            case 'R':
                rightmove();
                break;
            case 'I':
                forwardRight();
                break;
            case 'J':
                backwardRight();
                break;
            case 'G':
                forwardLeft();
                break;
            case 'H':
                backwardRight();
                break;
            case 'X':
                digitalWrite(7, LOW);
                break;
            case 'x':
                digitalWrite(7, HIGH);
                break;
            case 'W':
                digitalWrite(6, HIGH);
                break;
            case 'w':
                digitalWrite(6, LOW);
                break;
            }
        }
    }
}

int sonarPing()
{
    int distance = sonar.ping_cm();
    if (distance == 0)
    {
        distance = 250;
    }
    return distance;
}

void forward()
{
    Serial.println("FORWARD");
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, HIGH);
    digitalWrite(m2b, LOW);
}

/**
 * @brief Function to move rover in backward direction
 *
 */
void backward()
{
    Serial.println("BACKWARD");
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, HIGH);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, HIGH);
}

/**
 * @brief Function to move rover in right direction
 *
 */
void rightmove()
{
    Serial.println("RIGHT");
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);
}

/**
 * @brief Function to move rover in left direction
 *
 */
void leftmove()
{
    Serial.println("LEFT");
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, HIGH);
    digitalWrite(m2b, LOW);
}

/**
 * @brief Function to moke the robot stop
 *
 */
void stop()
{
    Serial.println("STOP");
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);
}

/**
 * @brief Function to move rover in forward right direction
 *
 */
void forwardRight()
{
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);
}

/**
 * @brief Function to move rover in backward right direction
 *
 */
void backwardRight()
{
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, HIGH);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);
}

/**
 * @brief Function to move rover in forward left direction
 *
 */
void forwardLeft()
{
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, HIGH);
    digitalWrite(m2b, LOW);
}

/**
 * @brief Function to move rover in backward left direction
 *
 */
void backwardLeft()
{
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, HIGH);
}
