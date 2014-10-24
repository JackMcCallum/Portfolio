#pragma once


// Ogres singleton templates cause a compatibility warning
// Info: http://msdn.microsoft.com/en-us/library/30kfwt8c.aspx
// Singleton templates are too powerful to ignore, hope this is ok.
#pragma warning(disable : 4356)

// Fixes some funky boost bug. It was giving:
// IntelliSense: #error directive: "Incompatible build options"
// This is a VS2010 bug according to http://royaltutorials.com/intellisense-error-directive-incompatible-build-options/
#define BOOST_ALL_NO_LIB 

// Ogre gives an annoying warning by default
// A blank project does this because of the way its built
// #pragma warning(disable : 4251)

// Most of the ogre stuff
#include <Ogre.h>
#include <OgreRectangle2D.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreFontManager.h>

using namespace Ogre;

