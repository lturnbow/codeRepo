`timescale 1ns / 1ps
/***********************************************************************************************************************************************************
Lauren Turnbow
ECE260 Final Project
***********************************************************************************************************************************************************/
module Project(input logic CLK100MHZ, input logic [3:1]JA, input logic BTNR, output logic LED[15:0], output logic CA,CB,CC,CD,CE,CF,CG, output logic [7:0]AN,
    output logic VGA_HS, VGA_VS, [3:0]VGA_R, [3:0]VGA_G, [3:0]VGA_B);
    logic data;                                       // Data and clock lines to take in from the PS/2 port
    logic clock;
    logic prevClock, prev2Clock, prev3Clock;          // Variables ot save the previous clock values
    logic [3:0] deathCounter = 3;
    logic [9:0] inputData = 8'b00000000;              // 10 bit input of the data from the PS/2 port
    assign data = JA[1];                              // Assigning the ports to the data and clock that the Pmod is plugged into
    assign clock = JA[3];
    logic [1:0] counter2 = 0;
    logic [15:0] counter = 0; 
    logic [6:0] counter3 = 0;
    logic [6:0] INPUTDATACOUNTER = 0;                 // Counter to know when all of the data, 11 bits, has been input
    logic [3:0] switches;                             // Variable to pass to the module to display the characters on the hex display
    logic [7:0] prevInputData = 8'b00000000;          // Previous data to be saved
    digit mod(switches, CA, CB, CC, CD, CE, CF, CG);

    always_ff @(posedge CLK100MHZ) begin
        counter <= counter + 1;
        if (counter == 500) begin           
            counter2 <= counter2 + 1;       // Counter for the hex display
            counter <= 0;
        end
    end
    
    always_ff @(posedge CLK100MHZ) begin
        counter3 <= counter3 + 1;
        if (counter3 == 50) begin                                                                                                    
            if (prevClock == 1 && prev2Clock == 1 && prev3Clock == 1 && clock == 0)    // If clock and data lines are high 
                inputData <= {data, inputData[9:1]};                                   // Take in data on data line
            else
                prev3Clock <= prev2Clock; prev2Clock <= prevClock; prevClock <= clock;     // Updating the previous values of the clock
            if (INPUTDATACOUNTER == 10) INPUTDATACOUNTER <= 0;                         // If all of the bits have been read in, reset the counter
            INPUTDATACOUNTER <= INPUTDATACOUNTER + 1;
        end
    end
    
    /************************************************************VGA Code***********************************************************************/
    logic [2:0] Counter = 0;
    logic [11:0] RGB;              
    logic [10:0] HSCOUNTER = 0; logic [10:0] VSCOUNTER = 0;
    logic [6:0] PREVKEYCOUNTER = 0;
    int signed PaddleCounter = 0; int signed BallCounter = -1;
    logic [10:0] topOfPaddle = 460;
    logic [10:0] currentPaddleLeft = 0; logic [10:0] currentPaddleRight = 0;
    logic flag;
    logic RRFlag = 0; logic RFlag = 0; logic LFlag = 0; logic LLFlag = 0;logic SFlag = 0;           // Flags to designate where the ball impacts the paddle
    logic WRFlag = 0; logic WSFlag = 0; logic WLFlag = 0;                                           // Flags to designate from what direction the ball hits the wall
    logic brickFlag1 = 0; logic brickFlag2 = 0; logic brickFlag3 = 0; logic brickFlag4 = 0; logic brickFlag5 = 0; logic brickFlag6 = 0;      // Flags for the bricks
    logic brickFlag7 = 0; logic brickFlag8 = 0; logic brickFlag9 = 0; logic brickFlag10 = 0; logic brickFlag11 = 0; logic brickFlag12 = 0;
    logic brickFlag13 = 0; logic brickFlag14 = 0; logic brickFlag15 = 0; logic brickFlag16 = 0; logic brickFlag17 = 0; logic brickFlag18 = 0;
    logic brickFlag19 = 0; logic brickFlag20 = 0; logic brickFlag21 = 0; logic brickFlag22 = 0; logic brickFlag23 = 0; logic brickFlag24 = 0;
    logic leftBrickFlag = 0; logic rightBrickFlag = 0; logic straightBrickFlag = 0;    // Flags to designate which way the ball bounces off the wall or a brick
    logic vNhN = 0; logic vNhP = 0; logic vPhN = 0; logic vPhP = 0;                    // Variables to save previous direction of the ball
    int signed vscounter;                                                              // Counters to move the ball
    int signed hscounter;
    logic [10:0] CP1; logic [10:0] CP2; logic [10:0] CP3; logic [10:0] CP4;
    assign {VGA_R, VGA_G, VGA_B} = RGB;
    always_ff @(posedge CLK100MHZ) begin     //Pixel Clock of 25MHZ
        Counter <= Counter + 1;
        if (Counter == 3) begin
            // DISPLAY TIME 
            if (deathCounter != 0) begin
                if (HSCOUNTER >= 0 && HSCOUNTER < 640 && VSCOUNTER < 480) begin
                    VGA_HS <= 0;                 // Turning off syncs
                    VGA_VS <= 0;
                    if(brickFlag1 == 1 && brickFlag2 == 1 && brickFlag3 == 1 && brickFlag4 == 1 && brickFlag5 == 1 && brickFlag6 == 1 && brickFlag7 == 1 && brickFlag8 == 1) begin
                        RGB <= 12'b100000001000;      // If all of the bricks have been hit, make the whole screen pink, indicating a win
                    end  
                    else RGB <= 12'b0000000000000;    // Making the background black, otherwise to place bricks, paddle, and ball on top of
                    
                    if (HSCOUNTER >= 280 + PaddleCounter && HSCOUNTER <= 360 + PaddleCounter && VSCOUNTER >= 440 && VSCOUNTER < 460 && 
                        (brickFlag1 == 0 || brickFlag2 == 0 || brickFlag3 == 0 || brickFlag4 == 0 || brickFlag5 == 0 || brickFlag6 == 0 || brickFlag7 == 0 || brickFlag8 == 0)) begin     // PLACING PADDLE
                        RGB <= 12'b111111111111;                     // Only place the paddle if there are still bricks to be hit
                        currentPaddleLeft <= 280 + PaddleCounter;     // Updating the paddle position after it moves
                        currentPaddleRight <= 360 + PaddleCounter;
                    end
               if (brickFlag1 == 0 || brickFlag2 == 0 || brickFlag3 == 0 || brickFlag4 == 0 || brickFlag5 == 0 || brickFlag6 == 0 || brickFlag7 == 0 || brickFlag8 == 0) begin   
                    if (HSCOUNTER >= 6 && HSCOUNTER < 79 && VSCOUNTER >= 7 && VSCOUNTER < 27) begin          // PLACING BRICK1    red
                        if (brickFlag1 == 0) RGB <= 12'b100000000000; else RGB <= 12'b000000000000; end      // If flag is 0, it hasn't been hit, place brick. If flag is 1 it has been hit, don't place
                    
                    if (HSCOUNTER >= 86 && HSCOUNTER < 158 && VSCOUNTER >= 7 && VSCOUNTER < 27) begin        // PLACING BRICK2  pink
                        if (brickFlag2 == 0) RGB <= 12'b100000001000; else RGB <= 12'b000000000000; end
                    
                    if (HSCOUNTER >= 165 && HSCOUNTER < 237 && VSCOUNTER >= 7 && VSCOUNTER < 27) begin       // PLACING BRICK3  orange
                        if (brickFlag3 == 0) RGB <= 12'b110000010000; else RGB <= 12'b000000000000; end
                    
                    if (HSCOUNTER >= 244 && HSCOUNTER < 316 && VSCOUNTER >= 7 && VSCOUNTER < 27) begin       // PLACING BRICK4 yellow
                        if (brickFlag4 == 0) RGB <= 12'b110010000000; else RGB <= 12'b000000000000; end
                    
                    if (HSCOUNTER >= 323 && HSCOUNTER < 395 && VSCOUNTER >= 7 && VSCOUNTER < 27) begin       // PLACING BRICK5 green
                        if (brickFlag5 == 0) RGB <= 12'b000010000000; else RGB <= 12'b000000000000; end
                    
                    if (HSCOUNTER >= 402 && HSCOUNTER < 474 && VSCOUNTER >= 7 && VSCOUNTER < 27) begin       // PLACING BRICK6 blue
                        if (brickFlag6 == 0) RGB <= 12'b000000001000; else RGB <= 12'b000000000000; end
 
                    if (HSCOUNTER >= 481 && HSCOUNTER < 553 && VSCOUNTER >= 7 && VSCOUNTER < 27) begin       // PLACING BRICK7 purple
                        if (brickFlag7 == 0) RGB <= 12'b001100000011; else RGB <= 12'b000000000000; end
                        
                    if (HSCOUNTER >= 560 && HSCOUNTER < 632 && VSCOUNTER >= 7 && VSCOUNTER < 27) begin       // PLACING BRICK8  red
                        if (brickFlag8 == 0) RGB <= 12'b100000000000; else RGB <= 12'b000000000000; end
                    
                    if (HSCOUNTER >= 6 && HSCOUNTER < 79 && VSCOUNTER >= 34 && VSCOUNTER < 54) begin         // PLACING BRICK9 pink
                        if (brickFlag9 == 0) RGB <= 12'b100000001000; else RGB <= 12'b000000000000; end
                    
                    if (HSCOUNTER >= 86 && HSCOUNTER < 158 && VSCOUNTER >= 34 && VSCOUNTER < 54) begin       // PLACING BRICK10 orange
                        if (brickFlag10 == 0) RGB <= 12'b110000010000; else RGB <= 12'b000000000000; end
                    
                    if (HSCOUNTER >= 165 && HSCOUNTER < 237 && VSCOUNTER >= 34 && VSCOUNTER < 54) begin      // PLACING BRICK11 yellow
                        if (brickFlag11 == 0) RGB <= 12'b110010000000; else RGB <= 12'b000000000000; end
                    
                    if (HSCOUNTER >= 244 && HSCOUNTER < 316 && VSCOUNTER >= 34 && VSCOUNTER < 54) begin      // PLACING BRICK12 green
                        if (brickFlag12 == 0) RGB <= 12'b000010000000; else RGB <= 12'b000000000000; end
                        
                    if (HSCOUNTER >= 323 && HSCOUNTER < 395 && VSCOUNTER >= 34 && VSCOUNTER < 54) begin      // PLACING BRICK13 blue
                        if (brickFlag13 == 0) RGB <= 12'b000000001000; else RGB <= 12'b000000000000; end
                    
                    if (HSCOUNTER >= 402 && HSCOUNTER < 474 && VSCOUNTER >= 34 && VSCOUNTER < 54) begin      // PLACING BRICK14 purple
                        if (brickFlag14 == 0) RGB <= 12'b001100000011; else RGB <= 12'b000000000000; end
                    
                    if (HSCOUNTER >= 481 && HSCOUNTER < 553 && VSCOUNTER >= 34 && VSCOUNTER < 54) begin      // PLACING BRICK15 red
                        if (brickFlag15 == 0) RGB <= 12'b100000000000; else RGB <= 12'b000000000000; end
                    
                    if (HSCOUNTER >= 560 && HSCOUNTER < 632 && VSCOUNTER >= 34 && VSCOUNTER < 54) begin      // PLACING BRICK16 pink
                        if (brickFlag16 == 0) RGB <= 12'b100000001000; else RGB <= 12'b000000000000; end
                    
                    if (HSCOUNTER >= 6 && HSCOUNTER < 79 && VSCOUNTER >= 61 && VSCOUNTER < 81) begin         // PLACING BRICK17 orange
                        if (brickFlag17 == 0) RGB <= 12'b110000010000; else RGB <= 12'b000000000000; end
                    
                    if (HSCOUNTER >= 86 && HSCOUNTER < 158 && VSCOUNTER >= 61 && VSCOUNTER < 81) begin       // PLACING BRICK18 yellow
                        if (brickFlag18 == 0) RGB <= 12'b110010000000; else RGB <= 12'b000000000000; end
                        
                    if (HSCOUNTER >= 165 && HSCOUNTER < 237 && VSCOUNTER >= 61 && VSCOUNTER < 81) begin      // PLACING BRICK19 green
                        if (brickFlag19 == 0) RGB <= 12'b000010000000; else RGB <= 12'b000000000000; end
                    
                    if (HSCOUNTER >= 244 && HSCOUNTER < 316 && VSCOUNTER >= 61 && VSCOUNTER < 81) begin      // PLACING BRICK20 blue
                        if (brickFlag20 == 0) RGB <= 12'b000000001000; else RGB <= 12'b000000000000; end
                    
                    if (HSCOUNTER >= 323 && HSCOUNTER < 395 && VSCOUNTER >= 61 && VSCOUNTER < 81) begin      // PLACING BRICK21 purple
                        if (brickFlag21 == 0) RGB <= 12'b001100000011; else RGB <= 12'b000000000000; end
                    
                    if (HSCOUNTER >= 402 && HSCOUNTER < 474 && VSCOUNTER >= 61 && VSCOUNTER < 81) begin      // PLACING BRICK22 red
                        if (brickFlag22 == 0) RGB <= 12'b100000000000; else RGB <= 12'b000000000000; end
                    
                    if (HSCOUNTER >= 481 && HSCOUNTER < 553 && VSCOUNTER >= 61 && VSCOUNTER < 81) begin      // PLACING BRICK23 pink
                        if (brickFlag23 == 0) RGB <= 12'b100000001000; else RGB <= 12'b000000000000; end
                    
                    if (HSCOUNTER >= 560 && HSCOUNTER < 632 && VSCOUNTER >= 61 && VSCOUNTER < 81) begin      // PLACING BRICK24 orange
                        if (brickFlag24 == 0) RGB <= 12'b110000010000; else RGB <= 12'b000000000000; end
               end
               
               if (HSCOUNTER >= 310 + hscounter && HSCOUNTER < 330 + hscounter && VSCOUNTER >= 415 + vscounter && VSCOUNTER < 435 + vscounter &&
                  (brickFlag1 == 0 || brickFlag2 == 0 || brickFlag3 == 0 || brickFlag4 == 0 || brickFlag5 == 0 || brickFlag6 == 0 || brickFlag7 == 0 || brickFlag8 == 0)) begin      // Ball
                   // Bricks are labeled 1 - 24 left to right, top to bottom. When hitting the bricks check if the ball is within the range of the brick,
                   // and if the bricks below that brick, if any, have been hit
                   if (VSCOUNTER == 27 && HSCOUNTER >= 6 && HSCOUNTER <= 79 && brickFlag1 == 0 && brickFlag9 == 1 && brickFlag17 == 1) begin                  // Hitting brick1
                       RGB <= 12'b111111111111; flag <= 1; brickFlag1 <= 1;                                            // Set the flag for this brick to 1, meaning it's hit                                            
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end       // If the brick is hit at a 90 degree angle
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end   // If the brick is hit from the left, go right after impact
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end   // If the brick is hit from the right, go left after impact
                   end
                          
                   else if (VSCOUNTER == 27 && HSCOUNTER >= 86 && HSCOUNTER <= 158 && brickFlag2 == 0 && brickFlag10 == 1 && brickFlag18 == 1) begin          // Hitting brick2
                       RGB <= 12'b111111111111; flag <= 1; brickFlag2 <= 1;
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end
                          
                   else if (VSCOUNTER == 27 && HSCOUNTER >= 165 && HSCOUNTER <= 237 && brickFlag3 == 0 && brickFlag11 == 1 && brickFlag19 == 1) begin        // Hitting brick3
                        RGB <= 12'b111111111111; flag <= 1; brickFlag3 <= 1;
                        if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                        else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                        else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end
                          
                   else if (VSCOUNTER == 27 && HSCOUNTER >= 244 && HSCOUNTER <= 316 && brickFlag4 == 0 && brickFlag12 == 1 && brickFlag20 == 1) begin        // Hitting brick4
                       RGB <= 12'b111111111111; flag <= 1; brickFlag4 <= 1;
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end
                          
                   else if (VSCOUNTER == 27 && HSCOUNTER >= 323 && HSCOUNTER <= 395 && brickFlag5 == 0 && brickFlag13 == 1 && brickFlag21 == 1) begin        // Hitting brick5
                       RGB <= 12'b111111111111; flag <= 1; brickFlag5 <= 1;
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end
                          
                   else if (VSCOUNTER == 27 && HSCOUNTER >= 402 && HSCOUNTER <= 474 && brickFlag6 == 0 && brickFlag14 == 1 && brickFlag22 == 1) begin       // Hitting brick6
                       RGB <= 12'b111111111111; flag <= 1; brickFlag6 <= 1;
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end
                  
                   else if (VSCOUNTER == 27 && HSCOUNTER >= 481 && HSCOUNTER <= 553 && brickFlag7 == 0 && brickFlag15 == 1 && brickFlag23 == 1) begin      // Hitting brick7
                       RGB <= 12'b111111111111; flag <= 1; brickFlag7 <= 1;
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end  
                  
                   else if (VSCOUNTER == 27 && HSCOUNTER >= 560 && HSCOUNTER <= 632 && brickFlag8 == 0 && brickFlag16 == 1 && brickFlag24 == 1) begin      // Hitting brick8
                       RGB <= 12'b111111111111; flag <= 1; brickFlag8 <= 1;
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end  
                  
                   else if (VSCOUNTER == 54 && HSCOUNTER >= 6 && HSCOUNTER <= 79 && brickFlag9 == 0 && brickFlag17 == 1) begin                             // Hitting brick9
                       RGB <= 12'b111111111111; flag <= 1; brickFlag9 <= 1;
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end  
                  
                   else if (VSCOUNTER == 54 && HSCOUNTER >= 86 && HSCOUNTER <= 158 && brickFlag10 == 0 && brickFlag18 == 1) begin                         // Hitting brick10
                       RGB <= 12'b111111111111; flag <= 1; brickFlag10 <= 1;
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end  
                  
                   else if (VSCOUNTER == 54 && HSCOUNTER >= 165 && HSCOUNTER <= 237 && brickFlag11 == 0 && brickFlag19 == 1) begin                        // Hitting brick11
                       RGB <= 12'b111111111111; flag <= 1; brickFlag11 <= 1; 
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end  
                  
                   else if (VSCOUNTER == 54 && HSCOUNTER >= 244 && HSCOUNTER <= 316 && brickFlag12 == 0 && brickFlag20 == 1) begin                        // Hitting brick12
                       RGB <= 12'b111111111111; flag <= 1; brickFlag12 <= 1;
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end  
                   
                   else if (VSCOUNTER == 54 && HSCOUNTER >= 323 && HSCOUNTER <= 395 && brickFlag13 == 0 && brickFlag21 == 1) begin                        // Hitting brick13
                       RGB <= 12'b111111111111; flag <= 1; brickFlag13 <= 1;
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end  
                          
                   else if (VSCOUNTER == 54 && HSCOUNTER >= 402 && HSCOUNTER <= 475 && brickFlag14 == 0 && brickFlag22 == 1) begin                        // Hitting brick14
                       RGB <= 12'b111111111111; flag <= 1; brickFlag14 <= 1;
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1;end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end  
                  
                   else if (VSCOUNTER == 54 && HSCOUNTER >= 481 && HSCOUNTER <= 553 && brickFlag15 == 0 && brickFlag23 == 1) begin                        // Hitting brick15
                       RGB <= 12'b111111111111; flag <= 1; brickFlag15 <= 1;
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0;straightBrickFlag <= 1; end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end  
                  
                   else if (VSCOUNTER == 54 && HSCOUNTER >= 560 && HSCOUNTER <= 632 && brickFlag16 == 0 && brickFlag24 == 1) begin                        // Hitting brick16
                       RGB <= 12'b111111111111; flag <= 1; brickFlag16 <= 1;
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end                            
                  
                   else if (VSCOUNTER == 81 && HSCOUNTER >= 6 && HSCOUNTER <= 79 && brickFlag17 == 0) begin                                               // Hitting brick17
                       RGB <= 12'b111111111111; flag <= 1; brickFlag17 <= 1;
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end  
                          
                   else if (VSCOUNTER == 81 && HSCOUNTER >= 86 && HSCOUNTER <= 158 && brickFlag18 == 0) begin                                            // Hitting brick18
                       RGB <= 12'b111111111111; flag <= 1; brickFlag18 <= 1;
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0;  straightBrickFlag <= 1;end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end  
                  
                   else if (VSCOUNTER == 81 && HSCOUNTER >= 165 && HSCOUNTER <= 237 && brickFlag19 == 0) begin                                          // Hitting brick19
                       RGB <= 12'b111111111111; flag <= 1; brickFlag19 <= 1;
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end  
                  
                   else if (VSCOUNTER == 81 && HSCOUNTER >= 244 && HSCOUNTER <= 316 && brickFlag20 == 0) begin                                          // Hitting brick20
                       RGB <= 12'b111111111111; flag <= 1; brickFlag20 <= 1; 
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end  
                  
                   else if (VSCOUNTER == 81 && HSCOUNTER >= 323 && HSCOUNTER <= 395 && brickFlag21 == 0) begin                                         // Hitting brick21
                       RGB <= 12'b111111111111; flag <= 1; brickFlag21 <= 1;
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end  
                  
                  else if (VSCOUNTER == 81 && HSCOUNTER >= 402 && HSCOUNTER <= 474 && brickFlag22 == 0) begin                                         // Hitting brick22
                      RGB <= 12'b111111111111; flag <= 1; brickFlag22 <= 1;
                      if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                      else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                      else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                  end  
                                                 
                   else if (VSCOUNTER == 81 && HSCOUNTER >= 481 && HSCOUNTER <= 553 && brickFlag23 == 0) begin                                       // Hitting brick23
                       RGB <= 12'b111111111111; flag <= 1; brickFlag23 <= 1;
                       if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                       else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                       else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                   end  
                   
                  else if (VSCOUNTER == 81 && HSCOUNTER >= 560 && HSCOUNTER <= 632 && brickFlag24 == 0) begin                                        // Hitting brick24
                      RGB <= 12'b111111111111; flag <= 1; brickFlag24 <= 1;
                      if (SFlag == 1) begin rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 1; end
                      else if (vNhP == 1) begin rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; end
                      else if (vNhN == 1) begin leftBrickFlag <= 1; rightBrickFlag <= 0; straightBrickFlag <= 0; end
                  end    
                          
                  else if (415 + vscounter == 0) begin                // If the ball hits the top of the screen
                        if (SFlag == 1) begin                         // If the ball hits the top of the screen at a 90 degree angle
                            straightBrickFlag <= 1;                    // Bounce back at a 90 degree angle
                        end
                        else if (vNhP == 1) begin                                           // If the top of the screen is hit from the left, go right after impact
                            straightBrickFlag <= 0; rightBrickFlag <= 1; leftBrickFlag <= 0;
                        end
                        
                        else if (vNhN == 1) begin
                            straightBrickFlag <= 0; rightBrickFlag <= 0; leftBrickFlag <= 1;   // If the top of the screen is hit from the right, go left after impact
                        end
                        flag = 1;
                  end                 
                          
                  else if (hscounter + 310 == 625) begin           // If the right side of the screen has been hit
                       if (vPhP == 1) begin                        // If the screen has been hit from the top right
                         WRFlag <= 0; WSFlag <= 0; WLFlag <= 0; rightBrickFlag <= 0; leftBrickFlag <= 1; straightBrickFlag <= 0;
                         flag <= 1;                                 // Go left
                       end 
                        
                       else begin                                  // Otherwise go right
                        WRFlag <= 0; WSFlag <= 0; WLFlag <= 0; rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; RFlag <= 1;
                        flag <= 0;
                       end
                  end
     
                  else if (hscounter + 310 == 1) begin        // If the left side of the screen has been hit
                     if (vPhN == 1) begin                     // If the screen has been hit from the top left
                        WRFlag <= 0; WSFlag <= 0; WLFlag <= 0; rightBrickFlag <= 1; leftBrickFlag <= 0; straightBrickFlag <= 0; RFlag <= 0;
                        flag <= 1;                             // Go right
                     end
                     
                     else begin                               // Otherwise go left
                        WRFlag <= 1; WSFlag <= 0; WLFlag <= 0; rightBrickFlag <= 0; leftBrickFlag <= 0; straightBrickFlag <= 0; LFlag <= 0;
                        flag <= 1;
                     end
                  end

                  else if (VSCOUNTER == topOfPaddle - 20 && (310 + hscounter) >= currentPaddleLeft - 29 && (330 + hscounter) < currentPaddleRight + 29) begin  // Hitting the paddle
                      CP1 = 30 + currentPaddleLeft;  // Splitting the paddle up into parts to designate the angle that the ball will bounce off of.
                      CP2 = 50 + currentPaddleLeft;  
                      if ((310 + hscounter) >= currentPaddleLeft - 29 && (310 + hscounter) < CP1) begin 
                            RRFlag <= 0; RFlag <= 1; LFlag <= 0; LLFlag <= 0; SFlag <= 0;
                      end
                      
                      else if ((320 + hscounter) >= CP1 && (320 + hscounter) < CP2) begin
                             RRFlag <= 0; RFlag <= 0; LFlag <= 0; LLFlag <= 0; SFlag <= 1;
                      end
                      
                      else if ((330 + hscounter) >= CP2 && (330 + hscounter) <= currentPaddleRight + 29) begin
                             RRFlag <= 0; RFlag <= 0; LFlag <= 1; LLFlag <= 0; SFlag <= 0;
                      end
                      
                      else begin
                           RRFlag <= 0; RFlag <= 0; LFlag <= 0; LLFlag <= 0; SFlag <= 0;
                      end
                      
                      RGB <= 12'b111111111111;
                      flag <= 0;
                  end

                 else if (vscounter + 415 == 479) begin          //If the player dies, goes off the bottom of the screen
                       flag <= 0;
                       vscounter <= 0;                           // Resetting the counters to reset the ball
                       hscounter <= 0;
                       RFlag <= 0; RRFlag <= 0; SFlag <= 1; LFlag <= 0; LLFlag <= 0;  // Go straight up
                       deathCounter <= deathCounter - 4'b0001;                    // Decrease the number of lives
                  end

                  else if (flag == 1) begin
                      RGB <= 12'b111111111111;
                      flag <= 1;
                  end
                 
                  else begin
                      RGB <= 12'b111111111111;
                      flag <= 0;
                  end
              end
     
              HSCOUNTER <= HSCOUNTER + 1;     // Incrementing horizontal Counter
          end
    
                // HORIZONTAL FRONT PORCH
          else if (HSCOUNTER >= 640 && HSCOUNTER < 656 && VSCOUNTER < 480) begin
              VGA_HS <= 0;                 // Turning off syncs
              VGA_VS <= 0;
              RGB <= 12'b000000000000;     // Turning off colors
              HSCOUNTER <= HSCOUNTER + 1;
          end

          // HORIZONTAL PULSE WIDTH
          else if (HSCOUNTER >= 656 && HSCOUNTER < 752 && VSCOUNTER < 480) begin
              VGA_HS <= 1;                    // Turning HS on during pulse width
              VGA_VS <= 0;
              RGB <= 12'b000000000000;
              HSCOUNTER <= HSCOUNTER + 1;
          end

          // HORIZONTAL BACK PORCH
          else if (HSCOUNTER >= 752 && HSCOUNTER <= 799 && VSCOUNTER < 480) begin
              VGA_HS <= 0;                 // Turning off syncs
              VGA_VS <= 0;
              RGB <= 12'b000000000000;
              HSCOUNTER <= HSCOUNTER + 1;
              if (HSCOUNTER == 799) begin  // Reset the HS if it has reached the end of the back porch
                  HSCOUNTER <= 0;
                  VSCOUNTER <= VSCOUNTER + 1;   // Incrementing VS by one after a line has finished
              end
          end
    
          // VERTICAL FRONT PORCH OR BACK PORCH
          else if ((VSCOUNTER >= 480 && VSCOUNTER < 490) || (VSCOUNTER >= 492 && VSCOUNTER <= 520)) begin
              VGA_VS <= 0;
              RGB <= 12'b000000000000;
              if (HSCOUNTER >= 0 && HSCOUNTER < 640) begin         // DISPLAY
                  VGA_HS <= 0;
                  HSCOUNTER <= HSCOUNTER + 1;
              end
              else if (HSCOUNTER >= 640 && HSCOUNTER < 656) begin  // HS FRONT PORCH
                 VGA_HS <= 0;
                 HSCOUNTER <= HSCOUNTER + 1;
              end
              else if (HSCOUNTER >= 656 && HSCOUNTER < 752) begin  // HS PULSE WIDTH
                  VGA_HS <= 1;
                  HSCOUNTER <= HSCOUNTER + 1;
              end
              else if (HSCOUNTER >= 752 && HSCOUNTER <= 799) begin // HS BACKPORCH
                  VGA_HS <= 0;
                  HSCOUNTER <= HSCOUNTER + 1;
                  if (HSCOUNTER == 799) begin       // Resetting HS after line has been reached
                      VSCOUNTER <= VSCOUNTER + 1;   // Incrementing VS Counter
                      HSCOUNTER <= 0;
                  end
              end
          end
    
          // VERTICAL PULSE WIDTH
          else if (VSCOUNTER >= 490 && VSCOUNTER < 492) begin
              VGA_VS <= 1;
              RGB <= 12'b000000000000;
              if (HSCOUNTER >= 0 && HSCOUNTER < 640) begin        // DISPLAY
                  VGA_HS <= 0;
                  HSCOUNTER <= HSCOUNTER + 1;
              end
              else if (HSCOUNTER >= 640 && HSCOUNTER < 656) begin // HS FRONT PORCH
                 VGA_HS <= 0;
                 HSCOUNTER <= HSCOUNTER + 1;
              end
              else if (HSCOUNTER >= 656 && HSCOUNTER < 752) begin // HS PULSE WIDTH
                  VGA_HS <= 1;
                  HSCOUNTER <= HSCOUNTER + 1;
              end
              else if (HSCOUNTER >= 752 && HSCOUNTER <= 799) begin // HS BACK PORCH
                  VGA_HS <= 0;
                  HSCOUNTER <= HSCOUNTER + 1;
                  if (HSCOUNTER == 799) begin      // Resetting HS Counter after line has been reached
                      VSCOUNTER <= VSCOUNTER + 1;  // Incrementing VS Counter
                      HSCOUNTER <= 0;
                  end
              end
          end
                
          if (VSCOUNTER == 520) begin
              VSCOUNTER <= 0;
              if (inputData[7:0] != prevInputData) begin                       // If the current input data is different than the previous data
                  if (inputData[3:0] == 4'b1011 && inputData[7:4] == 4'b0110)  // If the left key is pressed
                      PaddleCounter <= PaddleCounter - 30;                      // Move the paddle left by 30 pixels
                  if (280 + PaddleCounter == 0)                                // If the paddle is at the right side of the screen
                      PaddleCounter <= -280;                                    // Reset the counter to stop
                  if (inputData[3:0] == 4'b0100 && inputData[7:4] == 4'b0111)  // If the right key is pressed
                      PaddleCounter <= PaddleCounter + 30;                      // Move the paddle right by 30 pixels
                  if (360 + PaddleCounter == 640)                              // If the paddle is at the left side of the screen
                      PaddleCounter <= 279;                                     // Reset the paddle counter to stop
              end
              prevInputData <= inputData[7:0];
               
              if (flag == 1) begin
                  if (straightBrickFlag == 1) begin               // Different flags to go different ways after bouncing off of the top, left, right of the screen and the paddle
                      vscounter <= vscounter + 1;                 // Increasing the vscounter makes the ball go down
                      vNhN <= 0; vNhP <= 0; vPhN <= 0; vPhP <= 0;     // Saving the previous direction the ball is going
                  end

                  else if (rightBrickFlag == 1) begin
                      vscounter <= vscounter + 1;
                      hscounter <= hscounter + 1;                 // Increasing the hscounter makes the ball go right
                      vNhN <= 0; vNhP <= 0; vPhN <= 0; vPhP <= 1;
                  end
                
                  else if (leftBrickFlag == 1) begin
                      vscounter <= vscounter + 1;
                      hscounter <= hscounter - 1;                 // Decreasing the hscounter makes the ball go left
                      vNhN <= 0; vNhP <= 0; vPhN <= 1; vPhP <= 0;                        
                  end
                
                  else if (WRFlag == 1) begin
                      vscounter <= vscounter - 1;
                      hscounter <= hscounter + 1;
                      vNhN = 0; vNhP = 1; vPhN = 0; vPhP = 0;
                  end
                
                  else if (WSFlag == 1) begin
                      vscounter <= vscounter + 1;
                      vNhN <= 0; vNhP <= 0; vPhN <= 0; vPhP <= 0;
                  end
                  
                  else if (WLFlag == 1) begin
                      vscounter <= vscounter - 1;
                      hscounter <= hscounter + 1;
                      vNhN <= 0; vNhP <= 1; vPhN <= 0; vPhP <= 0;
                  end

                  else
                      vscounter <= vscounter + 1;
              end

              else if (flag == 0) begin                // Flags to designate where the ball bounches after it bounces off the paddle
                  if (RRFlag == 1) begin
                      vscounter <= vscounter - 1;
                      hscounter <= hscounter - 1;
                      vNhN <= 1; vNhP <= 0; vPhN <= 0; vPhP <= 0;
                  end
                  else if (RFlag == 1) begin
                      vscounter <= vscounter - 1;
                      hscounter <= hscounter - 1;
                      vNhN <= 1; vNhP <= 0; vPhN <= 0; vPhP <= 0;
                  end
                  else if (LFlag == 1) begin
                      vscounter <= vscounter - 1;
                      hscounter <= hscounter + 1;
                      vNhN <= 0; vNhP <= 1; vPhN <= 0; vPhP <= 0;
                  end
                  else if (LLFlag == 1) begin
                      vscounter <= vscounter - 1;
                      hscounter <= hscounter + 1;
                      vNhN <= 0; vNhP <= 1; vPhN <= 0; vPhP <= 0;
                  end
                  else if (SFlag == 1) begin
                      vscounter <= vscounter - 1;
                      vNhN <= 0; vNhP <= 0; vPhN <= 0; vPhP <= 0;
                  end
                  else
                      vscounter <= vscounter - 1;
                end
            end
                
            Counter <= 0;                  // Incrementing clock Counter
          end
        end
    end
/*********************************************************End VGA Code**********************************************************************/
    always_comb begin  
        if (INPUTDATACOUNTER == 9) begin
            if (counter2 == 0) begin          
                AN = ~1;                   // Displays the scan code
                switches = inputData[3:0];           
            end
    
            else if (counter2 == 1) begin
                AN = ~2;                     
                switches = inputData[7:4];                 
            end
            
            else if (counter == 2) begin    // Displays the number of lives left on the left most hex display
                AN = ~128;
                switches = deathCounter;
            end
        end
    end
endmodule

// Code for displaying value on the hex display
module digit(input logic [15:0]SW, output logic CA, CB, CC, CD, CE, CF, CG);
    logic [6:0] segments;                         // Variable to hold 7 bits for the 7 cathodes
    assign {CA,CB,CC,CD,CE,CF,CG} = ~segments;    // Set the 7 bits to the inverse of segments to make active high
    always_comb begin
        casez(SW)
        // CA CB CC CD CE CF CG
            4'b0000: segments = 7'b1111110;    // 0
            4'b0001: segments = 7'b0110000;    // 1
            4'b0010: segments = 7'b1101101;    // 2
            4'b0011: segments = 7'b1111001;    // 3
            4'b0100: segments = 7'b0110011;    // 4
            4'b0101: segments = 7'b1011011;    // 5
            4'b0110: segments = 7'b1011111;    // 6
            4'b0111: segments = 7'b1110000;    // 7
            4'b1000: segments = 7'b1111111;    // 8
            4'b1001: segments = 7'b1110011;    // 9
            4'b1010: segments = 7'b1110111;    // A
            4'b1011: segments = 7'b0011111;    // B
            4'b1100: segments = 7'b1001110;    // C
            4'b1101: segments = 7'b0111101;    // D
            4'b1110: segments = 7'b1001111;    // E
            4'b1111: segments = 7'b1000111;    // F    
        endcase    
    end
endmodule
