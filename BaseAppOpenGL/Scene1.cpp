#include "Scene1.h"

CScene1::CScene1()
{
	pCamera = NULL;
	pTexto = NULL;
	pTextures = NULL;

	bIsWireframe = false;
	bIsCameraFPS = true;

	iFPS = 0;
	iFrames = 0;
	ulLastFPS = 0;
	szTitle[256] = 0;

	// Cria gerenciador de impressão de texto na tela
	pTexto = new CTexto();

	// Cria camera
	pCamera = new CCamera(0.0f, 1.0f, 20.0f);

	// Cria o Timer
	pTimer = new CTimer();
	pTimer->Init();

	fTimerPosY = 0.0f;
	fRenderPosY = 0.0f;

	fPosXZ = 0.0f;

	fDirecao = true;

	// Carrega todas as texturas
	//pTextures = new CTexture();	

	// Definição das configurações do material do objeto1 (REFLEXÂO)
	MatAmbient[0] = 1.0f; MatAmbient[1] = 1; MatAmbient[2] = 1.0f; MatAmbient[3] = 1.0f;
	MatDiffuse[0] = 1.0f; MatDiffuse[1] = 1.0f; MatDiffuse[2] = 1.0f; MatDiffuse[3] = 1.0f;
	MatSpecular[0] = 1.0f; MatSpecular[1] = 1.0f; MatSpecular[2] = 1.0f; MatSpecular[3] = 1.0f;
	MatShininess = 128.0f;

	// Definição das configurações da fonte de luz1 (EMISSOR)
	LightAmbient1[0] = 0.0f; LightAmbient1[1] = 0.0f; LightAmbient1[2] = 0.0f; LightAmbient1[3] = 1.0f;
	LightDiffuse1[0] = 0.0f; LightDiffuse1[1] = 0.0f; LightDiffuse1[2] = 1.0f; LightDiffuse1[3] = 1.0f;
	LightSpecular1[0] = 1.0f; LightSpecular1[1] = 1.0f; LightSpecular1[2] = 1.0f; LightSpecular1[3] = 1.0f;
	LightPosition1[0] = 0.0f; LightPosition1[1] = 4.0f; LightPosition1[2] = fPosXZ; LightPosition1[3] = 1.0f;
	LightSpotDir1[0] = 0.0f; LightSpotDir1[1] = 3.0f; LightSpotDir1[2] = 0.0f;

	// Definição das configurações da fonte de luz2 (EMISSOR)
	LightAmbient2[0] = 0.0f; LightAmbient2[1] = 0.0f; LightAmbient2[2] = 0.0f; LightAmbient2[3] = 1.0f;
	LightDiffuse2[0] = 1.0f; LightDiffuse2[1] = 0.0f; LightDiffuse2[2] = 0.0f; LightDiffuse2[3] = 1.0f;
	LightSpecular2[0] = 1.0f; LightSpecular2[1] = 1.0f; LightSpecular2[2] = 1.0f; LightSpecular2[3] = 1.0f;
	LightPosition2[0] = fPosXZ; LightPosition2[1] = 4.0f; LightPosition2[2] = 0.0f; LightPosition2[3] = 1.0f;
	LightSpotDir2[0] = 0.0f; LightSpotDir2[1] = 3.0f; LightSpotDir2[2] = 0.0f;

	// Definição das configurações da fonte de luz3 (EMISSOR)
	LightAmbient3[0] = 0.0f; LightAmbient3[1] = 0.0f; LightAmbient3[2] = 0.0f; LightAmbient3[3] = 1.0f;
	LightDiffuse3[0] = 0.0f; LightDiffuse3[1] = 1.0f; LightDiffuse3[2] = 0.0f; LightDiffuse3[3] = 1.0f;
	LightSpecular3[0] = 1.0f; LightSpecular3[1] = 1.0f; LightSpecular3[2] = 1.0f; LightSpecular3[3] = 1.0f;
	LightPosition3[0] = fPosXZ; LightPosition3[1] = 4.0f; LightPosition3[2] = fPosXZ; LightPosition3[3] = 1.0f;
	LightSpotDir3[0] = 0.0f; LightSpotDir3[1] = 3.0f; LightSpotDir3[2] = 0.0f;
}


CScene1::~CScene1(void)
{
	if (pTexto)
	{
		delete pTexto;
		pTexto = NULL;
	}

	if (pTextures)
	{
		delete pTextures;
		pTextures = NULL;
	}

	if (pCamera)
	{
		delete pCamera;
		pCamera = NULL;
	}

	if (pTimer)
	{
		delete pTimer;
		pTimer = NULL;
	}
}

int CScene1::DrawGLScene(void)	// Função que desenha a cena
{
	// Get FPS
	if (GetTickCount() - ulLastFPS >= 1000)	// When A Second Has Passed...
	{
		ulLastFPS = GetTickCount();				// Update Our Time Variable
		iFPS = iFrames;							// Save The FPS
		iFrames = 0;							// Reset The FPS Counter
	}
	iFrames++;									// FPS counter

	pTimer->Update();							// Atualiza o timer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpa a tela e o Depth Buffer
	glLoadIdentity();									// Inicializa a Modelview Matrix Atual

	// Seta as posições da câmera
	pCamera->setView();

	// Desenha grid 
	//Draw3DSGrid(200.0f, 200.0f);

	// Desenha os eixos do sistema cartesiano
	//DrawAxis();

	// Modo FILL ou WIREFRAME (pressione barra de espaço)	
	if (bIsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (INÍCIO)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Desenha lâmpada 1////
	LightPosition1[0] = 0.0f;
	LightPosition1[1] = 4.0f;
	LightPosition1[2] = fPosXZ;
	LightPosition1[3] = 1.0f;

	// Desenha lâmpada 2////
	LightPosition2[0] = fPosXZ;
	LightPosition2[1] = 4.0f;
	LightPosition2[2] = 0.0f;
	LightPosition2[3] = 1.0f;

	// Desenha lâmpada 3////
	LightPosition3[0] = fPosXZ;
	LightPosition3[1] = 4.0f;
	LightPosition3[2] = fPosXZ;
	LightPosition3[3] = 1.0f;

	glEnable(GL_LIGHTING);

	// Atribui os parâmetros de reflexão  do objeto
	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular);
	glMateriali(GL_FRONT, GL_SHININESS, MatShininess);

	// Atribui os parâmetros da luz 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular1);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition1);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, LightSpotDir1);
	glEnable(GL_LIGHT0);

	// Atribui os parâmetros da luz 1
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular2);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition2);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, LightSpotDir2);
	glEnable(GL_LIGHT1);

	// Atribui os parâmetros da luz 1
	glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient3);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, LightSpecular3);
	glLightfv(GL_LIGHT2, GL_POSITION, LightPosition3);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, LightSpotDir3);
	glEnable(GL_LIGHT2);

	Draw3DSGrid(50.0f, 50.0f);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHTING);

	if (fDirecao) {
		fPosXZ += 0.5f;

		if (fPosXZ >= 50.0f) {
			fDirecao = false;
		}
	}
	else {
		fPosXZ -= 0.5;

		if (fPosXZ <= -50.0f) {
			fDirecao = true;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (FIM)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fTimerPosY = pTimer->GetTime() / 1000.0f;
	fRenderPosY += 0.2f;

	// Impressão de texto na tela...
	// Muda para modo de projeção ortogonal 2D
	// OBS: Desabilite Texturas e Iluminação antes de entrar nesse modo de projeção
	OrthoMode(0, 0, WIDTH, HEIGHT);


	glPushMatrix();
	glTranslatef(0.0f, HEIGHT - 100, 0.0f);	// Move 1 unidade para dentro da tela (eixo Z)

	// Cor da fonte
	glColor3f(1.0f, 1.0f, 0.0f);


	glRasterPos2f(10.0f, 0.0f);	// Posicionando o texto na tela
	if (!bIsWireframe) {
		pTexto->glPrint("[TAB]  Modo LINE"); // Imprime texto na tela
	}
	else {
		pTexto->glPrint("[TAB]  Modo FILL");
	}


	//// Camera LookAt
	glRasterPos2f(10.0f, 40.0f);
	pTexto->glPrint("Player LookAt  : %f, %f, %f", pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);

	//// Posição do Player
	glRasterPos2f(10.0f, 60.0f);
	pTexto->glPrint("Player Position: %f, %f, %f", pCamera->Position[0], pCamera->Position[1], pCamera->Position[2]);

	//// Imprime o FPS da aplicação e o Timer
	glRasterPos2f(10.0f, 80.0f);
	pTexto->glPrint("Frames-per-Second: %d ---- Timer: %.1f segundos", iFPS, (pTimer->GetTime() / 1000));


	glPopMatrix();

	// Muda para modo de projeção perspectiva 3D
	PerspectiveMode();

	return true;
}




void CScene1::MouseMove(void) // Tratamento de movimento do mouse
{
	// Realiza os cálculos de rotação da visão do Player (através das coordenadas
	// X do mouse.
	POINT mousePos;
	int middleX = WIDTH >> 1;
	int middleY = HEIGHT >> 1;

	GetCursorPos(&mousePos);

	if ((mousePos.x == middleX) && (mousePos.y == middleY)) return;

	SetCursorPos(middleX, middleY);

	fDeltaX = (float)((middleX - mousePos.x)) / 10;
	fDeltaY = (float)((middleY - mousePos.y)) / 10;

	// Rotaciona apenas a câmera
	pCamera->rotateGlob(-fDeltaX, 0.0f, 1.0f, 0.0f);
	pCamera->rotateLoc(-fDeltaY, 1.0f, 0.0f, 0.0f);
}

void CScene1::KeyPressed(void) // Tratamento de teclas pressionadas
{

	// Verifica se a tecla 'W' foi pressionada e move o Player para frente
	if (GetKeyState('W') & 0x80)
	{
		pCamera->moveGlob(pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);
	}
	// Verifica se a tecla 'S' foi pressionada e move o Player para tras
	else if (GetKeyState('S') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Forward[0], -pCamera->Forward[1], -pCamera->Forward[2]);
	}
	// Verifica se a tecla 'A' foi pressionada e move o Player para esquerda
	else if (GetKeyState('A') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Right[0], -pCamera->Right[1], -pCamera->Right[2]);
	}
	// Verifica se a tecla 'D' foi pressionada e move o Player para direira
	else if (GetKeyState('D') & 0x80)
	{
		pCamera->moveGlob(pCamera->Right[0], pCamera->Right[1], pCamera->Right[2]);
	}
	else if (GetKeyState('Q') & 0x80)
	{
		pCamera->moveGlob(0.0f, -pCamera->Up[1], 0.0f);
	}
	else if (GetKeyState('E') & 0x80)
	{
		pCamera->moveGlob(0.0f, pCamera->Up[1], 0.0f);
	}
	// Senão, interrompe movimento do Player
	else
	{
	}
}

void CScene1::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
{
	switch (wParam)
	{
	case VK_TAB:
		bIsWireframe = !bIsWireframe;
		break;

	case VK_SPACE:
		pTimer->Init();
		break;

	case VK_RETURN:
		break;

	}
}

//	Cria um grid horizontal ao longo dos eixos X e Z
void CScene1::Draw3DSGrid(float width, float length)
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	for (float i = -width; i <= length; i += 1)
	{
		for (float j = -width; j <= length; j += 1)
		{
			// inicia o desenho das linhas
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, 0.0f, j + 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i + 1, 0.0f, j + 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i + 1, 0.0f, j);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i, 0.0f, j);
			glEnd();
		}
	}
	glPopMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void CScene1::DrawAxis()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	// Eixo X
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1000.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);

	// Eixo Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	glVertex3f(0.0f, -1000.0f, 0.0f);

	// Eixo Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glVertex3f(0.0f, 0.0f, -1000.0f);
	glEnd();
	glPopMatrix();
}


