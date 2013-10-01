/*****************************************************************************************
 * Desc: Tutorial a) 03 Ind_Image
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

#include "IND_Surface.h"
#include "IND_Entity2d.h"
#include "IND_Image.h"
#include "../../WorkingPath.h"

/*
==================
Main
==================
*/
IndieLib_Main()		
{
    //Sets the working path at the resources directory. Resources paths are relative to that directory
	if (!WorkingPathSetup::setWorkingPath(WorkingPathSetup::resourcesDirectory())) {
		std::cout<<"\nUnable to Set the working path !";
	}
	
	// ----- IndieLib intialization -----

	CIndieLib *mI = CIndieLib::instance();
	if (!mI->init()) return 0;									

	// ----- Loading of the original image and making 4 duplicates -----

	IND_Image *mImageBugOriginal = IND_Image::newImage();
	if (!mI->_imageManager->add(mImageBugOriginal, "Enemy Bug.png")) return 0;

	IND_Image *mImageBugGaussian = IND_Image::newImage();
	if (!mI->_imageManager->clone(mImageBugGaussian, mImageBugOriginal)) return 0;

	IND_Image *mImageBugPixelize = IND_Image::newImage();
	if (!mI->_imageManager->clone(mImageBugPixelize, mImageBugOriginal)) return 0;

	IND_Image *mImageBugContrast = IND_Image::newImage();
	if (!mI->_imageManager->clone(mImageBugContrast, mImageBugOriginal)) return 0;

	// ----- Applying filters -----

	mImageBugGaussian->gaussianBlur(5);
	mImageBugPixelize->pixelize(5);
	mImageBugContrast->contrast(60);

	// ----- Surface creation -----

	// Loading Background
	IND_Surface *mSurfaceBack = IND_Surface::newSurface();
	if (!mI->_surfaceManager->add(mSurfaceBack, "blue_background.jpg", IND_OPAQUE, IND_32)) return 0;

	// Creating the "Original Bug" surface from the IND_Image
	IND_Surface *mOriginalSurface = IND_Surface::newSurface();
	if (!mI->_surfaceManager->add(mOriginalSurface, mImageBugOriginal, IND_ALPHA, IND_32)) return 0;

	// Creating the "Gaussian bug" surface from the IND_Image
	IND_Surface *mGaussianSurface = IND_Surface::newSurface();
	if (!mI->_surfaceManager->add(mGaussianSurface, mImageBugGaussian, IND_ALPHA, IND_32)) return 0;
	
	// Creating the "Pixelize bug" surface from the IND_Image
	IND_Surface *mPixelizeSurface = IND_Surface::newSurface();
	if (!mI->_surfaceManager->add(mPixelizeSurface, mImageBugPixelize, IND_ALPHA, IND_32)) return 0;

	// Creating the "Contrast bug" surface from the IND_Image
	IND_Surface *mContrastSurface = IND_Surface::newSurface();
	if (!mI->_surfaceManager->add(mContrastSurface, mImageBugContrast, IND_ALPHA, IND_32)) return 0;

	// ----- Deleting of images -----

	mI->_imageManager->remove(mImageBugOriginal);
	mI->_imageManager->remove(mImageBugGaussian);
	mI->_imageManager->remove(mImageBugPixelize);
	mI->_imageManager->remove(mImageBugContrast);

	// ----- Set the surfaces into the 2d entities -----

	// Creating 2d entity for the background
	IND_Entity2d *mBack = IND_Entity2d::newEntity2d();				
	mI->_entity2dManager->add(mBack);					// Entity adding
	mBack->setSurface(mSurfaceBack);					    // Set the surface into the entity

	// Creating 2d entity for the "Original bug"
	IND_Entity2d *mOriginal = IND_Entity2d::newEntity2d();					
	mI->_entity2dManager->add(mOriginal);					// Entity adding
	mOriginal->setSurface(mOriginalSurface);				// Set the surface into the entity

	// Creating 2d entity for the "Gaussian bug"
	IND_Entity2d *mGaussian = IND_Entity2d::newEntity2d();					
	mI->_entity2dManager->add(mGaussian);					// Entity adding
	mGaussian->setSurface(mGaussianSurface);				// Set the surface into the entity

	// Creating 2d entity for the "pixelize bug"
	IND_Entity2d *mPixelize = IND_Entity2d::newEntity2d();					
	mI->_entity2dManager->add(mPixelize);					// Entity adding
	mPixelize->setSurface(mPixelizeSurface);				// Set the surface into the entity

	// Creating 2d entity for the "Contrast bug"
	IND_Entity2d *mContrast = IND_Entity2d::newEntity2d();					
	mI->_entity2dManager->add(mContrast);					// Entity adding
	mContrast->setSurface(mContrastSurface);				// Set the surface into the entity

	// ----- Changing the attributes of the 2d entities -----

	mOriginal->setPosition(290,  90, 0);
	mGaussian->setPosition( 50, 230, 0);
	mPixelize->setPosition(290, 230, 0);
	mContrast->setPosition(520, 230, 0);

	// ----- Main Loop -----

	while (!mI->_input->onKeyPress(IND_ESCAPE) && !mI->_input->quit())
	{
		mI->_input->update();
		mI->_render->beginScene();
		mI->_entity2dManager->renderEntities2d();
		mI->_render->endScene();	
	}

	// ----- Free -----

	mI->end();

	return 0;
}
