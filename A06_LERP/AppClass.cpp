#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	fDuration = 1.0f;

}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here

	for (uint i = 0; i < numPoints; i++) {
		//Render spheres on the screen to represent points
		m_pMeshMngr->AddSphereToQueue(glm::scale(glm::translate(points[i]), vector3(.1f)), RERED, 1);
	}

	//Map proportion of runTime to total Duration into a percentage
	float fPercent = MapValue(static_cast<float>(fRunTime), 0.0f, static_cast<float>(fDuration), 0.0f, 1.0f);

	//If it's not the last point, lerp between the current point and the next point
	//Otherwise, lerp between the current point and the first point
	vector3 newPosition;
	if(currentPoint+1 < numPoints) newPosition = glm::lerp(points[currentPoint], points[currentPoint+1], fPercent);
	else newPosition = glm::lerp(points[currentPoint], points[0], fPercent);

	//update model matrix
	m_pMeshMngr->SetModelMatrix(glm::translate(newPosition), "WallEye");

	//If the model has moved past the current point, start over
	if (fRunTime > fDuration) {
		currentPoint++;
		fRunTime = 0;
	}
	
	//If done with the loop, restart
	if (currentPoint >= numPoints) currentPoint = 0;



#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	//Print Current Point
	m_pMeshMngr->Print("Current Point:");
	m_pMeshMngr->PrintLine(std::to_string(currentPoint), REWHITE);

	//Print fTimeSpan
	m_pMeshMngr->Print("fTimeSpan:");
	m_pMeshMngr->PrintLine(std::to_string(fTimeSpan), REWHITE);

	//Print fRunSpan
	m_pMeshMngr->Print("fRunTime:");
	m_pMeshMngr->PrintLine(std::to_string(fRunTime), REWHITE);

	//Print fDuration
	m_pMeshMngr->Print("fDuration:");
	m_pMeshMngr->PrintLine(std::to_string(fDuration), REWHITE);

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print FPS
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}