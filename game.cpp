

//included for Sleep() function
//system includes
#include <Windows.h>

//engine includes
#include "logManager.h"
#include "Clock.h"
#include "GameManager.h"
#include "Vector.h"
#include "Object.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "Event.h"
#include "EventStep.h"
#include "Saucer.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "Hero.h"
#include "InputManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Frame.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "Animation.h"
#include "CameraObj.h"
#include "Box.h"
#include "Utility.h"
#include "Music.h"
#include "Sound.h"

//test method stubs
int testLog(void);
void testClock(void);
int testGM(void);
int testVector();
int testObject();
int testObjList();
int testIterate();
void testEvent();
void testStep();
void testHandler();
int testWorld();
int testDisp();
int testInput();
int testMouseEvent();
int testKeyEvent();
int testFrame();
int testSprite();
int testRM();
int testAnimation();
int testBox();
int testOverlap();
void testSound();

int main()
{
    //ALL TEST FUNCTIONS CALLED HERE

    //TO SEE LOGS FROM GAME MANAGER, LOG MANAGER, AND DISPLAY MANAGER, COMMENT OUT ALL OTHER TESTS

    LM.startUp();

    /*
    testSound();
    printf("Sound + music tested.\n");
    
    testDisp();
    printf("Display Manager tested.\n");
    */
 
    //tests game manager
    if (!testGM()) return 0;
    printf("Game Manager Success!\n");
    /*
    
    //tests log manager
    if (!testLog()) return 0;
    printf("Log Manager Success!\n");
    
    //start up log manager again, after tests shut it down
    LM.startUp();

    //test clock script
    testClock();
    printf("Clock tested, check logs.\n");

    //test vector class
    if (!testVector()) return 0;
    printf("Vector Success!\n");

    //test object class
    if (!testObject()) return 0;
    printf("Object base class success!\n");

    //test object list class
    if (!testObjList()) return 0;
    printf("Object list success!\n");

    //test ObjectListIterator class
    testIterate();
    printf("Object List Iterator tested, check logs.\n");

    //test Event base class
    testEvent();
    printf("Event base class tested, check logs.\n");

    //test StepEvent class
    testStep();
    printf("Event Step tested, check logs.\n");

    //test eventHandler method in object
    testHandler();
    printf("Event handler tested, check logs.\n");

    //test WorldManager
    testWorld();
    printf("World Manager tested, check logs.\n");
    
    if (!testInput()) return 0;
    printf("Input Manager success!\n");
    

    //tests for eventMouse
    if (!testMouseEvent()) return 0;
    printf("EventMouse success!\n");

    //tests for eventKeyboard
    if (!testKeyEvent()) return 0;
    printf("EventKeyboard success!\n");

    //tests for frame
    if (!testFrame()) return 0;
    printf("Frame success!\n");

    //tests for sprite
    if (!testSprite()) return 0;
    printf("Sprite success!\n");

    //tests for resource manager
    if (!testRM()) return 0;
    printf("RM sucess!\n");
    */

    //tests for animation
    if (!testAnimation()) return 0;
    printf("Animation success!\n");

    //tests for box
    if (!testBox()) return 0;
    printf("Box success!\n");

    if (!testOverlap()) return 0;
    printf("Overlap Success!\n");
    


    //GM.shutDown();
    
    
    //tests ran successfully
    return 1;
}



void testSound() {

    df::Music m;
    df::Sound s;

    //check that nonexistant sound won't load
    if (s.loadSound("jkjkjk") == 0)
    {
        LM.writeLog("\nload sound fail! loading non existant file");
    }

    //load nuke sound
    s.loadSound("sounds/nuke.wav");

    //listen for sound playing on loop and stopping abruptly
    s.play(true);

    Sleep(5000);

    s.stop();

    Sleep(500);

    //play should start from the beginning, pause, and then resume
    s.play(true);

    Sleep(3000);
    s.pause();
    Sleep(500);
    s.play();
    Sleep(3000);

    //check that nonexistant file won't load
    if (m.loadMusic("jkjkjk") == 0)
    {
        LM.writeLog("\nload music fail! loading non existant file");
    }

    //load start music and play
    m.loadMusic("sounds/start-music.wav");

    m.play(true);

    Sleep(5000);

    //stop abruptly
    m.stop();

    Sleep(500);

    //play from start, pause, then resume
    m.play(true);
    Sleep(3000);
    m.pause();
    Sleep(500);
    m.play();
    Sleep(3000);
    //stop music
    m.stop();

    //start RM and load in sounds + music
    RM.startUp();
    RM.loadSound("sounds/nuke.wav", "nuke");
    RM.loadSound("sounds/explode.wav", "explosion");
    RM.loadMusic("sounds/start-music.wav", "Start Music");

    //play explosion sound 
    RM.getSound("explosion")->play(false);

    Sleep(3000);

    //play start music
    RM.getMusic("Start Music")->play(false);

    Sleep(5000);

    //unload one sound file
    RM.unloadSound("nuke");

    //check that nonexistant sound won't unload
    if (RM.unloadSound("jkjkjk") == 0)
    {
        LM.writeLog("\nRM unloaded nonexistant sound!");
    }

    //check that nonexistant music won't unload
    if (RM.unloadMusic("jkjkjk") == 0)
    {
        LM.writeLog("\nRM unloaded nonexistant music!");
    }

    //unload music
    RM.unloadMusic("Start Music");

    RM.shutDown();

}



int testOverlap() {

    LM.writeLog("\nBOX OVERLAP TESTS\n_______________________________________");

    df::Utility u = df::Utility();

    df::Box b1 = df::Box();
    df::Box b2 = df::Box();

    //FIRST TEST CASE- corresponds with order in pdf
    b1.setCorner(df::Vector(0, 0));
    b1.setHorizontal(4);
    b1.setVertical(4);

    b2.setCorner(df::Vector(3, 3));
    b2.setHorizontal(7);
    b2.setVertical(3);

    if (!u.boxIntersectsBox(b1, b2)) {
        LM.writeLog("\ntest one failed!");
        return 0;
    }
    //test reversing which box is A and which is B
    if (!u.boxIntersectsBox(b2, b1)) {
        LM.writeLog("\ntest two failed!");
        return 0;
    }
    
    //SECOND TEST CASE
    b1.setCorner(df::Vector(5, 0));
    b1.setHorizontal(2);
    b1.setVertical(6);

    b2.setCorner(df::Vector(2, 2));
    b2.setHorizontal(8);
    b2.setVertical(2);

    if (!u.boxIntersectsBox(b1, b2)) {
        LM.writeLog("\ntest three failed!");
        return 0;
    }
    //test reversing which box is A and which is B
    if (!u.boxIntersectsBox(b2, b1)) {
        LM.writeLog("\ntest four failed!");
        return 0;
    }

    //THIRD TEST CASE
    b1.setCorner(df::Vector(0, 0));
    b1.setHorizontal(10);
    b1.setVertical(5);

    b2.setCorner(df::Vector(2, 2));
    b2.setHorizontal(2);
    b2.setVertical(2);

    if (!u.boxIntersectsBox(b1, b2)) {
        LM.writeLog("\ntest five failed!");
        return 0;
    }
    //test reversing which box is A and which is B
    if (!u.boxIntersectsBox(b2, b1)) {
        LM.writeLog("\ntest six failed!");
        return 0;
    }

    //FOURTH TEST CASE- HORIZONTAL BORDERS LINE UP EXACTLY
    b1.setCorner(df::Vector(1, 1));
    b1.setHorizontal(4);
    b1.setVertical(2);

    b2.setCorner(df::Vector(1, 3));
    b2.setHorizontal(4);
    b2.setVertical(2);

    if (!u.boxIntersectsBox(b1, b2)) {
        LM.writeLog("\ntest seven failed!");
        return 0;
    }
    //test reversing which box is A and which is B
    if (!u.boxIntersectsBox(b2, b1)) {
        LM.writeLog("\ntest eight failed!");
        return 0;
    }

    //FIFTH TEST CASE- VERTICAL BORDERS LINE UP EXACTLY
    b1.setCorner(df::Vector(0, 0));
    b1.setHorizontal(1);
    b1.setVertical(1);

    b2.setCorner(df::Vector(0, 1));
    b2.setHorizontal(1);
    b2.setVertical(1);

    if (!u.boxIntersectsBox(b1, b2)) {
        LM.writeLog("\ntest nine failed!");
        return 0;
    }
    //test reversing which box is A and which is B
    if (!u.boxIntersectsBox(b2, b1)) {
        LM.writeLog("\ntest ten failed!");
        return 0;
    }

    //SIXTH TEST CASE- CORNERS LINE UP EXACTLY
    b1.setCorner(df::Vector(2, 2));
    b1.setHorizontal(4);
    b1.setVertical(2);

    b2.setCorner(df::Vector(6, 4));
    b2.setHorizontal(1);
    b2.setVertical(4);

    if (!u.boxIntersectsBox(b1, b2)) {
        LM.writeLog("\ntest eleven failed!");
        return 0;
    }
    //test reversing which box is A and which is B
    if (!u.boxIntersectsBox(b2, b1)) {
        LM.writeLog("\ntest twelve failed!");
        return 0;
    }

    //SEVENTH TEST CASE- boxes do not overlap
    b1.setCorner(df::Vector(0, 0));
    b1.setHorizontal(1);
    b1.setVertical(1);

    b2.setCorner(df::Vector(2, 2));
    b2.setHorizontal(1);
    b2.setVertical(1);

    if (u.boxIntersectsBox(b1, b2)) {
        LM.writeLog("\ntest thirteen failed!");
        return 0;
    }
    //test reversing which box is A and which is B
    if (u.boxIntersectsBox(b2, b1)) {
        LM.writeLog("\ntest fourteen failed!");
        return 0;
    }
    
    return 1;

}





int testBox() {

    LM.writeLog("\nBOX TESTS\n__________________________________");

    df::Box b = df::Box();
    df::Object o = df::Object();

    //check dimension defaults
    if (b.getHorizontal() != 0 || b.getVertical() != 0)
    {
        LM.writeLog("\nDimensions not set to 0 by default!");
        return 0;
    }
    //check corner default
    if (b.getCorner().getX() != 0 || b.getCorner().getY() != 0)
    {
        LM.writeLog("\n Corner not set to 0,0 by default!");
        return 0;
    }

    //use setters
    b.setCorner(df::Vector(3, 3));
    b.setHorizontal(5);
    b.setVertical(4);

    //check set dimensions
    if (b.getHorizontal() != 5 || b.getVertical() != 4)
    {
        LM.writeLog("\nDimensions setters not working! h: %d, v: %d", b.getHorizontal(), b.getVertical());
        return 0;
    }

    //check set corner
    if (b.getCorner().getX() != 3 || b.getCorner().getY() != 3)
    {
        LM.writeLog("\nError with corner setter! x: %d y %d", b.getCorner().getX(), b.getCorner().getY());
        return 0;
    }

    df::Box b2 = o.getBox();

    //check dimension defaults for object box
    if (b2.getHorizontal() != 1 || b2.getVertical() != 1)
    {
        LM.writeLog("\nDimensions not set to 1 by default! (object box)");
        return 0;
    }
    //check corner default
    if (b2.getCorner().getX() != 0 || b2.getCorner().getY() != 0)
    {
        LM.writeLog("\n Corner not set to 0,0 by default!");
        return 0;
    }

    o.setBox(b);
    b2 = o.getBox();

    //check set dimensions
    if (b2.getHorizontal() != 5 || b2.getVertical() != 4)
    {
        LM.writeLog("\nDimensions setters not working! h: %d, v: %d", b.getHorizontal(), b.getVertical());
        return 0;
    }

    //check set corner
    if (b2.getCorner().getX() != 3 || b2.getCorner().getY() != 3)
    {
        LM.writeLog("\nError with corner setter! x: %d y %d", b.getCorner().getX(), b.getCorner().getY());
        return 0;
    }


    LM.writeLog("\nall passed!");
    return 1;

}




int testAnimation()
{
    LM.writeLog("\nANIMATION TESTS\n_____________________________________________");
    df::Animation a = df::Animation();

    //check default values for index and count
    if (a.getIndex() != 0 || a.getSlowdownCount() != 0)
    {
        LM.writeLog("\nIndex or slowdown count not set to 0 by default!");
        return 0;
    }
    //check that name set to empty by default
    if (!a.getName().empty())
    {
        LM.writeLog("\nsprite name not set to empty by default!");
        return 0;
    }
    //check sprite set to null by default
    if (a.getSprite() != NULL)
    {
        LM.writeLog("\nsprite not set to null by default!");
        return 0;
    }

    df::Sprite s = df::Sprite(6);
    //set values 
    a.setIndex(3);
    a.setSlowdownCount(3);
    a.setName("bullet");
    //check setters worked
    if (a.getIndex() != 3 || a.getSlowdownCount() != 3)
    {
        LM.writeLog("\nIndex or slowdown count not set by setters! i: %d, sl: %d", a.getIndex(), a.getSlowdownCount());
        return 0;
    }

    a.setSprite(&s);
    //check that set sprite indexed to 0
    if (a.getIndex() != 0)
    {
        LM.writeLog("\nIndex not set to 0 by setSprite()!");
        return 0;
    }
    //check name setter
    if (a.getName() != "bullet")
    {
        LM.writeLog("\nsprite name not set by setter!");
        return 0;
    }
    //check sprite getter
    if (a.getSprite() != &s)
    {
        LM.writeLog("\nsprite not set by setter!");
        return 0;
    }
    //start up display and resource manager, load bullet sprite
    DM.startUp();
    RM.startUp();
    RM.loadSprite("sprites/bullet-spr.txt", "bullet");
    df::Sprite* bullet = RM.getSprite("bullet");

    a.setSprite(bullet);

    //loop 20 times and check animation
    for (int i = 0; i < 20; i++)
    {
        a.draw(df::Vector(10, 10));
        DM.getWindow()->display();
        Sleep(100);
    }
    //clear window
    DM.shutDown();

    DM.startUp();
    //load saucer sprite
    RM.loadSprite("sprites/saucer-spr.txt", "saucer");
    //create saucer and hero with sprites (hero with bullet sprite)
    Saucer saucer = Saucer();
    Hero* b = new Hero;
    
    saucer.setSprite("saucer");
    b->setSprite("bullet");

    saucer.setPosition(df::Vector(10, 10));
    saucer.setPosition(df::Vector(15, 15));

    df::Animation saucerAni = saucer.getAnimation();

    //set slowdown of both to zero
    saucerAni.getSprite()->setSlowdown(0);
    b->getAnimation().getSprite()->setSlowdown(0);

    LM.writeLog("\nsaucer slowdown: %d", saucer.getAnimation().getSprite()->getSlowdown());
    LM.writeLog("\nbullet slowdown: %d", b->getAnimation().getSprite()->getSlowdown());

    //loop through and watch for no slowdown
    for (int i = 0; i < 100; i++) {
        saucer.draw();
        b->draw();
        DM.getWindow()->display();
    }
    //set slowdown to 10
    saucerAni.getSprite()->setSlowdown(10);
    b->getAnimation().getSprite()->setSlowdown(10);

    LM.writeLog("\nsaucer slowdown: %d", saucer.getAnimation().getSprite()->getSlowdown());
    LM.writeLog("\nbullet slowdown: %d", b->getAnimation().getSprite()->getSlowdown());
    
    //loop through and watch for slowdown
    for (int i = 0; i < 100; i++) {
        saucer.draw();
        b->draw();
        DM.getWindow()->display();
    }

    //freeze both animations
    saucer.setSlowdownCount(-1);
    b->setSlowdownCount(-1);

    LM.writeLog("\nsaucer slowdown count: %d", saucer.getAnimation().getSlowdownCount());
    LM.writeLog("\nbullet slowdown: %d", b->getAnimation().getSlowdownCount());

    //check that animations are frozen
    for (int i = 0; i < 100; i++) {
        saucer.draw();
        b->draw();
        DM.getWindow()->display();
    }

    //shut down managers
    RM.shutDown();
    DM.shutDown();

    LM.writeLog("\nall passed!");
    return 1;
}


int testRM()
{
    LM.writeLog("\nRESOURCE MANAGER TESTS:\n___________________________________________________");

    RM.startUp();
    //check typed corredctly
    if (RM.getType() != "ResourceManager") {
        LM.writeLog("\nRM typed incorrectly!");
        return 0;
    }
    //load sprites into RM
    if (RM.loadSprite("sprites/bullet-spr.txt", "bullet") == -1) return 0;
    if (RM.loadSprite("sprites/saucer-spr.txt", "saucer") == -1) return 0;
    if (RM.loadSprite("sprites/explosion-spr.txt", "explosion") == -1) return 0;

    //assign loaded sprites to sprite pointers
    df::Sprite* bullet = RM.getSprite("bullet");
    df::Sprite* saucer = RM.getSprite("saucer");
    df::Sprite* explosion = RM.getSprite("explosion");

    DM.startUp();

    //draw three loaded sprites
    bullet->draw(0, df::Vector(1,1));
    saucer->draw(3, df::Vector(3, 3));
    explosion->draw(5, df::Vector(5, 5));

    DM.getWindow()->display();

    Sleep(1000);

    DM.shutDown();

    //check that unloading is successful
    if (RM.unloadSprite("bullet") == -1) {
        LM.writeLog("\nunload bullet unsuccessful!");
        return 0;
    }

    if (RM.unloadSprite("explosion") == -1) {
        LM.writeLog("\nunload explosion unsucessful!");
        return 0;
    }

    if (RM.unloadSprite("saucer") == -1) {
        LM.writeLog("\nunload saucer unsuccessful!");
        return 0;
    }

    RM.shutDown();

    return 1;
}






int testSprite()
{
    LM.writeLog("\nSPRITE TESTS\n______________________________________");
    df::Sprite s = df::Sprite(3);

    //check that default int attributes are set to 0
    if (s.getHeight() != 0 || s.getWidth() != 0 || s.getFrameCount() != 0 || s.getSlowdown() != 0) {
        LM.writeLog("\nsprite width, height, frame count, or slowdown not 0 to start!");
        return 0;
    }
    //check color set to DEFAULT
    if (s.getColor() != df::COLOR_DEFAULT)
    {
        LM.writeLog("\nColor not set to default!");
        return 0;
    }
    //check label set to blank
    if (s.getLabel() != "")
    {
        LM.writeLog("\nLabel not set to empty by default!");
        return 0;
    }
    //use setters
    s.setHeight(1);
    s.setWidth(1);
    s.setSlowdown(1);
    //check ints set correctly
    if (s.getHeight() != 1 || s.getWidth() != 1 ||  s.getSlowdown() != 1) {
        LM.writeLog("\nsprite width, height, and slowdown not 1 by setter!");
        return 0;
    }
    //use setters
    s.setColor(df::BLACK);
    s.setLabel("test");

    //check color set correctly
    if (s.getColor() != df::BLACK)
    {
        LM.writeLog("\nColor not set to black by setter!");
        return 0;
    }

    //check label set correctly
    if (s.getLabel() != "test") {
        LM.writeLog("\nLabel not set to 'test' by setter!");
        return 0;
    }

    //create three test frames
    df::Frame f = df::Frame();
    df::Frame f2 = df::Frame(4, 5, "o o o o o o o o o o ");
    df::Frame f3 = df::Frame();

    //in third frame, test setters
    f3.setHeight(5);
    f3.setWidth(4);
    f3.setString(". . . . . . . . . . ");

    //add frames to sprite
    s.addFrame(f3);
    s.addFrame(f2);
    s.addFrame(f2);
    //check that sprite won't accept frames beyond limit
    if (s.addFrame(f) != -1) {
        LM.writeLog("\nsprite allows for adding frames beyond limit!");
        return -0;
    }

    df::Frame ftest = s.getFrame(0);

    //check that frames are set correctly within sprite
    if (ftest.getHeight() != 5 || ftest.getWidth() != 4 || ftest.getString().c_str() == ". . . . . . . . . . ")
    {
        LM.writeLog("\nftest incorrect parameters! w: %d, h: %d, s: %s",
            f3.getHeight(), f3.getWidth(), f3.getString());
        return 0;
    }

    df::Frame f4 = s.getFrame(3);

    if (f4.getHeight() != 0 || f4.getWidth() != 0 || f4.getString().empty() == false)
    {
        LM.writeLog("\ndefault frame incorrect parameters! w: %d, h: %d, s: %s",
            f.getHeight(), f.getWidth(), f.getString());
        return 0;
    }

    //create bullet sprite with all frames
    s.setColor(df::CYAN);
    df::Sprite bullet = df::Sprite(2);

    bullet.setHeight(1);
    bullet.setWidth(2);
    bullet.setColor(df::BLUE);
    bullet.setSlowdown(5);

    df::Frame b1 = df::Frame(2, 1, ">-");
    df::Frame b2 = df::Frame(2, 1, ">:");

    bullet.addFrame(b1);
    bullet.addFrame(b2);

    DM.startUp();

    //draw both on screen
    s.draw(2, df::Vector(20, 10));
    bullet.draw(0, df::Vector(30, 10));
    DM.getWindow()->display();
    
    Sleep(1000);

    //change to a different frame and draw on screen
    s.draw(0, df::Vector(20, 10));
    bullet.draw(1, df::Vector(30, 20));
    DM.getWindow()->display();

    Sleep(1000);

    DM.shutDown();

    LM.writeLog("\nAll passed!");
    return 1;
}




int testFrame()
{
    LM.writeLog("\nFRAME TESTS:\n_____________________________________");

    //create three test frames
    df::Frame f = df::Frame();
    df::Frame f2 = df::Frame(2, 3, "oooooo");
    df::Frame f3 = df::Frame();

    //in third frame, test setters
    f3.setHeight(5);
    f3.setWidth(4);
    f3.setString(". . . . . . . . . . ");

    //checks that default constructor works as needed
    if (f.getHeight() != 0 || f.getWidth() != 0 || f.getString().empty() == false)
    {
        LM.writeLog("\ndefault frame incorrect parameters! w: %d, h: %d, s: %s", 
            f.getHeight(), f.getWidth(), f.getString());
        return 0;
    }

    //checks that second constructor works
    if (f2.getHeight() != 3 || f2.getWidth() != 2 || f2.getString().c_str() == "oooooo")
    {
        LM.writeLog("\nframe2 incorrect parameters! w: %d, h: %d, s: %s",
            f2.getHeight(), f2.getWidth(), f2.getString().c_str());
        return 0;
    }

    //checks that setters work
    if (f3.getHeight() != 5 || f3.getWidth() != 4 || f3.getString().c_str() == ". . . . . . . . . . ")
    {
        LM.writeLog("\nframe3 incorrect parameters! w: %d, h: %d, s: %s",
            f3.getHeight(), f3.getWidth(), f3.getString());
        return 0;
    }

    DM.startUp();

    //make sure that an empty frame cannot be drawn
    if (f.draw(df::Vector(1, 1), df::BLUE) != -1) {
        LM.writeLog("\nframe draw method does not reject empty frame!");
        return 0;
    }
    //draw two frames on screen
    f2.draw(df::Vector(10, 10), df::GREEN);
    f3.draw(df::Vector(15, 15), df::RED);

    DM.getWindow()->display();

    Sleep(2000);

    DM.shutDown();

    return 1;
    
}




int testKeyEvent()
{
    LM.writeLog("\nEVENT KEYBOARD TESTS\n_______________________________________");

    df::EventKeyboard* k = new df::EventKeyboard;

    //test to make sure key and action undefined by default
    if (k->getKey() != df::Keyboard::UNDEFINED_KEY)
    {
        LM.writeLog("\n Key not set to undefined by default!");
        return 0;
    }
    if (k->getKeyboardAction() != df::UNDEFINED_KEYBOARD_ACTION)
    {
        LM.writeLog("\nKey action not set to undefined!");
        return 0;
    }

    //use setters to change key and action
    k->setKey(df::Keyboard::A);
    k->setKeyboardAction(df::KEY_PRESSED);

    //check that setters worked
    if (k->getKey() != df::Keyboard::A)
    {
        LM.writeLog("\n Key not set to A by setter!");
        return 0;
    }
    if (k->getKeyboardAction() != df::KEY_PRESSED)
    {
        LM.writeLog("\nKey action not set to pressed by setter!");
        return 0;
    }
    LM.writeLog("\nAll passed!");

    //Success
    return 1;
}


int testMouseEvent()
{
    LM.writeLog("\nEVENT MOUSE TESTS\n_______________________________________");
    df::EventMouse* m = new df::EventMouse;

    //check mouse action set to default undefined
    if (m->getMouseAction() != df::UNDEFINED_MOUSE_ACTION)
    {
        LM.writeLog("\nMouse action not set to undefined by default");
        return 0;
    }
    //check default button undefined
    if (m->getMouseButton() != df::Mouse::UNDEFINED_MOUSE_BUTTON)
    {
        LM.writeLog("\nMouse button not set to undefined by default");
        return 0;
    }
    //check default position 0
    if (m->getMousePosition().getX() != 0 && m->getMousePosition().getY() != 0)
    {
        LM.writeLog("\nMouse position not set to 0,0 by default");
        return 0;
    }

    m->setMouseAction(df::CLICKED);
    m->setMouseButton(df::Mouse::LEFT);
    m->setMousePosition(df::Vector(3, 3));

    //check all setters worked
    if (m->getMouseAction() != df::CLICKED)
    {
        LM.writeLog("\nMouse action not set to clicked by setter");
        return 0;
    }

    if (m->getMouseButton() != df::Mouse::LEFT)
    {
        LM.writeLog("\nMouse button not set to left by setter");
        return 0;
    }

    if (m->getMousePosition().getX() != 3 && m->getMousePosition().getY() != 3)
    {
        LM.writeLog("\nMouse position not set to 3,3 by setter");
        return 0;
    }

    LM.writeLog("\nAll passed!");
    return 1;

}


int testInput()
{
    LM.writeLog("\nINPUT MANAGER TESTS\n________________________________________");

    //test to make sure input manager does not start up without display manager
    if (IM.startUp() == 0)
    {
        LM.writeLog("\nInput Manager started up without Display Manager!");
        return 0;
    }

    DM.startUp();
    
    //check im starts up now
    if (IM.startUp() != 0)
    {
        LM.writeLog("\nInput Manager failed startup!");
        return 0;
    }

    Hero* h = new Hero;
    printf("\nTesting input! Use buttons/mouse");
    //run getInput repeatedly, check logs for output
    for (int i = 0; i < 300; i++)
    {
        IM.getInput();
        Sleep(10);
    }
    //success
    return 1;
}



//TEST DISPLAY MANAGER
int testDisp() {
    LM.writeLog("\nDISPLAY MANAGER TESTS\n___________________________________________");

    //start up the manager
    DM.startUp();

    //check DM is typed correctly
    if (DM.getType() != "DisplayManager")
    {
        LM.writeLog("\nDisplay Manager typed incorrectly!");
        return 0;
    }
    
    //check getters for window size
    LM.writeLog("\nHorizontal chars: %d   Horizontal pixels: %d", DM.getHorizontal(), DM.getHorizontalPixels());
    LM.writeLog("\nVertical chars: %d    Vertical pixels: %d", DM.getVertical(), DM.getVerticalPixels());

    //create vectors for testing
    df::Vector v = df::Vector(1, 1);
    df::Vector v2 = df::Vector();
    df::Vector v3 = df::Vector(2, 2);
    df::Vector v4 = df::Vector(5, 5);
    df::Vector v5 = df::Vector(9, 9);

    //draw three chars with different colors, in different locations
    DM.drawCh(v3, '*', df::CYAN);
    DM.drawCh(v, '*', df::GREEN);
    DM.drawCh(v2, '*', df::YELLOW);

    //draw three strings, each a different justification, color, location
    DM.drawString(v3, "testing", df::CENTER_JUSTIFIED, df::MAGENTA);
    DM.drawString(v5, "the quick brown fox jumped over the lazy dog", df::LEFT_JUSTIFIED, df::RED);
    DM.drawString(v4, ".", df::RIGHT_JUSTIFIED, df::WHITE);

    //show on screen
    DM.getWindow()->display();

    //sleep so results are visible
    Sleep(1000);
    
    DM.shutDown();

    return 1;
}






//TEST WORLD MANAGER
int testWorld()
{
    LM.writeLog("\nWORLD MANAGER TESTS\n____________________________________________");

    //create three test objects
    Saucer* s1 = new Saucer;
    Saucer* s2 = new Saucer;
    Saucer* s3 = new Saucer;

    //check that all three objects added themselves to the world
    if (WM.getAllObjects().getCount() != 3) {
        LM.writeLog("\nThere aren't 3 objects inserted into the world!");
        return 0;
    }

    //delete two of the objects
    WM.markForDelete(s1);
    WM.markForDelete(s3);
    WM.update();

    //verify that only one object is left in the world
    if (WM.getAllObjects().getCount() != 1)
    {
        LM.writeLog("\nnumber of objects in list not 1! Number: %d", WM.getAllObjects().getCount());
        return 0;
    }

    //delete the last object in the world
    WM.markForDelete(s2);
    WM.update();

    //verify that the world is empty
    if (!WM.getAllObjects().isEmpty())
    {
        LM.writeLog("\nObject list not empty after all objects removed!");
        return 0;
    }

    //create three more test objects of different types
    df::Object* o = new df::Object();
    Saucer* s4 = new Saucer;
    Saucer* s5 = new Saucer;

    //verify that objects of type returns a list with 2 saucer objects
    if (WM.objectsOfType("Saucer").getCount() != 2)
    {
        LM.writeLog("\nIncorrect count of sacuer objects! Number: %d", WM.objectsOfType("Saucer").getCount());
        return 0;
    }

    //delete all objects
    WM.markForDelete(o);
    WM.markForDelete(s4);
    WM.markForDelete(s5);
    WM.update();

    //verify world empty
    if (!WM.getAllObjects().isEmpty())
    {
        LM.writeLog("\nWorld Manager not empty after marking all obejcts for deletion!");
        return 0;
    }

    df::Box b1 = df::Box();

    WM.setBoundary(b1);

    LM.writeLog("\nBox set to corner (%d,%d), %d x %d", b1.getCorner().getX(), b1.getCorner().getY(), b1.getHorizontal(), b1.getVertical());


    //if reached here, all tests passed
    LM.writeLog("\nAll passed!");

    return 1;
}





//TEST EVENT HANDLER METHOD IN OBJECT
void testHandler()
{
    //format log file and create test object
    LM.writeLog("\nEVENT HANDLER TESTS\n_________________________________________");
    Saucer* s1 = new Saucer;

    //create base event and step event
    df::Event e = df::Event();
    df::EventStep step = df::EventStep();

    //pass in both events into object event handler, to verify that events are handled properly
    s1->eventHandler(&e);

    s1->eventHandler(&step);
    //delete test object from world
    delete s1;
}



//TEST STEP EVENT CLASS
void testStep()
{
    //write title in log and create test EventStep object
    LM.writeLog("\nSTEP EVENT TESTS\n_____________________________________________");

    df::EventStep step = df::EventStep();

    //ensure step set type to "step"
    LM.writeLog("\nDefault event type: %s", step.getType().c_str());
    
    //ensure step set count to 0, default
    LM.writeLog("\nDefault step count: %d", step.getStepCount());

    //set step count to 6 manually and verify
    step.setStepCount(6);

    LM.writeLog("\nSet step count, should print '6': %d", step.getStepCount());

    //construct new step event with count 10
    df::EventStep step2 = df::EventStep(10);

    //verify step count is set to 10
    LM.writeLog("\nSet step count using constructor, should print '10': %d", step2.getStepCount());


}




//TEST BASE EVENT CLASS
void testEvent()
{
    LM.writeLog("\nEVENT BASE CLASS TESTS\n __________________________________________");

    //create default base event to test with
    df::Event e = df::Event();

    //check that empty event reads "undefined" type
    LM.writeLog("\nEmpty event type: %s", e.getType().c_str());

    //use setter to set type
    e.setType("Explosion");

    //verify setter works
    LM.writeLog("\nShould print 'explosion:' %s", e.getType().c_str());
}





//TESTS FOR OBJECT LIST ITERATOR
int testIterate()
{
    //format logfile, create list, create iterator
    LM.writeLog("\nOBJECT LIST ITERATOR TESTS:\n_______________________________________________");
    df::ObjectList list = df::ObjectList();

    df::ObjectListIterator iter = df::ObjectListIterator(&list);

    //check iterator is done iterating over empty list
    if (!iter.isDone())
    {
        LM.writeLog("\nIterator not done iterating over empty list!");
        return 0;
    }
    
    //check iterator still done even after next()
    iter.next();
    if (!iter.isDone())
    {
        LM.writeLog("\nIterator not done iterating over empty list!");
        return 0;
    }

    //3 test objects
    df::Object o1 = df::Object(); //ID 9
    df::Object o2 = df::Object(); //ID 10
    df::Object o3 = df::Object(); //ID 11

    //insert objects into list
    list.insert(&o1);
    list.insert(&o2);
    list.insert(&o3);

    //reset iterator to start
    iter.first();

    //print out all 3 IDs to verify that iterator goes over all three objects
    LM.writeLog("\nPrinting out IDs of 3 objects:");
    for (int i = 0; !iter.isDone(); i++)
    {
        LM.writeLog("\n%d", iter.currentObejct()->getId());
        iter.next();
    }

    df::Object o4 = df::Object(); //ID 12
    df::Object o5 = df::Object(); //ID 13

    //reset iterator, insert new objects
    iter.first();

    list.insert(&o4);
    list.insert(&o5);

    //print out IDs as objects are being removed

    //should print 9- correct
    LM.writeLog("\nPrinting out IDs of 3 objects, with list changing:");
    LM.writeLog("\n%d", iter.currentObejct()->getId());
    list.remove(&o3);
    iter.next();

    //10 - correct
    LM.writeLog("\n%d", iter.currentObejct()->getId());
    list.remove(&o2);
    iter.next();

    //13- correct
    LM.writeLog("\n%d", iter.currentObejct()->getId());
    list.remove(&o3);
    iter.next();

    //13- correct
    LM.writeLog("\n%d", iter.currentObejct()->getId());
    list.remove(&o1);
    iter.next();

    //13- correct
    LM.writeLog("\n%d", iter.currentObejct()->getId());

    return 1;
}


//TESTS FOR OBJECT LIST
int testObjList()
{
    LM.writeLog("\nOBJECT LIST TESTS:\n__________________________________________");
    //construct object list
    df::ObjectList ol = df::ObjectList();

    //is the object list empty?
    if (!ol.isEmpty()) {
        LM.writeLog("\nOBJECT LIST TESTS: List not empty upon construction!");
        return 0;
    }

    //create default objects for use during tests
    df::Object o1 = df::Object();
    df::Object o2 = df::Object();
    df::Object o3 = df::Object();
    df::Object o4 = df::Object();

    //insert first three objects into list
    ol.insert(&o1);
    ol.insert(&o2);
    ol.insert(&o3);

    //verify list not empty
    if (ol.isEmpty())
    {
        LM.writeLog("\nObject list contains 3 objects and is registered as empty");
        return 0;
    }
    
    //verify list not full
    if (ol.isFull())
    {
        LM.writeLog("\nObject list contains 3 objects and is registered as full");
        return 0;
    }

    //remove three items previously added
    ol.remove(&o1);
    ol.remove(&o2);
    ol.remove(&o3);

    //verify empty
    if (!ol.isEmpty())
    {
        LM.writeLog("\n Object list not empty upon removing all items.");
        return 0;
    }

    //attempt to remove an object not in list, verify fcn returns -1 to reject
    if (ol.remove(&o4) != -1)
    {
        LM.writeLog("\n Object list remove() function not rejecting unadded object");
        return 0;
    }

    //insert 2000 items into the list
    for (int i = 0; i < 2000; i++)
    {
        ol.insert(&o1);
    }

    //verify list full
    if (!ol.isFull())
    {
        LM.writeLog("\n Object list contains 2000 items and not registered as full!");
        return 0;
    }

    //verify list rejects a 2001th item
    if (ol.insert(&o1) != -1)
    {
        LM.writeLog("\n Object List insert function allowing for more than 2000 items!");
        return 0;
    }

    //clear all items from list
    ol.clear();

    //verify list empty
    if (!ol.isEmpty())
    {
        LM.writeLog("\n Object list not empty upon clearing all items.");
        return 0;
    }
    LM.writeLog("\nAll tests passed!");
    return 1;
}







//TESTS FOR OBEJCT
int testObject()
{
    LM.writeLog("\nOBJECT BASE CLASS TESTS:\n_________________________________________");
    //create 3 objects
    df::Object o1 = df::Object();
    df::Object o2 = df::Object();
    df::Object o3 = df::Object();

    //check that IDs ascending ints
    if(o3.getId() - 1 != o2.getId() || o2.getId() - 1 != o1.getId())
    {
        LM.writeLog("\none or more object ID incorrect! values: %d, %d, %d\n", o1.getId(), o2.getId(), o3.getId());
        return 0;
    }

    //check types are empty
    if (o1.getType() != "" || o2.getType() != "")
    {
        LM.writeLog("\none or more object type incorrect! values: %s, %s\n", o1.getType(), o2.getType());
        return 0;
    }

    //check positions are default
    if (o1.getPosition().getX() != 0 || o1.getPosition().getY() != 0 || o2.getPosition().getX() != 0 || o2.getPosition().getY() != 0)
    {
        LM.writeLog("\none or more object position incorrect! values: %f, %f\n", o1.getPosition(), o2.getPosition());
        return 0;
    }

    //set a new ID, type, and position
    o1.setId(6);
    o1.setType("Bullet");
    o1.setPosition(df::Vector(1, 1));

    //verify that these attributes have been set
    if (o1.getId() != 6 || o1.getType() != "Bullet" || o1.getPosition().getX() != 1 || o1.getPosition().getY() != 1)
    {
        LM.writeLog("\none of more setter malfunctioning! values: %d, %s, %f, %f\n",
            o1.getId(), o1.getType().c_str(), o1.getPosition().getX(), o1.getPosition().getY());

        return 0;
    }
    LM.writeLog("\nAll tests passed!");
    //all tests passed at this point
    return 1;
}






//TESTS FOR VECTOR
int testVector()
{
    LM.writeLog("\nVECTOR TESTS:\n_____________________________________");
    //create two vectors for testing, one as default 0,0 x and y
    df::Vector v = df::Vector(2.0, 3.0);
    df::Vector v2 = df::Vector();

    //check that the constructors and getters work by checking x and y of both
    if (v.getX() != 2.0 || v.getY() != 3.0)
    {
        //if incorrect values, print to logfile with error message and the get() values for debugging
        LM.writeLog("\n1- Vectors incorrect! x:%f y%f\n", v.getX(), v.getY()); 
        return 0;
    }
    if (v2.getX() != 0 || v2.getY() != 0.0)
    {
        LM.writeLog("\n2- Vectors incorrect! x:%f y%f\n", v2.getX(), v2.getY());
        return 0;
    }

    //use the setter functions to change both test vectors
    v.setX(5);
    v.setY(10);
    v2.setXY(1, 1);

    //check that these worked successfully by getting and checking their values
    if (v.getX() != 5 || v.getY() != 10)
    {
        //print to log with error and values if wrong
        LM.writeLog("\n3- Vectors incorrect! x:%f y%f\n", v.getX(), v.getY());
        return 0;
    }
    if (v2.getX() != 1 || v2.getY() != 1)
    {
        LM.writeLog("\n4- Vectors incorrect! x:%f y%f\n", v2.getX(), v2.getY());
        return 0;
    }

    //check getMagnitude() method by printing output to logfile and checking against calculated values
    LM.writeLog("\ntest getMagnitude, %f = 11.18034, %f = 1.41421\n", v.getMagnitude(), v2.getMagnitude());

    //create new default vector for testing (0,0)
    df::Vector v3 = df::Vector();

    //notmalize default and non-zero vectors
    v3.normalize(); 
    v.normalize();

    //print the outputs and check in log file to verify 
    LM.writeLog("\nTest normalize: v3 %f = 0, %f = 0, v %f = 0.447214, %f = 0.894427\n",
        v3.getX(), v3.getY(), v.getX(), v.getY());

    //scale all three test vectors
    //v3 is (0,0), and v is nonzero. after this, both should be zero, and v2 will be the only nonzero vector
    v3.scale(5);
    v2.scale(5);
    v.scale(0);

    //print to log file to verify
    LM.writeLog("\nTest scale: print 4 zeros: %f %f %f %f, print two 5s: %f %f\n", 
        v3.getX(), v3.getY(), v.getX(), v.getY(), v2.getX(), v2.getY());

    //create two new vectors using + operator
    df::Vector v4 = v + v3; //results in (0,0) vector
    df::Vector v5 = v + v2; //nonzero

    //print to log file to verify values
    LM.writeLog("\nTest + operator: print 2 zeros: %f %f, print two 5s: %f %f",
        v4.getX(), v4.getY(), v5.getX(), v5.getY());

    //successful testing
    return 1;
}





//TESTS FOR GAME MANAGER
int testGM()
{
    //start up game manager, instantiate all other managers
    GM.startUp();

    //test that this worked by writing a log
    if (LM.writeLog("\nGAME MANAGER TESTS:\n__________________________________") == -1)
    {
        printf("Log manager unsuccessfully instantiated by GM\n");
        return 0;
    }

    //test objects with varying velocities + positions

    Saucer* s1 = new Saucer; //ID 0
    
    Saucer* s2 = new Saucer; //ID 1
    s2->setPosition(df::Vector(10, 0));
    s2->setVelocity(df::Vector(-0.5, 0.1));
    Saucer* s3 = new Saucer; //ID 2
    s3->setPosition(df::Vector(3, 3));
    s3->setVelocity(df::Vector(0.1, 0.75));
    

    //collides with s1, ID 3
    Saucer* s4 = new Saucer;
    s4->setPosition(df::Vector (15, 0));
    s4->setVelocity(df::Vector(-0.25, 0));

    //soft saucer, collides with s6 ID 4
    Saucer* s5 = new Saucer;
    s5->setPosition(df::Vector(0, 20));
    s5->setVelocity(df::Vector(0.25, 0));
    s5->setSolidness(df::SOFT);

    //soft saucer, collides with s5 ID 5
    Saucer* s6 = new Saucer;
    s6->setPosition(df::Vector(20, 20));
    s6->setVelocity(df::Vector(-0.25, 0));
    s5->setSolidness(df::SOFT);

    //load saucer sprite
    RM.loadSprite("sprites/saucer-spr.txt", "saucer");
    
    //set sprite for all saucers
    
    s1->setSprite("saucer");
    s2->setSprite("saucer");
    s3->setSprite("saucer");
    s4->setSprite("saucer");
    s5->setSprite("saucer");
    s6->setSprite("saucer");
    

    Hero* h1 = new Hero; //ID 6
    Hero* h2 = new Hero; //ID 7
    Hero* h3 = new Hero; //ID 8
    Hero* h4 = new Hero; //ID 9
    Hero* h5 = new Hero; //ID 10

    if (h1->setAltitude(-1) != -1)
    {
        LM.writeLog("\nsetting altitude to less than 0 allowed!");
        return 0;
    }

    if (h1->setAltitude(5) != -1)
    {
        LM.writeLog("\nsetting altitude to over 4 is allowed!");
        return 0;
    }
    h2->setPosition(df::Vector(4, 4));
    h3->setPosition(df::Vector(5, 5));
    h4->setPosition(df::Vector(6, 6));
    h5->setPosition(df::Vector(7, 7));
    
    //game manager typed correctly?
    if (GM.getType() != "Game Manager") {
        
        printf("fail2\n");
        return 0;
    }
    
    //FOR VIEW + OBJECT FOLLOWER TESTS- COMMENT OUT IF NOT WANTED
    //Set world boundaries to 80 horizontal, 50 vertcial
    
    df::Vector corner(0, 0);
    df::Box world_boundary(corner, 80, 90);
    WM.setBoundary(world_boundary);
    

    //Set view to 80 horizontal, 24 vertical
    df::Box view(df::Vector(), 80, 24);
    WM.setView(view);
    

    //camera should follow a magenta '+'
    new CameraObj; //ID 11
    
    
    //for testing purposes, game manager is designed to run game loop 900 times
    //this should take ~10 seconds, time to test
    printf("Running game loop; should take 10 seconds\n");
    GM.run();
    printf("game loop finished\n");

    WM.markForDelete(s1);
    WM.markForDelete(s2);
    WM.update();

    GM.shutDown();
    
    //log manager still running? shut down did not work
    if (LM.writeLog("this should not work\n\n") != -1) {

        printf("fail3");
        return 0;
    }

    //game over set to false? failure
    if (GM.getGameOver() == false) {
        printf("Shutdown not working properly!\n");
        return 0;
    }
   
    return 1;

}






//TESTS FOR CLOCK
void testClock(void){
    
    LM.writeLog("\nCLOCK TESTS:\n________________________________________");

    //instantiate new clock
    df::Clock* clk = new df::Clock;

    //sleeps for 50 ms and prints timed output to log file
    int sleep_time = 50;
    Sleep(sleep_time);

    LM.writeLog("\nSlept 50 ms.Clock delta() output: % ld \n", clk->delta());
    
    //sleeps for 30 ms, prints output from split()
    sleep_time = 30;
    Sleep(sleep_time);

    LM.writeLog("Slept 30 ms. Clock split() output: %ld \n", clk->split());

    //sleeps for another 30 ms, prints output from delta() (will be ~60 ms)
    Sleep(sleep_time);

    LM.writeLog("Slept another 30 ms. Clock delta() output: %ld \n", clk->delta());
    
}




//TESTS FOR LOG MANAGER
int testLog(void) { 

   //checks if manager type is set to "logManager"
   if (LM.getType() != "Log Manager")
   {
       printf("Manager not typed properly \n");
       return 0;
   }

   //Checks to see if startup method confirms that the log file was created
   if (!LM.startUp())
   {
       printf("Log file null\n");
       return 0;
   }

   //tests writeLog method with one parameter, checking right numerical output
   if (LM.writeLog("test log\n") != 9)
   {
       printf("fail1\n");
       return 0;
   }
   
   //test writeLog with two parameters
   if (LM.writeLog("abc %s", "testing again\n") != 18)
   {
       printf("fail2");
       return 0;
   }

   //testing writeLog with flush set to true
   LM.setFlush(true);

   //test writeLog with no input
   if (LM.writeLog("") != 0)
   {
       printf("fail3");
       return 0;
   }

   //test writeLog with integers, 3 inputs
   if (LM.writeLog("values:%d %d\n", 2, 3) != 11)
   {
       printf("fail4");
       return 0;
   }

   LM.setFlush(false);

   //test writeLog with inputs float, int, char, and string, five inputs total
   if (LM.writeLog("all the types! %d %f %c %s\n", 99, 99.99, "!", " :)") != 34)
   {
       printf("fail5");
       return 0;
   }

   //destroy log manager, closing the log file
   LM.~logManager();

   //all tests ran successfully
   return 1;

}
