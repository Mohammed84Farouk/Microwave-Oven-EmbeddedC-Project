# Microwave-Oven-EmbeddedC-Project
This project simulates the embedded controller in a microwave oven.
The Microwave program works as follow :

If A is pressed, the LCD shows "Popcorn" and the timer counts down 1 minute then clears it when time's up .

If B or C is pressed, the LCD shows "Beef Weight?" or "Chicken Weight?" respectively and upon entering a correct value(1 to 9) from the keypad, the timer will count down the appropiate time needed for each meal. If an incorrect value is entered, the LCD shows "ERR" and gets back to the previous messages.

If D is pressed, the LCD shows "Cooking Time?". The user can enter a time from 1 to 30 minutes and presses SW1 to start counting down or SW2 to clear the LCD.

The microwave can enter a paused state if the user wishes after the countdown starts, pressing SW1 will pause the timer. If SW1 is pressed again, the timer will clear and cooking will stop while if SW2 is pressed , the timer will continue normally.

SW3 emulates the microwave's door and a pressed SW3 correspondes to an open door. The microwave WILL NOT COOK if the door is open. If SW3 is pressed mid countdown, the microwave enters the paused state.

While the Microwave is running, the 3 LEDs will be on and if the microwave stops, they will be off. If it enters the paused state the LEDs will blink and when it finishes cooking, the LEDs will flash 3 times and the buzzer will produce an audible alarm during the 3 second period.

Here is a FSM of the project:
![FSM_Embedded_Project_-_Copy](https://user-images.githubusercontent.com/105364907/170357842-1f581765-b571-48cb-a494-724ea441c49a.png)
