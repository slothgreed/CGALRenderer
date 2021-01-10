#ifndef KI_FOUNDATION_PCH_H
#define KI_FOUNDATION_PCH_H

#ifndef DLL_EXPORT
#define DLL_EXPORT  __declspec(dllexport)
#endif

#pragma warning( disable : 4251 )
#define USE_VAR(x) (void)x;
#include<memory>
#include<string>
#include <iostream>
#include <vector>
#include<iostream>
#include<fstream>
#include <stack>
#include <assert.h>

#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;
using namespace glm;

#include "Random.h"
#include "MathHelper.h"

#include "PropertyBase.h"

#include "Timer.h"
#include "Interface.h"
#include "IController.h"
#include "ICommand.h"
#include "CommandManager.h"
#include "IEventArgs.h"
#include "IObserver.h"

#include "BDB.h"
#include "AnyTreeNode.h"

#include "SystemTypes.h"
#include "Logger.h"
#include "Mouse.h"
#include "MouseInput.h"
#include "WindowEvent.h"

#include "ColorUtility.h"

#include "FileUtility.h"
#include "FileWriter.h"

#define RELEASE_INSTANCE(x) if(x != NULL) { delete x; x = NULL;}
#define RELEASE_ARRAY_INSTANCE(x,size) for(int i = 0; i < size; i++){RELEASE_INSTANCE(x);} size = 0;
#ifdef NDEBUG
#define KI_ASSERT(x) if(x) {assert(0); retrun;}
#else
#define	KI_ASSERT(x) assert(x);
#endif

#endif //KI_FOUNDATION_PCH_H
