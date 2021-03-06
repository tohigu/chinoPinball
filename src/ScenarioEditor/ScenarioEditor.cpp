//
//  ScenarioEditor.cpp
//  ofxBulletEventsExample
//
//  Created by Ovidiu on 30/12/13.
//
//

#include "ScenarioEditor.h"

//--------------------------------------------------------------
void ScenarioEditor::setup(chinoWorld &world, Scenario &scenario){
    
    this->world = &world;
    this->scenario = &scenario;
    
	// enables mouse Pick events //
	this->world->enableGrabbing(-1);
	ofAddListener(world.MOUSE_PICK_EVENT, this, &ScenarioEditor::onMousePick);
    
    ofRegisterMouseEvents(this);
    
    selectedObject = NULL;
    
    /*GUI setup */
    //set some sketch parameters
    //Background Color
    red = 233;     blue = 240;    green = 52;    alpha = 200;
    radius = 150;    noiseScale = .1;
    drawFill = true;
    backgroundColor = ofColor(233, 52, 27);
    resolution = 30;
    position = ofPoint(ofGetWidth()*.5, ofGetHeight()*.5);
    ofSetCircleResolution(resolution);
    
    gui = new ofxUICanvas();
    gui->addLabel("CONTEXTUAL MENU");
    gui->addSpacer();
    gui->addFPSSlider("FPS");
    gui->addSpacer();
    gui->addSlider("RADIUS", 0.0, 255.0, &radius);
    gui->addSlider("RED", 0.0, 255.0, &red);
    gui->addSlider("GREEN", 0.0, 255.0, &green);
    gui->addSlider("BLUE", 0.0, 255.0, &blue);
    gui->addSlider("ALPHA", 0.0, 255.0, &alpha);
    gui->addSpacer();
    gui->add2DPad("CENTER", ofPoint(0,ofGetWidth()), ofPoint(0, ofGetHeight()), &position);
    gui->addLabelToggle("DRAWFILL", &drawFill);
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent,this,&ScenarioEditor::guiEvent);
    gui->loadSettings("GUI/guiSettings.xml");
    gui->setVisible(false);
}

//--------------------------------------------------------------
void ScenarioEditor::update(){
}

//--------------------------------------------------------------
void ScenarioEditor::draw(){
}

//--------------------------------------------------------------
void ScenarioEditor::keyReleased(int key){
    
    switch(key)
    {
		case 'e':
            bEscenarioEditorMode = !bEscenarioEditorMode;
			cout << "bScenarioEditorActive= " << bEscenarioEditorMode << endl;   
            break;
        case 'x':
            scenario->saveToXml();
            cout << "saving scenario to Xml" << endl;
            break;
            
        case '0':
            addObject(SimpleObject::ShapeTypeBall);
            break;
        case '3':
            addObject(SimpleObject::ShapeTypeLever);
            break;
        case '5':
            addObject(SimpleObject::ShapeTypeHammer);
            break;
        case '6':
            addObject(SimpleObject::ShapeTypeObstacle);
            break;
            
    }
    
}

//--------------------------------------------------------------
void ScenarioEditor::onMousePick( ofxBulletMousePickEvent &e ) {
    
    selectedObject = NULL;

    for(int i = 0; i < scenario->ScenarioObjects.size(); i++) {
		ofxBulletBaseShape *baseShape;
        baseShape = scenario->ScenarioObjects[i]->getBulletBaseShape();
      
		if( *baseShape == e ) {
            
            selectedObject = scenario->ScenarioObjects[i];
            
            //selectedObject
            ofLogVerbose("EditorVerbose") << "ScenarioEditor::onMousePick : selected a " << scenario->ScenarioObjects[i]->getObjectName() << endl;
            
			//mousePickPos = e.pickPosWorld;
			//Save current location and current mouse
			//objPressedLoc = ofVec2f(selectedObject->position.x, selectedObject->position.y);
			mousePickLoc = ofVec2f(ofGetMouseX(), ofGetMouseY());
			
			break; //Stop looking for objects
		}
	}
	
}

//--------------------------------------------------------
void ScenarioEditor::mouseDragged(ofMouseEventArgs &args){
    
    
    if (bEscenarioEditorMode && (selectedObject != NULL))
    {
        ofVec3f newPos = selectedObject->position;
        newPos.x = newPos.x + (args.x - mouseOldPosition.x)/50;
        newPos.y = newPos.y + (args.y - mouseOldPosition.y)/50;
        selectedObject -> position = newPos;
        selectedObject -> setPosition(newPos);
        mouseOldPosition = args;
    }

    /*
	if(bEscenarioEditorMode){
		ofVec2f mousePos = ofVec2f(args.x, args.y);
		ofVec2f mouseDir = mousePickLoc - mousePos;
		mouseDir.normalize();
		
		ofVec3f newPos;
		if (selectedObject != NULL){
			
			newPos = selectedObject->position;
			//newPos.x = newPos.x + (args.x/1000);
			//newPos.y = newPos.y + (args.y/1000);
			newPos += 0.1* mouseDir;
			
			ofLogVerbose("EditorVerbose") << "mouseDragged, newpos = " << newPos << " mouseDir =" << mouseDir << endl;
			
			selectedObject -> position = newPos;
			selectedObject -> setPosition(newPos);
		}
	}
     */
}

//--------------------------------------------------------
void ScenarioEditor::mouseMoved(ofMouseEventArgs &args){
    
}

//--------------------------------------------------------
void ScenarioEditor::mousePressed(ofMouseEventArgs &args){
	
	if(bEscenarioEditorMode){
		///deactivate camera mouse events //can be added more params to do this action in eventMoveObjectScenario
		eventMoveObjectScenario newMoveObjectEvent;
        newMoveObjectEvent.bMovingObject = true;
        ofNotifyEvent(eventMoveObjectScenario::onMoveObject, newMoveObjectEvent);
	}
    
    if(args.button == 2)
    {
        gui->setPosition(args.x, args.y);
        gui->setVisible(true);
        return;
    }
    
    if(!gui->isHit(args.x, args.y))
    {
        gui->setVisible(false);
    }
    
    mouseOldPosition = args;
}

//--------------------------------------------------------
void ScenarioEditor::guiEvent(ofxUIEventArgs &e)
{
    //	string name = e.widget->getName();
    //	int kind = e.widget->getKind();
}


//--------------------------------------------------------
void ScenarioEditor::mouseReleased(ofMouseEventArgs &args){
    
	if(bEscenarioEditorMode){
		///deactivate camera mouse events //can be added more params to do this action in eventMoveObjectScenario
		eventMoveObjectScenario newMoveObjectEvent;
        newMoveObjectEvent.bMovingObject = false;
        ofNotifyEvent(eventMoveObjectScenario::onMoveObject, newMoveObjectEvent);
	}
	
}

//--------------------------------------------------------------
void ScenarioEditor::addObject(SimpleObject::shapeType type) {
	
    //Set new objects if Editor mode is active and Selected Obstacle
    if(bEscenarioEditorMode){
        
        //Create class to save type of objec and Notifie the Event to escenario
        eventObjectScenario newObjectEvent;
        newObjectEvent.posObject = ofVec3f(world->getWorldPos());
        newObjectEvent.type = type;
        ofNotifyEvent(eventObjectScenario::onNewObject, newObjectEvent);
    };
    
}