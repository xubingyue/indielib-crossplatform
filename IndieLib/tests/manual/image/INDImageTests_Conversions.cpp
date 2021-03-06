/*****************************************************************************************
 * Desc: INDImageTests_Conversions class
 *****************************************************************************************/

/*********************************** The zlib License ************************************
 *
 * Copyright (c) 2013 Indielib-crossplatform Development Team
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 *
 *****************************************************************************************/


#include "CIndieLib.h"
#include "INDImageTests_Conversions.h"
#include "IND_Surface.h"
#include "IND_Entity2d.h"
#include "IND_Image.h"

void INDImageTests_Conversions::prepareTests() {
	CIndieLib *iLib = CIndieLib::instance();
	// ----- Images loading -----
	iLib->_imageManager->add(_images[0],  const_cast<char *>("gem_squared_noalpha.jpg"));
	iLib->_imageManager->add(_images[1],  const_cast<char *>("gem_squared_noalpha.jpg"));
	iLib->_imageManager->add(_images[2],  const_cast<char *>("gem_squared.png"));
	iLib->_imageManager->add(_images[3],  const_cast<char *>("gem_squared.png"));
	iLib->_imageManager->add(_images[4],  const_cast<char *>("star.png"));
	iLib->_imageManager->add(_images[5],  const_cast<char *>("star.png"));
	iLib->_imageManager->add(_images[6],  const_cast<char *>("rabbit.png"));
	iLib->_imageManager->add(_images[7],  const_cast<char *>("rabbit.png"));
	iLib->_imageManager->add(_images[8],  const_cast<char *>("rabbit.png"));
	iLib->_imageManager->add(_images[9],  const_cast<char *>("rabbit.png"));
	iLib->_imageManager->add(_images[10], const_cast<char *>("rabbit.png"));
	iLib->_imageManager->add(_images[11], const_cast<char *>("rabbit.png"));
	iLib->_imageManager->add(_images[12], const_cast<char *>("rabbit.png"));
	iLib->_imageManager->add(_images[13],"rabbit.png");
	iLib->_imageManager->add(_images[14],150,150,IND_RGBA);
	iLib->_imageManager->add(_images[15],150,150,IND_RGBA);

	// ----- Surfaces loading -----
	//No conversion
	iLib->_surfaceManager->add(_surfaces[0], _images[0], IND_OPAQUE, IND_32);
	//Convert image - Add alpha channel to opaque image
	_images[1]->setAlpha(255,0,0);
	iLib->_surfaceManager->add(_surfaces[1], _images[1], IND_ALPHA, IND_32);

	//No conversion
	iLib->_surfaceManager->add(_surfaces[2], _images[2], IND_ALPHA, IND_32);
	//Convert image - Clear to half opaque and greenish color
	_images[3]->clear(0,255,0,25);
	iLib->_surfaceManager->add(_surfaces[3], _images[3], IND_ALPHA, IND_32);

	//No conversion
	iLib->_surfaceManager->add(_surfaces[4], _images[4], IND_ALPHA, IND_32);
	//Convert image - Invert alpha channel
	_images[5]->invertAlpha();
	iLib->_surfaceManager->add(_surfaces[5], _images[5], IND_ALPHA, IND_32);

	//No conversion
	iLib->_surfaceManager->add(_surfaces[6], _images[6], IND_ALPHA, IND_32);
	//Convert image - Rotate 90 degrees
	_images[7]->rotate(90);
	iLib->_surfaceManager->add(_surfaces[7], _images[7], IND_ALPHA, IND_32);
	//Convert image - Rotate 45 degrees
	_images[8]->rotate(45);
	iLib->_surfaceManager->add(_surfaces[8], _images[8], IND_ALPHA, IND_32);
	//Convert image - Rotate 180 degrees
	_images[9]->rotate(180);
	iLib->_surfaceManager->add(_surfaces[9], _images[9], IND_ALPHA, IND_32);

	//No conversion
	iLib->_surfaceManager->add(_surfaces[10], _images[10], IND_ALPHA, IND_32);
	//Convert image - Scale (bigger)
	_images[11]->scale(150, 150);
	iLib->_surfaceManager->add(_surfaces[11], _images[11], IND_ALPHA, IND_32);
	//Convert image - Scale (smaller)
	_images[12]->scale(50, 50);
	iLib->_surfaceManager->add(_surfaces[12], _images[12], IND_ALPHA, IND_32);

	//No conversion
	iLib->_surfaceManager->add(_surfaces[13], _images[13], IND_ALPHA, IND_32);
	//Show a procedurally-generated image (red)
	_images[14]->clear(255,0,0,255);
	iLib->_surfaceManager->add(_surfaces[14], _images[14], IND_ALPHA, IND_32);
	//Paste an image into the target
	_images[15]->clear(0,255,0,255);
	_images[15]->pasteImage(_images[13],20,20,100);
	iLib->_surfaceManager->add(_surfaces[15], _images[15], IND_ALPHA, IND_32);
}


void INDImageTests_Conversions::performTests(float dt) {
   
    //IF - Check if test is active
    if(!_active)
        return;

	CIndieLib *iLib = CIndieLib::instance();
	
	//Toggling of entity border lines in entities
	if(iLib->_input->onKeyPress(IND_G) && _active) {
		for (int i = 0; i < _testedEntities; ++i) {
			_entities[i]->showGridAreas(!_entities[i]->isShowGridAreas());
		}
	}

}

bool INDImageTests_Conversions::isActive(){
    return (ManualTests::isActive());
}
    
void INDImageTests_Conversions::setActive(bool active){
    ManualTests::setActive(active);

    CIndieLib *iLib = CIndieLib::instance();
    //IF - Active
    if(active){
	    // ----- Set the surfaces into 2d entities -----
		for (int i = 0; i < _testedEntities; ++i) {
			_entities[i]->setSurface(_surfaces[i]);
			iLib->_entity2dManager->add(_entities[i]);
		}
	    // ----- Changing the attributes of the 2d entities -----
		_entities[0]->setPosition(0.0f,0.0f,0);
		_entities[1]->setPosition(static_cast<float>(_entities[0]->getSurface()->getWidth()),static_cast<float>(_entities[0]->getPosY()),0);

		_entities[13]->setPosition(static_cast<float>(_entities[1]->getPosX() + _entities[1]->getSurface()->getWidth()),static_cast<float>(_entities[1]->getPosY()) , 0);
		_entities[14]->setPosition(static_cast<float>(_entities[13]->getPosX() + _entities[13]->getSurface()->getWidth()),static_cast<float>(_entities[13]->getPosY()) , 0);
		_entities[15]->setPosition(static_cast<float>(_entities[14]->getPosX() + _entities[14]->getSurface()->getWidth()),static_cast<float>(_entities[14]->getPosY()) , 0);

		_entities[2]->setPosition(0.0f,static_cast<float>(_entities[0]->getPosY() + _entities[0]->getSurface()->getHeight()),0);
		_entities[3]->setPosition(static_cast<float>(_entities[2]->getPosX() + _entities[2]->getSurface()->getWidth()) ,static_cast<float>(_entities[2]->getPosY()),0);

		_entities[4]->setPosition(0.0f,static_cast<float>(_entities[2]->getPosY() + _entities[2]->getSurface()->getHeight()) , 0);
		_entities[5]->setPosition(static_cast<float>(_entities[4]->getPosX() + _entities[4]->getSurface()->getWidth()),static_cast<float>(_entities[4]->getPosY()) , 0);

		_entities[6]->setPosition(0.0f,static_cast<float>(_entities[4]->getPosY() + _entities[4]->getSurface()->getHeight()) , 0);
		_entities[7]->setPosition(static_cast<float>(_entities[6]->getPosX() + _entities[6]->getSurface()->getWidth()),static_cast<float>(_entities[6]->getPosY()) , 0);
		_entities[8]->setPosition(static_cast<float>(_entities[7]->getPosX() + _entities[7]->getSurface()->getWidth()),static_cast<float>(_entities[7]->getPosY()) , 0);
		_entities[9]->setPosition(static_cast<float>(_entities[8]->getPosX() + _entities[8]->getSurface()->getWidth()),static_cast<float>(_entities[8]->getPosY()) , 0);

		_entities[10]->setPosition(0.0f,static_cast<float>(_entities[6]->getPosY() + _entities[6]->getSurface()->getHeight()*1.5) , 0);
		_entities[11]->setPosition(static_cast<float>(_entities[10]->getPosX() + _entities[10]->getSurface()->getWidth()),static_cast<float>(_entities[10]->getPosY()) , 0);
		_entities[12]->setPosition(static_cast<float>(_entities[11]->getPosX() + _entities[11]->getSurface()->getWidth()),static_cast<float>(_entities[11]->getPosY()) , 0);
    } else { //Inactive
		//Release all variables from indieLib before exiting
		for (int i = 0; i < _testedEntities; ++i) {
			iLib->_entity2dManager->remove(_entities[i]);
		}
	}
}

//-----------------------------------PRIVATE METHODS----------------------------

void INDImageTests_Conversions::init() {

	_testedEntities = 16;

	_images = new IND_Image*[_testedEntities];
	_surfaces = new IND_Surface*[_testedEntities];
	_entities = new IND_Entity2d*[_testedEntities];

	//Create underlying entities
	for (int i = 0; i < _testedEntities; ++i) {
		_images[i] = IND_Image::newImage();
		_surfaces[i] = IND_Surface::newSurface();
		_entities[i] = IND_Entity2d::newEntity2d();
	}
}	

void INDImageTests_Conversions::release() {
    CIndieLib* iLib = CIndieLib::instance();
    //Release all variables from indieLib before exiting
	for (int i = 0; i < _testedEntities; ++i) {
		iLib->_imageManager->remove(_images[i]);
		iLib->_surfaceManager->remove(_surfaces[i]);
		iLib->_entity2dManager->remove(_entities[i]);
	}

	DISPOSEARRAY(_images);
	DISPOSEARRAY(_surfaces);
	DISPOSEARRAY(_entities);
}
