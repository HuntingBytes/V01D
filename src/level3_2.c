#include "includes/utils.h"

#define MAX_INPUT_CHARS 9

extern const int screenWidth;
extern const int screenHeight;
extern Level currentLevel;
extern bool game_running;
extern Camera2D camera;
extern Texture2D player_textures[];
extern Texture2D bullet_texture;

void mainLevel3_2() {
    // Initialization

    //variable that control the game cicle

    bool level3_phase2_finished = false;

    //Texture2D background = LoadTexture(MAPS_DIR"/menu/menu_background.png");

    //loading assets
    Texture2D spriteright = player_textures[WALK];
    Texture2D spriteup = player_textures[CLIMB];
    Texture2D spriteleft = LoadTexture(PLAYER_DIR"/walk_left.png");
    Texture2D background_1 = LoadTexture(MAPS_DIR"/level3/phase2/final-2plat.png");
    Texture2D background_2 = LoadTexture(MAPS_DIR"/level3/phase2/final-1plat.png");
    Texture2D background_3 = LoadTexture(MAPS_DIR"/level3/phase2/final-0plat.png");
    Texture2D spriteJump_left = LoadTexture(PLAYER_DIR"/jump_left.png");
    Texture2D spriteJump_right = player_textures[JUMP];
    Texture2D spritestopped_right = player_textures[IDLE];
    Texture2D spritestopped_left = LoadTexture(PLAYER_DIR"/idle_left.png");
    Texture2D bullet = bullet_texture;

    //Garantindo que todas texturas foram carregadas. Caso não, termina o jogo
    if(spriteright.id <= 0 || spriteup.id <= 0 || spriteleft.id <= 0 || background_1.id <= 0 || background_2.id <= 0 || background_3.id <= 0 || spriteJump_left.id <= 0 || spriteJump_right.id <= 0) {
        level3_phase2_finished = true;
        game_running = false;
        return;
    }

    if(spritestopped_right.id <= 0 || spritestopped_left.id <= 0 || bullet.id <= 0) {
        level3_phase2_finished = true;
        game_running = false;
        return;
    }

    //increasing size of sprites
    spriteright.height = (int) (spriteright.height * 2);
    spriteright.width = (int) (spriteright.width * 2);

    spriteup.height = (int) (spriteup.height * 2);
    spriteup.width = (int) (spriteup.width * 2);

    spriteleft.height = (int) (spriteleft.height * 2);
    spriteleft.width = (int) (spriteleft.width * 2);

    spriteJump_left.height = (int) (spriteJump_left.height * 2);
    spriteJump_left.width = (int) (spriteJump_left.width * 2);

    spriteJump_right.height = (int) (spriteJump_right.height * 2);
    spriteJump_right.width = (int) (spriteJump_right.width * 2);

    spritestopped_left.height = (int) (spritestopped_left.height * 2);
    spritestopped_left.width = (int) (spritestopped_left.width * 2);

    spritestopped_right.height = (int) (spritestopped_right.height * 2);
    spritestopped_right.width = (int) (spritestopped_right.width * 2);


    //declaration of rectangles rectangles related to position of player

    Vector2 position_of_sprite = {160, 370.0f};
    Rectangle trackposition = {170.0f, 360.0f, (float) 35.0f, (float) 72.0f};
    Rectangle how_far_gravity_is_applied = {170.0f, 362.0f, (float) 35.0f, (float) 72.0f};
    Rectangle immediately_previous_position = trackposition;

    //declaration of the rectangles that will collect the correct sprite for execution

    Rectangle frameRecRight = {0.0f, 0.0f, (float) spriteright.width / 6, (float) spriteright.height};
    Rectangle frameRecUpDown = {0.0f, 0.0f, (float) spriteup.width / 4, (float) spriteup.height};
    Rectangle frameRecleft = {0.0f, 0.0f, (float) spriteleft.width / 6, (float) spriteleft.height};
    Rectangle frameRecjump_left = {0.0f, 0.0f, (float) spriteJump_left.width / 8, (float) spriteJump_left.height};
    Rectangle frameRecjump_right = {0.0f, 0.0f, (float) spriteJump_right.width / 8, (float) spriteJump_right.height};
    Rectangle frameRecstopped_right = {0.0f, 0.0f, (float) spritestopped_right.width / 4,
                                       (float) spritestopped_right.height};
    Rectangle frameRecstopped_left = {0.0f, 0.0f, (float) spritestopped_left.width / 4,
                                      (float) spritestopped_left.height};

    //declaration of colliders

    Rectangle limitsdown = {0.0f, 433.0f, (float) 1280, 10.0f};
    Rectangle limitsleft_forbullet = {38, 0, 10, (float) screenWidth};
    Rectangle limitsright_forbullet = {1230, 0, 10, (float) screenWidth};
    Rectangle rec2 = {476.0f, 144.0f, (float) 145.0f, (float) 13.0f};
    Rectangle rec3 = {665.0f, 193.0f, (float) 23.0f, (float) 13.0f};
    Rectangle lever = {562.0f, 117.0f, (float) 35.0f, (float) 25.0f};
    Rectangle broken_rec1 = {720.0f, 166.0f, 50.0f, 13.0f};
    Rectangle broken_rec2 = {1021.0f, 166.0f, 50.0f, 13.0f};

    //the declaration that change rectangles that not used anymore(broken_rec1 and broken_rec2)

    Rectangle RECNULL = {0, 0, 0, 0};

    //declaration of stair

    Rectangle stair = {445.0f, 145.0f, (float) 30.0f, (float) 300.0f};

    //declaration of rectangles that permisses player go to left and right along the scene

    Rectangle AllowRightLeftintop = {0.0f, 110.0f, (float) 1280.0f, (float) 13.0f};
    Rectangle AllowRightLeftinBottom = {0.0f, 430.0f, (float) 1280, 2.0f};

    //declaration of variables that control the sprite cycle

    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;

    //declaration of a variable that identifies if the player is stopped or not

    int stoppedOn = 1;

    //declaration of variables that control the which cycle needs to be run(start stopped and looking for right)

    int pressjump_right = 0;
    int pressjump_left = 0;
    int pressRight = 0;
    int pressLeft = 0;
    int pressUpDown = 0;
    int stopped_right = 1;
    int stopped_left = 0;

    //declaration of variables that control the jump and gravity

    int maxpixelsjump = 80;
    int controljump = 0;
    int cangravity = 1;

    //ENIGMA VARIABLES

    char name[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;
    Rectangle textBox = {570.0f, 230.0f, 230.0f, 50.0f};
    bool mouseOnText = false;
    int FramesCounter_Enigma = 2;
    int fixingcounterbug_enigma = 0;//delay  underscore show when colides with a latter

    //Camera Declaration

    camera.target = (Vector2) {position_of_sprite.x + 10, position_of_sprite.y - 9};
    camera.offset = (Vector2) {170, 360};
    camera.rotation = 0.0f;
    camera.zoom = 1.2f;

    //BULLET VARIABLES

    const int bulletvelocity = 4;//the value that incremented in position of bullet
    Rectangle bullet_position = {0.0f, 200.0f, 14.0f, 14.0f};//rectangle of bullet calculus
    bool bulletOn = false;
    bool catchplayerpositition_forbullet = false;//bool that decides if bullet catch of not the position of the player
    bool cyclebullet_right = false;
    bool cyclebullet_left = false;
    bool damage_broken_rec1 = false;
    bool damage_broken_rec2 = false;
    int life_of_broken_rec1 = 5;
    int life_of_broken_rec2 = 3;

    // Main game loop
    while (!level3_phase2_finished) {
        //UPDATES------------------------------------------------------

        //------------------------------------------BULLET DECISIONS----------------------------------------------
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {//BULLET press IF

            bulletOn = true;

            catchplayerpositition_forbullet = true;

            if (pressRight == true || pressjump_right == true) {// bullet  will go to right
                cyclebullet_right = true;
                cyclebullet_left = false;
            } else if (pressLeft == true || pressjump_left == true) {//bullet will go to left
                cyclebullet_left = true;
                cyclebullet_right = false;
            }
        }
        if (CheckCollisionRecs(bullet_position, broken_rec1)) {//damage on rec 1
            damage_broken_rec1 = true;
        } else if (CheckCollisionRecs(bullet_position, broken_rec2)) {//damage on rec 2
            damage_broken_rec2 = true;
        }

        // checking collisions of bullet and multiples limits
        if (CheckCollisionRecs(bullet_position, limitsright_forbullet) ||
            CheckCollisionRecs(bullet_position, limitsleft_forbullet) ||
            CheckCollisionRecs(bullet_position, broken_rec1) || CheckCollisionRecs(bullet_position, broken_rec2)) {

            bullet_position.x = 0;
            bullet_position.y = 200;
            bulletOn = false;
            cyclebullet_left = false;
            cyclebullet_right = false;

        } else if (catchplayerpositition_forbullet == true) {//catch position of player when tap fire

            bullet_position.x = trackposition.x + 13;
            bullet_position.y = trackposition.y + 45;

            catchplayerpositition_forbullet = false;


        } else if (cyclebullet_left == true) {//bullet moving

            bullet_position.x -= (float) bulletvelocity;

        } else if (cyclebullet_right == true) {//bullet moving

            bullet_position.x += (float) bulletvelocity;

        }

        //----------------------sprite animation when stopped-------------------------------------

        if (framesCounter >= (150 / framesSpeed))  //doing the sprite stopped animation
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 3) currentFrame = 0;

            frameRecstopped_left.x = (float) currentFrame * (float) spritestopped_left.width / 4;

            if (currentFrame > 3) currentFrame = 0;

            frameRecstopped_right.x = (float) currentFrame * (float) spritestopped_right.width / 4;
        }

        // general update of gravity rectangle----------------------------------------

        how_far_gravity_is_applied = trackposition;
        how_far_gravity_is_applied.y = trackposition.y + 2;

        //general update for sprite position(based on trackposition)------------------

        position_of_sprite.x = trackposition.x - 10;
        position_of_sprite.y = trackposition.y + 7;

        //framescounter++ function: do the progress of the time-----------------------

        framesCounter++;

        //camera target update--------------------------------------------------------

        camera.target = (Vector2) {position_of_sprite.x + 10, position_of_sprite.y - 9};

        if (camera.target.x < 144) {//camera limits LEFT
            camera.target.x = 144;
        }
        if (camera.target.x > 886) {//camera limits RIGHT
            camera.target.x = 886;
        }
        if (camera.target.y < 298) {//camera limits TOP
            camera.target.y = 298;
        }

        if (trackposition.x < 46) {//limits player LEFT
            trackposition.x = 46;
        }
        if (trackposition.x > 1192) {//limits player RIGHT
            trackposition.x = 1192;
        }
        ///-----------------------------------------------  main ifs-------------------------------------------------

        //IF OF JUMP
        // this decision has the function of making the jump and deciding what the player can do when he is in the process of jumping
        if (cangravity == false) {

            if (controljump >
                maxpixelsjump) { // this if is for the computer know what the time to start the applying the gravity
                cangravity = 1;
                controljump = false;
            }

                //this else has te function of apply the gravity and deciding what the player can do when he is in this process
            else {
                //update the immediately previous position
                immediately_previous_position.y = trackposition.y + 6.0f;//it's 6 because the player is jumping(-4.0f actualization)

                if (pressjump_left == true) {//run sprite left jump,changing images
                    if (framesCounter >= (45 / framesSpeed))  //doing the sprite jump left animation
                    {
                        framesCounter = 0;
                        currentFrame++;

                        if (currentFrame > 7) currentFrame = false;

                        frameRecjump_left.x = (float) currentFrame * (float) spriteJump_left.width / 8;
                    }

                }
                if (pressjump_right == true) {//run sprite right jump
                    if (framesCounter >= (45 / framesSpeed))  //doing the sprite animation
                    {
                        framesCounter = 0;
                        currentFrame++;

                        if (currentFrame > 7) currentFrame = false;

                        frameRecjump_right.x = (float) currentFrame * (float) spriteJump_right.width / 8;
                    }
                }

                //(trackposition.y-=4) is gravity being applied

                trackposition.y -= 4.0f;//

                controljump += 4;//controljump makes the limit of jump(until where player jump)

                if (IsKeyDown(KEY_A)) {// while player jump, he can go to left

                    trackposition.x -= 2.0f;//going to left

                    pressUpDown = false;
                    pressRight = false;
                    pressLeft = false;
                    pressjump_right = false;
                    pressjump_left = true;//setting the sprite of going to left jump
                    stopped_right = false;
                    stopped_left = true;//if the player  stopped, the stopped cycle left will be run
                    stoppedOn = false;

                    immediately_previous_position.x = trackposition.x + 2.0f;//updating immediately previous position

                }
                if (IsKeyDown(KEY_D)) {

                    pressUpDown = false;
                    pressRight = false;
                    pressLeft = false;
                    pressjump_left = false;
                    pressjump_right = true;//setting the sprite of go-to jumping to  right
                    stopped_right = true;//if player stops, run standing sprite looking right
                    stopped_left = false;
                    stoppedOn = false;

                    trackposition.x += 2.0f;//going to right

                    immediately_previous_position.x = trackposition.x - 2.0f;//updating immediately previous position

                }
            }

        }

            //IF OF GRAVITY
            // this decision has the function of check collisions of rectangle(how_far_gravity_is_applied) and the colliders,if the collision not occured with at least one of colliders the gravity will be applied
        else if (!(CheckCollisionRecs(how_far_gravity_is_applied, limitsdown) ||
                   CheckCollisionRecs(how_far_gravity_is_applied, rec2) ||
                   CheckCollisionRecs(how_far_gravity_is_applied, rec3) ||
                   CheckCollisionRecs(how_far_gravity_is_applied, stair)) && cangravity == 1) {

            if (pressjump_left == 1 || pressLeft == 1) {//run sprite left jump,changing images
                if (framesCounter >= (45 / framesSpeed))  //doing the sprite animation
                {
                    framesCounter = 0;
                    currentFrame++;

                    if (currentFrame > 7) currentFrame = 0;

                    frameRecjump_left.x = (float) currentFrame * (float) spriteJump_left.width / 8;
                }

            }
            if (pressjump_right == 1 || pressRight == 1) {//run sprite right jump
                if (framesCounter >= (45 / framesSpeed))  //doing the sprite animation
                {
                    framesCounter = 0;
                    currentFrame++;

                    if (currentFrame > 7) currentFrame = 0;

                    frameRecjump_right.x = (float) currentFrame * (float) spriteJump_right.width / 8;
                }
            }

            trackposition.y += 4.0f;// gravity

            immediately_previous_position.y = trackposition.y - 6.0f; //updating previous position y

            if (IsKeyDown(KEY_A)) {

                if ((trackposition.x < 624 && trackposition.x > 482) &&
                    (trackposition.y < 216 && trackposition.y > 118)) {//bug of rec2 collision
                    trackposition.x = 624;

                }
                if ((trackposition.x < 690 && trackposition.x > 628) &&
                    (trackposition.y < 214 && trackposition.y > 128)) {//bug rec 3 collision
                    trackposition.x = 690;

                }
                trackposition.x -= 2.0f;// going to left

                pressUpDown = 0;
                pressRight = 0;
                pressLeft = 0;  //setting the sprite of going to left
                pressjump_left = 1;
                pressjump_right = 0;
                stopped_right = 0;
                stopped_left = 1;
                stoppedOn = 0;

                immediately_previous_position.x = trackposition.x + 2.0f;//updating immediately previous position

            }
            if (IsKeyDown(KEY_D)) {

                if ((trackposition.x < 644 && trackposition.x > 628) &&
                    (trackposition.y < 204 && trackposition.y > 126)) {//bug rec 3 collision
                    trackposition.x = 628;
                }

                trackposition.x += 2.0f;//going to right

                pressUpDown = 0;
                pressRight = 0;   //setting the sprite of going to right
                pressLeft = 0;
                pressjump_left = 0;
                pressjump_right = 1;
                stopped_right = 1;
                stopped_left = 0;
                stoppedOn = 0;

                immediately_previous_position.x = trackposition.x - 2.0f;//updating immediately previous position

            }
        }

            //IF OF PLAYER ON THE TOP OF COLLIDERS
            // this decision is for the replace the trackposition, if that colliding with the colliders
        else if (CheckCollisionRecs(trackposition, limitsdown) || CheckCollisionRecs(trackposition, rec2) ||
                 CheckCollisionRecs(trackposition, rec3)) {
            trackposition = immediately_previous_position;//here's the reason why rectangle immediately_previous_position exists

        }

            //IF OF COMPUTE THE MOVEMENTS IN STAIR
            // this decision if for the make all possibilitys if the player collides with a stair
        else if (CheckCollisionRecs(trackposition, stair)) {

            if (IsKeyDown(KEY_W)) {


                pressUpDown = true;  //setting the sprite of going to up or down
                pressRight = false;
                pressLeft = false;
                pressjump_left = false;
                pressjump_right = false;
                stopped_right = false;
                stopped_left = false;
                stoppedOn = false;

                trackposition.y -= 2.0f;//going to up

                immediately_previous_position.y = trackposition.y + 2.0f;//saving the before of the trackposition

                if (framesCounter >= (60 / framesSpeed))//doing the sprite animation
                {
                    framesCounter = 0;
                    currentFrame++;

                    if (currentFrame > 3) currentFrame = 0;

                    frameRecUpDown.x = (float) currentFrame * (float) spriteup.width / 4;
                }
            }

            if (IsKeyDown(KEY_S)) {

                pressUpDown = true; //setting the sprite of going to up or down
                pressRight = false;
                pressLeft = false;
                pressjump_left = false;
                pressjump_right = false;
                stopped_right = false;
                stopped_left = false;
                stoppedOn = false;

                trackposition.y += 2.0f; //going to down

                immediately_previous_position.y = trackposition.y - 2.0f;//saving the before of the trackposition

                if (framesCounter >= (60 / framesSpeed)) //doing the sprite animation
                {
                    framesCounter = 0;
                    currentFrame++;

                    if (currentFrame > 3) currentFrame = 0;

                    frameRecUpDown.x = (float) currentFrame * (float) spriteup.width / 4;
                }
            }
            if (IsKeyDown(KEY_D)) {

                pressUpDown = false;
                pressRight = true;//setting the sprite of right
                pressLeft = false;
                pressjump_left = false;
                pressjump_right = false;
                stopped_right = true;
                stopped_left = false;
                stoppedOn = false;

                trackposition.x += 2.0f;//going to right

                immediately_previous_position.x = trackposition.x - 2.0f;//saving the before of the trackposition

                if (framesCounter >= (60 / framesSpeed))//doing the sprite cycle
                {
                    framesCounter = 0;
                    currentFrame++;

                    if (currentFrame > 5) currentFrame = 0;

                    frameRecRight.x = (float) currentFrame * (float) spriteright.width / 6;
                }
            }
            if (IsKeyDown(KEY_A)) {

                if ((trackposition.x < 623 && trackposition.x > 618) &&
                    (trackposition.y < 160 && trackposition.y > 72)) {//bug of rec2 collision
                    trackposition.x = 623;
                }

                trackposition.x -= 2.0f;//going to left

                pressUpDown = false;
                pressRight = false;
                pressLeft = true;//setting the sprite of right
                pressjump_left = false;
                pressjump_right = false;
                stopped_right = false;
                stopped_left = true;
                stoppedOn = false;

                immediately_previous_position.x = trackposition.x + 2.0f;//saving the before of the trackposition

                if (framesCounter >= (60 / framesSpeed))//doing the sprite left animation
                {
                    framesCounter = 0;
                    currentFrame++;

                    if (currentFrame > 5) currentFrame = 0;

                    frameRecleft.x = (float) currentFrame * (float) spriteleft.width / 6;
                }
            }
        }

            //THAT IF:what happening if the player collides with the lever
        else if (CheckCollisionRecs(trackposition, lever)) {

            mouseOnText = true;

            // Get pressed key (character) on the queue
            int key = GetKeyPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0) {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)) {
                    name[letterCount] = (char) key;
                    letterCount++;
                }

                key = GetKeyPressed();  // Check next character in the queue
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                letterCount--;
                name[letterCount] = '\0';

                if (letterCount < 0) letterCount = 0;
            }

            fixingcounterbug_enigma++;

            if (fixingcounterbug_enigma <= 40) {
                FramesCounter_Enigma = 2;
            } else if (fixingcounterbug_enigma > 40 && fixingcounterbug_enigma < 100) {
                FramesCounter_Enigma = 1;
            } else {
                fixingcounterbug_enigma = 0;
            }

            if (IsKeyDown(KEY_D)) {

                pressUpDown = false;
                pressRight = true;//setting the sprite of right
                pressLeft = false;
                pressjump_left = false;
                pressjump_right = false;
                stopped_right = true;
                stopped_left = false;
                stoppedOn = false;

                trackposition.x += 2.0f;//going to right

                immediately_previous_position.x = trackposition.x - 2.0f;//saving the before of the trackposition

                if (framesCounter >= (60 / framesSpeed))//doing the sprite cycle
                {
                    framesCounter = 0;
                    currentFrame++;

                    if (currentFrame > 5) currentFrame = 0;

                    frameRecRight.x = (float) currentFrame * (float) spriteright.width / 6;
                }
            }
            if (IsKeyDown(KEY_A)) {

                if ((trackposition.x < 623 && trackposition.x > 618) &&
                    (trackposition.y < 160 && trackposition.y > 72)) {//bug of rec2 collision
                    trackposition.x = 623;

                }

                trackposition.x -= 2.0f;//going to left

                pressUpDown = false;
                pressRight = false;
                pressLeft = true;//setting the sprite of right
                pressjump_left = false;
                pressjump_right = false;
                stopped_right = false;
                stopped_left = true;
                stoppedOn = false;

                immediately_previous_position.x = trackposition.x + 2.0f;//saving the before of the trackposition

                if (framesCounter >= (60 / framesSpeed))//doing the sprite left animation
                {
                    framesCounter = 0;
                    currentFrame++;

                    if (currentFrame > 5) currentFrame = 0;

                    frameRecleft.x = (float) currentFrame * (float) spriteleft.width / 6;
                }
            }
        }

            //THAT IF:ALLOW THE PLAYER GO TO LEFT OR RIGHT
            // this decision is to fix the bug that happened at the top of the stairs previously
        else if (CheckCollisionRecs(trackposition, AllowRightLeftinBottom) ||
                 CheckCollisionRecs(trackposition, AllowRightLeftintop)) {
            if (IsKeyDown(KEY_D)) {

                pressUpDown = false;
                pressRight = true;//setting the sprite of right
                pressLeft = false;
                pressjump_left = false;
                pressjump_right = false;
                stopped_right = true;
                stopped_left = false;
                stoppedOn = false;

                trackposition.x += 2.0f;//going to right

                immediately_previous_position.x = trackposition.x - 2.0f;//saving the before of the trackposition

                if (framesCounter >= (60 / framesSpeed))//doing the sprite cycle
                {
                    framesCounter = 0;
                    currentFrame++;

                    if (currentFrame > 5) currentFrame = 0;

                    frameRecRight.x = (float) currentFrame * (float) spriteright.width / 6;
                }
            }
            if (IsKeyDown(KEY_A)) {

                if ((trackposition.x < 623 && trackposition.x > 618) &&
                    (trackposition.y < 160 && trackposition.y > 72)) {//bug of rec2 collision
                    trackposition.x = 623;

                }

                trackposition.x -= 2.0f;//going to left

                pressUpDown = false;
                pressRight = false;
                pressLeft = true;//setting the sprite of left
                pressjump_left = false;
                pressjump_right = false;
                stopped_right = false;
                stopped_left = true;
                stoppedOn = false;

                immediately_previous_position.x = trackposition.x + 2.0f;//saving the before of the trackposition

                if (framesCounter >= (60 / framesSpeed))//doing the sprite left animation
                {
                    framesCounter = 0;
                    currentFrame++;

                    if (currentFrame > 5) currentFrame = 0;

                    frameRecleft.x = (float) currentFrame * (float) spriteleft.width / 6;
                }
            }
            if (IsKeyPressed(KEY_SPACE)) {//collecting the key space of player
                cangravity = 0;//enabling the jump cycle,making it impossible the gravity cycle operate
            }

        }
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        BeginMode2D(camera);

        ClearBackground(GetColor(0x052c46ff));

        //selecting backgrounds according to broken recs
        if (life_of_broken_rec1 > 0 && life_of_broken_rec2 == 3) {
            DrawTexture(background_1, (int) 0.f, (int) 0.f, WHITE);
        } else if (life_of_broken_rec1 == 0 && life_of_broken_rec2 > 0) {
            broken_rec1 = RECNULL;
            DrawTexture(background_2, (int) 0.f, (int) 0.f, WHITE);
        } else if (life_of_broken_rec1 == 0 && life_of_broken_rec2 == 0) {
            broken_rec2 = RECNULL;
            DrawTexture(background_3, (int) 0.f, (int) 0.f, WHITE);
        }

        //draw correct texture

        if (stopped_left == true && stoppedOn == true) {
            DrawTextureRec(spritestopped_left, frameRecstopped_left, position_of_sprite, WHITE);
        } else if (stopped_right == true && stoppedOn == true) {
            DrawTextureRec(spritestopped_right, frameRecstopped_right, position_of_sprite, WHITE);
        } else if (pressjump_left == true) {
            DrawTextureRec(spriteJump_left, frameRecjump_left, position_of_sprite, WHITE);
        } else if (pressjump_right == true) {
            DrawTextureRec(spriteJump_right, frameRecjump_right, position_of_sprite, WHITE);
        } else if (pressRight == true) {
            DrawTextureRec(spriteright, frameRecRight, position_of_sprite, WHITE);  // Draw part of the texture
        } else if (pressLeft == true) {
            DrawTextureRec(spriteleft, frameRecleft, position_of_sprite, WHITE);
        } else if (pressUpDown == true) {
            DrawTextureRec(spriteup, frameRecUpDown, position_of_sprite, WHITE);
        }
        //draw bullet texture
        if (bulletOn) {
            DrawTexture(bullet, (int) bullet_position.x, (int) bullet_position.y, WHITE);
        }

        //draw damage broken recs
        if (damage_broken_rec1 == true) {
            life_of_broken_rec1--;
            DrawRectangle(720, 166, 50, 13, RED);
            damage_broken_rec1 = false;

        }
        if (damage_broken_rec2 == true) {
            life_of_broken_rec2--;
            DrawRectangle(1021, 166, 50, 13, RED);
            damage_broken_rec2 = false;

        }

        //enigma draw decisions
        if (CheckCollisionRecs(trackposition, lever)) {


            DrawRectangleLinesEx(textBox, 4, LIGHTGRAY);


            DrawText(name, (int) textBox.x + 5, (int) textBox.y + 8, 40, MAROON);



            if (letterCount < MAX_INPUT_CHARS) {

                // Draw blinking underscore char
                if (((FramesCounter_Enigma) % 2) == 0)
                    DrawText("_", (int) textBox.x + 8 + (int) MeasureText(name, 40), (int) textBox.y + 12, 40, MAROON);
            }
        }

        //string analysis
        if (strcmp("crocodilo", name) == 0) {
            level3_phase2_finished = true;
            currentLevel = ENDING;
        }

        EndDrawing();
        EndMode2D();
        //----------------------------------------------------------------------------------
        stoppedOn = 1;

        if (WindowShouldClose()) {
            level3_phase2_finished = true;
            game_running = false;
        }

    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // Texture unloading
    UnloadTexture(spriteleft);
    UnloadTexture(spriteJump_left);
    UnloadTexture(spritestopped_left);
    UnloadTexture(background_1);
    UnloadTexture(background_2);
    UnloadTexture(background_3);

    //--------------------------------------------------------------------------------------
}