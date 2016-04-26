#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("MyBoundingSphereClass example"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Initialize positions
	m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	m_v3O2 = vector3(2.5f, 0.0f, 0.0f);

	//Load Models
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");
	m_pMeshMngr->LoadModel("Minecraft\\Creeper.obj", "Creeper");
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	ArcBall();

	//Set the model matrices for both objects and Bounding Spheres
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O1) * ToMatrix4(m_qArcBall), "Steve");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O2), "Creeper");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");


	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
<<<<<<< HEAD
	bool bAreColliding = false;

	vector3 v3Center1G = vector3(m_m4Steve * vector4(m_v3Center1, 1.0f));
	vector3 v3Center2G = vector3(m_m4Creeper * vector4(m_v3Center2, 1.0f));

	float fDistanceCenters = glm::distance(v3Center1G, v3Center2G);

	bAreColliding = false;
	if (fDistanceCenters < (m_fRadius1 + m_fRadius2)) {
		bAreColliding = true;
	}

	//Collision check goes here
	m_pMeshMngr->Print("x:" + std::to_string(v3Center1G.x ) + " ", RERED);
	m_pMeshMngr->Print("y:" + std::to_string(v3Center1G.y) + " ", RERED);
	m_pMeshMngr->Print("z:" + std::to_string(v3Center1G.z) + " ", RERED);
	m_pMeshMngr->PrintLine("");

=======
>>>>>>> 8f580f7f9fede253430f22e409d3eac4ead431c5
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
<<<<<<< HEAD
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
	
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	/*m_m4Steve =
		m_pMeshMngr->GetModelMatrix("Steve") *
		glm::translate(m_v3Center1) *
		glm::scale(vector3(m_fRadius1 * 2.0f));
	//m_pSphere1->Render(m4Projection, m4View, m4Model);
	m_pMeshMngr->AddSphereToQueue(m_m4Steve, RERED, WIRE);

	m_m4Creeper =
		m_pMeshMngr->GetModelMatrix("Creeper") *
		glm::translate(m_v3Center2) *
		glm::scale(vector3(m_fRadius2 * 2.0f));
	//m_pSphere2->Render(m4Projection, m4View, m4Model);
	m_pMeshMngr->AddSphereToQueue(m_m4Creeper, RERED, WIRE);*/

	m_m4Steve =
		m_pMeshMngr->GetModelMatrix("Steve") *
		glm::translate(m_v3Center1);
		
	//m_pSphere1->Render(m4Projection, m4View, m4Model);
	m_pMeshMngr->AddSphereToQueue(m_m4Steve * glm::scale(vector3(m_fRadius1 * 2.0f)), RERED, WIRE);

	m_m4Creeper =
		m_pMeshMngr->GetModelMatrix("Creeper") *
		glm::translate(m_v3Center2);
		
	//m_pSphere2->Render(m4Projection, m4View, m4Model);
	m_pMeshMngr->AddSphereToQueue(m_m4Creeper * glm::scale(vector3(m_fRadius2 * 2.0f)), RERED, WIRE);

=======
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
>>>>>>> 8f580f7f9fede253430f22e409d3eac4ead431c5
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ResetRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}